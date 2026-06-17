#ifndef AM_TYPES_H
#define AM_TYPES_H

#include <cstdint>
#include <vector>


enum class BodyPart : uint8_t {
    HEAD, EYE, EAR, NECK, SPINE,
    HEART, KIDNEY, BLADDER, TAIL, SHIN, PAW
};

inline const char* part_name(BodyPart p) {
    switch (p) {
        case BodyPart::HEAD:    return "Hoshuu";
        case BodyPart::EYE:     return "Nud";
        case BodyPart::EAR:     return "Chih";
        case BodyPart::NECK:    return "Huzuu";
        case BodyPart::SPINE:   return "Nuruu";
        case BodyPart::HEART:   return "Zurh";
        case BodyPart::KIDNEY:  return "Buur";
        case BodyPart::BLADDER: return "Davsag";
        case BodyPart::TAIL:    return "Suul";
        case BodyPart::SHIN:    return "Shilbe";
        case BodyPart::PAW:     return "Sarvuu";
        default:                return "?";
    }
}


struct Shagai {
    float    x, y, z;
    float    r, g, b;
    bool     active    = true;
    BodyPart part      = BodyPart::SPINE;
    uint8_t  group_idx = 0;
    float    rot_y     = 0.f;
};


struct Player {
    char  name[32];
    int   inventory;
    float col[3];
};


struct RemovedEntry { size_t shagai_idx; int player; };


enum class Phase  { IDLE, ROLLING, SELECTING, RETURNING, GAME_OVER };
enum class Screen { MAIN_MENU, PLAYER_SELECT, SCORE_VIEW, GAME, BERH4_GAME };

struct GameState {
    Phase    phase        = Phase::IDLE;
    int      dice         = 0;
    int      take_count   = 0;
    int      return_count = 0;
    int      remaining    = 0;
    int      total        = 0;
    int      winner       = -1;
    int      winning_score = 0;
    bool     first_roll   = true;
    char     msg[512]     = {};
    std::vector<BodyPart> valid_targets;
};


struct DiceAnim {
    bool rolling = false;
    int  frame   = 0;
    int  total   = 28;
    int  final_v = 0;
    int  show_v  = 0;
};


enum class ButtonAction {
    PLAY, SCORE, RESET, EXIT, BACK,
    PLAYERS_2, PLAYERS_3, PLAYERS_4,
    BERH4
};

struct UiButton {
    float x, y, w, h;
    const char* label;
    ButtonAction action;
};


struct Vec3 { float x, y, z; };

#endif