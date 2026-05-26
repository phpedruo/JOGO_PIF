#include "road.h"

Segment road[ROAD_LENGTH];

float roadPosition = 0;

float Lerp(float a, float b, float t) {

    return a + (b - a) * t;
}

void InitRoad(void) {

    for (int i = 0; i < ROAD_LENGTH; i++) {

        road[i].curve = 0;
    }

    // =========================
    // CURVA DIREITA
    // =========================

    for (int i = 300; i < 700; i++) {

        float t =
            (float)(i - 300) /
            (700 - 300);

        road[i].curve =
            Lerp(0, 0.8f, t);
    }

    // =========================
    // CURVA ESQUERDA
    // =========================

    for (int i = 900; i < 1300; i++) {

        float t =
            (float)(i - 900) /
            (1300 - 900);

        road[i].curve =
            Lerp(0, -0.8f, t);
    }
}


void DrawRoad(void) {

    int horizon = 250;

    // desenha do horizonte até baixo
    for (int y = horizon; y < SCREEN_HEIGHT; y++) {

        // profundidade da scanline
        float perspective =
            (float)(y - horizon) /
            (SCREEN_HEIGHT - horizon);

        // segmento da pista
        int segment =
            (((int)(-roadPosition * 0.3f) + y)
            + ROAD_LENGTH)
            % ROAD_LENGTH;

        // =========================
        // CURVA DA PISTA
        // =========================

        float curve =
            road[segment].curve;

        // deslocamento da pista
        float offset =
            curve *
            perspective *
            600;

        // centro da pista
        float roadCenter =
            SCREEN_WIDTH / 2
            + offset;

        // largura da pista
        float roadWidth =
            300 +
            perspective * 700;

        // =========================
        // CORES
        // =========================

        Color grassColor;
        Color roadColor;

        if ((segment / 8) % 2 == 0) {

            grassColor = DARKGREEN;
            roadColor = DARKGRAY;

        } else {

            grassColor = GREEN;
            roadColor = GRAY;
        }

        // =========================
        // GRAMA
        // =========================

        DrawRectangle(
            0,
            y,
            SCREEN_WIDTH,
            1,
            grassColor
        );

        // =========================
        // PISTA
        // =========================

        DrawRectangle(
            roadCenter - roadWidth / 2,
            y,
            roadWidth,
            1,
            roadColor
        );

        // =========================
        // FAIXA CENTRAL
        // =========================

        if ((segment / 64) % 2 == 0) {

            DrawRectangle(
                roadCenter - 5,
                y,
                10,
                1,
                YELLOW
            );
        }
    }
}