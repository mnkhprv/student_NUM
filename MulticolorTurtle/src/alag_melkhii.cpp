#include "alag_melkhii.h"
#include "input.h"
#include "back.h"
#include "sound.h"
#include <GL/freeglut.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>

void alag_melkhii::run_game(int argc, char** argv)
{
    srand((unsigned)time(nullptr));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH|GLUT_MULTISAMPLE);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Alag melhii oroh");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glClearColor(0.07f, 0.09f, 0.13f, 1.f);

    GLfloat gAmb[]={0.28f,0.28f,0.28f,1.f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gAmb);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    GLfloat white[]={1.f,1.f,1.f,1.f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    sound_init();
    init_background("background.bmp");
    init_menu_background("menu.bmp");
    loadShagai("shagai.obj");
    buildLayout();

    g_screen = Screen::MAIN_MENU;
    set_msg("Togloh darj ehelne.");

    glutDisplayFunc   (display);
    glutReshapeFunc   (reshape);
    glutMouseFunc     (mouseBtn);
    glutMotionFunc    (mouseMove);
    glutMouseWheelFunc(mouseWheel);
    glutKeyboardFunc  (keyboard);
    glutTimerFunc(16, timer_cb, 0);

    printf("Alag Melkhii started.\n");
    glutMainLoop();
}