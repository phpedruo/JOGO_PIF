#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#define MAX_SCORES  10
#define SCORE_FILE  "scores.txt"

typedef struct {
    char name[32];
    int  score;
} ScoreEntry;

typedef struct {
    int   lives;
    int   score;
    float scoreTimer;
    bool  gameOver;
    // entrada de nome
    bool  enteringName;
    bool  scoreSaved;
    char  playerName[32];
    int   nameLen;
    // highscores
    ScoreEntry highscores[MAX_SCORES];
    int        scoreCount;
} GameState;

extern GameState gameState;

void InitGame(void);
void UpdateGame(float playerSpeed);
void DrawHUD(void);

#endif