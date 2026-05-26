#include "player.h"
#include "road.h"

Player player;

void InitPlayer(void) {

    player.x = 0;
    player.speed = 0;

    player.texture =
        LoadTexture("assets/sprites/player.png");
}

void UpdatePlayer(void) {

    // =========================
    // ACELERAÇÃO
    // =========================

    if (IsKeyDown(KEY_UP)) {

        player.speed += 0.25f;
    }

    // =========================
    // FREIO
    // =========================

    if (IsKeyDown(KEY_DOWN)) {

        player.speed -= 0.35f;
    }

    // =========================
    // ATRITO NATURAL
    // =========================

    player.speed *= 0.992f;

    // =========================
    // LIMITES
    // =========================

    if (player.speed < 0)
        player.speed = 0;

    if (player.speed > 80)
        player.speed = 80;

    // =========================
    // DIREÇÃO
    // =========================

    float steerStrength =
        2.0f + player.speed * 0.03f;

    if (IsKeyDown(KEY_LEFT))
        player.x -= steerStrength;

    if (IsKeyDown(KEY_RIGHT))
        player.x += steerStrength;

    // =========================
    // LIMITE DA PISTA
    // =========================

    if (player.x < -400)
        player.x = -400;

    if (player.x > 400)
        player.x = 400;

    // =========================
    // MOVIMENTO DA PISTA
    // =========================

    roadPosition += player.speed;

    int segment =
        (((int)(-roadPosition * 0.3f))
        + ROAD_LENGTH)
        % ROAD_LENGTH;

    player.x +=
        road[segment].curve
        * player.speed
        * 0.02f;
}

void DrawPlayer(void) {

    float scale = 2.0f;

    float width =
        player.texture.width * scale;

    float height =
        player.texture.height * scale;

    DrawTexturePro(

        player.texture,

        (Rectangle){
            0,
            0,
            player.texture.width,
            player.texture.height
        },

        (Rectangle){
            SCREEN_WIDTH / 2 + player.x,
            SCREEN_HEIGHT - 70,
            width,
            height
        },

        (Vector2){
            width / 2,
            height / 2
        },

        0,
        WHITE
    );
}

void UnloadPlayer(void) {

    UnloadTexture(player.texture);
}