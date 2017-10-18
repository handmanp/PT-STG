
#include "global.h"

#define EDITOR_TOP  0
#define EDITOR_EDIT 1

//�v���g�^�C�v�錾
int draw_EditorMainMenu();
int draw_NewProjectMenu();
void init_EditorStage();
void delete_EditorStage();
int draw_StageEditor();

//Editor Global
int ss_x[4], ss_y[4];
int stage_size_x = 0, stage_size_y = 0;
int stage_left_x = 0, stage_left_y = 0;

int ***stage_editor;

int block_id;

//�G�f�B�^�[���C�����[�v
void main_Editor() {

	switch (mode_flag) {
	case 0: //�G�f�B�^���j���[���
		if (draw_EditorMainMenu() != -1) {
			mode_flag++;
		}
		break;
	case 1: //�V�K�쐬���
		draw_NewProjectMenu();
		break;
	case 2: //�G�f�B�^���
	//	draw_StageEditor();
		break;
	default:
		break;
	}
}


int draw_StageEditor() {

	for (int i = 0; i < stage_size_x; i++) {
		for (int j = 0; j < stage_size_y; j++) {
			switch (block_id) {
			case -1:
				//DrawBox(-stage_left_x + i * STAGE_TIP_SIZE, );
				break;
			}
		}
	}
	return 0;
}

//�V�K�쐬��ʂ̕`��
int draw_NewProjectMenu() {

	DrawBox(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y, GetColor(10, 10, 10), TRUE);

	unsigned int nc = GetColor(100, 100, 100);
	unsigned int oc = GetColor(150, 150, 150);

	DrawFormatStringToHandle(100, 60,  GetColor(255, 255, 255), font_handle[FONT_HEADING], "�V�K�X�e�[�W�쐬");
	DrawFormatStringToHandle(100, 130, GetColor(255, 255, 255), font_handle[FONT_BUTTON], "���X�e�[�W�T�C�Y��ݒ肵�悤(500x50�ȉ��ɂ͐ݒ�ł��܂���)");

	DrawFormatStringToHandle(100, 210, GetColor(255, 255, 255), font_handle[FONT_HEADING], "X:        Block �~ Y:        Block");

	//X+
	if (button.draw_Button(150, 170, 28, 28, nc, oc, "��") == true) ss_x[3]++;
	if (button.draw_Button(180, 170, 28, 28, nc, oc, "��") == true) ss_x[2]++;
	if (button.draw_Button(210, 170, 28, 28, nc, oc, "��") == true) ss_x[1]++;
	if (button.draw_Button(240, 170, 28, 28, nc, oc, "��") == true) ss_x[0]++;

	//X-
	if (button.draw_Button(150, 260, 28, 28, nc, oc, "��") == true) ss_x[3]--;
	if (button.draw_Button(180, 260, 28, 28, nc, oc, "��") == true) ss_x[2]--;
	if (button.draw_Button(210, 260, 28, 28, nc, oc, "��") == true) ss_x[1]--;
	if (button.draw_Button(240, 260, 28, 28, nc, oc, "��") == true) ss_x[0]--;

	//Y+
	if (button.draw_Button(490, 170, 28, 28, nc, oc, "��") == true) ss_y[3]++;
	if (button.draw_Button(520, 170, 28, 28, nc, oc, "��") == true) ss_y[2]++;
	if (button.draw_Button(550, 170, 28, 28, nc, oc, "��") == true) ss_y[1]++;
	if (button.draw_Button(580, 170, 28, 28, nc, oc, "��") == true) ss_y[0]++;

	//Y-
	if (button.draw_Button(490, 260, 28, 28, nc, oc, "��") == true) ss_y[3]--;
	if (button.draw_Button(520, 260, 28, 28, nc, oc, "��") == true) ss_y[2]--;
	if (button.draw_Button(550, 260, 28, 28, nc, oc, "��") == true) ss_y[1]--;
	if (button.draw_Button(580, 260, 28, 28, nc, oc, "��") == true) ss_y[0]--;

	//�n�~������
	for (int i = 0; i < 4; i++) {
		if (ss_x[i] > 9) ss_x[i] = 9;
		if (ss_x[i] < 0) ss_x[i] = 0;
		if (ss_y[i] > 9) ss_y[i] = 9;
		if (ss_y[i] < 0) ss_y[i] = 0;

		DrawFormatStringToHandle(240 - (i * 30), 210, GetColor(255, 200, 15), font_handle[FONT_HEADING], "%d", ss_x[i]);
		DrawFormatStringToHandle(580 - (i * 30), 210, GetColor(255, 200, 15), font_handle[FONT_HEADING], "%d", ss_y[i]);
	}
	stage_size_x = (ss_x[3] * 1000) + (ss_x[2] * 100) + (ss_x[1] * 10) + ss_x[0];
	stage_size_y = (ss_y[3] * 1000) + (ss_y[2] * 100) + (ss_y[1] * 10) + ss_y[0];

	//�Œ�l
	if (stage_size_x < 500) {
		ss_x[0] = 0;
		ss_x[1] = 0;
		ss_x[2] = 5;
	}
	if (stage_size_y < 50) {
		ss_y[0] = 0;
		ss_y[1] = 5;
	}

	//�쐬�{�^��
	if (button.draw_Button(860, 550, 300, 100, nc, oc, "�쐬") == true) {
		init_EditorStage();
		mode_flag++;
	}

	return 0;
}

//�G�f�B�^�[�̃��C�����j���[�`��
int draw_EditorMainMenu() {

	DrawBox(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y, GetColor(10, 10, 10), TRUE);

	unsigned int nc = GetColor(100, 100, 100);
	unsigned int oc = GetColor(150, 150, 150);

	bool return_data[5];

	for (int i = 0; i < 5; i++) {
		return_data[i] = button.draw_Button(750, 60 + (i * 120), 450, 100, nc, oc, "�X�e�[�W�Z�[�u�f�[�^�F�m������");
		if (return_data[i] == true) {
			return i;
		}
	}

	DrawFormatStringToHandle(100, 60,  GetColor(255, 255, 255), font_handle[FONT_HEADING], "�X�e�[�W�G�f�B�^�[");
	DrawFormatStringToHandle(100, 130, GetColor(255, 255, 255), font_handle[FONT_BUTTON],  "�{�҂ɏo�Ă����f�ނ��g���Ď���X�e�[�W����郂�[�h����I\n�z���͂��������Ď��������̃I���W�i���X�e�[�W���v���C���悤�I");

	return -1;
}

//�G�f�B�^�[�pBG�ʔz��̏�����
void init_EditorStage() {

	//3�����z��̓��I�m�ہi�J�b�R�C�C�j
	stage_editor = new int**[stage_size_x];
	for (int i = 0; i < stage_size_x; i++) {
		stage_editor[i] = new int*[stage_size_y];
		for (int j = 0; j < stage_size_y; j++) {
			stage_editor[i][j] = new int[2];
		}
	}
	//������
	for (int i = 0; i < stage_size_x; i++) {
		for (int j = 0; j < stage_size_y; j++) {
			stage_editor[i][j][0] = -1;
			stage_editor[i][j][1] = -1;
		}
	}
}

//�X�e�[�W�̔j��
//���R���ʂ��Ȃ��Ǝ��ʂ��璍��
void delete_EditorStage() {
	for (int i = 0; i < stage_size_x; i++) {
		for (int j = 0; j < stage_size_y; j++) {
			delete[] stage_editor[i][j];
		}
		delete[] stage_editor[i];
	}
	delete[] stage_editor;
}