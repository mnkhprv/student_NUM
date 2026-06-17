#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>
float x_shift = 0.0f;
float y_shift = 0.0f;
float numbers = 6.0f;
float s = 5.0f;

void drawSpiral(float centerX, float centerY) {
    float startSize = 0.2f;
    float growth = 0.22f;
    float rotation = 0.1f;

    for (int i = 0; i < 45; i++) {
        float r = startSize + (i * growth);
        float angleOffSet = i * rotation;

        glBegin(GL_LINE_LOOP);
        for (int j = 0; j < numbers; j++) {

            float theta = (j * 2.0f * M_PI / 6.0f) + angleOffSet;

            float vx = centerX + cos(theta) * r;
            float vy = centerY + sin(theta) * r;

            glVertex2f(vx, vy);
        }
        glEnd();
    }
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    int win_w = glutGet(GLUT_WINDOW_WIDTH);
    int win_h = glutGet(GLUT_WINDOW_HEIGHT);

    glViewport(0, 0, win_w / 2, win_h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-15, 15, -15, 15, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(0.1f, 0.1f, 0.2f);
    drawSpiral(0.0f, 0.0f);

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x_shift - s, y_shift - s);
        glVertex2f(x_shift + s, y_shift - s);
        glVertex2f(x_shift + s, y_shift + s);
        glVertex2f(x_shift - s, y_shift + s);
    glEnd();

    int rows = 5, cols = 5;
    int right_start_x = win_w / 2;
    int prt_w = (win_w / 2) / rows;
    int prt_h = win_h / cols;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            glViewport(right_start_x + (j * prt_w), i * prt_h, prt_w, prt_h);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            float left = x_shift - s;
            float right = x_shift + s;
            float bot = y_shift - s;
            float top = y_shift + s;

            if (j % 2 == 0) {
                float tmp = left;
                left = right;
                right = tmp;
            }
            if (i % 2 == 0) {
                float tmp = top;
                top = bot;
                bot = tmp;
            }
            glOrtho(left, right, bot, top, -1.0, 1.0);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            glColor3f(0.0f, 0.0f, 0.0f);
            drawSpiral(0.0f, 0.0f);
        }
    }
    glutSwapBuffers();
}

void specialKeys(int key, int, int) {
    float move_step = 0.3f;
    if(key == GLUT_KEY_UP)    y_shift += move_step;
    if(key == GLUT_KEY_DOWN)  y_shift -= move_step;
    if(key == GLUT_KEY_LEFT)  x_shift -= move_step;
    if(key == GLUT_KEY_RIGHT) x_shift += move_step;

    glutPostRedisplay();
}

void resize(GLsizei w, GLsizei h) {
    if (h == 0) h = 1;
    glViewport(5, 5, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

}

void init() {
    glClearColor(0.85f, 0.88f, 0.92f, 1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(900, 700);
    glutCreateWindow("Ortho & Viewport");


    init();

    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutSpecialFunc(specialKeys);
    glutMainLoop();

    return 0;
}
