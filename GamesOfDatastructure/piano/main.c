#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <stdio.h>

int play_audio(const char *file_name) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 0;
    }

    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "Mix_OpenAudio failed: %s\n", Mix_GetError());
        SDL_Quit();
        return 0;
    }

    // Load the audio file
    Mix_Music *music = Mix_LoadMUS(file_name);
    if (!music) {
        fprintf(stderr, "Mix_LoadMUS failed: %s\n", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return 0;
    }

    // Play the audio
    if (Mix_PlayMusic(music, 1) < 0) { // 1 = play once
        fprintf(stderr, "Mix_PlayMusic failed: %s\n", Mix_GetError());
        Mix_FreeMusic(music);
        Mix_CloseAudio();
        SDL_Quit();
        return 0;
    }

    // Wait until playback finishes
    while (Mix_PlayingMusic()) {
        SDL_Delay(100); // Avoid CPU overuse
    }

    // Cleanup
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_Quit();
    return 1;
}

int main(void) {
    const char *file_name = "/home/munkhpurev/Desktop/My games of data structure/piano/sounds/A5.wav"; // Replace with your audio file
    if (play_audio(file_name)) {
        printf("Played %s successfully!\n", file_name);
    } else {
        printf("Failed to play %s\n", file_name);
    }
    return 0;
}