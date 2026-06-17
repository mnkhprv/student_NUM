#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

static GLfloat xRot = 20.0f;
static GLfloat yRot = 45.0f;
static GLfloat zTrans = -15.0f; 

struct Vertex {
    float x, y, z;
};

struct Face {
    int v1, v2, v3;
};

class OBJModel {
public:
    vector<Vertex> vertices;
    vector<Face> faces;

    bool load(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            return false;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string type;
            ss >> type;

            if (type == "v") {
                Vertex v;
                ss >> v.x >> v.y >> v.z;
                vertices.push_back(v);
            } 
            else if (type == "f") {
                string v1, v2, v3;
                ss >> v1 >> v2 >> v3;
                
                auto getIndex = [](string s) {
                    try {
                        return stoi(s.substr(0, s.find('/'))) - 1;
                    } catch (...) { return -1; }
                };

                Face f;
                f.v1 = getIndex(v1);
                f.v2 = getIndex(v2);
                f.v3 = getIndex(v3);
                if(f.v1 >= 0 && f.v2 >= 0 && f.v3 >= 0)
                    faces.push_back(f);
            }
        }
        cout << "Амжилттай: " << filename << " (" << vertices.size() << " цэгтэй)" << endl;
        return true;
    }

    void render() {
        glBegin(GL_TRIANGLES);
        for (const auto& f : faces) {
            glVertex3f(vertices[f.v1].x, vertices[f.v1].y, vertices[f.v1].z);
            glVertex3f(vertices[f.v2].x, vertices[f.v2].y, vertices[f.v2].z);
            glVertex3f(vertices[f.v3].x, vertices[f.v3].y, vertices[f.v3].z);
        }
        glEnd();
    }
};

OBJModel model;

void DrawAxes() {
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(0, 0, 0); glVertex3f(100, 0, 0);
        glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0, 0, 0); glVertex3f(0, 100, 0);
        glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0, 0, 0); glVertex3f(0, 0, 100);
    glEnd();
    glLineWidth(1.0f);
}

void SpecialKeys(int key, int x, int y) {
    (void)x; (void)y;
    if (key == GLUT_KEY_UP) xRot -= 5.0f;
    if (key == GLUT_KEY_DOWN) xRot += 5.0f;
    if (key == GLUT_KEY_LEFT) yRot -= 5.0f;
    if (key == GLUT_KEY_RIGHT) yRot += 5.0f;
    if (key == GLUT_KEY_PAGE_UP) zTrans += 0.5f;   
    if (key == GLUT_KEY_PAGE_DOWN) zTrans -= 0.5f;
    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    glTranslatef(0.0f, 0.0f, zTrans); 
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    
    DrawAxes();
    
    glColor3f(0.0f, 1.0f, 1.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    model.render();
    
    glutSwapBuffers();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    
    if (!model.load("bunny.obj")) { 
        exit(1);
    }
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w/h, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 700);
    glutCreateWindow("OBJ VERTICES");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(SpecialKeys);
    
    glutMainLoop();
    return 0;
}