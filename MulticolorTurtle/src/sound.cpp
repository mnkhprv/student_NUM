#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include "sound.h"
#include <stdio.h>

static ma_engine g_engine;

void sound_init()
{
    if (ma_engine_init(NULL, &g_engine) != MA_SUCCESS)
        printf("sound: failed to init engine\n");
}

void sound_play_dice()
{
    ma_engine_play_sound(&g_engine, "dice.mp3", NULL);
}

void sound_play_button()
{
    ma_engine_play_sound(&g_engine, "button.mp3", NULL);
}
