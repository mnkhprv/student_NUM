#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <vector>
#include <stdlib.h>
using namespace std;

struct Point {
    int x, y;
};
struct Color {
    float r, g, b;
};
struct Stroke {
    vector<Point> points;
    Color color;
    int size;
    bool eraser;
};
enum Tool {
    PENCIL,
    ERASER
};

Tool currentTool = PENCIL;
Color currentColor =  { 0.0f, 0.0f, 0.0f,};
int brushSize = 3;
bool isDrawing = false;
int winWidth = 900;
int winHeight = 700;
vector<Stroke> strokes;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    for (const auto& s : strokes) {
        if (s.eraser)
            glColor3f(1.0f, 1.0f, 1.0f);
        else
            glColor3f(s.color.r, s.color.g, s.color.b);
        glLineWidth(s.size);

        if (s.points.size() == 1) {
            glPointSize(s.size);
            glBegin(GL_POINTS);
            glVertex2i(s.points[0].x, s.points[0].y);
            glEnd();
        } else {
            glBegin(GL_LINE_STRIP);
            for (const auto& p : s.points) {
                glVertex2i(p.x, p.y);
            }
            glEnd();
        }
    }
    glFlush();
}

void mouse (int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN){
            isDrawing = true;
            Stroke s;
            s.color = currentColor;
            s.size = brushSize;
            s.eraser = ( currentTool == ERASER);
            s.points.push_back({x, y});
            strokes.push_back(s);

            glutPostRedisplay();
        } else if (state == GLUT_UP) {
            isDrawing = false;
        }
    }
}

void motion(int x, int y) {
    if (isDrawing) {
        strokes.back().points.push_back({x, y});
        glutPostRedisplay();
    }
}

void keyboard (unsigned char key, int x, int y) {
    switch (key) {
        case 'p':
            currentTool = PENCIL;
            break;
        case 'e':
            currentTool = ERASER;
            break;
        case 'r':
            currentColor = {1.0f, 0.0f, 0.0f};
            break;
        case 'g':
            currentColor = {0.0f, 1.0f, 0.0f};
            break;
        case 'b':
            currentColor = {0.0f, 0.0f, 1.0f};
            break;
        case 'k':
            currentColor = {0.0f, 0.0f, 0.0f};
            break;
        case '+':
            brushSize++;
            break;
        case '-':
            if (brushSize > 1) brushSize--;
            break;
        case 'c':
            strokes.clear();
            break;
        case 27:        // ESC
            exit(0);
    }

    glutPostRedisplay();
}

void reshape (int w, int h) {
    winWidth = w;
    winHeight = h;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, h, 0);
    glMatrixMode(GL_MODELVIEW);

    glutPostRedisplay();
}

void init() {
  glClearColor(1.0, 1.0, 1.0, 1.0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 900, 700, 0);
  glMatrixMode(GL_MODELVIEW);
};

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(900, 700);
    glutCreateWindow("Paint");

    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMotionFunc(motion);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return EXIT_SUCCESS;
}
