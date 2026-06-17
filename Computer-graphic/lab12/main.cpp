#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
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

Vertex subtract(Vertex v1, Vertex v2) {
    return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

Vertex calculateNormal(Vertex p1, Vertex p2, Vertex p3) {
    Vertex v1 = subtract(p2, p1);
    Vertex v2 = subtract(p3, p1);
    Vertex normal;
    normal.x = v1.y * v2.z - v1.z * v2.y;
    normal.y = v1.z * v2.x - v1.x * v2.z;
    normal.z = v1.x * v2.y - v1.y * v2.x;
    
    float length = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
    if (length > 0.0f) {
        normal.x /= length; normal.y /= length; normal.z /= length;
    }
    return normal;
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
                auto getIdx = [](string s) { return stoi(s.substr(0, s.find('/'))) - 1; };
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

void DrawAxes() {
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(0, 0, 0); glVertex3f(100, 0, 0);
        glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0, 0, 0); glVertex3f(0, 100, 0);
        glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0, 0, 0); glVertex3f(0, 0, 100);
    glEnd();
    glLineWidth(1.0f);
}

void setupLighting() {
    glEnable(GL_LIGHTING);   
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat lightPos[] = { 0.0f, 30.0f, 0.0f, 1.0f }; 
    GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f }; 
    GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);

    glShadeModel(GL_FLAT);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    glTranslatef(0.0f, 0.0f, zTrans); 
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    DrawAxes();
    setupLighting();
    
    glColor3f(0.0f, 0.8f, 0.8f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
    
    model.render();
    
    glutSwapBuffers();
}


void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    if (!model.load("bunny.obj")) exit(1);
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

void reshape(int w, int h) {
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
    glutCreateWindow("OBJ Viewer - Lighting and Normals");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(SpecialKeys);
    glutMainLoop();
    return 0;
}