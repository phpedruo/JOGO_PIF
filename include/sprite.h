#ifndef SPRITE_H
#define SPRITE_H

#include "raylib.h"

typedef struct {

    Texture2D texture;

    float x;
    float z;

} RoadSprite;

void InitSprites(void);

void DrawSprites(void);

void UnloadSprites(void);

#endif