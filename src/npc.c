#include "npc.h"
#include "raylib.h"
#include <stdlib.h>
#include <math.h>

// Deve bater com o main.c
#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720

NPC npcs[MAX_NPCS];
Texture2D npcSprites[NPC_SPRITE_COUNT];

static float lanes[] = { -300.0f, -150.0f, 0.0f, 150.0f, 300.0f };
#define LANE_COUNT 5

void InitNPCs(void) {
    npcSprites[0] = LoadTexture("assets/sprites/npc_green.png");
    npcSprites[1] = LoadTexture("assets/sprites/npc_black.png");

    for (int i = 0; i < MAX_NPCS; i++) {
        npcs[i].active    = true;
        npcs[i].roadPos   = (float)(i * 15);
        npcs[i].laneX     = lanes[i % LANE_COUNT];
        npcs[i].speed     = 0.5f + (float)(rand() % 10) * 0.1f;
        npcs[i].spriteIdx = i % NPC_SPRITE_COUNT;
    }
}

void UpdateNPCs(float playerRoadPos, float playerSpeed) {
    for (int i = 0; i < MAX_NPCS; i++) {
        if (!npcs[i].active) continue;

        npcs[i].roadPos += npcs[i].speed * 0.005f;

        float diff = npcs[i].roadPos - playerRoadPos;
        if (diff < -5.0f || diff > 80.0f) {
            npcs[i].roadPos   = playerRoadPos + 20.0f + (float)(rand() % 40);
            npcs[i].laneX     = lanes[rand() % LANE_COUNT];
            npcs[i].spriteIdx = rand() % NPC_SPRITE_COUNT;
        }
    }
}

void DrawNPCs(float playerRoadPos, float camX) {
    for (int i = 0; i < MAX_NPCS; i++) {
        if (!npcs[i].active) continue;

        float diff = npcs[i].roadPos - playerRoadPos;
        if (diff < 1.0f || diff > 60.0f) continue;

        float t     = 1.0f - (diff / 60.0f);  // 0=longe, 1=perto
        float scale = t * 2.5f;
        if (scale < 0.1f) continue;

        Texture2D tex = npcSprites[npcs[i].spriteIdx];
        float w = tex.width  * scale;
        float h = tex.height * scale;

        // Posição horizontal — centralizado na pista
        float screenX = SCREEN_WIDTH / 2
                      + (npcs[i].laneX - camX) * t * 0.4f;

        // Posição vertical — alinha com o chão da pista
        float screenY = SCREEN_HEIGHT * 0.58f + t * (SCREEN_HEIGHT * 0.22f);

        DrawTexturePro(
            tex,
            (Rectangle){ 0, 0, tex.width, tex.height },
            (Rectangle){ screenX, screenY, w, h },
            (Vector2){ w / 2, h },
            0.0f,
            WHITE
        );
    }
}

void UnloadNPCs(void) {
    for (int i = 0; i < NPC_SPRITE_COUNT; i++)
        UnloadTexture(npcSprites[i]);
}