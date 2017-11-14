
#include "global.h"
#include "menu.h"



void draw_Menu() {
	switch (menu_mode) {
	case Title:
		draw_Title();
		break;
	case CharaSelect:
		draw_CharSelect();
		break;
	}
}

// �^�C�g�����j���[
// ----------------------------------------------------------
void draw_Title() {

	// ���^�C�g��
	DrawGraph(0, 0, title_img_1, TRUE);

	// �t�@�[�t�@�[�Ȃ���
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, title_alpha);
	DrawGraph(0, 0, title_img_2, TRUE);

	// ���ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (frame % ((((int)fps + 1) / 60) + 1) == 0) {
		title_alpha += title_dir;
		if (title_alpha > 255 || title_alpha < 0) title_dir *= -1;
	}

	// �e���j���[�ֈړ�
	switch (title.draw(550, 280, 5, title_str)) {
	// GAME START
	case 0:
		menu_mode = CharaSelect;
		break;
	// STAGE EDITOR
	case 2:
		gamemode = 3; // �G�f�B�^�N��
		break;
	// QUIT GAME
	case 4:
		quit = false;
		break;
	default:
		break;
	}
}

// �L�����I�����j���[
// ----------------------------------------------------------
void draw_CharSelect() {

	// ���^�C�g��
	DrawGraph(0, 0, menu_bg_1, TRUE);

	// �t�@�[�t�@�[�Ȃ���
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, title_alpha);
	DrawGraph(0, 0, menu_bg_2, TRUE);

	// ���ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (chara.selected < 2) {
		DrawGraph(-200, (chara.selected * -120) + sin(a2r(rad)) * 10, chara_img[chara.selected][0], TRUE);
		DrawFormatStringToHandle(600, 200, GetColor(122, 122, 122), font_handle[FONT_BIG], "%s", charSelect_fstr[chara.selected]);
		DrawFormatStringToHandle(600, 300, GetColor(122, 122, 122), font_handle[FONT_INGAME], "%s", charSelect_mes[chara.selected]);
	}

	if (frame % ((((int)fps + 1) / 60) + 1) == 0) {
		title_alpha += title_dir;
		if (title_alpha > 255 || title_alpha < 0) title_dir *= -1;

		rad++;
		if (rad > 360) rad = 0;
	}
	// �e���j���[�ֈړ�
	switch (chara.draw(550, 420, 3, charSelect_str)) {
	case 0:
		gamemode = 2;
		debug_Init();
		ship.type = 0;					// ���@�̎�ނ�ݒ� 0:�t�� 1:�A��
		break;
	case 1:
		gamemode = 2;
		debug_Init();
		ship.type = 1;
		break;
	case 2:
		menu_mode = Title;
		break;
	default:
		break;
	}
}

// �|�[�Y���j���[
// ----------------------------------------------------------
void draw_Pause() {

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, title_alpha);

	// ���^�C�g��
	DrawGraph(0, 100, design_img[4], TRUE);

	// ���ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (frame % ((((int)fps + 1) / 60) + 1) == 0) {
		title_alpha += title_dir;
		if (title_alpha > 155 || title_alpha < 100) title_dir *= -1;
	}

	// �e���j���[�ֈړ�
	switch (pause.draw(550, 280, 3, pause_str)) {
		// GAME START
	case 0:
		pause_flag = 0;
		break;
		// STAGE EDITOR
	case 1:
		break;
		// QUIT GAME
	case 2:
		gamemode = 1;
		menu_mode = Title;
		pause_flag = 0;
		test.del_Stage();
		StopSoundFile();
		break;
	default:
		break;
	}
}

// CONTINUE���j���[
// ----------------------------------------------------------
void draw_Over() {

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, title_alpha);

	// ���^�C�g��
	DrawGraph(0, 100, design_img[4], TRUE);

	// ���ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (frame % ((((int)fps + 1) / 60) + 1) == 0) {
		title_alpha += title_dir;
		if (title_alpha > 155 || title_alpha < 100) title_dir *= -1;
	}

	DrawFormatStringToHandle(800, 190, GetColor(222, 222, 222), font_handle[FONT_BIG], "GAME OVER");

	// �e���j���[�ֈړ�
	switch (pause.draw(550, 280, 3, over_str)) {
		// GAME START
	case 0:
		pause_flag = 0;
		ship.left = 5;
		break;
		// STAGE EDITOR
	case 1:
		break;
		// QUIT GAME
	case 2:
		gamemode   = 1;
		menu_mode  = Title;
		pause_flag = 0;
		test.del_Stage();
		StopSoundFile();
		break;
	default:
		break;
	}
}

// �������������j���[
// =========================================================================================
int coolmenu::draw(int mx, int my, int n, char **str) {

	x = mx, y = my;

	// �C�[�W���O
	if (ease_flag != 0) {
		double tx = OutQuint(ease_time, 1.0, x - ((double)selected * 36), x - (((double)selected + ease_flag) * 36));
		double ty = OutQuint(ease_time, 1.0, y + ((double)selected * 61), y + (((double)selected + ease_flag) * 61));
		int color = OutQuint(ease_time, 1.0, 222, 122);

		DrawGraph(tx, ty, title_selected, TRUE);
		int str_x = (x + 560) - ((selected * 36) + GetDrawFormatStringWidthToHandle(font_handle[FONT_TI_MENU], "%s", str[selected]));
		DrawFormatStringToHandle(str_x, y + (selected * 61) + 8, GetColor(color, color, color), font_handle[FONT_TI_MENU], "%s", str[selected]);
		
		ease_time += 0.05 * frame_Time;
		if (ease_time > 1.0) ease_flag = 0;
	}

	// ���ɕ\��
	for (int i = 0; i < n; i++) {
		int str_x = (x + 560) - ((i * 36) + GetDrawFormatStringWidthToHandle(font_handle[FONT_TI_MENU], "%s", str[i]));
		if (selected == i) {
			if (ease_flag == 0) {
				DrawGraph(x - (i * 36), y + (i * 61), title_selected, TRUE);
				DrawFormatStringToHandle(str_x, y + (i * 61) + 8, GetColor(222, 222, 222), font_handle[FONT_TI_MENU], "%s", str[i]);
			}
		}
		else {
			DrawFormatStringToHandle(str_x, y + (i * 61) + 8, GetColor(122, 122, 122), font_handle[FONT_TI_MENU], "%s", str[i]);
		}
	}
	// ��������������
	DrawLineAA(x + 600, y, x + 600 - (n * 36), y + (n * 61), GetColor(122, 122, 122));

	// �R���g���[���g���K�[��
	ctrl_trigg();

	// �L�[����
	if (ctrl_key[KEY_INPUT_UP] == 1 || ctrl_trig[XINPUT_BUTTON_DPAD_UP] == 1) {
		selected--;
		ease_flag = 1;
		ease_time = 0.0;
		PlaySoundMem(menu_sehnd[1], DX_PLAYTYPE_BACK, TRUE);
	}
	if (ctrl_key[KEY_INPUT_DOWN] == 1 || ctrl_trig[XINPUT_BUTTON_DPAD_DOWN] == 1) {
		selected++;
		ease_flag = -1;
		ease_time = 0.0;
		PlaySoundMem(menu_sehnd[1], DX_PLAYTYPE_BACK, TRUE);
	}
	// ���莞
	if (ctrl_key[KEY_INPUT_Z] == 1 || ctrl_pad.Buttons[XINPUT_BUTTON_X] == 1) {
		PlaySoundMem(menu_sehnd[0], DX_PLAYTYPE_BACK, TRUE);
		return selected;
	}

	//�͈͊O�h�~
	if (selected >= n) selected = --n;
	if (selected <  0) selected = 0;

	return -1;
}

// �������h�~
void ctrl_trigg(){

	for (int i = 0; i < num; i++) {
		if (ctrl_pad.Buttons[i]) {
			if (ctrl_trig[i] == 0) ctrl_trig[i] = 1;
			else if (ctrl_trig[i] == 1) ctrl_trig[i] = 2;
		}
		else ctrl_trig[i] = 0;
	}
}

// �C�[�W���O
double OutQuint(double t, double totaltime, double max, double min){
	max -= min;
	t = t / totaltime - 1;
	return max*(t*t*t*t*t + 1) + min;
}

/*
void coolmenu::init(int select) {
	selected = select;
}
*/