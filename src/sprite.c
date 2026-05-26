#include "sprite.h"
#include "road.h"

RoadSprite tree;

void InitSprites(void) {

    tree.texture =
        LoadTexture("assets/sprites/tree.png");

    tree.x = 1.3f;
    tree.z = 500;
}

void DrawSprites(void) {

    float dz =
        tree.z +
        roadPosition * 0.05f;

    // looping infinito
    while (dz < 0)
        dz += 1000;

    // perspectiva
    float perspective =
        dz / 1000.0f;

    // posição vertical
    float y =
        250 +
        perspective *
        (SCREEN_HEIGHT - 250);

    // largura da pista
    float roadWidth =
        200 +
        perspective * 1000;

    // posição horizontal
    float x =
        SCREEN_WIDTH / 2 +
        roadWidth * tree.x;

    // escala
    float scale =
        0.2f +
        perspective * 1.5f;

    float width =
        tree.texture.width * scale;

    float height =
        tree.texture.height * scale;

    DrawTexturePro(

        tree.texture,

        (Rectangle){
            0,
            0,
            tree.texture.width,
            tree.texture.height
        },

        (Rectangle){
            x,
            y,
            width,
            height
        },

        (Vector2){
            width / 2,
            height
        },

        0,
        WHITE
    );
}

void UnloadSprites(void) {

    UnloadTexture(tree.texture);
}