
// 22275133773333721127155751757755152211275727111711132731155151
// 75351351373373513557717755531555237255752713375153557117532512
// 53131551737732223215755323122252531371573311713121113153515137
// 51225272311712377135573351551122351315722232357515355771533122
// 22533335333125531221517323155112252211273232231217277731223711
// 75327711277135755522355532323235353253732533715375227557132337
// 15331121525725231731550752151780511775723101731258502271833125
// 51001332110070880008008025727707317525888800008022083808880073
// 77072202270121233705751153088808008718035703725857705123032711
// 33837758238751377502333223371102323357100800001757007127821152
// 33077718370573121580027371312281573855317783557510582280880155
// 37075123381351115381381210000808080827208800805125283727213221
// 22072512303371155582378175277888552337757785757077371287225777
// 72032075081537171701517575570202851538880000880038088088008832
// 31800755820773535381535337101205102527222030127237288328250232
// 70822758537055157287732520015202318011780212801252030531002173
// 50322003725053315207111327217107371520833321518070728802138075
// 51775731327317155353173555323535173771215553577227557273372573


#include "global.h"
#include "editor.h"

// �G�f�B�^�[���C�����[�v
void main_Editor() {

	switch (mode_flag) {
	case 0: // �G�f�B�^���j���[���
		if (draw_EditorMainMenu() != -1) {
			mode_flag++;
		}
		break;
	case 1: // �V�K�쐬���
		draw_NewProjectMenu();
		break;
	case 2: // �G�f�B�^���
		draw_StageEditor();
		break;
	default:
		break;
	}
}

//-------------------------------------------------------------------------------
//
//   �G�f�B�^
//
//-------------------------------------------------------------------------------
// �G�f�B�^�{�̂̃��C��
int draw_StageEditor() {

	for (int i = 0; i < stage_size_x; i++) {
		for (int j = 0; j < stage_size_y; j++) {
			switch (stage_editor[i][j][0]) {
			case -1:
				DrawBox(stage_left_x + (i * STAGE_TIP_SIZE), stage_left_y + (j * STAGE_TIP_SIZE), stage_left_x + (i * STAGE_TIP_SIZE) + STAGE_TIP_SIZE, stage_left_y + (j * STAGE_TIP_SIZE) + STAGE_TIP_SIZE, GetColor(20, 20, 20), FALSE);
				break;
			}
		}
	}
	move_StageEditor();
	draw_StageEditorRuler();
	draw_StageEditorMenu();

	return 0;
}


// ���j���[�ނ̕`��
void draw_StageEditorMenu() {

	DrawBox(1000, 0, 1280, 720, GetColor(100, 100, 100), TRUE);

	if (button.draw_Button(1000, 200, 70, 30, GetColor(100,   0,   0), GetColor(55,  0,  0), "�ð��")    == true) editor_mode = 0;
	if (button.draw_Button(1070, 200, 70, 30, GetColor(  0, 100,   0), GetColor( 0, 55,  0), "��а")     == true) editor_mode = 1;
	if (button.draw_Button(1140, 200, 70, 30, GetColor(  0,   0, 100), GetColor( 0,  0, 55), "�t���O")   == true) editor_mode = 2;
	if (button.draw_Button(1210, 200, 70, 30, GetColor(100, 100,   0), GetColor(55, 55,  0), "�H����")   == true) editor_mode = 3;

	char *list_str[4] = {"�X�e�[�W�P�̓G", "�X�e�[�W�Q�̓G", "�X�e�[�W�R�̓G", "�{�X", };

	switch (editor_mode) {
	case 0:
		DrawBox(1000, 230, 1280, 720, GetColor(100, 0, 0), TRUE);
		draw_StageEditorMenuStage();
		break;
	case 1:
		DrawBox(1000, 230, 1280, 720, GetColor(0, 100, 0), TRUE);
		com.draw_Combo(1010, 300, 250, 4, list_str);
		break;
	case 2:
		DrawBox(1000, 230, 1280, 720, GetColor(0, 0, 100), TRUE);
		break;
	case 3:
		DrawBox(1000, 230, 1280, 720, GetColor(100, 100, 0), TRUE);
		break;
	}
}

void draw_StageEditorMenuStage() {

}

// ���[���̕`��
void draw_StageEditorRuler() {

	// X�����[��
	for (int i = 0; i < stage_size_x; i++) {
		if (i == 0 || i % 10 == 0) {
			DrawLine(stage_left_x + (i * STAGE_TIP_SIZE), 0, stage_left_x + (i * STAGE_TIP_SIZE), 20, GetColor(255, 255, 255));
			DrawFormatString(stage_left_x + (i * STAGE_TIP_SIZE) + 5, 5, GetColor(255, 255, 255), "%d", i);
		}
		else if (i % 5 == 0) {
			DrawLine(stage_left_x + (i * STAGE_TIP_SIZE), 0, stage_left_x + (i * STAGE_TIP_SIZE), 10, GetColor(255, 255, 255));
		}
		else {
			DrawLine(stage_left_x + (i * STAGE_TIP_SIZE), 0, stage_left_x + (i * STAGE_TIP_SIZE), 5, GetColor(255, 255, 255));
		}
	}

	// Y�����[��
	for (int i = 0; i < stage_size_y; i++) {
		if (i == 0 || i % 10 == 0) {
			DrawLine(0, stage_left_y + (i * STAGE_TIP_SIZE), 20, stage_left_y + (i * STAGE_TIP_SIZE), GetColor(255, 255, 255));
			DrawFormatString(5, stage_left_y + (i * STAGE_TIP_SIZE) + 5, GetColor(255, 255, 255), "%d", i);
		}
		else if (i % 5 == 0) {
			DrawLine(0, stage_left_y + (i * STAGE_TIP_SIZE), 10, stage_left_y + (i * STAGE_TIP_SIZE), GetColor(255, 255, 255));
		}
		else {
			DrawLine(0, stage_left_y + (i * STAGE_TIP_SIZE), 5, stage_left_y + (i * STAGE_TIP_SIZE), GetColor(255, 255, 255));
		}
	}
}

// �G�f�B�^�̈ړ�
void move_StageEditor() {
	if (mouse_r == 1) {
		mouse_diff_x = mouse_x - stage_left_x;
		mouse_diff_y = mouse_y - stage_left_y;
	}
	else if (mouse_r == 2){
		stage_left_x = mouse_x - mouse_diff_x;
		stage_left_y = mouse_y - mouse_diff_y;
	}
}
//-------------------------------------------------------------------------------
//
//   ���j���[
//
//-------------------------------------------------------------------------------
// �V�K�쐬��ʂ̕`��
int draw_NewProjectMenu() {

	DrawBox(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y, GetColor(10, 10, 10), TRUE);

	unsigned int nc = GetColor(100, 100, 100);
	unsigned int oc = GetColor(150, 150, 150);

	DrawFormatStringToHandle(100, 60,  GetColor(255, 255, 255), font_handle[FONT_HEADING], "�V�K�X�e�[�W�쐬");
	DrawFormatStringToHandle(100, 130, GetColor(255, 255, 255), font_handle[FONT_BUTTON], "���X�e�[�W�T�C�Y��ݒ肵�悤(500x50�ȉ��ɂ͐ݒ�ł��܂���)");

	DrawFormatStringToHandle(100, 210, GetColor(255, 255, 255), font_handle[FONT_HEADING], "X:        Block �~ Y:        Block");

	// X+
	if (button.draw_Button(150, 170, 28, 28, nc, oc, "��") == true) ss_x[3]++;
	if (button.draw_Button(180, 170, 28, 28, nc, oc, "��") == true) ss_x[2]++;
	if (button.draw_Button(210, 170, 28, 28, nc, oc, "��") == true) ss_x[1]++;
	if (button.draw_Button(240, 170, 28, 28, nc, oc, "��") == true) ss_x[0]++;

	// X-
	if (button.draw_Button(150, 260, 28, 28, nc, oc, "��") == true) ss_x[3]--;
	if (button.draw_Button(180, 260, 28, 28, nc, oc, "��") == true) ss_x[2]--;
	if (button.draw_Button(210, 260, 28, 28, nc, oc, "��") == true) ss_x[1]--;
	if (button.draw_Button(240, 260, 28, 28, nc, oc, "��") == true) ss_x[0]--;

	// Y+
	if (button.draw_Button(490, 170, 28, 28, nc, oc, "��") == true) ss_y[3]++;
	if (button.draw_Button(520, 170, 28, 28, nc, oc, "��") == true) ss_y[2]++;
	if (button.draw_Button(550, 170, 28, 28, nc, oc, "��") == true) ss_y[1]++;
	if (button.draw_Button(580, 170, 28, 28, nc, oc, "��") == true) ss_y[0]++;

	// Y-
	if (button.draw_Button(490, 260, 28, 28, nc, oc, "��") == true) ss_y[3]--;
	if (button.draw_Button(520, 260, 28, 28, nc, oc, "��") == true) ss_y[2]--;
	if (button.draw_Button(550, 260, 28, 28, nc, oc, "��") == true) ss_y[1]--;
	if (button.draw_Button(580, 260, 28, 28, nc, oc, "��") == true) ss_y[0]--;

	// �n�~������
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

	// �Œ�l
	if (stage_size_x < 500) {
		ss_x[0] = 0;
		ss_x[1] = 0;
		ss_x[2] = 5;
	}
	if (stage_size_y < 50) {
		ss_y[0] = 0;
		ss_y[1] = 5;
	}

	// �쐬�{�^��
	if (button.draw_Button(860, 550, 300, 100, nc, oc, "�쐬") == true) {
		init_EditorStage();
		mode_flag++;
	}

	return 0;
}

// �G�f�B�^�[�̃��C�����j���[�`��
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

// �G�f�B�^�[�pBG�ʔz��̏�����
void init_EditorStage() {

	// 3�����z��̓��I�m�ہi�J�b�R�C�C�j
	stage_editor = new int**[stage_size_x];
	for (int i = 0; i < stage_size_x; i++) {
		stage_editor[i] = new int*[stage_size_y];
		for (int j = 0; j < stage_size_y; j++) {
			stage_editor[i][j] = new int[2];
		}
	}
	// ������
	for (int i = 0; i < stage_size_x; i++) {
		for (int j = 0; j < stage_size_y; j++) {
			stage_editor[i][j][0] = -1;
			stage_editor[i][j][1] = -1;
		}
	}
}

// �X�e�[�W�̔j��
// ���R���ʂ��Ȃ��Ǝ��ʂ��璍��
void delete_EditorStage() {
	for (int i = 0; i < stage_size_x; i++) {
		for (int j = 0; j < stage_size_y; j++) {
			delete[] stage_editor[i][j];
		}
		delete[] stage_editor[i];
	}
	delete[] stage_editor;
}