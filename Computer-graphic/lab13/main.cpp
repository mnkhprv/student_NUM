#include <GL/freeglut.h>
#include <bits/stdc++.h>

using namespace std;

static GLfloat xRot = 20.0f;
static GLfloat yRot = 45.0f;
static GLfloat zTrans = -1.0f; 
static GLfloat scaleFactor = 1.0f;

int materialType = 0;
bool lightX = true;
int lastMouseX, lastMouseY;
bool isLeftMouseButtonPressed = false;

struct Vertex { float x, y, z; };
struct Face { int v1, v2, v3; };

Vertex subtract(Vertex v1, Vertex v2) { return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z}; }

Vertex calculateNormal(Vertex p1, Vertex p2, Vertex p3) {
    Vertex v1 = subtract(p2, p1);
    Vertex v2 = subtract(p3, p1);
    Vertex n;
    n.x = v1.y * v2.z - v1.z * v2.y;
    n.y = v1.z * v2.x - v1.x * v2.z;
    n.z = v1.x * v2.y - v1.y * v2.x;
    float len = sqrt(n.x * n.x + n.y * n.y + n.z * n.z);
    if (len > 0) { n.x /= len; n.y /= len; n.z /= len; }
    return n;
}

class OBJModel {
public:
    vector<Vertex> vertices;
    vector<Face> faces;
    bool load(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) return false;
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string type; ss >> type;
            if (type == "v") {
                Vertex v; ss >> v.x >> v.y >> v.z;
                vertices.push_back(v);
            } else if (type == "f") {
                string s1, s2, s3; ss >> s1 >> s2 >> s3;
                auto getIdx = [](string s) {
                    try { return stoi(s.substr(0, s.find('/'))) - 1; }
                    catch (...) { return -1; }
                };
                faces.push_back({getIdx(s1), getIdx(s2), getIdx(s3)});
            }
        }
        return true;
    }
    void render() {
        glBegin(GL_TRIANGLES);
        for (const auto& f : faces) {
            Vertex n = calculateNormal(vertices[f.v1], vertices[f.v2], vertices[f.v3]);
            glNormal3f(n.x, n.y, n.z);
            glVertex3f(vertices[f.v1].x, vertices[f.v1].y, vertices[f.v1].z);
            glVertex3f(vertices[f.v2].x, vertices[f.v2].y, vertices[f.v2].z);
            glVertex3f(vertices[f.v3].x, vertices[f.v3].y, vertices[f.v3].z);
        }
        glEnd();
    }
};

OBJModel model;

void setupLights() {
    GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat position[] = {0.0, 3.0, 3.0, 0.0}; 
    GLfloat lmodel_ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat local_view[] = {0.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE); 
    glEnable(GL_DEPTH_TEST);
}

void setGoldMaterial() {
    GLfloat mat_ambient[] = {0.24725, 0.1995, 0.0745, 1.0};
    GLfloat mat_diffuse[] = {0.75164, 0.60648, 0.22648, 1.0};
    GLfloat mat_specular[] = {0.628281, 0.555802, 0.366065, 1.0};
    GLfloat shine = 0.4 * 128.0;

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shine);
}

void setJadeMaterial() {
    GLfloat mat_ambient[] = {0.135f, 0.2225f, 0.1575f, 1.0f};    
    GLfloat mat_diffuse[] = {0.54f, 0.89f, 0.63f, 1.0f};
    GLfloat mat_specular[] = {0.316228f, 0.316228f, 0.316228f, 1.0f};
    GLfloat shine = 0.1 * 128.0;

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shine);
}


void KeyboardFunc(unsigned char key, int x, int y) {
    if (key == '+' || key == '=') scaleFactor *= 1.1f;
    if (key == '-' || key == '_') scaleFactor *= 0.9f;
    if (key == 'j' || key == 'J') materialType = 0;
    if (key == 'g' || key == 'G') materialType = 1;
    if (key == 27) exit(0);
    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, zTrans);
    
    setupLights(); 

    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glScalef(scaleFactor, scaleFactor, scaleFactor);

    if (materialType == 0) setJadeMaterial();
    else setGoldMaterial();
    model.render();
    
    glutSwapBuffers();
}

void init() {
    glClearColor(0.1, 0.1, 0.1, 1.0);
    if (!model.load("dragon.obj")) exit(1);
}


void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w/(float)h, 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void MouseFunc(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) { isLeftMouseButtonPressed = true; lastMouseX = x; lastMouseY = y; }
        else isLeftMouseButtonPressed = false;
    }
}

void MotionFunc(int x, int y) {
    if (isLeftMouseButtonPressed) {
        yRot += (x - lastMouseX);
        xRot += (y - lastMouseY);
        lastMouseX = x; lastMouseY = y;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("LUUGIIN DAICHIN");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(KeyboardFunc);
    glutMouseFunc(MouseFunc);
    glutMotionFunc(MotionFunc);
    glutMainLoop();
    return 0;
}