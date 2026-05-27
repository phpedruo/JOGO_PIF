#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
extern float playerX;

typedef struct {

    float x;
    float speed;

    Texture2D texture;

    float hitboxWidth;
    float hitboxHeight;

    bool onGrass;
    float hitTimer;

} Player;

extern Player player;

void InitPlayer(void);

void UpdatePlayer(void);

void DrawPlayer(void);

void UnloadPlayer(void);

Rectangle GetPlayerHitbox();
bool CheckPlayerOnGrass();

#endif