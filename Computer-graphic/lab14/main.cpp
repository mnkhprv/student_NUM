#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __APPLE__
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

int num_texture = -1; // Counter to keep track of the last loaded texture

#define MAX_VERTICES 7000 // Max number of vertices (for each object)
#define MAX_POLYGONS 3500 // Max number of polygons (for each object)

// Our vertex type
typedef struct {
    float x, y, z;
} vertex_type;

// The polygon (triangle), 3 numbers that point to 3 vertices
typedef struct {
    int a, b, c;
} polygon_type;

// The mapcoord type, 2 texture coordinates for each vertex
typedef struct {
    float u, v;
} mapcoord_type;

// The object type
typedef struct {
    vertex_type  vertex[MAX_VERTICES];
    polygon_type polygon[MAX_POLYGONS];
    mapcoord_type mapcoord[MAX_VERTICES];
    int id_texture;
    int num_vertices;
    int num_polygons;
} obj_type, *obj_type_ptr;

// The width and height of your window
int screen_width  = 640;
int screen_height = 480;

double rotation_x = 0;
double rotation_y = 0;
double rotation_z = 0;

// Flag for rendering as lines or filled polygons
int filling = 1; // 0=OFF  1=ON

// Zoom: controls the Z translation (more negative = further away)
float zoom = -30.0f;

// Mouse state for drag-to-rotate
int mouse_last_x = 0, mouse_last_y = 0;
int mouse_dragging = 0;

obj_type character;

int LoadBitmap(const char *filename) {
    int width, height, channels;

    // stbi_load forces 4 channels (RGBA) regardless of source format
    unsigned char *l_texture = stbi_load(filename, &width, &height, &channels, 4);

    if (!l_texture) {
        printf("Error: Could not load image '%s'\n", filename);
        printf("stb_image reason: %s\n", stbi_failure_reason());
        return -1;
    }

    num_texture++; // Advance texture counter

    glBindTexture(GL_TEXTURE_2D, num_texture);

    // Texture parameters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,       GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,       GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,   GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,   GL_LINEAR_MIPMAP_NEAREST);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // Upload texture data
    glTexImage2D(GL_TEXTURE_2D, 0, 4,
                 width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

    // Build mipmaps
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4,
                      width, height,
                      GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

    stbi_image_free(l_texture); // Free stb_image memory

    return num_texture;
}

int LoadOBJ(const char *filename, obj_type *obj) {
    // Static to avoid blowing the stack (~200 KB of temp data)
    static float raw_pos[3000][3];
    static float raw_uv[3000][2];
    static int   combo_pos[MAX_VERTICES]; // combined vertex → position index
    static int   combo_uv[MAX_VERTICES];  // combined vertex → UV index

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error: cannot open '%s'\n", filename);
        return 0;
    }

    int num_raw_pos = 0, num_raw_uv = 0, num_combined = 0;
    obj->num_polygons = 0;

    char line[512];
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "v ", 2) == 0) {
            if (num_raw_pos < 3000)
                sscanf(line + 2, "%f %f %f",
                       &raw_pos[num_raw_pos][0],
                       &raw_pos[num_raw_pos][1],
                       &raw_pos[num_raw_pos][2]);
            num_raw_pos++;
        } else if (strncmp(line, "vt ", 3) == 0) {
            if (num_raw_uv < 3000)
                sscanf(line + 3, "%f %f",
                       &raw_uv[num_raw_uv][0],
                       &raw_uv[num_raw_uv][1]);
            num_raw_uv++;
        } else if (strncmp(line, "f ", 2) == 0) {
            int pi[4], ti[4], ni[4], nv = 0;
            char *ptr = line + 2;
            int p, t, n, consumed;
            while (nv < 4 &&
                   sscanf(ptr, " %d/%d/%d%n", &p, &t, &n, &consumed) == 3) {
                pi[nv] = p - 1;
                ti[nv] = t - 1;
                nv++;
                ptr += consumed;
            }
            if (nv < 3) continue;

            // Resolve each face-vertex to a combined (pos+uv) index
            int idx[4];
            for (int i = 0; i < nv; i++) {
                int found = -1;
                for (int j = 0; j < num_combined; j++) {
                    if (combo_pos[j] == pi[i] && combo_uv[j] == ti[i]) {
                        found = j;
                        break;
                    }
                }
                if (found == -1 && num_combined < MAX_VERTICES) {
                    found = num_combined;
                    combo_pos[num_combined] = pi[i];
                    combo_uv[num_combined]  = ti[i];
                    obj->vertex[num_combined].x   = raw_pos[pi[i]][0];
                    obj->vertex[num_combined].y   = raw_pos[pi[i]][1];
                    obj->vertex[num_combined].z   = raw_pos[pi[i]][2];
                    obj->mapcoord[num_combined].u = raw_uv[ti[i]][0];
                    obj->mapcoord[num_combined].v = 1.0f - raw_uv[ti[i]][1];
                    num_combined++;
                }
                idx[i] = found;
            }

            // Fan-triangulate: (0,1,2) and for quads also (0,2,3)
            if (obj->num_polygons < MAX_POLYGONS) {
                obj->polygon[obj->num_polygons].a = idx[0];
                obj->polygon[obj->num_polygons].b = idx[1];
                obj->polygon[obj->num_polygons].c = idx[2];
                obj->num_polygons++;
            }
            if (nv == 4 && obj->num_polygons < MAX_POLYGONS) {
                obj->polygon[obj->num_polygons].a = idx[0];
                obj->polygon[obj->num_polygons].b = idx[2];
                obj->polygon[obj->num_polygons].c = idx[3];
                obj->num_polygons++;
            }
        }
    }

    fclose(fp);
    obj->num_vertices = num_combined;
    printf("Loaded '%s': %d vertices, %d triangles\n",
           filename, num_combined, obj->num_polygons);
    return 1;
}


void init(void)
{
    glClearColor(0.0, 0.0, 0.2, 0.0); // Dark blue background
    glShadeModel(GL_SMOOTH);
    glViewport(0, 0, screen_width, screen_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,
                   (GLfloat)screen_width / (GLfloat)screen_height,
                   1.0f, 1000.0f);
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_TEXTURE_2D);
    if (!LoadOBJ("Character.obj", &character)) {
        printf("Fatal: Character.obj not found. Exiting.\n");
        exit(0);
    }

    character.id_texture = LoadBitmap("Texture.jpg");
    if (character.id_texture == -1) {
        printf("Fatal: Texture.jpg not found. Exiting.\n");
        exit(0);
    }
}


void resize(int width, int height)
{
    screen_width  = width;
    screen_height = height;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, screen_width, screen_height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,
                   (GLfloat)screen_width / (GLfloat)screen_height,
                   1.0f, 1000.0f);

    glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'r': case 'R':
            if (filling == 0) {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                filling = 1;
            } else {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                filling = 0;
            }
            break;
        case '+': case '=':
            zoom += 1.0f;
            break;
        case '-': case '_':
            zoom -= 1.0f;
            break;
        case 27: // ESC key — exit
            exit(0);
            break;
    }
}


void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        mouse_dragging = (state == GLUT_DOWN);
        mouse_last_x = x;
        mouse_last_y = y;
    }
}


void motion(int x, int y)
{
    if (mouse_dragging) {
        int dx = x - mouse_last_x;
        int dy = y - mouse_last_y;
        rotation_y += dx * 0.5;
        rotation_x += dy * 0.5;
        mouse_last_x = x;
        mouse_last_y = y;
        glutPostRedisplay();
    }
}



void display(void) {
    int l_index;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, -6.0, zoom);

    glRotatef((float)rotation_x, 1.0, 0.0, 0.0);
    glRotatef((float)rotation_y, 0.0, 1.0, 0.0);
    glRotatef((float)rotation_z, 0.0, 0.0, 1.0);

    glBindTexture(GL_TEXTURE_2D, character.id_texture);

    glBegin(GL_TRIANGLES);
    for (l_index = 0; l_index < character.num_polygons; l_index++) {
        glTexCoord2f(character.mapcoord[ character.polygon[l_index].a ].u,
                     character.mapcoord[ character.polygon[l_index].a ].v);
        glVertex3f(  character.vertex[   character.polygon[l_index].a ].x,
                     character.vertex[   character.polygon[l_index].a ].y,
                     character.vertex[   character.polygon[l_index].a ].z);

        glTexCoord2f(character.mapcoord[ character.polygon[l_index].b ].u,
                     character.mapcoord[ character.polygon[l_index].b ].v);
        glVertex3f(  character.vertex[   character.polygon[l_index].b ].x,
                     character.vertex[   character.polygon[l_index].b ].y,
                     character.vertex[   character.polygon[l_index].b ].z);

        glTexCoord2f(character.mapcoord[ character.polygon[l_index].c ].u,
                     character.mapcoord[ character.polygon[l_index].c ].v);
        glVertex3f(  character.vertex[   character.polygon[l_index].c ].x,
                     character.vertex[   character.polygon[l_index].c ].y,
                     character.vertex[   character.polygon[l_index].c ].z);
    }
    glEnd();

    glFlush();
    glutSwapBuffers();
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(screen_width, screen_height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Texture");

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    init();
    glutMainLoop();

    return 0;
}