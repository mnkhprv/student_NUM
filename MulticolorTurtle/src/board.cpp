#include "board.h"
#include <GL/freeglut.h>
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <string>
using std::min;
using std::max;

void loadShagai(const char* path)
{
    std::ifstream f(path);
    if (!f) { fprintf(stderr, "Cannot open %s\n", path); return; }

    std::vector<Vec3> raw;
    std::vector<std::array<int,3>> faces;
    std::string line;
    while (std::getline(f, line)) {
        if (line.size() < 2) continue;
        if (line[0]=='v' && line[1]==' ') {
            Vec3 v; sscanf(line.c_str(),"v %f %f %f",&v.x,&v.y,&v.z);
            raw.push_back(v);
        } else if (line[0]=='f' && line[1]==' ') {
            int vi[3],ti[3];
            if (sscanf(line.c_str(),"f %d/%d %d/%d %d/%d",
                       &vi[0],&ti[0],&vi[1],&ti[1],&vi[2],&ti[2])==6)
                faces.push_back({vi[0]-1,vi[1]-1,vi[2]-1});
        }
    }

    float mnX=1e9f,mnY=1e9f,mnZ=1e9f,mxX=-1e9f,mxY=-1e9f,mxZ=-1e9f;
    for (auto& v : raw) {
        mnX=min(mnX,v.x); mxX=max(mxX,v.x);
        mnY=min(mnY,v.y); mxY=max(mxY,v.y);
        mnZ=min(mnZ,v.z); mxZ=max(mxZ,v.z);
    }
    float cx=(mnX+mxX)*.5f, cy=(mnY+mxY)*.5f, cz=(mnZ+mxZ)*.5f;
    float sc=1.f/(mxY-mnY);
    g_meshVerts.reserve(raw.size());
    for (auto& v : raw)
        g_meshVerts.push_back({(v.x-cx)*sc,(v.z-cz)*sc,(v.y-cy)*sc});

    g_meshFaceIdx.reserve(faces.size()*3);
    g_faceNormals.reserve(faces.size());
    for (auto& fi : faces) {
        g_meshFaceIdx.push_back(fi[0]);
        g_meshFaceIdx.push_back(fi[1]);
        g_meshFaceIdx.push_back(fi[2]);
        Vec3& a=g_meshVerts[fi[0]], &b=g_meshVerts[fi[1]], &c=g_meshVerts[fi[2]];
        float ux=b.x-a.x,uy=b.y-a.y,uz=b.z-a.z;
        float vx=c.x-a.x,vy=c.y-a.y,vz=c.z-a.z;
        Vec3 n={uy*vz-uz*vy,uz*vx-ux*vz,ux*vy-uy*vx};
        float len=sqrtf(n.x*n.x+n.y*n.y+n.z*n.z);
        if (len>1e-7f){n.x/=len;n.y/=len;n.z/=len;}
        g_faceNormals.push_back(n);
    }

    g_shagaiList=glGenLists(1);
    glNewList(g_shagaiList,GL_COMPILE);
    glBegin(GL_TRIANGLES);
    for (size_t i=0;i<g_faceNormals.size();++i) {
        Vec3& n=g_faceNormals[i];
        glNormal3f(n.x,n.y,n.z);
        for (int j=0;j<3;++j){Vec3& v=g_meshVerts[g_meshFaceIdx[i*3+j]];glVertex3f(v.x,v.y,v.z);}
    }
    glEnd();
    glEndList();
}

void buildLayout()
{
    g_shagai.clear();
    const float SX=0.70f, SZ=0.85f;

    auto add = [&](float x,float y,float z,
                   float r,float g,float b,
                   BodyPart p, uint8_t grp=0, float ry=0.f)
    { g_shagai.push_back({x,y,z,r,g,b,true,p,grp,ry}); };

    const float BROWN[] ={0.42f,0.12f,0.04f};
    const float BLUE[]  ={0.02f,0.08f,0.42f};
    const float LBLUE[] ={0.10f,0.82f,0.90f};
    const float TURQ[]  ={0.00f,0.52f,0.42f};
    const float RED[]   ={0.78f,0.03f,0.02f};
    const float YELLOW[]={0.96f,0.86f,0.03f};
    const float BLACK[] ={0.08f,0.08f,0.08f};
    const float PINK[]  ={0.98f,0.74f,0.84f};
    const float GREEN[] ={0.04f,0.62f,0.16f};

    for (int r=0;r<6;++r) for (int c=0;c<6;++c)
        add((c-2.5f)*SX,0.f,(2.5f-r)*SZ,BROWN[0],BROWN[1],BROWN[2],BodyPart::SPINE);

    float spineL=-2.5f*SX,spineR=2.5f*SX,spineT=2.5f*SZ,spineB=-2.5f*SZ;

    const float ORGAN_Y = 0.75f;
    add((3-2.5f)*SX,ORGAN_Y,(2.5f-2)*SZ, RED[0],   RED[1],   RED[2],   BodyPart::HEART);
    add((3-2.5f)*SX,ORGAN_Y,(2.5f-3)*SZ, YELLOW[0],YELLOW[1],YELLOW[2],BodyPart::KIDNEY);
    add((2-2.5f)*SX,ORGAN_Y,(2.5f-3)*SZ, YELLOW[0],YELLOW[1],YELLOW[2],BodyPart::KIDNEY);
    add((2-2.5f)*SX,ORGAN_Y,(2.5f-4)*SZ, LBLUE[0], LBLUE[1], LBLUE[2], BodyPart::BLADDER);

    // Neck 6
    float neckZ=spineT+SZ;
    for (int r=0;r<3;++r) for (int c=0;c<2;++c)
        add((c-0.5f)*SX,0.f,neckZ+r*SZ, BLUE[0],BLUE[1],BLUE[2],BodyPart::NECK);

    // Head 3
    float headZ=neckZ+3*SZ;
    for (int r=0;r<3;++r)
        add(0.f,0.f,headZ+r*SZ, LBLUE[0],LBLUE[1],LBLUE[2],BodyPart::HEAD);

    // Eyes 2: beside middle of head, rotated 45°
    float eyeZ = headZ + SZ;
    add(-1.5f*SX, 0.f, eyeZ, TURQ[0],TURQ[1],TURQ[2], BodyPart::EYE, 0, -45.f);
    add( 1.5f*SX, 0.f, eyeZ, TURQ[0],TURQ[1],TURQ[2], BodyPart::EYE, 0, +45.f);

    // Ears 2: beside top of neck, rotated 45°
    float earZ = neckZ + 2.0f*SZ;
    add(-2.0f*SX, 0.f, earZ, RED[0],RED[1],RED[2], BodyPart::EAR, 0, +45.f);
    add( 2.0f*SX, 0.f, earZ, RED[0],RED[1],RED[2], BodyPart::EAR, 1, -45.f);

    // Tail 3
    float tailZ=spineB-SZ;
    for (int r=0;r<3;++r)
        add(0.f,0.f,tailZ-r*SZ, BLACK[0],BLACK[1],BLACK[2],BodyPart::TAIL);

    // Shins — 4 groups × 4
    float shinBX[4]={spineL-SX,spineR+SX,spineL-SX,spineR+SX};
    float shinBZ[4]={spineT-0.5f*SZ,spineT-0.5f*SZ,spineB+0.5f*SZ,spineB+0.5f*SZ};
    float shinDX[4]={-1.f,1.f,-1.f,1.f};
    float shinDZ[4]={1.f,1.f,-1.f,-1.f};
    for (int g=0;g<4;++g)
        for (int r=0;r<2;++r) for (int c=0;c<2;++c)
            add(shinBX[g]+c*shinDX[g]*SX, 0.f, shinBZ[g]+r*shinDZ[g]*SZ,
                PINK[0],PINK[1],PINK[2], BodyPart::SHIN,(uint8_t)g);

    // Paws — 4 groups × 5
    float pawBX[4]={shinBX[0]-2*SX, shinBX[1]+2*SX, shinBX[2]-2*SX, shinBX[3]+2*SX};
    float pawBZ[4]={shinBZ[0]+2*SZ, shinBZ[1]+2*SZ, shinBZ[2]-2*SZ, shinBZ[3]-2*SZ};
    float pawArc[4]={2.35f,0.78f,3.93f,5.50f};
    for (int g=0;g<4;++g)
        for (int i=0;i<5;++i) {
            float a=(float)(i-2)*0.35f+pawArc[g];
            float s=(i%2==0)?1.0f:1.5f;
            add(pawBX[g]+cosf(a)*SX*1.2f*s, 0.f,
                pawBZ[g]+sinf(a)*SZ*1.2f*s,
                GREEN[0],GREEN[1],GREEN[2], BodyPart::PAW,(uint8_t)g);
        }

    gs.remaining = gs.total = (int)g_shagai.size();
    printf("[Layout] %d pieces placed.\n", gs.total);
}

// ============================================================
//  Active-piece queries
// ============================================================
int count_active(BodyPart p)
{
    int n=0;
    for (auto& s:g_shagai) if(s.active&&s.part==p) ++n;
    return n;
}

int count_active_group(BodyPart part, int group)
{
    int n=0;
    for (const auto& s:g_shagai)
        if (s.part==part && s.group_idx==(uint8_t)group && s.active) ++n;
    return n;
}

int available_shin_group()
{
    for (int g=0;g<4;++g) {
        int n=0;
        for (auto& s:g_shagai) if(s.part==BodyPart::SHIN&&s.group_idx==g&&s.active) ++n;
        if (n==4) return g;
    }
    return -1;
}

int available_paw_group()
{
    for (int g=0;g<4;++g) {
        int n=0;
        for (auto& s:g_shagai) if(s.part==BodyPart::PAW&&s.group_idx==g&&s.active) ++n;
        if (n==5) return g;
    }
    return -1;
}

int available_ear_group()
{
    for (int g=0;g<2;++g) {
        int n=0;
        for (auto& s:g_shagai) if(s.part==BodyPart::EAR&&s.group_idx==g&&s.active) ++n;
        if (n==1) return g;
    }
    return -1;
}


int removed_owner(size_t shagai_idx)
{
    for (int i=(int)g_removed.size()-1;i>=0;--i)
        if (g_removed[i].shagai_idx==shagai_idx) return g_removed[i].player;
    return -1;
}

int count_removed_part(BodyPart part)
{
    int n=0;
    for (const auto& e:g_removed)
        if (e.player==g_current_player && g_shagai[e.shagai_idx].part==part) ++n;
    return n;
}

int count_removed_group(BodyPart part, int group)
{
    int n=0;
    for (const auto& e:g_removed) {
        const Shagai& s=g_shagai[e.shagai_idx];
        if (e.player==g_current_player && s.part==part && s.group_idx==(uint8_t)group) ++n;
    }
    return n;
}