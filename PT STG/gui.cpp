
#include "global.h"

bool gui::draw_Button(int mx, int my, int mw, int mh, unsigned int normal, unsigned int over, const char *str) {

	// ƒƒ“ƒo‚É‘ã“ü
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

	// ”»’è
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

int  combo::draw_Combo(int mx, int my, int mw, int list, char **list_str) {

	x = mx;
	y = my;
	w = mw;
	list_num = list;

	DrawBox(x, y, x + w, y + 14, GetColor(40, 40, 40), TRUE);
	DrawBox(x, y, x + w, y + 14, GetColor(140, 140, 140), FALSE);
	if (com_button.draw_Button(x + w - 14, y, 14, 14, GetColor(140, 140, 140), GetColor(160, 160, 160), "¥") == true) stats = 1;

	DrawFormatStringToHandle(x, y, GetColor(255, 255, 255), font_handle[FONT_COMBOX], "%s", list_str[select]);

	if (stats == 1) {

		// ”wŒi•`‰æ
		DrawBox(x, y + 14, x + w, y + 14 + (list_num * 14), GetColor(40, 40, 40), TRUE);
		
		// ”»’è
		if (mouse_x > x && mouse_x < x + w && mouse_y > y && mouse_y < y + 14 + (list_num * 14)) {
			for (int i = 0; i < list_num; i++) {
				if (mouse_y > y + 14 + (i * 14) && mouse_y < y + 28 + (i * 14)) {
					DrawBox(x, y + 14 + (i * 14), x + w, y + 28 + (i * 14), GetColor(255, 0, 0), TRUE);
					if (mouse_l == 1) {
						select = (mouse_y - (y + 14)) / 14;
						if (select > list_num) select = list_num;
						stats = 0;
					}
				}
			}
		}
		else if (mouse_l == 1) {
			stats = 0;
		}

		// •¶Žš—ñ•`‰æ
		for (int i = 0; i < list_num; i++) {
			DrawFormatStringToHandle(x, y + 14 + (i * 14), GetColor(255, 255, 255), font_handle[FONT_COMBOX], "%s", list_str[i]);
		}
	}
	return select;
}

int combo::init_Combo(int selected) {
	select = selected;
	return 0;
}

