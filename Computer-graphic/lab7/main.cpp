#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include <cmath>
#include <cstdlib>
#include <iostream>
using namespace std;

struct Point {
    float x, y;
};

float t = 0.0f;
float speed = 0.002f;
bool isAnimating = false;
bool forwardAnim = true;

int winW = 900;
int winH = 700;

vector<Point> shape1;
vector<Point> shape2;

bool drawingShape1 = true;
bool drawingShape2 = false;
bool shape1Done = false;
bool shape2Done = false;
bool isDrawing = false;

// ----------------------------
// Utility
// ----------------------------
float lerp(float a, float b, float tt) {
    return a + (b - a) * tt;
}

Point lerpPoint(const Point& a, const Point& b, float tt) {
    Point p;
    p.x = lerp(a.x, b.x, tt);
    p.y = lerp(a.y, b.y, tt);
    return p;
}

// Window pixel -> OpenGL world coords
Point screenToWorld(int x, int y) {
    Point p;
    p.x = (float)x;
    p.y = (float)y;
    return p;
}

// Draw polyline/polygon
void drawShape(const vector<Point>& shape, float r, float g, float b, bool closed = true) {
    if (shape.empty()) return;

    glColor3f(r, g, b);
    glLineWidth(2.0f);

    if (closed && shape.size() >= 3)
        glBegin(GL_LINE_LOOP);
    else
        glBegin(GL_LINE_STRIP);

    for (const auto& p : shape) {
        glVertex2f(p.x, p.y);
    }
    glEnd();

    // vertices
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    for (const auto& p : shape) {
        glVertex2f(p.x, p.y);
    }
    glEnd();
}

// Resample shape so both shapes have same number of points
vector<Point> resampleShape(const vector<Point>& input, int targetCount) {
    vector<Point> out;
    if (input.empty() || targetCount <= 0) return out;
    if ((int)input.size() == targetCount) return input;
    if (input.size() == 1) {
        out.assign(targetCount, input[0]);
        return out;
    }

    int n = (int)input.size();
    for (int i = 0; i < targetCount; i++) {
        float pos = (float)i * (n - 1) / (float)(targetCount - 1);
        int idx = (int)floor(pos);
        float localT = pos - idx;

        if (idx >= n - 1) {
            out.push_back(input[n - 1]);
        } else {
            out.push_back(lerpPoint(input[idx], input[idx + 1], localT));
        }
    }
    return out;
}

vector<Point> tweenedShape;

// Prepare tweening
void prepareTween() {
    if (shape1.size() < 2 || shape2.size() < 2) {
        cout << "Need at least 2 points in each shape.\n";
        return;
    }

    int targetCount = max((int)shape1.size(), (int)shape2.size());
    shape1 = resampleShape(shape1, targetCount);
    shape2 = resampleShape(shape2, targetCount);

    t = 0.0f;
    forwardAnim = true;
    isAnimating = true;
}

// ----------------------------
// Drawing
// ----------------------------
void drawTweened() {
    if (!shape1Done || !shape2Done) return;
    if (shape1.size() != shape2.size()) return;

    tweenedShape.clear();

    for (size_t i = 0; i < shape1.size(); i++) {
        tweenedShape.push_back(lerpPoint(shape1[i], shape2[i], t));
    }

    // fill
    if (tweenedShape.size() >= 3) {
        glColor3f(0.7f, 0.2f + 0.8f * (1.0f - t), 0.9f * (1.0f - t));
        glBegin(GL_POLYGON);
        for (const auto& p : tweenedShape) {
            glVertex2f(p.x, p.y);
        }
        glEnd();
    }

    // outline
    drawShape(tweenedShape, 1.0f, 1.0f, 1.0f, true);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Reference shapes
    if (!shape1.empty()) drawShape(shape1, 0.2f, 0.4f, 1.0f, true);
    if (!shape2.empty()) drawShape(shape2, 1.0f, 0.2f, 0.2f, true);

    drawTweened();

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    Point p = screenToWorld(x, y);

    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isDrawing = true;

            if (drawingShape1 && !shape1Done) {
                shape1.push_back(p);
            } else if (drawingShape2 && !shape2Done) {
                shape2.push_back(p);
            }
        } else if (state == GLUT_UP) {
            isDrawing = false;
        }
    }

    glutPostRedisplay();
}

void motion(int x, int y) {
    if (!isDrawing) return;

    Point p = screenToWorld(x, y);

    if (drawingShape1 && !shape1Done) {
        shape1.push_back(p);
    } else if (drawingShape2 && !shape2Done) {
        shape2.push_back(p);
    }

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '1':
            if (!shape1Done) {
                drawingShape1 = true;
                drawingShape2 = false;
            }
            break;

        case '2':
            if (shape1Done && !shape2Done) {
                drawingShape1 = false;
                drawingShape2 = true;
            }
            break;

        case 'n':   // finish current shape, move to next
        case 'N':
            if (drawingShape1 && !shape1.empty()) {
                shape1Done = true;
                drawingShape1 = false;
                drawingShape2 = true;
                cout << "Shape 1 done. Now draw Shape 2.\n";
            } else if (drawingShape2 && !shape2.empty()) {
                shape2Done = true;
                drawingShape2 = false;
                cout << "Shape 2 done. Press ENTER to tween.\n";
            }
            break;

        case 13:    // Enter
            if (shape1Done && shape2Done) {
                prepareTween();
            }
            break;

        case ' ':
            if (shape1Done && shape2Done) {
                isAnimating = !isAnimating;
            }
            break;

        case 'r':
        case 'R':
            t = 0.0f;
            forwardAnim = true;
            isAnimating = false;
            shape1.clear();
            shape2.clear();
            tweenedShape.clear();
            drawingShape1 = true;
            drawingShape2 = false;
            shape1Done = false;
            shape2Done = false;
            cout << "Reset.\n";
            break;

        case '+':
            speed += 0.001f;
            break;

        case '-':
            speed -= 0.001f;
            if (speed < 0.001f) speed = 0.001f;
            break;

        case 27: // ESC
            exit(0);
            break;
    }

    glutPostRedisplay();
}

void update() {
    if (isAnimating && shape1Done && shape2Done) {
        if (forwardAnim) {
            t += speed;
            if (t >= 1.0f) {
                t = 1.0f;
                forwardAnim = false;
            }
        } else {
            t -= speed;
            if (t <= 0.0f) {
                t = 0.0f;
                forwardAnim = true;
            }
        }

        glutPostRedisplay();
    }
}

void reshape(int w, int h) {
    winW = w;
    winH = h;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, h, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init() {
    glClearColor(0.08f, 0.08f, 0.1f, 1.0f);
    glPointSize(4.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(winW, winH);
    glutCreateWindow("Draw Two Shapes and Tween");

    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutIdleFunc(update);

    cout << "Instructions:\n";
    cout << "- Draw Shape 1 with mouse\n";
    cout << "- Press N to finish Shape 1\n";
    cout << "- Draw Shape 2 with mouse\n";
    cout << "- Press N to finish Shape 2\n";
    cout << "- Press ENTER to start tweening\n";
    cout << "- SPACE = pause/play\n";
    cout << "- +/- = speed control\n";
    cout << "- R = reset\n";
    cout << "- ESC = exit\n";

    glutMainLoop();
    return 0;
}
