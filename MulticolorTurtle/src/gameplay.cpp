#include "gameplay.h"
#include "4berh.h"
#include "sound.h"
#include <GL/freeglut.h>
#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>

bool is_return_candidate(size_t idx)
{
    if (idx>=g_shagai.size() || g_shagai[idx].active || removed_owner(idx)!=g_current_player)
        return false;

    const Shagai& s=g_shagai[idx];
    switch (gs.dice) {
        case 1:
            return s.part==BodyPart::HEART || s.part==BodyPart::BLADDER;
        case 2:
            return (s.part==BodyPart::EYE || s.part==BodyPart::EAR || s.part==BodyPart::KIDNEY)
                   && count_removed_part(s.part)>=2;
        case 3:
            return (s.part==BodyPart::TAIL && count_removed_part(BodyPart::TAIL)>=3) ||
                   (s.part==BodyPart::HEAD && count_removed_part(BodyPart::HEAD)>=3);
        case 4:
            return s.part==BodyPart::SHIN && count_removed_group(BodyPart::SHIN,s.group_idx)>=4;
        case 5:
            return s.part==BodyPart::PAW  && count_removed_group(BodyPart::PAW, s.group_idx)>=5;
        case 6:
            return (s.part==BodyPart::NECK || s.part==BodyPart::SPINE)
                   && count_removed_part(s.part)>=6;
    }
    return false;
}

bool has_return_candidate()
{
    for (size_t i=0;i<g_shagai.size();++i)
        if (is_return_candidate(i)) return true;
    return false;
}

void set_msg(const char* fmt,...)
{
    va_list ap; va_start(ap,fmt);
    vsnprintf(gs.msg,sizeof(gs.msg),fmt,ap);
    va_end(ap);
}

void determine_winner()
{
    int best=-1, winner=-1;
    for (int i=0;i<g_num_players;++i)
        if (g_players[i].inventory>best) { best=g_players[i].inventory; winner=i; }
    gs.winner        = winner;
    gs.winning_score = best;
    set_msg("%s yallaa. Onoo: %d", g_players[winner].name, best);
}

void end_turn()
{
    gs.valid_targets.clear();
    gs.dice         = 0;
    gs.return_count = 0;
    if (gs.phase != Phase::GAME_OVER) {
        gs.phase        = Phase::IDLE;
        g_current_player = (g_current_player+1) % g_num_players;
    }
}

void execute_take(BodyPart target, int chosen_group)
{
    int taken=0;
    auto take_piece = [&](Shagai& s) {
        if (!s.active) return;
        s.active = false;
        g_removed.push_back({(size_t)(&s - g_shagai.data()), g_current_player});
        --gs.remaining;
        ++g_players[g_current_player].inventory;
        ++taken;
    };

    if (target==BodyPart::SHIN) {
        int grp=(chosen_group>=0 && count_active_group(BodyPart::SHIN,chosen_group)==4)
              ? chosen_group : available_shin_group();
        if (grp<0) return;
        for (auto& s:g_shagai) if(s.part==BodyPart::SHIN&&s.group_idx==(uint8_t)grp) take_piece(s);
    } else if (target==BodyPart::PAW) {
        int grp=(chosen_group>=0 && count_active_group(BodyPart::PAW,chosen_group)==5)
              ? chosen_group : available_paw_group();
        if (grp<0) return;
        for (auto& s:g_shagai) if(s.part==BodyPart::PAW&&s.group_idx==(uint8_t)grp) take_piece(s);
    } else {
        int need=gs.take_count;
        for (auto& s:g_shagai) if(s.part==target&&s.active&&need>0) { take_piece(s); --need; }
    }

    if (gs.remaining==0) {
        gs.phase = Phase::GAME_OVER;
        determine_winner();
    } else {
        set_msg("%s %s hesgees %d avlaa. Daraagiin: %s",
                g_players[g_current_player].name, part_name(target), taken,
                g_players[(g_current_player+1)%g_num_players].name);
        end_turn();
    }
    glutPostRedisplay();
}

bool restore_piece(size_t idx)
{
    if (idx>=g_shagai.size() || g_shagai[idx].active) return false;
    for (int i=(int)g_removed.size()-1;i>=0;--i) {
        if (g_removed[i].shagai_idx==idx && g_removed[i].player==g_current_player) {
            g_shagai[idx].active = true;
            ++gs.remaining;
            --g_players[g_current_player].inventory;
            g_removed.erase(g_removed.begin()+i);
            return true;
        }
    }
    return false;
}

int restore_removed_part(BodyPart part, int need, size_t first_idx)
{
    int restored=0;
    if (first_idx<g_shagai.size() && g_shagai[first_idx].part==part)
        restored += restore_piece(first_idx) ? 1 : 0;
    for (size_t i=0;i<g_shagai.size()&&restored<need;++i) {
        if (i==first_idx) continue;
        if (!g_shagai[i].active && g_shagai[i].part==part && removed_owner(i)==g_current_player)
            restored += restore_piece(i) ? 1 : 0;
    }
    return restored;
}

int restore_removed_group(BodyPart part, int group, int need)
{
    int restored=0;
    for (size_t i=0;i<g_shagai.size()&&restored<need;++i) {
        const Shagai& s=g_shagai[i];
        if (!s.active && s.part==part && s.group_idx==(uint8_t)group && removed_owner(i)==g_current_player)
            restored += restore_piece(i) ? 1 : 0;
    }
    return restored;
}

void choose_return_piece(size_t idx)
{
    if (gs.phase!=Phase::RETURNING || !is_return_candidate(idx)) return;

    const Shagai picked=g_shagai[idx];
    int restored=0;
    switch (gs.dice) {
        case 1: restored=restore_removed_part(picked.part,1,idx); break;
        case 2: restored=restore_removed_part(picked.part,2,idx); break;
        case 3: restored=restore_removed_part(picked.part,3,idx); break;
        case 4: restored=restore_removed_group(BodyPart::SHIN,picked.group_idx,4); break;
        case 5: restored=restore_removed_group(BodyPart::PAW, picked.group_idx,5); break;
        case 6: restored=restore_removed_part(picked.part,6,idx); break;
    }
    set_msg("%s %s hesgees %d butsaalaa. Daraagiin: %s",
            g_players[g_current_player].name, part_name(picked.part), restored,
            g_players[(g_current_player+1)%g_num_players].name);
    end_turn();
    glutPostRedisplay();
}

void start_penalty_return(int n)
{
    if (g_players[g_current_player].inventory<=0) {
        set_msg("%s butsaah zuilgui. Daraagiin: %s",
                g_players[g_current_player].name,
                g_players[(g_current_player+1)%g_num_players].name);
        end_turn();
        glutPostRedisplay();
        return;
    }
    gs.phase        = Phase::RETURNING;
    gs.return_count = n;
    if (!has_return_candidate()) {
        set_msg("%s-d tohiroh heseg alga. Daraagiin: %s",
                g_players[g_current_player].name,
                g_players[(g_current_player+1)%g_num_players].name);
        end_turn();
        glutPostRedisplay();
        return;
    }
    set_msg("%s %d buulgalaa. Tohiroh hesgiig butsaa.",
            g_players[g_current_player].name, n);
    glutPostRedisplay();
}

void apply_roll(int roll)
{
    gs.take_count = roll;
    gs.valid_targets.clear();

    switch (roll) {
        case 1:
            if (count_active(BodyPart::HEART)   >=1) gs.valid_targets.push_back(BodyPart::HEART);
            if (count_active(BodyPart::BLADDER) >=1) gs.valid_targets.push_back(BodyPart::BLADDER);
            break;
        case 2:
            if (count_active(BodyPart::EYE)    ==2) gs.valid_targets.push_back(BodyPart::EYE);
            if (count_active(BodyPart::EAR)    ==2) gs.valid_targets.push_back(BodyPart::EAR);
            if (count_active(BodyPart::KIDNEY) ==2) gs.valid_targets.push_back(BodyPart::KIDNEY);
            break;
        case 3:
            if (count_active(BodyPart::HEAD)==3) gs.valid_targets.push_back(BodyPart::HEAD);
            if (count_active(BodyPart::TAIL)==3) gs.valid_targets.push_back(BodyPart::TAIL);
            break;
        case 4:
            if (available_shin_group()>=0) gs.valid_targets.push_back(BodyPart::SHIN);
            break;
        case 5:
            if (available_paw_group()>=0) gs.valid_targets.push_back(BodyPart::PAW);
            break;
        case 6:
            if (count_active(BodyPart::NECK) >=6) gs.valid_targets.push_back(BodyPart::NECK);
            if (count_active(BodyPart::SPINE)>=6) gs.valid_targets.push_back(BodyPart::SPINE);
            break;
    }

    if (gs.valid_targets.empty()) {
        start_penalty_return(roll);
        return;
    }
    gs.phase = Phase::SELECTING;
    char buf[512]={};
    int pos=snprintf(buf,sizeof(buf),"%s %d buulgalaa: ",
                     g_players[g_current_player].name, roll);
    for (int i=0;i<(int)gs.valid_targets.size()&&pos<480;++i) {
        BodyPart p=gs.valid_targets[i];
        pos+=snprintf(buf+pos,sizeof(buf)-pos,"[%d] %s(%d)  ",i+1,part_name(p),count_active(p));
    }
    set_msg("%s",buf);
    glutPostRedisplay();
}

void processTurn()
{
    if (gs.phase!=Phase::IDLE || g_dice.rolling) return;
    gs.first_roll = false;

    g_dice.final_v = (rand()%6)+1;
    g_dice.frame   = 0;
    g_dice.show_v  = 0;
    g_dice.rolling = true;
    gs.phase       = Phase::ROLLING;
    sound_play_dice();

    set_msg("%s shoo hayaj baina...", g_players[g_current_player].name);
    glutPostRedisplay();
}

void reset_game()
{
    for (auto& s:g_shagai) s.active=true;
    g_removed.clear();
    for (int i=0;i<4;++i) g_players[i].inventory=0;
    gs.remaining = gs.total;
    gs.valid_targets.clear();
    gs.dice=gs.take_count=gs.return_count=0;
    gs.winner=-1;
    gs.winning_score=0;
    gs.phase      = Phase::IDLE;
    gs.first_roll = true;
    g_current_player = 0;
    g_dice = {};
    set_msg("Shine togloom. %d toglogch.", g_num_players);
    glutPostRedisplay();
}

void start_game_with_players(int players)
{
    g_num_players = players;
    reset_game();
    g_screen = Screen::GAME;
    set_msg("%d toglogch. %s ehelne.", g_num_players, g_players[g_current_player].name);
    glutPostRedisplay();
}

void handle_button_action(ButtonAction action)
{
    switch (action) {
        case ButtonAction::PLAY:      g_screen = Screen::PLAYER_SELECT; break;
        case ButtonAction::SCORE:     g_screen = Screen::SCORE_VIEW;    break;
        case ButtonAction::EXIT:      glutLeaveMainLoop();               break;
        case ButtonAction::BACK:      g_screen = Screen::MAIN_MENU;     break;
        case ButtonAction::RESET:
            reset_game();
            g_screen = Screen::MAIN_MENU;
            set_msg("Shine togloom ehlehed Togloh darna uu.");
            break;
        case ButtonAction::PLAYERS_2: start_game_with_players(2); break;
        case ButtonAction::PLAYERS_3: start_game_with_players(3); break;
        case ButtonAction::PLAYERS_4: start_game_with_players(4); break;
        case ButtonAction::BERH4:
            berh4::init();
            g_screen = Screen::BERH4_GAME;
            break;
    }
    glutPostRedisplay();
}

bool handle_ui_click(int x, int y)
{
    int H=glutGet(GLUT_WINDOW_HEIGHT);
    float gx=(float)x, gy=(float)(H-y);
    for (const auto& b:g_buttons) {
        if (gx>=b.x && gx<=b.x+b.w && gy>=b.y && gy<=b.y+b.h) {
            sound_play_button();
            handle_button_action(b.action);
            return true;
        }
    }
    return false;
}
