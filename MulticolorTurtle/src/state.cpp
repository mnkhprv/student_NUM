#include "state.h"

std::vector<Shagai>       g_shagai;
std::vector<RemovedEntry> g_removed;

Player g_players[4] = {
    { "Toglogch 1", 0, {1.00f, 0.45f, 0.45f} },
    { "Toglogch 2", 0, {0.40f, 0.75f, 1.00f} },
    { "Toglogch 3", 0, {0.45f, 1.00f, 0.50f} },
    { "Toglogch 4", 0, {1.00f, 0.88f, 0.25f} },
};
int g_num_players    = 2;
int g_current_player = 0;

GameState             gs;
Screen                g_screen = Screen::MAIN_MENU;
std::vector<UiButton> g_buttons;

DiceAnim g_dice;

float   g_yaw   = 180.f, g_pitch = 68.f, g_dist = 20.f;
int     g_lastX = 0,     g_lastY = 0;
bool    g_drag  = false, g_left_down = false;
int     g_click_startX = 0, g_click_startY = 0;
GLdouble g_mv[16]   = {};
GLdouble g_proj[16] = {};
GLint    g_vp[4]    = {};

std::vector<Vec3> g_meshVerts, g_faceNormals;
std::vector<int>  g_meshFaceIdx;
GLuint            g_shagaiList = 0;