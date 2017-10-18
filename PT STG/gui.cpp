
#include "global.h"

bool gui::draw_Button(int mx, int my, int mw, int mh, unsigned int normal, unsigned int over, const char *str) {

	//ƒƒ“ƒo‚É‘ã“ü
	stats = 1;
	x = mx;
	y = my;
	h = mh;
	w = mw;
	normal_color = normal;
	over_color = over;

	int len = strlen(str);
	int draw_px = (x + (w / 2)) - GetDrawFormatStringWidthToHandle(font_handle[FONT_BUTTON], "%s", str) / 2;
	int draw_py = (y + (h / 2)) - 10;

	//”»’è
	if (mouse_x > x && mouse_x < x + w && mouse_y > y && mouse_y < y + h) {
		if (mouse_l != 0) {
			DrawBox(x, y, x + w, y + h, GetColor(255, 0, 0), TRUE);
			DrawFormatStringToHandle(draw_px, draw_py, GetColor(255, 255, 255), font_handle[FONT_BUTTON], "%s", str);
			if (mouse_l == 1) return true;
		}
		DrawBox(x, y, x + w, y + h, over_color, TRUE);
	}
	else {
		DrawBox(x, y, x + w, y + h, normal_color, TRUE);
	}

	DrawFormatStringToHandle(draw_px, draw_py, GetColor(255, 255, 255), font_handle[FONT_BUTTON], "%s", str);

	return false;
}