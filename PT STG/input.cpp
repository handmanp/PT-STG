
#include "global.h"

void input_key() {

	// �}�E�X���擾
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

	// �L�[�{�[�h���͂��擾
	GetHitKeyStateAll(ctrl_key);

	// �Q�[���p�b�h���͂��擾
	GetJoypadXInputState(DX_INPUT_PAD1, &ctrl_pad);
}