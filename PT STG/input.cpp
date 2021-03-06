
#include "global.h"

void input_key() {

	// マウスを取得
	GetMousePoint(&mouse_x, &mouse_y);

	if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		if (mouse_l == 0) mouse_l = 1;
		else if (mouse_l == 1) mouse_l = 2;
	}
	else mouse_l = 0;

	if (GetMouseInput() & MOUSE_INPUT_RIGHT) {
		if (mouse_r == 0) mouse_r = 1;
		else if (mouse_r == 1) mouse_r = 2;
	}
	else mouse_r = 0;

	// キーボード入力を取得
	static char buf[256];
	GetHitKeyStateAll(buf);

	//トリガー判定
	for (int i = 0; i < 256; i++) {
		if (buf[i]) {
			if (ctrl_key[i] == 0) ctrl_key[i] = 1;
			else if (ctrl_key[i] == 1) ctrl_key[i] = 2;
		}
		else ctrl_key[i] = 0;
	}

	// ゲームパッド入力を取得
	GetJoypadXInputState(DX_INPUT_PAD1, &ctrl_pad);
}