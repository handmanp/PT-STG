#include "global.h"
#include "game.h"

void ingame_GUI(){

	DrawGraph(0, -20, design_img[0], TRUE);
	DrawGraph(0, 660, design_img[1], TRUE);

	DrawFormatStringToHandle(5, 5, GetColor(122, 122, 122), font_handle[FONT_TI_MENU], "SCORE = %d", score);
	DrawFormatStringToHandle(1100, 5, GetColor(122, 122, 122), font_handle[FONT_TI_MENU], "LEFT = %d", ship.left);

	int length = GetDrawFormatStringWidthToHandle(font_handle[FONT_TI_MENU], "%dFPS", (int)fps);
	DrawFormatStringToHandle(1270 - length, 670, GetColor(122, 122, 122), font_handle[FONT_TI_MENU], "%dFPS", (int)fps);
}