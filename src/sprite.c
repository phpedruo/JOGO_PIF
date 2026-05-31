#include "sprite.h"
#include "road.h"
#include "raylib.h"
#include <math.h>
#include <stdio.h>

#define MAX_SPRITE_TYPES  16
#define OBJECTS_PER_SIDE  (TRACK_LENGTH * 10)

typedef struct {
    Texture2D tex;
    float     sizeScale;
    float     offset;
} SpriteType;

static SpriteType spriteTypes[MAX_SPRITE_TYPES];
static int spriteTypeCount   = 0;
static int idxTunnelWall     = -1;
static int idxTunnelLamp     = -1;
static int idxTunnelEntrance = -1;
static int idxCityLamp       = -1;
static int idxCityBillboard  = -1;
static int idxBuilding1      = -1;
static int idxBuilding2      = -1;
static int idxBuilding3      = -1;
static int idxPlaca          = -1;

typedef struct { int typeIdx; } SideObject;

static SideObject leftObjects[OBJECTS_PER_SIDE];
static SideObject rightObjects[OBJECTS_PER_SIDE];

static int AddSpriteType(const char *path, float sizeScale, float offset) {
    if (spriteTypeCount >= MAX_SPRITE_TYPES) return -1;
    int idx = spriteTypeCount++;
    spriteTypes[idx].tex       = LoadTexture(path);
    spriteTypes[idx].sizeScale = sizeScale;
    spriteTypes[idx].offset    = offset;
    return idx;
}

void InitSprites(void) {
    /* --- sprites rurais --- */
    int idxTree     = AddSpriteType("assets/sprites/tree.png",       2.0f, 0.3f);
    int idxBush     = AddSpriteType("assets/sprites/bush.png",       0.8f, 0.1f);
    int idxRock     = AddSpriteType("assets/sprites/rock_sml.png",   0.6f, 0.0f);
    int idxBirch    = AddSpriteType("assets/sprites/Birch1.png",     2.0f, 0.3f);
    int idxMaple    = AddSpriteType("assets/sprites/Maple7.png",     2.0f, 0.3f);
    int idxBanco    = AddSpriteType("assets/sprites/banquinho.png",  0.8f, 0.0f);
    int idxArbusto  = AddSpriteType("assets/sprites/arbusto.png",    0.8f, 0.0f);
    int idxCogumelo = AddSpriteType("assets/sprites/cogumelo.png",   0.5f, 0.0f);
    int idxTronco   = AddSpriteType("assets/sprites/tronco.png",     0.5f, 0.0f);

    /* --- sprites do túnel --- */
    idxTunnelWall     = AddSpriteType("assets/sprites/tunnel_wall.png",          0.8f, 0.0f);
    idxTunnelLamp     = AddSpriteType("assets/sprites/tunnel_lamp.png",          0.5f, 0.0f);
    idxTunnelEntrance = AddSpriteType("assets/sprites/tunnel_entrance_clean.png",3.0f, 0.0f);

    /* --- sprites da cidade --- */
    idxCityLamp      = AddSpriteType("assets/sprites/poste.png",     0.8f, 0.2f);
    // idxCityBillboard = AddSpriteType("assets/sprites/placa.png", 0.8f, 0.3f);
    idxBuilding1     = AddSpriteType("assets/sprites/predio1.png",   1.2f, 0.5f);
    idxBuilding2     = AddSpriteType("assets/sprites/predio2.png",   1.2f, 0.5f);
    idxBuilding3     = AddSpriteType("assets/sprites/predio3.png",   1.2f, 0.5f);
    idxPlaca         = AddSpriteType("assets/sprites/placa.png",     0.8f, 0.1f);

    /* inicializa tudo vazio */
    for (int i = 0; i < OBJECTS_PER_SIDE; i++) {
        leftObjects[i].typeIdx  = -1;
        rightObjects[i].typeIdx = -1;
    }

    /* ----------------------------------------------------------------
       DISTRIBUIÇÃO RURAL — segmentos 0 a 600 (roadPos 0..60)
    ---------------------------------------------------------------- */
    int ruralEnd = 600;

    for (int i = 0; i < ruralEnd; i++) {
        if (GetRandomValue(0, 99) < 12) leftObjects[i].typeIdx  = idxTree;
        if (GetRandomValue(0, 99) < 12) rightObjects[i].typeIdx = idxTree;
    }
    for (int i = 0; i < ruralEnd; i++) {
        if (GetRandomValue(0, 99) < 2) leftObjects[i].typeIdx   = idxRock;
        if (GetRandomValue(0, 99) < 2) rightObjects[i].typeIdx  = idxRock;
    }
    for (int i = 0; i < ruralEnd; i++) {
        if (GetRandomValue(0, 99) < 10) leftObjects[i].typeIdx  = idxBush;
        if (GetRandomValue(0, 99) < 10) rightObjects[i].typeIdx = idxBush;
    }
    for (int i = 0; i < ruralEnd; i++) {
        if (GetRandomValue(0, 99) < 10) leftObjects[i].typeIdx  = idxBirch;
        if (GetRandomValue(0, 99) < 10) rightObjects[i].typeIdx = idxBirch;
    }
    for (int i = 0; i < ruralEnd; i++) {
        if (GetRandomValue(0, 99) < 8) leftObjects[i].typeIdx   = idxMaple;
        if (GetRandomValue(0, 99) < 8) rightObjects[i].typeIdx  = idxMaple;
    }
    for (int i = 0; i < ruralEnd; i++) {
        if (GetRandomValue(0, 99) < 1) leftObjects[i].typeIdx   = idxBanco;
        if (GetRandomValue(0, 99) < 1) rightObjects[i].typeIdx  = idxBanco;
    }
    for (int i = 0; i < ruralEnd; i++) {
        if (GetRandomValue(0, 99) < 6) leftObjects[i].typeIdx   = idxArbusto;
        if (GetRandomValue(0, 99) < 6) rightObjects[i].typeIdx  = idxArbusto;
    }
    for (int i = 0; i < ruralEnd; i++) {
        if (GetRandomValue(0, 99) < 6) leftObjects[i].typeIdx   = idxCogumelo;
        if (GetRandomValue(0, 99) < 6) rightObjects[i].typeIdx  = idxCogumelo;
    }
    for (int i = 0; i < ruralEnd; i++) {
        if (GetRandomValue(0, 99) < 6) leftObjects[i].typeIdx   = idxTronco;
        if (GetRandomValue(0, 99) < 6) rightObjects[i].typeIdx  = idxTronco;
    }

    /* ----------------------------------------------------------------
       DISTRIBUIÇÃO CIDADE — segmentos 1210 a 1810 (roadPos 121..181)
    ---------------------------------------------------------------- */
    int cityStart = 1210;
    int cityEnd   = 1810;

    /* limpa qualquer objeto rural que tenha caído nessa faixa */
    for (int i = cityStart; i < cityEnd && i < OBJECTS_PER_SIDE; i++) {
        leftObjects[i].typeIdx  = -1;
        rightObjects[i].typeIdx = -1;
    }

    /* cooldown para não empilhar objetos */
    int coolL = 0, coolR = 0;
    for (int i = cityStart; i < cityEnd && i < OBJECTS_PER_SIDE; i++) {
        /* lado esquerdo */
        if (coolL > 0) {
            coolL--;
        } else if (GetRandomValue(0, 99) < 25) {
            int r = GetRandomValue(0, 99);
            if (r < 40)       leftObjects[i].typeIdx = idxCityLamp;
            else if (r < 65)  leftObjects[i].typeIdx = idxBuilding1;
            else if (r < 80)  leftObjects[i].typeIdx = idxBuilding2;
            else if (r < 90)  leftObjects[i].typeIdx = idxBuilding3;
            else if (r < 96)  leftObjects[i].typeIdx = idxCityBillboard;
            else              leftObjects[i].typeIdx = idxPlaca;
            coolL = 6;
        }

        /* lado direito */
        if (coolR > 0) {
            coolR--;
        } else if (GetRandomValue(0, 99) < 25) {
            int r = GetRandomValue(0, 99);
            if (r < 40)       rightObjects[i].typeIdx = idxCityLamp;
            else if (r < 65)  rightObjects[i].typeIdx = idxBuilding1;
            else if (r < 80)  rightObjects[i].typeIdx = idxBuilding2;
            else if (r < 90)  rightObjects[i].typeIdx = idxBuilding3;
            else if (r < 96)  rightObjects[i].typeIdx = idxCityBillboard;
            else              rightObjects[i].typeIdx = idxPlaca;
            coolR = 6;
        }
    }

    printf("spriteTypeCount: %d\n", spriteTypeCount);
}

void DrawSprites(void) {
    int sh      = SCREEN_HEIGHT;
    int sw      = SCREEN_WIDTH;
    int horizon = sh / 2 + 35;

    int isTunnel = (currentBiome == BIOME_TUNEL);

    for (int i = 98; i >= 5; i--) {
        float line = (float)i;
        float d    = lineToDistance(line);

        int segmento = (int)floorf(roadPosition * 10.0f) + i;
        int objIdx   = ((segmento % OBJECTS_PER_SIDE) + OBJECTS_PER_SIDE) % OBJECTS_PER_SIDE;

        int   h  = i < 5 ? 5 : (i > 98 ? 98 : i);
        float px = track[h];

        float scale_ms      = 1000.0f / (d * 120.0f);
        float roadHalfWidth = (sw * 0.06f) / d;
        float screenY       = (float)sh - line * (float)(sh - horizon) / 100.0f;
        float scalePx       = scale_ms * ((float)sh / 200.0f);

        /* lâmpadas no teto do túnel */
        if (isTunnel && idxTunnelLamp >= 0 && i % 15 == 0) {
            SpriteType *lamp = &spriteTypes[idxTunnelLamp];
            float w  = (float)lamp->tex.width  * (scalePx / 80.0f) * lamp->sizeScale;
            float h2 = (float)lamp->tex.height * (scalePx / 80.0f) * lamp->sizeScale;
            if (w >= 4.0f) {
                DrawTexturePro(lamp->tex,
                    (Rectangle){ 0, 0, (float)lamp->tex.width, (float)lamp->tex.height },
                    (Rectangle){ px - w / 2.0f, screenY - h2 * 7.0f, w, h2 },
                    (Vector2){ 0, 0 }, 0.0f, WHITE);
            }
        }

        /* lado esquerdo */
        int leftIdx = isTunnel ? idxTunnelWall : leftObjects[objIdx].typeIdx;
        if (leftIdx >= 0) {
            SpriteType *sp = &spriteTypes[leftIdx];
            float w  = (float)sp->tex.width  * (scalePx / 80.0f) * sp->sizeScale;
            float h2 = (float)sp->tex.height * (scalePx / 80.0f) * sp->sizeScale;
            if (w >= 4.0f) {
                float screenX = px - roadHalfWidth - w * sp->offset - w * 0.5f;
                DrawTexturePro(sp->tex,
                    (Rectangle){ 0, 0, (float)sp->tex.width, (float)sp->tex.height },
                    (Rectangle){ screenX - w / 2.0f, screenY - h2, w, h2 },
                    (Vector2){ 0, 0 }, 0.0f, WHITE);
            }
        }

        /* lado direito */
        int rightIdx = isTunnel ? idxTunnelWall : rightObjects[objIdx].typeIdx;
        if (rightIdx >= 0) {
            SpriteType *sp = &spriteTypes[rightIdx];
            float w  = (float)sp->tex.width  * (scalePx / 80.0f) * sp->sizeScale;
            float h2 = (float)sp->tex.height * (scalePx / 80.0f) * sp->sizeScale;
            if (w >= 4.0f) {
                float screenX = px + roadHalfWidth + w * sp->offset + w * 0.5f;
                DrawTexturePro(sp->tex,
                    (Rectangle){ 0, 0, (float)sp->tex.width, (float)sp->tex.height },
                    (Rectangle){ screenX - w / 2.0f, screenY - h2, w, h2 },
                    (Vector2){ 0, 0 }, 0.0f, WHITE);
            }
        }
    }

    /* entrada do túnel — objeto único na posição roadPos=60 */
    if (idxTunnelEntrance >= 0) {
        float d = 60.0f - roadPosition;
        if (d > 0.0f && d < 10.0f) {
            float line = distanceToLine(d);
            if (line >= 5.0f && line <= 99.0f) {
                int h = (int)line;
                if (h < 5) h = 5;
                if (h > 98) h = 98;
                float px       = track[h];
                float scale_ms = 1000.0f / (d * 120.0f);
                float scalePx  = scale_ms * ((float)sh / 200.0f);
                SpriteType *sp = &spriteTypes[idxTunnelEntrance];
                float w  = (float)sp->tex.width  * (scalePx / 80.0f) * sp->sizeScale;
                float h2 = (float)sp->tex.height * (scalePx / 80.0f) * sp->sizeScale;
                float screenY = (float)sh - line * (float)(sh - horizon) / 100.0f;
                if (w >= 4.0f) {
                    DrawTexturePro(sp->tex,
                        (Rectangle){ 0, 0, (float)sp->tex.width, (float)sp->tex.height },
                        (Rectangle){ px - w / 2.0f, screenY - h2, w, h2 },
                        (Vector2){ 0, 0 }, 0.0f, WHITE);
                }
            }
        }
    }
}

void UnloadSprites(void) {
    for (int i = 0; i < spriteTypeCount; i++)
        UnloadTexture(spriteTypes[i].tex);
}