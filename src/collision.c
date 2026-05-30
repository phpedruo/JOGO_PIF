#include "collision.h"
#include "npc.h"
#include "game.h"
#include "player.h"
#include "raylib.h"
#include <stdlib.h>
#include "road.h"

void CheckCollisions(float playerRoadPos) {
    (void)playerRoadPos;
    if (player.hitTimer > 0) return;

    Rectangle playerBox = GetPlayerScreenBox();

    for (NPCNode* node = npcList; node != NULL; node = node->next) {
        if (!node->data.active) continue;
        if (node->data.screenBox.width < 4.0f) continue;

        if (CheckCollisionRecs(playerBox, node->data.screenBox)) {
            gameState.lives--;
            player.hitTimer  = 2.0f;
            player.speed    *= 0.3f;
            if (gameState.lives <= 0)
                gameState.gameOver = true;
            break;
        }
    }
    /* colisão com paredes do túnel */
    if (currentBiome == BIOME_TUNNEL) {
    /* largura da pista na posição do player (linha i=5, mais próxima) */
        float roadHalfWidth = (SCREEN_WIDTH * 0.06f) / lineToDistance(5.0f);
        float roadCenter    = track[5];
        float leftWall      = roadCenter - roadHalfWidth;
        float rightWall     = roadCenter + roadHalfWidth;

        /* limita o playerX para não ultrapassar as paredes */
        if (playerBox.x < leftWall) {
        extern float playerX;
        playerX = -(roadHalfWidth * 0.8f);
        player.speed *= 0.95f;
        }
        if (playerBox.x + playerBox.width > rightWall) {
        extern float playerX;
        playerX = roadHalfWidth * 0.8f;
        player.speed *= 0.95f;
        }
}
}