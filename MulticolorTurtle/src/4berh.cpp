
#include "4berh.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_VERTS   40000
#define MAX_UVS     40000
#define MAX_FACES   75000
#define NUM_BONES   4

typedef enum {
    SIDE_HORSE  = 0,   /* Морь  */
    SIDE_CAMEL  = 1,   /* Тэмээ */
    SIDE_SHEEP  = 2,   /* Хонь  */
    SIDE_GOAT   = 3,   /* Ямаа  */
    SIDE_ONH    = 4    /* Онх – босоо зогсоно */
} Side;

#define NUM_SIDES 5

static const char* SIDE_NAME[] = { "Morj", "Temee", "Khoni", "Yamaa", "ONKH!" };
static const char* SIDE_MN[]   = { "МОРЬ", "ТЭМЭЭ", "ХОНЬ",  "ЯМАА",  "ОНХ!" };

typedef struct { float x, y, z; } Vec3;
typedef struct { float u, v;    } Vec2;
typedef struct { int vi, ti;    } FaceVert;
typedef struct { FaceVert v[3]; } Face;

typedef struct {
    Vec3  pos[MAX_VERTS];
    Vec2  uv [MAX_UVS];
    Face  face[MAX_FACES];
    int   nv, nuv, nf;
    Vec3  center;
} Mesh;

typedef struct {
    float px, py, pz;
    float rx, ry, rz;
    float scale;
    Side  side;
    float anim_t;
    float spin_speed;
    float target_rx, target_ry, target_rz;
    float r, g, b;
} Bone;

typedef struct {
    Mesh  mesh;
    Bone  bones[NUM_BONES];
    char  result_msg[256];
    float bg_t;
    float bg_r, bg_g, bg_b;
    int   animating;
    int   anim_frame;
    int   total_frames;
} Game;

static Game G;


static void mesh_load(Mesh* m, const char* path)
{
    FILE* f = fopen(path, "r");
    if (!f) {
        fprintf(stderr, "[ERROR] Cannot open %s\n", path);
        exit(1);
    }

    m->nv = m->nuv = m->nf = 0;

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        int len = (int)strlen(line);
        while (len > 0 && (line[len-1]=='\r'||line[len-1]=='\n'))
            line[--len] = '\0';

        if (line[0]=='v' && line[1]==' ') {
            Vec3 p;
            sscanf(line+2, "%f %f %f", &p.x, &p.y, &p.z);
            m->pos[m->nv++] = p;

        } else if (line[0]=='v' && line[1]=='t' && line[2]==' ') {
            Vec2 uv;
            sscanf(line+3, "%f %f", &uv.u, &uv.v);
            m->uv[m->nuv++] = uv;

        } else if (line[0]=='f' && line[1]==' ') {
            Face face;
            unsigned int vi[3], ti[3];
            int ok = sscanf(line+2,
                "%u/%u %u/%u %u/%u",
                &vi[0],&ti[0], &vi[1],&ti[1], &vi[2],&ti[2]);
            if (ok != 6) continue;
            for (int k=0; k<3; k++) {
                face.v[k].vi = (int)vi[k]-1;
                face.v[k].ti = (int)ti[k]-1;
            }
            m->face[m->nf++] = face;
        }
    }
    fclose(f);

    float xmin=m->pos[0].x, xmax=xmin;
    float ymin=m->pos[0].y, ymax=ymin;
    float zmin=m->pos[0].z, zmax=zmin;
    for (int i=1; i<m->nv; i++) {
        if (m->pos[i].x<xmin) xmin=m->pos[i].x;
        if (m->pos[i].x>xmax) xmax=m->pos[i].x;
        if (m->pos[i].y<ymin) ymin=m->pos[i].y;
        if (m->pos[i].y>ymax) ymax=m->pos[i].y;
        if (m->pos[i].z<zmin) zmin=m->pos[i].z;
        if (m->pos[i].z>zmax) zmax=m->pos[i].z;
    }
    m->center.x = (xmin+xmax)*0.5f;
    m->center.y = (ymin+ymax)*0.5f;
    m->center.z = (zmin+zmax)*0.5f;

    for (int i=0; i<m->nv; i++) {
        m->pos[i].x -= m->center.x;
        m->pos[i].y -= m->center.y;
        m->pos[i].z -= m->center.z;
    }

    printf("[Mesh] Loaded %d verts, %d faces from %s\n", m->nv, m->nf, path);
    printf("[Mesh] Centre offset: (%.3f, %.3f, %.3f)\n",
           m->center.x, m->center.y, m->center.z);
}


static void mesh_draw(const Mesh* m)
{
    glBegin(GL_TRIANGLES);
    for (int i=0; i<m->nf; i++) {
        const Face* f = &m->face[i];

        Vec3 a = m->pos[f->v[0].vi];
        Vec3 b = m->pos[f->v[1].vi];
        Vec3 c = m->pos[f->v[2].vi];

        float ex = b.x-a.x, ey = b.y-a.y, ez = b.z-a.z;
        float fx = c.x-a.x, fy = c.y-a.y, fz = c.z-a.z;
        float nx = ey*fz - ez*fy;
        float ny = ez*fx - ex*fz;
        float nz = ex*fy - ey*fx;
        float len = sqrtf(nx*nx+ny*ny+nz*nz);
        if (len > 1e-7f) { nx/=len; ny/=len; nz/=len; }

        glNormal3f(nx, ny, nz);

        for (int k=0; k<3; k++) {
            Vec3 p = m->pos[f->v[k].vi];
            glVertex3f(p.x, p.y, p.z);
        }
    }
    glEnd();
}


static void side_color(Side s, float* r, float* g, float* b)
{
    switch(s) {
        case SIDE_HORSE: *r=0.85f; *g=0.55f; *b=0.10f; break;
        case SIDE_CAMEL: *r=0.75f; *g=0.45f; *b=0.20f; break;
        case SIDE_SHEEP: *r=0.90f; *g=0.90f; *b=0.90f; break;
        case SIDE_GOAT:  *r=0.30f; *g=0.70f; *b=0.30f; break;
        case SIDE_ONH:   *r=1.00f; *g=0.20f; *b=0.20f; break;
    }
}


static void bone_set_side_rotation(Bone* b, Side s)
{
    b->target_ry = (float)(rand() % 360);

    if (s == SIDE_ONH) {
        b->target_rx = 0.f;
        b->target_rz = 0.f;
    } else {
        b->target_rx = 90.f;
        /* rx=90 дараа дээш харах талыг тааруулах эргэлт:
           Морь +X, Тэмээ -X, Хонь +Z, Ямаа -Z */
        static const float SIDE_RZ[4] = { 270.f, 90.f, 0.f, 180.f };
        b->target_rz = SIDE_RZ[s];
    }
}

static void bone_init(Bone* b, int idx)
{
    float gx = (idx % 2 == 0) ? -2.5f :  2.5f;
    float gz = (idx < 2)      ? -2.5f :  2.5f;
    b->px    = gx;
    b->py    = 0.f;
    b->pz    = gz;
    b->rx = 90.f;
    b->ry = 0.f;
    b->rz = 0.f;
    b->scale = 0.045f;
    b->side  = (Side)(idx % 4);
    b->anim_t = 1.f;
    b->spin_speed = 0.f;
    b->r = b->g = b->b = 0.8f;
}

static void bone_toss(Bone* b)
{
    /* ОНХ 4% магадлал – бодит амьдралтай ойролцоо */
    int roll = rand() % 100;
    if (roll < 4)
        b->side = SIDE_ONH;
    else
        b->side = (Side)(rand() % 4);

    bone_set_side_rotation(b, b->side);
    b->anim_t    = 0.f;
    b->spin_speed = 8.f + (float)(rand()%12);
    side_color(b->side, &b->r, &b->g, &b->b);
}

static void bone_draw(const Bone* b, const Mesh* m)
{
    float t   = b->anim_t;
    float inv = 1.f - t;
    float rx  = inv * (b->rx + b->spin_speed * 720.f) + t * b->target_rx;
    float ry  = inv * b->ry + t * b->target_ry;
    float rz  = inv * b->rz + t * b->target_rz;

    float dy = (b->anim_t < 1.f)
               ? sinf(b->anim_t * 3.14159f) * 2.5f
               : 0.f;

    glPushMatrix();
      glTranslatef(b->px, b->py + dy, b->pz);
      glRotatef(rx, 1,0,0);
      glRotatef(ry, 0,1,0);
      glRotatef(rz, 0,0,1);
      glScalef(b->scale, b->scale, b->scale);

      GLfloat amb[4]  = {b->r*0.3f, b->g*0.3f, b->b*0.3f, 1.f};
      GLfloat diff[4] = {b->r,      b->g,      b->b,      1.f};
      GLfloat spec[4] = {0.8f, 0.8f, 0.8f, 1.f};
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   amb);
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   diff);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  spec);
      glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 48.f);

      mesh_draw(m);
    glPopMatrix();
}

static void bg_update(float dt)
{
    G.bg_t += dt * 0.15f;
    float t = G.bg_t;
    float s = sinf(t);
    float c = cosf(t);
    float s2= sinf(t*1.3f);

    G.bg_r = 0.08f + 0.12f*(s*0.5f+0.5f) + 0.10f*(s2*0.5f+0.5f);
    G.bg_g = 0.05f + 0.10f*(c*0.5f+0.5f);
    G.bg_b = 0.15f + 0.20f*(sinf(t+1.5f)*0.5f+0.5f);
}

static void game_init(void)
{
    srand((unsigned)time(NULL));
    mesh_load(&G.mesh, "shagai.obj");
    for (int i=0; i<NUM_BONES; i++) bone_init(&G.bones[i], i);
    G.animating    = 0;
    G.anim_frame   = 0;
    G.total_frames = 60;
    G.bg_t = 0.f;
    G.bg_r = 0.08f; G.bg_g = 0.05f; G.bg_b = 0.18f;
    strcpy(G.result_msg, "SPACE daraad shagaigaa orkh!");
}

static void game_toss(void)
{
    if (G.animating) return;
    for (int i=0; i<NUM_BONES; i++) bone_toss(&G.bones[i]);
    G.animating  = 1;
    G.anim_frame = 0;
}

static void game_finish_toss(void)
{
    for (int i=0; i<NUM_BONES; i++) {
        Bone* b = &G.bones[i];
        b->rx     = b->target_rx;
        b->ry     = b->target_ry;
        b->rz     = b->target_rz;
        b->anim_t = 1.f;
    }

    char buf[128] = "";
    int seen[5] = {0,0,0,0,0};
    int has_onkh = 0;

    for (int i=0; i<NUM_BONES; i++) {
        int s = (int)G.bones[i].side;
        seen[s]++;
        if (s == SIDE_ONH) has_onkh = 1;
        if (i > 0) strcat(buf, " | ");
        strcat(buf, SIDE_NAME[s]);
    }

    /* дөрвөн бэрх: 4 өөр тал, ОНХ байхгүй */
    int all_diff = (!has_onkh &&
                    seen[0]==1 && seen[1]==1 &&
                    seen[2]==1 && seen[3]==1);

    if (has_onkh)
        snprintf(G.result_msg, sizeof(G.result_msg),
                 "*** ONKH! Ukher buulaa! ***  %s", buf);
    else if (all_diff)
        snprintf(G.result_msg, sizeof(G.result_msg),
                 "** DORVEN BERKH! **  %s", buf);
    else
        snprintf(G.result_msg, sizeof(G.result_msg), "%s", buf);
}

static void game_reset(void)
{
    G.animating = 0;
    for (int i=0; i<NUM_BONES; i++) bone_init(&G.bones[i], i);
    strcpy(G.result_msg, "SPACE daraad shagaigaa orkh!");
}

static void draw_string(float x, float y, void* font, const char* s)
{
    glRasterPos2f(x, y);
    while (*s) glutBitmapCharacter(font, (unsigned char)*s++);
}

static void draw_hud(void)
{
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glColor3f(1.f, 0.95f, 0.4f);
    draw_string(w/2 - 110, h-36, GLUT_BITMAP_HELVETICA_18,
                "DORVEN BERKH  -  4 Berh Shagai");

    glColor3f(1.f, 1.f, 0.5f);
    draw_string(w/2 - 180, 24, GLUT_BITMAP_HELVETICA_18, G.result_msg);

    for (int i=0; i<NUM_BONES; i++) {
        const Bone* b = &G.bones[i];
        if (b->anim_t < 1.f) continue;

        GLdouble mv[16], proj[16];
        GLint vp[4];
        glGetDoublev(GL_MODELVIEW_MATRIX,  mv);
        glGetDoublev(GL_PROJECTION_MATRIX, proj);
        glGetIntegerv(GL_VIEWPORT, vp);

        double sx, sy, sz;
        gluProject(b->px, b->py - 0.8, b->pz, mv, proj, vp, &sx, &sy, &sz);

        glColor3f(b->r, b->g, b->b);
        draw_string((float)sx - 20, (float)sy - 20,
                    GLUT_BITMAP_HELVETICA_12, SIDE_MN[b->side]);
    }

    glColor3f(0.6f, 0.6f, 0.6f);
    draw_string(8, 8, GLUT_BITMAP_HELVETICA_12,
                "SPACE=Toss  R=Reset  ESC=Back");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

static void cb_display(void)
{
    glClearColor(G.bg_r, G.bg_g, G.bg_b, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    /* дээрээс харах, Z-offset gimbal lock-оос сэргийлнэ */
    gluLookAt(0, 14, 0.01,  0, 0, 0,  0, 0, -1);

    GLfloat lpos[4] = {3.f, 15.f, 3.f, 1.f};
    GLfloat lcol[4] = {1.f,  1.f, 1.f, 1.f};
    GLfloat lamp[4] = {0.25f,0.25f,0.25f,1.f};
    glLightfv(GL_LIGHT0, GL_POSITION, lpos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  lcol);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lcol);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  lamp);

    for (int i=0; i<NUM_BONES; i++)
        bone_draw(&G.bones[i], &G.mesh);

    glDisable(GL_LIGHTING);
    glColor4f(1.f, 1.f, 1.f, 0.12f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_LINES);
    for (int i=-8; i<=8; i++) {
        glVertex3f((float)i, -0.5f, -8.f);
        glVertex3f((float)i, -0.5f,  8.f);
        glVertex3f(-8.f, -0.5f, (float)i);
        glVertex3f( 8.f, -0.5f, (float)i);
    }
    glEnd();
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);

    draw_hud();
    glutSwapBuffers();
}

static void cb_reshape(int w, int h)
{
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = (float)w / h;
    float half_h = 6.0f;
    glOrtho(-half_h*aspect, half_h*aspect, -half_h, half_h, 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

static void cb_keyboard(unsigned char key, int x, int y)
{
    (void)x; (void)y;
    switch (key) {
        case ' ':  game_toss();  break;
        case 'r':
        case 'R':  game_reset(); break;
        case 27:   exit(0);      break;
    }
}

static void cb_timer(int val)
{
    (void)val;
    bg_update(0.016f);

    if (G.animating) {
        G.anim_frame++;
        float progress = (float)G.anim_frame / G.total_frames;

        for (int i=0; i<NUM_BONES; i++) {
            float t = progress - i * 0.05f;
            if (t < 0.f) t = 0.f;
            if (t > 1.f) t = 1.f;
            /* гурвалсан хялбар нам (ease-out cubic) */
            float et = 1.f - (1.f-t)*(1.f-t)*(1.f-t);
            G.bones[i].anim_t = et;
        }

        if (G.anim_frame >= G.total_frames + NUM_BONES*3) {
            G.animating = 0;
            game_finish_toss();
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, cb_timer, 0);
}

void berh4::run_game(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 600);
    glutCreateWindow("Dorven Berkh - Traditional Mongolian Shagai Game");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    game_init();

    glutDisplayFunc (cb_display);
    glutReshapeFunc (cb_reshape);
    glutKeyboardFunc(cb_keyboard);
    glutTimerFunc(16, cb_timer, 0);

    glutMainLoop();
}

void berh4::init()
{
    game_init();
}

void berh4::render()
{
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    float aspect = (float)w / h;
    float half_h = 6.0f;
    glOrtho(-half_h*aspect, half_h*aspect, -half_h, half_h, 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);

    glClearColor(G.bg_r, G.bg_g, G.bg_b, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(0, 14, 0.01,  0, 0, 0,  0, 0, -1);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat lpos[4] = {3.f, 15.f, 3.f, 1.f};
    GLfloat lcol[4] = {1.f,  1.f, 1.f, 1.f};
    GLfloat lamp[4] = {0.25f, 0.25f, 0.25f, 1.f};
    glLightfv(GL_LIGHT0, GL_POSITION, lpos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  lcol);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lcol);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  lamp);

    for (int i = 0; i < NUM_BONES; i++)
        bone_draw(&G.bones[i], &G.mesh);

    glDisable(GL_LIGHTING);
    glColor4f(1.f, 1.f, 1.f, 0.12f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_LINES);
    for (int i = -8; i <= 8; i++) {
        glVertex3f((float)i, -0.5f, -8.f); glVertex3f((float)i, -0.5f,  8.f);
        glVertex3f(-8.f, -0.5f, (float)i); glVertex3f( 8.f, -0.5f, (float)i);
    }
    glEnd();
    glDisable(GL_BLEND);

    draw_hud();
    glutSwapBuffers();
}

bool berh4::on_key(unsigned char key)
{
    switch (key) {
        case ' ':  game_toss();  return false;
        case 'r': case 'R': game_reset(); return false;
        case 27: return true;
    }
    return false;
}

void berh4::on_timer()
{
    bg_update(0.016f);

    if (G.animating) {
        G.anim_frame++;
        float progress = (float)G.anim_frame / G.total_frames;
        for (int i = 0; i < NUM_BONES; i++) {
            float t = progress - i * 0.05f;
            if (t < 0.f) t = 0.f;
            if (t > 1.f) t = 1.f;
            /* гурвалсан хялбар нам (ease-out cubic) */
            float et = 1.f - (1.f-t)*(1.f-t)*(1.f-t);
            G.bones[i].anim_t = et;
        }
        if (G.anim_frame >= G.total_frames + NUM_BONES*3) {
            G.animating = 0;
            game_finish_toss();
        }
    }
    glutPostRedisplay();
}
