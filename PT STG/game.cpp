#include "global.h"
#include "game.h"

void ingame_GUI(){

	DrawGraph(0, -20, design_img[0], TRUE);
	DrawGraph(0, 660, design_img[1], TRUE);

	DrawFormatStringToHandle(5, 5, GetColor(222, 222, 222), font_handle[FONT_TI_MENU], "SCORE = %d", score);
	DrawFormatStringToHandle(1100, 5, GetColor(222, 222, 222), font_handle[FONT_TI_MENU], "LEFT = %d", ship.left);

	int length = GetDrawFormatStringWidthToHandle(font_handle[FONT_TI_MENU], "%dFPS", (int)fps);
	DrawFormatStringToHandle(1270 - length, 670, GetColor(222, 222, 222), font_handle[FONT_TI_MENU], "%dFPS", (int)fps);

	int l = (int)pow((0.f - ship.x)*(0.f - ship.x) + (720.f - ship.y)*(720.f - ship.y), 0.5);

	if (l > 510) l = 510;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, l / 2);

	if (ship.type == 0) {
		DrawRectGraph(0, 500, 730 / 2, 50 / 2, 420, 360, chara_img[0][0], TRUE, FALSE);
	}
	else {
		DrawRectGraph(0, 500, 830 / 2, 330 / 2, 420, 360, chara_img[1][0], TRUE, FALSE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}