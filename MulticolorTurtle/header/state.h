#ifndef AM_STATE_H
#define AM_STATE_H

#include "types.h"
#include <vector>
#include <GL/freeglut.h>

extern std::vector<Shagai>       g_shagai;
extern std::vector<RemovedEntry> g_removed;

// ─── Players ─────────────────────────────────────────────────
extern Player g_players[4];
extern int    g_num_players;
extern int    g_current_player;

// ─── Game + UI state ────────────────────────────────────────
extern GameState             gs;
extern Screen                g_screen;
extern std::vector<UiButton> g_buttons;

extern DiceAnim g_dice;

extern float    g_yaw, g_pitch, g_dist;
extern int      g_lastX, g_lastY;
extern bool     g_drag, g_left_down;
extern int      g_click_startX, g_click_startY;
extern GLdouble g_mv[16], g_proj[16];
extern GLint    g_vp[4];

extern std::vector<Vec3> g_meshVerts, g_faceNormals;
extern std::vector<int>  g_meshFaceIdx;
extern GLuint            g_shagaiList;

#endif