#include "npc.h"
#include "raylib.h"
#include <stdlib.h>
#include <math.h>

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

NPC npcs[MAX_NPCS];
Texture2D npcSprites[NPC_SPRITE_COUNT];

// Faixas disponíveis na pista
static float lanes[] = { -300.0f, -150.0f, 0.0f, 150.0f, 300.0f };
#define LANE_COUNT 5

void InitNPCs(void) {
    npcSprites[0] = LoadTexture("assets/sprites/npc_green.png");
    npcSprites[1] = LoadTexture("assets/sprites/npc_black.png");

    for (int i = 0; i < MAX_NPCS; i++) {
        npcs[i].active    = true;
        npcs[i].roadPos   = (float)(i * 15);           // espaçados na pista
        npcs[i].laneX     = lanes[i % LANE_COUNT];
        npcs[i].speed     = 0.5f + (float)(rand() % 10) * 0.1f;
        npcs[i].spriteIdx = i % NPC_SPRITE_COUNT;
    }
}

void UpdateNPCs(float playerRoadPos, float playerSpeed) {
    for (int i = 0; i < MAX_NPCS; i++) {
        if (!npcs[i].active) continue;

        // NPCs andam mais devagar que o player
        npcs[i].roadPos += npcs[i].speed * 0.005f;

        // Se ficou muito para trás, reposiciona à frente
        float diff = npcs[i].roadPos - playerRoadPos;
        if (diff < -20.0f || diff > 80.0f) {
            npcs[i].roadPos   = playerRoadPos + 20.0f + (float)(rand() % 40);
            npcs[i].laneX     = lanes[rand() % LANE_COUNT];
            npcs[i].spriteIdx = rand() % NPC_SPRITE_COUNT;
        }
    }
}

void DrawNPCs(float playerRoadPos, float cameraX) {
    for (int i = 0; i < MAX_NPCS; i++) {
        if (!npcs[i].active) continue;

        float diff = npcs[i].roadPos - playerRoadPos;

        // Só desenha se estiver à frente do player
        if (diff < 1.0f || diff > 60.0f) continue;

        // Perspectiva simples: quanto mais longe, menor e mais alto
        float t       = 1.0f - (diff / 60.0f);   // 0 = longe, 1 = perto
        float scale   = t * 2.5f;
        if (scale < 0.1f) continue;

        Texture2D tex = npcSprites[npcs[i].spriteIdx];
        float w = tex.width  * scale;
        float h = tex.height * scale;

        // Posição na tela
        float screenX = SCREEN_WIDTH / 2
                      + (npcs[i].laneX - cameraX) * t * 0.5f;
        float screenY = SCREEN_HEIGHT * 0.75f - (t * SCREEN_HEIGHT * 0.25f) + h;

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