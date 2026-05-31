#ifndef MENU_H
#define MENU_H

#include <stdbool.h>

typedef enum
{
	MENU = 0,
	JOGO,
	TOP10
} GameScreen;

typedef struct {
	bool startGame;
	bool requestExit;
} MenuAction;

void Menu_Init(void);
void Menu_Unload(void);

MenuAction Menu_Update(GameScreen* telaAtual);
void Menu_Draw(void);

void Top10_Update(GameScreen* telaAtual);
void Top10_Draw(void);

#endif
