#ifndef AM_BOARD_H
#define AM_BOARD_H

#include "state.h"

void loadShagai(const char* path);
void buildLayout();

int  count_active(BodyPart p);
int  count_active_group(BodyPart part, int group);
int  available_shin_group();
int  available_paw_group();
int  available_ear_group();

int  removed_owner(size_t shagai_idx);
int  count_removed_part(BodyPart part);
int  count_removed_group(BodyPart part, int group);

#endif