#include "input.h"
#include "back.h"
#include "4berh.h"
#include <GL/freeglut.h>
#include <cmath>

static void compute_ray(int wx,int wy,
                        float& ox,float& oy,float& oz,
                        float& dx,float& dy,float& dz)
{
    int gy=g_vp[3]-wy-1;
    GLdouble nx,ny,nz,fx,fy,fz;
    gluUnProject(wx,gy,0.0, g_mv,g_proj,g_vp, &nx,&ny,&nz);
    gluUnProject(wx,gy,1.0, g_mv,g_proj,g_vp, &fx,&fy,&fz);
    ox=(float)nx; oy=(float)ny; oz=(float)nz;
    dx=(float)(fx-nx); dy=(float)(fy-ny); dz=(float)(fz-nz);
    float len=sqrtf(dx*dx+dy*dy+dz*dz);
    if (len>1e-7f){dx/=len;dy/=len;dz/=len;}
}

static float ray_sphere(float ox,float oy,float oz,
                        float dx,float dy,float dz,
                        float cx,float cy,float cz,float r)
{
    float ex=ox-cx,ey=oy-cy,ez=oz-cz;
    float b=dx*ex+dy*ey+dz*ez;
    float c=ex*ex+ey*ey+ez*ez-r*r;
    float disc=b*b-c;
    if (disc<0) return -1.f;
    float t=-b-sqrtf(disc);
    return (t>0)?t:-1.f;
}

static void on_pick(int wx,int wy)
{
    if (g_screen!=Screen::GAME) return;
    if (g_dice.rolling) return;

    if (gs.phase==Phase::IDLE) { processTurn(); return; }
    if (gs.phase!=Phase::SELECTING && gs.phase!=Phase::RETURNING) return;

    float ox,oy,oz,dx,dy,dz;
    compute_ray(wx,wy,ox,oy,oz,dx,dy,dz);

    if (gs.phase==Phase::RETURNING) {
        float best_t=1e9f;
        size_t best_idx=0;
        bool found=false;
        for (size_t i=0;i<g_shagai.size();++i) {
            if (!is_return_candidate(i)) continue;
            const Shagai& s=g_shagai[i];
            float t=ray_sphere(ox,oy,oz,dx,dy,dz, s.x,s.y+0.16f,s.z, 0.45f);
            if (t>0&&t<best_t){ best_t=t; best_idx=i; found=true; }
        }
        if (found) choose_return_piece(best_idx);
        return;
    }

    float    best_t    =1e9f;
    BodyPart best_part =BodyPart::SPINE;
    int      best_group=-1;
    bool     found     =false;

    for (const auto& s:g_shagai) {
        if (!s.active) continue;
        bool is_target=false;
        for (BodyPart p:gs.valid_targets) if(s.part==p){is_target=true;break;}
        if (!is_target) continue;

        float t=ray_sphere(ox,oy,oz,dx,dy,dz, s.x,s.y,s.z, 0.45f);
        if (t>0&&t<best_t){
            best_t=t;
            best_part=s.part;
            best_group=s.group_idx;
            found=true;
        }
    }
    if (found) execute_take(best_part,best_group);
}

void timer_cb(int)
{
    if (g_screen == Screen::BERH4_GAME) {
        berh4::on_timer();
        glutTimerFunc(16, timer_cb, 0);
        return;
    }
    if (g_dice.rolling) {
        ++g_dice.frame;
        bool settled=(g_dice.frame>=g_dice.total);
        g_dice.show_v = settled ? g_dice.final_v : (rand()%6)+1;
        if (settled) {
            g_dice.rolling = false;
            gs.dice        = g_dice.final_v;
            apply_roll(gs.dice);
        }
        glutPostRedisplay();
    } else if (gs.phase==Phase::GAME_OVER) {
        glutPostRedisplay();
    }
    glutTimerFunc(16, timer_cb, 0);
}

void display()
{
    if (g_screen == Screen::BERH4_GAME) {
        berh4::render();
        return;
    }
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    drawBackground();

    GLfloat lpos[]={0.f,0.f,1.f,0.f};
    glLightfv(GL_LIGHT0,GL_POSITION,lpos);

    float yr=g_yaw*3.14159f/180.f, pr=g_pitch*3.14159f/180.f;
    float ecx=g_dist*cosf(pr)*sinf(yr);
    float ecy=g_dist*sinf(pr);
    float ecz=g_dist*cosf(pr)*cosf(yr);
    gluLookAt(ecx,ecy,ecz, 0,0,0, 0,1,0);

    glGetDoublev(GL_MODELVIEW_MATRIX,  g_mv);
    glGetDoublev(GL_PROJECTION_MATRIX, g_proj);
    glGetIntegerv(GL_VIEWPORT,         g_vp);

    for (size_t i=0;i<g_shagai.size();++i) {
        const Shagai& s=g_shagai[i];
        if (s.active) drawShagai(s);
        else if (gs.phase==Phase::RETURNING && is_return_candidate(i))
            drawReturnGhost(s);
    }
    draw_hud();
    glutSwapBuffers();
}

void reshape(int w,int h)
{
    if (!h) h=1;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    gluPerspective(45.0,(double)w/h,0.1,200.0);
    glMatrixMode(GL_MODELVIEW);
}

void mouseBtn(int btn,int state,int x,int y)
{
    if (g_screen == Screen::BERH4_GAME) return;
    if (btn==GLUT_LEFT_BUTTON) {
        if (state==GLUT_DOWN) {
            g_left_down=true;
            g_lastX=x; g_lastY=y;
            g_click_startX=x; g_click_startY=y;
        } else {
            g_left_down=false;
            int ddx=x-g_click_startX, ddy=y-g_click_startY;
            if (ddx*ddx+ddy*ddy<25) {
                if (g_screen!=Screen::GAME || gs.phase==Phase::GAME_OVER)
                    handle_ui_click(x,y);
                else
                    on_pick(x,y);
            }
        }
    } else if (btn==GLUT_RIGHT_BUTTON) {
        if (state==GLUT_DOWN) { g_drag=true;  g_lastX=x; g_lastY=y; }
        else                  { g_drag=false; }
    }
}

void mouseMove(int x,int y)
{
    if (!g_drag) return;
    g_yaw  +=(x-g_lastX)*0.4f;
    g_pitch-=(y-g_lastY)*0.4f;
    if(g_pitch> 89.f) g_pitch= 89.f;
    if(g_pitch<-89.f) g_pitch=-89.f;
    g_lastX=x; g_lastY=y;
    glutPostRedisplay();
}

void mouseWheel(int,int dir,int,int)
{
    g_dist-=dir*0.8f;
    if(g_dist<1.f)   g_dist=1.f;
    if(g_dist>100.f) g_dist=100.f;
    glutPostRedisplay();
}

void keyboard(unsigned char key,int,int)
{
    if (g_screen == Screen::BERH4_GAME) {
        if (berh4::on_key(key)) {
            g_screen = Screen::MAIN_MENU;
            int w = glutGet(GLUT_WINDOW_WIDTH), h = glutGet(GLUT_WINDOW_HEIGHT);
            reshape(w, h);
            glutPostRedisplay();
        }
        return;
    }
    if (g_screen!=Screen::GAME) {
        switch (key) {
            case 'p': case 'P': g_screen=Screen::PLAYER_SELECT; glutPostRedisplay(); return;
            case 's': case 'S': g_screen=Screen::SCORE_VIEW;    glutPostRedisplay(); return;
            case 'r': case 'R':
                reset_game(); g_screen=Screen::MAIN_MENU;
                set_msg("Shine togloom ehlehed Togloh darna uu.");
                glutPostRedisplay(); return;
            case '2': start_game_with_players(2); return;
            case '3': start_game_with_players(3); return;
            case '4': start_game_with_players(4); return;
            case 27:
                if (g_screen==Screen::MAIN_MENU) glutLeaveMainLoop();
                else { g_screen=Screen::MAIN_MENU; glutPostRedisplay(); }
                return;
        }
        return;
    }

    switch (key) {
        case ' ': processTurn(); break;
        case '1': case '2': case '3':
            if (gs.phase==Phase::SELECTING) {
                int idx=key-'1';
                if (idx<(int)gs.valid_targets.size())
                    execute_take(gs.valid_targets[idx]);
            }
            break;
        case 'n': case 'N':
            if (gs.first_roll) { g_screen=Screen::PLAYER_SELECT; glutPostRedisplay(); }
            break;
        case 'r': case 'R': reset_game(); break;
        case 27: glutLeaveMainLoop(); break;
    }
}
