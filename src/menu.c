
#include "menu.h"

#include "raylib.h"
#include "game.h"

#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720

static Texture2D menuBackground;

static Rectangle botaoJogar;
static Rectangle botaoTop10;
static Rectangle botaoSair;

void Menu_Init(void)
{
	menuBackground = LoadTexture("assets/menu.png");

	// Coordenadas alinhadas com o menu.png (cantos: sup-esq e inf-dir)
	// Jogar:     (457,306) -> (822,411)
	// Top rank:  (457,432) -> (822,532)
	// Sair:      (457,556) -> (822,658)
	botaoJogar = (Rectangle){ 457, 306, 822 - 457, 411 - 306 };
	botaoTop10 = (Rectangle){ 457, 432, 822 - 457, 532 - 432 };
	botaoSair  = (Rectangle){ 457, 556, 822 - 457, 658 - 556 };
}

void Menu_Unload(void)
{
	UnloadTexture(menuBackground);
}

MenuAction Menu_Update(GameScreen* telaAtual)
{
	MenuAction action = { 0 };

	Vector2 mouse = GetMousePosition();

	bool hoverJogar = CheckCollisionPointRec(mouse, botaoJogar);
	bool hoverTop10 = CheckCollisionPointRec(mouse, botaoTop10);
	bool hoverSair  = CheckCollisionPointRec(mouse, botaoSair);

	if (hoverJogar && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		action.startGame = true;
		*telaAtual = JOGO;
	}

	if (hoverTop10 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		InitGame(); // recarrega highscores
		*telaAtual = TOP10;
	}

	if (hoverSair && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		action.requestExit = true;
	}

	return action;
}

void Menu_Draw(void)
{
	Vector2 mouse = GetMousePosition();

	bool hoverJogar = CheckCollisionPointRec(mouse, botaoJogar);
	bool hoverTop10 = CheckCollisionPointRec(mouse, botaoTop10);
	bool hoverSair  = CheckCollisionPointRec(mouse, botaoSair);

	DrawTexture(menuBackground, 0, 0, WHITE);

	if (hoverJogar) DrawRectangleLinesEx(botaoJogar, 4, GREEN);
	if (hoverTop10) DrawRectangleLinesEx(botaoTop10, 4, YELLOW);
	if (hoverSair)  DrawRectangleLinesEx(botaoSair, 4, RED);
}

void Top10_Update(GameScreen* telaAtual)
{
	if (IsKeyPressed(KEY_ESCAPE))
		*telaAtual = MENU;
}

void Top10_Draw(void)
{
	DrawText("TOP 10", SCREEN_WIDTH / 2 - 70, 80, 60, GOLD);

	if (gameState.scoreCount == 0)
	{
		DrawText("Nenhuma pontuacao ainda", SCREEN_WIDTH / 2 - 160, 170, 22, LIGHTGRAY);
	}
	else
	{
		for (int i = 0; i < gameState.scoreCount && i < MAX_SCORES; i++)
		{
			Color c = (i == 0) ? GOLD :
					  (i == 1) ? LIGHTGRAY :
					  (i == 2) ? ORANGE : RAYWHITE;

			DrawText(TextFormat("%2d. %-14s %d",
								i + 1,
								gameState.highscores[i].name,
								gameState.highscores[i].score),
					 SCREEN_WIDTH / 2 - 220,
					 180 + i * 36,
					 24,
					 c);
		}
	}

	DrawText("ESC PARA VOLTAR", SCREEN_WIDTH / 2 - 140, SCREEN_HEIGHT - 80, 28, LIGHTGRAY);
}
