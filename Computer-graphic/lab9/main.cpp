#include <GL/freeglut.h>
#include <bits/stdc++.h>
using namespace std;

static GLfloat xRot = 20.0f;
static GLfloat yRot = 45.0f;

class TrainPart {
protected:
    float x, y, z;
    float r, g, b;
    float length, radius;

public:
    TrainPart(float x, float y, float z, float radius, float length, float r, float g, float b)
        : x(x), y(y), z(z), radius(radius), length(length), r(r), g(g), b(b) {}

    void drawCylinder(GLUquadricObj* pObj, float bRad, float tRad, float len, float cr, float cg, float cb) {
        glPushMatrix();
            glColor3f(cr, cg, cb);
            gluCylinder(pObj, bRad, tRad, len, 26, 13);
            gluDisk(pObj, 0.0f, bRad, 26, 1);
            glTranslatef(0.0f, 0.0f, len);
            gluDisk(pObj, 0.0f, tRad, 26, 1);
        glPopMatrix();
    }

    void drawWheels(GLUquadricObj* pObj) {
        float spacing = length / 3.0f;
        for (float zSide : {-0.8f, 0.6f}) {
            for (int i = 0; i < 3; i++) {
                glPushMatrix();
                    glTranslatef(x + (i * spacing) + 0.4f, y - 0.8f, zSide);
                    drawCylinder(pObj, 0.35f, 0.35f, 0.2f, 0.1f, 0.1f, 0.1f);
                glPopMatrix();
            }
        }
    }

    virtual void draw(GLUquadricObj* pObj) = 0;
};

class Locomotive : public TrainPart {
public:
    Locomotive(float x) : TrainPart(x, 0, 0, 0.8f, 3.0f, 0.7f, 0.0f, 0.0f) {}

    void draw(GLUquadricObj* pObj) override {
        glPushMatrix();
            glTranslatef(x, y, z);
            glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            
            // Их бие
            drawCylinder(pObj, radius, radius, length, r, g, b);

            // Урд хошуу (Cone)
            glPushMatrix();
                glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
                drawCylinder(pObj, radius, 0.0f, 1.0f, 0.3f, 0.3f, 0.3f);
            glPopMatrix();

            // Кабин
            glPushMatrix();
                glTranslatef(0.0f, 0.0f, 2.0f);
                glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
                drawCylinder(pObj, 0.9f, 0.9f, 1.5f, 0.5f, 0.1f, 0.1f);
                // Гэрэл
                glTranslatef(0.0f, 0.0f, 1.5f);
                drawCylinder(pObj, 0.2f, 0.2f, 0.3f, 1.0f, 1.0f, 0.0f);
            glPopMatrix();

            // Яндан
            glPushMatrix();
                glTranslatef(0.0f, 0.8f, 0.8f);
                glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
                drawCylinder(pObj, 0.25f, 0.35f, 1.2f, 0.2f, 0.2f, 0.2f);
            glPopMatrix();
        glPopMatrix();
        drawWheels(pObj);
    }
};

class Carriage : public TrainPart {
public:
    Carriage(float x, float r, float g, float b) : TrainPart(x, 0, 0, 0.8f, 3.0f, r, g, b) {}

    void draw(GLUquadricObj* pObj) override {
        glPushMatrix();
            glTranslatef(x, y, z);
            glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            drawCylinder(pObj, radius, radius, length, r, g, b);
        glPopMatrix();
        drawWheels(pObj);
    }
};

class Train {
    vector<TrainPart*> parts;
public:
    Train() {
        parts.push_back(new Locomotive(-6.5f));
        parts.push_back(new Carriage(-3.0f, 0.1f, 0.5f, 0.1f));
        parts.push_back(new Carriage(0.5f, 0.1f, 0.1f, 0.6f));
    }

    ~Train() {
        for (auto p : parts) delete p;
    }

    void render(GLUquadricObj* pObj) {
        for (auto p : parts) p->draw(pObj);
        drawLinks(pObj);
    }

private:
    void drawLinks(GLUquadricObj* pObj) {
        float linkPositions[] = {-3.5f, 0.0f};
        for (float lx : linkPositions) {
            glPushMatrix();
                glTranslatef(lx, -0.3f, 0.0f);
                glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
                glColor3f(0.5f, 0.5f, 0.5f);
                gluCylinder(pObj, 0.1f, 0.1f, 0.5f, 10, 5);
            glPopMatrix();
        }
    }
};

Train* myTrain;

void DrawAxes() {
    glBegin(GL_LINES);
        glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(5,0,0);
        glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,5,0);
        glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,5);
    glEnd();
}

void RenderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, -20.0f);
        glRotatef(xRot, 1.0f, 0.0f, 0.0f);
        glRotatef(yRot, 0.0f, 1.0f, 0.0f);

        DrawAxes();
        GLUquadricObj* pObj = gluNewQuadric();
        gluQuadricNormals(pObj, GLU_SMOOTH);

        myTrain->render(pObj);

        gluDeleteQuadric(pObj);
    glPopMatrix();
    glutSwapBuffers();
}

void SetupRC() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    myTrain = new Train();
}


void ChangeSize(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(35.0f, (GLfloat)w/(GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void SpecialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_UP) xRot -= 2.0f;
    if (key == GLUT_KEY_DOWN) xRot += 2.0f;
    if (key == GLUT_KEY_LEFT) yRot -= 2.0f;
    if (key == GLUT_KEY_RIGHT) yRot += 2.0f;
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("Galt tereg");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();
    return 0;
}