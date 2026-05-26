#ifndef ROAD_H
#define ROAD_H

#include "raylib.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define ROAD_LENGTH 2000

typedef struct {

    float curve;

} Segment;

extern Segment road[ROAD_LENGTH];

extern float roadPosition;

void InitRoad(void);

void DrawRoad(void);

#endif