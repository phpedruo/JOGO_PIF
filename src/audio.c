#include "audio.h"
#include "raylib.h"
#include <stdlib.h>
#include <time.h>

// Liste aqui todos os arquivos da sua playlist
static const char* tracks[] = {
    "musicGame/01.mp3",
    "musicGame/02.mp3",
    "musicGame/03.mp3",
    "musicGame/04.mp3",
    "musicGame/05.mp3",
    "musicGame/06.mp3",
    "musicGame/07.mp3",
    "musicGame/08.mp3",
    "musicGame/09.mp3",
    "musicGame/10.mp3",
    "musicGame/11.mp3",
    "musicGame/12.mp3",
    "musicGame/13.mp3",
    "musicGame/14.mp3",
    "musicGame/15.mp3",
    "musicGame/16.mp3",
    "musicGame/17.mp3",
    "musicGame/18.mp3", 
    "musicGame/19.mp3",      
};

#define TRACK_COUNT (sizeof(tracks) / sizeof(tracks[0]))

static Music currentMusic;
static int   currentTrack = -1;

static void PlayRandomTrack(void) {
    // Para a música atual se estiver tocando
    if (currentTrack >= 0)
        UnloadMusicStream(currentMusic);

    // Escolhe uma diferente da atual
    int next;
    do {
        next = rand() % TRACK_COUNT;
    } while (next == currentTrack && TRACK_COUNT > 1);

    currentTrack  = next;
    currentMusic  = LoadMusicStream(tracks[currentTrack]);
    PlayMusicStream(currentMusic);
}

void InitAudio_Game(void) {
    InitAudioDevice();
    srand((unsigned int)time(NULL));  // seed aleatória
    PlayRandomTrack();
}

void UpdateAudio(void) {
    // Necessário chamar todo frame para manter o stream
    UpdateMusicStream(currentMusic);

    // Quando a música terminar, toca outra aleatória
    if (!IsMusicStreamPlaying(currentMusic))
        PlayRandomTrack();
}

void UnloadAudio_Game(void) {
    UnloadMusicStream(currentMusic);
    CloseAudioDevice();
}