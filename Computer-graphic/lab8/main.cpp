#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <cmath>
#include <cstdlib>
#include <vector>

static const float PI = 3.14159265358979323846f;

struct ProfilePoint {
    float r;
    float y;
};

struct Vertex3D {
    float x;
    float y;
    float z;
};

class Part {
public:
    virtual ~Part() {}
    virtual void draw() const = 0;
};

class RevolutionSurface : public Part {
protected:
    std::vector<ProfilePoint> profile;
    int slices;
    float cr;
    float cg;
    float cb;

    Vertex3D rotateY(const ProfilePoint& p, float angle) const {
        Vertex3D v;
        v.x = p.r * std::cos(angle);
        v.y = p.y;
        v.z = p.r * std::sin(angle);
        return v;
    }

public:
    RevolutionSurface(const std::vector<ProfilePoint>& points, int sliceCount,
                      float red, float green, float blue)
        : profile(points), slices(sliceCount), cr(red), cg(green), cb(blue) {}

    void draw() const override {
        glColor3f(cr, cg, cb);
        for (std::size_t row = 0; row + 1 < profile.size(); ++row) {
            glBegin(GL_QUAD_STRIP);
            for (int i = 0; i <= slices; ++i) {
                const float angle = 2.0f * PI * static_cast<float>(i) / static_cast<float>(slices);
                const Vertex3D a = rotateY(profile[row], angle);
                const Vertex3D b = rotateY(profile[row + 1], angle);
                glVertex3f(a.x, a.y, a.z);
                glVertex3f(b.x, b.y, b.z);
            }
            glEnd();
        }
    }
};

class RoseBud : public RevolutionSurface {
public:
    RoseBud()
        : RevolutionSurface({
              {0.00f, -1.65f},
              {0.10f, -1.55f},
              {0.18f, -1.38f},
              {0.22f, -1.15f},
              {0.24f, -0.90f},
              {0.26f, -0.62f},
              {0.34f, -0.34f},
              {0.48f, -0.10f},
              {0.65f,  0.12f},
              {0.82f,  0.35f},
              {0.96f,  0.60f},
              {1.02f,  0.82f},
              {0.96f,  1.02f},
              {0.84f,  1.18f},
              {0.72f,  1.28f},
              {0.84f,  1.40f},
              {0.98f,  1.54f},
              {0.88f,  1.67f},
              {0.60f,  1.82f},
              {0.28f,  1.94f},
              {0.00f,  2.02f},
          }, 64, 0.86f, 0.08f, 0.18f) {}
};

class InnerBud : public RevolutionSurface {
public:
    InnerBud()
        : RevolutionSurface({
              {0.00f, -1.15f},
              {0.12f, -1.00f},
              {0.18f, -0.74f},
              {0.22f, -0.48f},
              {0.30f, -0.20f},
              {0.46f,  0.05f},
              {0.60f,  0.34f},
              {0.64f,  0.62f},
              {0.54f,  0.92f},
              {0.36f,  1.18f},
              {0.14f,  1.36f},
              {0.00f,  1.48f},
          }, 64, 0.98f, 0.34f, 0.48f) {}
};

class SepalCrown : public Part {
public:
    void draw() const override {
        glColor3f(0.12f, 0.58f, 0.20f);
        for (int i = 0; i < 8; ++i) {
            glPushMatrix();
            glRotatef(45.0f * i, 0.0f, 1.0f, 0.0f);
            glTranslatef(0.18f, -1.58f, 0.0f);
            glRotatef(-65.0f, 0.0f, 0.0f, 1.0f);
            glBegin(GL_TRIANGLES);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(0.95f, -0.14f, 0.10f);
            glVertex3f(0.95f,  0.14f, -0.10f);
            glEnd();
            glPopMatrix();
        }
    }
};

class Stem : public Part {
public:
    void draw() const override {
        GLUquadric* q = gluNewQuadric();

        glColor3f(0.10f, 0.55f, 0.18f);
        glPushMatrix();
        glTranslatef(0.0f, -5.7f, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(q, 0.10, 0.07, 4.2, 18, 1);
        glPopMatrix();

        glColor3f(0.12f, 0.62f, 0.20f);
        glPushMatrix();
        glTranslatef(0.22f, -3.7f, 0.0f);
        glRotatef(25.0f, 0.0f, 0.0f, 1.0f);
        glScalef(1.35f, 0.34f, 0.10f);
        glutSolidSphere(1.0, 18, 12);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-0.18f, -4.45f, 0.0f);
        glRotatef(-32.0f, 0.0f, 0.0f, 1.0f);
        glScalef(1.05f, 0.26f, 0.10f);
        glutSolidSphere(1.0, 18, 12);
        glPopMatrix();

        gluDeleteQuadric(q);
    }
};

class RoseModel : public Part {
private:
    RoseBud outerBud;
    InnerBud innerBud;
    SepalCrown sepals;
    Stem stem;

public:
    void draw() const override {
        stem.draw();

        glPushMatrix();
        glTranslatef(0.0f, -1.2f, 0.0f);
        outerBud.draw();
        glScalef(0.75f, 0.75f, 0.75f);
        innerBud.draw();
        glPopMatrix();

        sepals.draw();
    }
};

static RoseModel rose;
static float angleX = -8.0f;
static float angleY = 28.0f;
static float zoom = -12.5f;
static bool wireframe = false;
static const float modelCenterY = -2.35f;
static const float modelScale = 1.15f;

void drawAxes() {
    glLineWidth(2.0f);
    glBegin(GL_LINES);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(3.5f, 0.0f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 3.5f, 0.0f);

    glColor3f(0.0f, 0.6f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 3.5f);

    glEnd();
    glLineWidth(1.0f);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, zoom);
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);
    glScalef(modelScale, modelScale, modelScale);
    glTranslatef(0.0f, -modelCenterY, 0.0f);

    drawAxes();
    rose.draw();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) {
        h = 1;
    }

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, static_cast<float>(w) / static_cast<float>(h), 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int, int) {
    if (key == 'w') {
        angleX -= 5.0f;
    }
    if (key == 's') {
        angleX += 5.0f;
    }
    if (key == 'a') {
        angleY -= 5.0f;
    }
    if (key == 'd') {
        angleY += 5.0f;
    }
    if (key == '+') {
        zoom += 0.5f;
    }
    if (key == '-') {
        zoom -= 0.5f;
    }
    if (key == 'm') {
        wireframe = !wireframe;
        glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
    }
    if (key == 27) {
        std::exit(0);
    }

    glutPostRedisplay();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.05f, 0.05f, 0.08f, 1.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 700);
    glutCreateWindow("Hard-Coded Rose Surface");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
