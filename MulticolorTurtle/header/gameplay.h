#ifndef AM_GAMEPLAY_H
#define AM_GAMEPLAY_H

#include "board.h"

bool is_return_candidate(size_t idx);
bool has_return_candidate();

void set_msg(const char* fmt, ...);

void determine_winner();
void end_turn();
void execute_take(BodyPart target, int chosen_group = -1);
void apply_roll(int roll);
void processTurn();

bool restore_piece(size_t idx);
int  restore_removed_part(BodyPart part, int need, size_t first_idx);
int  restore_removed_group(BodyPart part, int group, int need);
void choose_return_piece(size_t idx);
void start_penalty_return(int n);

void reset_game();
void start_game_with_players(int players);

void handle_button_action(ButtonAction action);
bool handle_ui_click(int x, int y);

#endif