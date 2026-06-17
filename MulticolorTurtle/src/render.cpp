#include "back.h"
#include "render.h"
#include <GL/freeglut.h>
#include <algorithm>
#include <cmath>
#include <cstdio>
using std::min;

void drawShagai(const Shagai& s)
{
    if (!s.active) return;

    bool highlight=false;
    if (gs.phase==Phase::SELECTING)
        for (BodyPart p:gs.valid_targets) if(s.part==p){highlight=true;break;}

    float boost=1.0f;
    if (highlight) {
        float t=(float)glutGet(GLUT_ELAPSED_TIME)*0.004f;
        boost=1.35f+0.35f*sinf(t);
    }

    float cr=min(1.f,s.r*boost);
    float cg=min(1.f,s.g*boost);
    float cb=min(1.f,s.b*boost);

    GLfloat amb[] ={cr*.3f,cg*.3f,cb*.3f,1.f};
    GLfloat diff[]={cr,cg,cb,1.f};
    GLfloat spec[]={0.5f,0.5f,0.5f,1.f};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,  amb);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,  diff);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, spec);
    glMaterialf (GL_FRONT_AND_BACK,GL_SHININESS,40.f);
    glPushMatrix();
      glTranslatef(s.x,s.y,s.z);
      if (s.rot_y!=0.f) glRotatef(s.rot_y,0.f,1.f,0.f);
      glCallList(g_shagaiList);
    glPopMatrix();
}

void drawReturnGhost(const Shagai& s)
{
    float t=(float)glutGet(GLUT_ELAPSED_TIME)*0.005f;
    float boost=0.60f+0.25f*sinf(t);
    float cr=min(1.f,s.r*boost+0.20f);
    float cg=min(1.f,s.g*boost+0.20f);
    float cb=min(1.f,s.b*boost+0.20f);

    GLfloat amb[] ={cr*.35f,cg*.35f,cb*.35f,1.f};
    GLfloat diff[]={cr,cg,cb,1.f};
    GLfloat spec[]={0.2f,0.2f,0.2f,1.f};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,  amb);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,  diff);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, spec);
    glMaterialf (GL_FRONT_AND_BACK,GL_SHININESS,20.f);
    glPushMatrix();
      glTranslatef(s.x,s.y+0.16f,s.z);
      if (s.rot_y!=0.f) glRotatef(s.rot_y,0.f,1.f,0.f);
      glCallList(g_shagaiList);
    glPopMatrix();
}

static void bitmapStr(float x,float y,void* font,const char* str)
{
    glRasterPos2f(x,y);
    for (const char* c=str;*c;++c) glutBitmapCharacter(font,(unsigned char)*c);
}

static void draw_dot(float cx,float cy,float r)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx,cy);
    for (int i=0;i<=18;++i) {
        float a=i*2.f*3.14159f/18.f;
        glVertex2f(cx+cosf(a)*r, cy+sinf(a)*r);
    }
    glEnd();
}

static void draw_centered_text(float cx,float y,void* font,const char* str)
{
    int tw=glutBitmapLength(font,(const unsigned char*)str);
    bitmapStr(cx-(float)tw*0.5f,y,font,str);
}

static void draw_rect(float x,float y,float w,float h,float r,float g,float b)
{
    glColor3f(r,g,b);
    glBegin(GL_QUADS);
    glVertex2f(x,y); glVertex2f(x+w,y);
    glVertex2f(x+w,y+h); glVertex2f(x,y+h);
    glEnd();
}

static void draw_dice_face(int bx,int by,int sz,int v,bool rolling)
{
    float hsz=(float)sz, hbx=(float)bx, hby=(float)by;

    glColor3f(0.1f,0.1f,0.1f);
    glBegin(GL_QUADS);
    glVertex2f(hbx+5,hby-5); glVertex2f(hbx+hsz+5,hby-5);
    glVertex2f(hbx+hsz+5,hby+hsz-5); glVertex2f(hbx+5,hby+hsz-5);
    glEnd();

    glColor3f(0.96f,0.95f,0.90f);
    glBegin(GL_QUADS);
    glVertex2f(hbx,hby); glVertex2f(hbx+hsz,hby);
    glVertex2f(hbx+hsz,hby+hsz); glVertex2f(hbx,hby+hsz);
    glEnd();

    float* pc=g_players[g_current_player].col;
    glColor3f(pc[0],pc[1],pc[2]);
    glLineWidth(3.f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(hbx+2,hby+2); glVertex2f(hbx+hsz-2,hby+2);
    glVertex2f(hbx+hsz-2,hby+hsz-2); glVertex2f(hbx+2,hby+hsz-2);
    glEnd();
    glLineWidth(1.f);

    if (v<1||v>6) return;

    static const float DOT[6][6][2]={
        {{ 0, 0},{ 0, 0},{ 0, 0},{ 0, 0},{ 0, 0},{ 0, 0}},
        {{-1,+1},{+1,-1},{ 0, 0},{ 0, 0},{ 0, 0},{ 0, 0}},
        {{-1,+1},{ 0, 0},{+1,-1},{ 0, 0},{ 0, 0},{ 0, 0}},
        {{-1,+1},{+1,+1},{-1,-1},{+1,-1},{ 0, 0},{ 0, 0}},
        {{-1,+1},{+1,+1},{ 0, 0},{-1,-1},{+1,-1},{ 0, 0}},
        {{-1,+1},{+1,+1},{-1, 0},{+1, 0},{-1,-1},{+1,-1}},
    };
    glColor3f(rolling?0.55f:0.08f, 0.08f, 0.08f);
    float cx=hbx+hsz*.5f, cy=hby+hsz*.5f;
    float sp=sz*0.27f, dr=sz*0.075f;
    for (int i=0;i<v;++i)
        draw_dot(cx+DOT[v-1][i][0]*sp, cy+DOT[v-1][i][1]*sp, dr);
}

static void draw_button(const UiButton& b, bool primary=false)
{
    void* f=GLUT_BITMAP_HELVETICA_18;
    if (primary) draw_rect(b.x,b.y,b.w,b.h,0.18f,0.36f,0.24f);
    else         draw_rect(b.x,b.y,b.w,b.h,0.10f,0.12f,0.17f);

    glColor3f(primary?0.55f:0.35f, primary?1.00f:0.55f, primary?0.70f:0.78f);
    glLineWidth(primary?3.f:2.f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(b.x,b.y); glVertex2f(b.x+b.w,b.y);
    glVertex2f(b.x+b.w,b.y+b.h); glVertex2f(b.x,b.y+b.h);
    glEnd();
    glLineWidth(1.f);

    int tw=glutBitmapLength(f,(const unsigned char*)b.label);
    glColor3f(0.96f,0.94f,0.86f);
    bitmapStr(b.x+b.w*0.5f-tw*0.5f, b.y+b.h*0.5f-5.f, f, b.label);
}

static void draw_menu_button(const UiButton& b)
{
    void* f=GLUT_BITMAP_HELVETICA_18;
    draw_rect(b.x,b.y,b.w,b.h, 0.55f,0.07f,0.10f);

    glColor3f(0.70f,0.10f,0.13f);
    glLineWidth(1.5f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(b.x,b.y); glVertex2f(b.x+b.w,b.y);
    glVertex2f(b.x+b.w,b.y+b.h); glVertex2f(b.x,b.y+b.h);
    glEnd();
    glLineWidth(1.f);

    int tw=glutBitmapLength(f,(const unsigned char*)b.label);
    glColor3f(1.f,1.f,1.f);
    bitmapStr(b.x+b.w*0.5f-tw*0.5f, b.y+b.h*0.5f-5.f, f, b.label);
}

static void draw_scoreboard(int W,int H)
{
    void* fBig=GLUT_BITMAP_HELVETICA_18;
    void* fSm =GLUT_BITMAP_HELVETICA_12;
    const int pw=124, ph=54, pad=12;

    for (int i=0;i<g_num_players;++i) {
        bool active=(i==g_current_player && gs.phase!=Phase::GAME_OVER);
        int px=pad, py=H-pad-ph;
        switch (i) {
            case 0: px=pad;       py=H-pad-ph; break;
            case 1: px=W-pad-pw;  py=H-pad-ph; break;
            case 2: px=W-pad-pw;  py=pad;      break;
            case 3: px=pad;       py=pad;      break;
        }
        float x=(float)px, y=(float)py;

        if (active) glColor3f(0.08f,0.20f,0.08f);
        else        glColor3f(0.08f,0.08f,0.12f);
        glBegin(GL_QUADS);
        glVertex2f(x,y); glVertex2f(x+(float)pw,y);
        glVertex2f(x+(float)pw,y+(float)ph); glVertex2f(x,y+(float)ph);
        glEnd();

        float* c=g_players[i].col;
        glColor3f(c[0]*(active?1.0f:0.4f), c[1]*(active?1.0f:0.4f), c[2]*(active?1.0f:0.4f));
        glLineWidth(active?2.f:1.f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x+1,y+1); glVertex2f(x+(float)pw-1,y+1);
        glVertex2f(x+(float)pw-1,y+(float)ph-1); glVertex2f(x+1,y+(float)ph-1);
        glEnd();
        glLineWidth(1.f);

        char buf[64];
        snprintf(buf,sizeof(buf),"T%d",i+1);
        glColor3f(c[0],c[1],c[2]);
        bitmapStr(x+10, y+(float)ph-20, fBig, buf);

        snprintf(buf,sizeof(buf),"%d",g_players[i].inventory);
        glColor3f(0.94f,0.94f,0.88f);
        int scoreW=glutBitmapLength(fBig,(const unsigned char*)buf);
        bitmapStr(x+(float)pw-12-(float)scoreW, y+(float)ph-20, fBig, buf);

        if (active) {
            glColor3f(0.52f,1.f,0.52f);
            bitmapStr(x+10, y+12, fSm, "eelj");
        } else if (gs.phase==Phase::GAME_OVER &&
                   g_players[i].inventory > g_players[g_current_player].inventory) {
            glColor3f(1.f,0.9f,0.1f);
            bitmapStr(x+10, y+12, fSm, "yalsan");
        }
    }
}

static void draw_menu_screen(int W,int H)
{
    void* title=GLUT_BITMAP_TIMES_ROMAN_24;
    g_buttons.clear();

    drawMenuBackground();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glColor3f(1.f,1.f,1.f);
    const char* name="Alag melhii";
    int titleW=glutBitmapLength(title,(const unsigned char*)name);
    bitmapStr(W*0.5f-titleW*0.5f,H-120.f,title,name);

    float bw=240.f,bh=48.f,x=W*0.5f-bw*0.5f,y=H*0.5f+76.f,gap=14.f;
    g_buttons.push_back({x,y,           bw,bh,"Togloh",      ButtonAction::PLAY});
    g_buttons.push_back({x,y-(bh+gap),  bw,bh,"Onoo",        ButtonAction::SCORE});
    g_buttons.push_back({x,y-2*(bh+gap),bw,bh,"Shinechleh",  ButtonAction::RESET});
    g_buttons.push_back({x,y-3*(bh+gap),bw,bh,"4 Berh",      ButtonAction::BERH4});
    g_buttons.push_back({x,y-4*(bh+gap),bw,bh,"Garah",       ButtonAction::EXIT});

    for (const auto& btn : g_buttons) draw_menu_button(btn);
}

static void draw_player_select_screen(int W,int H)
{
    void* fBig=GLUT_BITMAP_HELVETICA_18;
    g_buttons.clear();

    drawMenuBackground();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glColor3f(1.f,1.f,1.f);
    const char* title="Toglogch songoh";
    int titleW=glutBitmapLength(fBig,(const unsigned char*)title);
    bitmapStr(W*0.5f-titleW*0.5f,H-150.f,fBig,title);

    float bw=150.f,bh=64.f,gap=18.f;
    float total=3.f*bw+2.f*gap, x=W*0.5f-total*0.5f, y=H*0.5f-10.f;
    g_buttons.push_back({x,           y,bw,bh,"2",ButtonAction::PLAYERS_2});
    g_buttons.push_back({x+bw+gap,    y,bw,bh,"3",ButtonAction::PLAYERS_3});
    g_buttons.push_back({x+2*(bw+gap),y,bw,bh,"4",ButtonAction::PLAYERS_4});
    for (const auto& b:g_buttons) draw_menu_button(b);

    UiButton back={W*0.5f-90.f,y-92.f,180.f,42.f,"Butsah",ButtonAction::BACK};
    g_buttons.push_back(back);
    draw_menu_button(back);
}

static void draw_score_screen(int W,int H)
{
    void* fBig=GLUT_BITMAP_HELVETICA_18;
    g_buttons.clear();

    drawMenuBackground();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glColor3f(1.f,1.f,1.f);
    const char* title="Onoo";
    int titleW=glutBitmapLength(fBig,(const unsigned char*)title);
    bitmapStr(W*0.5f-titleW*0.5f,H-150.f,fBig,title);

    float x=W*0.5f-150.f, y=H*0.5f+80.f;
    for (int i=0;i<g_num_players;++i) {
        char buf[256];
        snprintf(buf,sizeof(buf),"%s: %d",g_players[i].name,g_players[i].inventory);
        glColor3f(g_players[i].col[0],g_players[i].col[1],g_players[i].col[2]);
        bitmapStr(x,y-i*32.f,fBig,buf);
    }

    UiButton reset={W*0.5f-210.f,H*0.5f-130.f,190.f,44.f,"Shinechleh",ButtonAction::RESET};
    UiButton back ={W*0.5f+20.f, H*0.5f-130.f,190.f,44.f,"Butsah",    ButtonAction::BACK};
    g_buttons.push_back(reset);
    g_buttons.push_back(back);
    draw_menu_button(reset);
    draw_menu_button(back);
}

static void draw_victory_overlay(int W,int H)
{
    if (gs.winner<0) return;

    void* title=GLUT_BITMAP_TIMES_ROMAN_24;
    void* fBig =GLUT_BITMAP_HELVETICA_18;
    void* fSm  =GLUT_BITMAP_HELVETICA_12;
    float* c=g_players[gs.winner].col;
    float t=(float)glutGet(GLUT_ELAPSED_TIME)*0.001f;

    for (int i=0;i<56;++i) {
        float rx=fmodf((i*83.f)+(t*55.f*(1+(i%3))),(float)W);
        float ry=fmodf((i*47.f)+(t*95.f*(1+(i%4))),(float)H);
        float r=(i%3==0)?1.f:(i%3==1?c[0]:0.25f);
        float g=(i%3==0)?0.86f:(i%3==1?c[1]:0.78f);
        float b=(i%3==0)?0.22f:(i%3==1?c[2]:1.f);
        draw_rect(rx,ry,7.f+(float)(i%4)*2.f,7.f,r,g,b);
    }

    float panelW=430.f,panelH=210.f;
    float x=(float)W*0.5f-panelW*0.5f;
    float y=(float)H*0.5f-panelH*0.5f+20.f;
    draw_rect(x,y,panelW,panelH,0.05f,0.07f,0.10f);

    glColor3f(c[0],c[1],c[2]);
    glLineWidth(4.f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x,y); glVertex2f(x+panelW,y);
    glVertex2f(x+panelW,y+panelH); glVertex2f(x,y+panelH);
    glEnd();
    glLineWidth(1.f);

    glColor3f(1.f,0.88f,0.30f);
    draw_centered_text((float)W*0.5f,y+panelH-52.f,title,"Yalalt");

    char buf[128];
    snprintf(buf,sizeof(buf),"%s yallaa",g_players[gs.winner].name);
    glColor3f(0.96f,0.96f,0.90f);
    draw_centered_text((float)W*0.5f,y+panelH-92.f,fBig,buf);

    snprintf(buf,sizeof(buf),"%d shagai tsugluullaa",gs.winning_score);
    glColor3f(0.68f,0.72f,0.70f);
    draw_centered_text((float)W*0.5f,y+panelH-122.f,fSm,buf);

    UiButton reset={x+62.f,     y+34.f,130.f,42.f,"Dahin", ButtonAction::RESET};
    UiButton menu ={x+panelW-192.f,y+34.f,130.f,42.f,"Tsess",ButtonAction::BACK};
    g_buttons.clear();
    g_buttons.push_back(reset);
    g_buttons.push_back(menu);
    draw_button(reset,true);
    draw_button(menu,false);
}

void draw_hud()
{
    int W=glutGet(GLUT_WINDOW_WIDTH), H=glutGet(GLUT_WINDOW_HEIGHT);

    glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();
    gluOrtho2D(0,W,0,H);
    glMatrixMode(GL_MODELVIEW);  glPushMatrix(); glLoadIdentity();
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    if (g_screen==Screen::MAIN_MENU) {
        draw_menu_screen(W,H);
    } else if (g_screen==Screen::PLAYER_SELECT) {
        draw_player_select_screen(W,H);
    } else if (g_screen==Screen::SCORE_VIEW) {
        draw_score_screen(W,H);
    } else {
        void* fBig=GLUT_BITMAP_HELVETICA_18;
        char buf[256];

        draw_scoreboard(W,H);

        int dSz=110, dBX=20, dBY=20;
        draw_dice_face(dBX,dBY,dSz, g_dice.show_v, g_dice.rolling);

        const char* action="";
        if      (g_dice.rolling)               action="Shoo ergej baina";
        else if (gs.phase==Phase::SELECTING)   action="Gereltsen hesgees songo";
        else if (gs.phase==Phase::RETURNING)   action="Gereltsen hesgiig butsaa";
        else if (gs.phase==Phase::IDLE)        action="Shoo hayah";
        else if (gs.phase==Phase::GAME_OVER)   action="Togloom duuslaa";

        glColor3f(0.92f,0.88f,0.54f);
        draw_centered_text((float)dBX + dSz*0.5f,(float)(dBY+dSz+14),fBig,action);

        snprintf(buf,sizeof(buf),"%d/%d",gs.remaining,gs.total);
        glColor3f(0.30f,0.65f,1.f);
        draw_centered_text((float)W*0.5f,(float)H-28.f,fBig,buf);

        if (gs.msg[0]) {
            glColor3f(0.92f,0.88f,0.60f);
            draw_centered_text((float)W*0.5f, 14.f, fBig, gs.msg);
        }

        if (gs.phase==Phase::GAME_OVER) draw_victory_overlay(W,H);
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION); glPopMatrix();
    glMatrixMode(GL_MODELVIEW);  glPopMatrix();
}
