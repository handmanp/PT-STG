#define GLOBAL_VALIABLE_DEFINE
#include "global.h"

#define TOP_MENU 1
#define GAME     2
#define EDITOR   3

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
	LPSTR lpCmdLine, int nCmdShow){

	//�ݒ�
	ChangeWindowMode(true);
	SetGraphMode(WINDOW_SIZE_X, WINDOW_SIZE_Y, 32);

	SetDrawScreen( DX_SCREEN_BACK ); 

	SetUseDirect3DVersion(DX_DIRECT3D_11);

	//������
	if (DxLib_Init() == -1) {
		return -1;
	}
	if (Effkseer_Init(2000) == -1) { // �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
		DxLib_End();
		return -1;
	}

	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ�
	//Effekseer_SetGraphicsDeviceLostCallbackFunctions();
	Effekseer_Set2DSetting(WINDOW_SIZE_X, WINDOW_SIZE_Y); // Effekseer��2D�`��̐ݒ������B

	//Z�o�b�t�@(�G�t�F�N�g�p)
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	//--------------------------------------
	//�I�I�I�I�I�f�o�b�O�p�֐��I�I�I�I�I
	//--------------------------------------
	void debug_Init();
	void debug_GameMain();

	//�摜�ǂݍ���
	load_Img();
	load_Effect();

	//�t�H���g�f�[�^
	make_FontData();

	//�f�o�b�O
	debug_Init();



	//�Q�[�����[�h
	int gamemode  = GAME;
	mode_flag = 0;
	frame = 0;

	//----------���C�����[�v------------------------------------------------------------
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {

		input_key();

		switch (gamemode) {
		//------�g�b�v���------------------------------------------------------------
		case TOP_MENU:
			break;

		//------�Q�[���i�s------------------------------------------------------------
		case GAME:

			debug_GameMain();
			break;

		//------�G�f�B�^���[�h------------------------------------------------------------
		case EDITOR:

			main_Editor();
			break;

		default:
			break;
		}
		frame++;
		if (frame >= UINT_MAX) {
			frame = 0;
		}

		//DrawFormatString(0, 30, GetColor(255, 255, 255), "%d / %d / %d / %d", nuts[0].stats, nuts[1].stats, nuts[2].stats, nuts[3].stats);

		// Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
		UpdateEffekseer2D();
		DrawEffekseer2D();
	}
	test.del_Stage();
	Effkseer_End();
	DxLib_End();

	return 0;
}

//�摜���~�RP�g
void load_Img() {

	//�w�i
	bg_handle = LoadGraph(_T("data/img/bg/bg000.png"));

	//�G�摜
	//stage:1
	enemy_img[0] = LoadGraph("data/img/enemy/st1/unis.png");     //�E�j�Y
	enemy_img[1] = LoadGraph("data/img/enemy/st1/edamamen.png"); //�G�_�}����
	enemy_img[2] = LoadGraph("data/img/enemy/st1/nuts.png");     //�i�b�c
	enemy_img[3] = LoadGraph("data/img/enemy/st1/pine.png");     //�s�l
	enemy_img[4] = LoadGraph("data/img/enemy/st1/kai.png");		 //�J�C
	enemy_img[5] = LoadGraph("data/img/enemy/st1/genocide_banana.png"); //�W�F�m�T�C�h�o�i�i
	enemy_img[6] = LoadGraph("data/img/enemy/st1/pine.png");		//�ҍ�
	enemy_img[7] = LoadGraph("data/img/enemy/st1/moving_statue.png");	//moving statue
	enemy_img[8] = LoadGraph("data/img/enemy/st1/meatball_spam.png");	//�~�[�g�{�[���X�p��
	enemy_img[9] = LoadGraph("data/img/enemy/st1/ivy.png");		 //�c�^
	enemy_img[10] = LoadGraph("data/img/enemy/st1/sporecore.png");//�E�q�R�A
	enemy_img[11] = LoadGraph("data/img/enemy/st1/kuwagatan.png");//�N���K�^��

	//���@�摜
	for (int i = 0; i < 2; i++) {
		int buf[5];
		if (i == 0) {
			LoadDivGraph("data/img/ship/ship_bro.png", 5, 1, 5, 100, 50, buf);
		}else{
			//LoadDivGraph("data/img/ship/ship_bro.png", 5, 1, 5, 100, 50, buf);
		}
		for (int j = 0; j < 5; j++) {
			ship_img[j][i] = buf[j];
		}
	}

	//bg�ʉ摜
	LoadDivGraph("data/img/tip/obj.png", 105, 21, 5, 32, 32, maptip_img);

	//pwup�摜
	LoadDivGraph("data/img/gui/powerup.png", 2, 2, 1, 128, 30, pwrup_img);

	//�e�摜
	LoadDivGraph("data/img/bullet/14x14.png", 84, 14, 6, 14, 14, bullet14_img);
	LoadDivGraph("data/img/bullet/16x16.png", 48,  6, 7, 14, 14, bullet16_img);
}

//�G�t�F�N�g�̓ǂݍ���
void load_Effect() {
	effects[0] = LoadEffekseerEffect(_T("data/effect/laser.efk"));
}

void make_FontData() {
	font_handle[FONT_BUTTON]  = CreateFontToHandle("Meiryo", 18, 2, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	font_handle[FONT_HEADING] = CreateFontToHandle("Meiryo", 40, 5, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
}

void debug_Init() {
	
	//debug ship
	ship.init();

	//debug stage
	test.init(500, 40);
	test.set_StagePos(0, 0);

	//debug unis 4tai
	for (int i = 0; i < 4; i++) {
		//unis[i].init(3, 1000 + 50 * i, 700, 300, 360, 1, 1);
	}

	//debug nuts 4tai
	for (int i = 0; i < 4; i++) {
		//nuts[i].init(1280 + 100 * i, 90 + 90 * i, 2, 90 * i, 1);
	}

	//debug shell 4tai
	for (int i = 0; i < 4; i++) {
		//shell[i].init(5, 700 + 40 * i, 650, 1);
	}

	//debug banana 4tai
	for (int i = 0; i < 4; i++) {
		//banana[i].init(10, 1000 + 200 * i, 300, 1);
	}

	//debug pine 4tai
	for (int i = 0; i < 4; i++) {
		//pine[i].init(5, 1800 + i * 40, 700, 300 + i * 60, 1);
	}

	//debug statue 4tai
	for (int i = 0; i < 4; i++) {
		//statue[i].init(5, 1200 + i * 70, 600 + i * 40, 1);
	}

	for (int i = 0; i < 4; i++) {
		//ivy[i].init(5, 1000 + 100 * i, 600, 1);
	}

	for (int i = 0; i < 1; i++) {
		//kuwagatan[i].init(5, 1000, 360, 1);
	}

	for (int i = 0; i < 4; i++) {
		houshi[i].init(5, 1000 + 100 * i, 650, 1);
	}

}

void debug_GameMain() {

	//�G�t�F�N�g�p�w�i�k��
	DrawGraph(0, 0, bg_handle, TRUE);

	//debug stage move and draw.
	test.move(2, 90);
	test.draw();

	//debug my ship move and draw
	ship.move();
	ship.draw();

	//draw debug message
	debug_Message();

	for (int i = 0; i < 4; i++) {
		//unis[i].move();
	}

	for (int i = 0; i < 4; i++) {
		//nuts[i].move();
	}

	for (int i = 0; i < 4; i++) {
		//shell[i].move();
	}

	for (int i = 0; i < 4; i++) {
		//banana[i].move();
	}

	for (int i = 0; i < 4; i++) {
		//pine[i].move();
	}

	for (int i = 0; i < 4; i++) {
		//statue[i].move();
	}

	for (int i = 0; i < 4; i++) {
		//ivy[i].move();
	}

	for (int i = 0; i < 1; i++) {
		//kuwagatan[i].move();
	}

	for (int i = 0; i < 4; i++) {
		houshi[i].move();
	}
}

void debug_Message() {
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Scroll_X:%d / Scroll_Y:%d", (int)test.x, (int)test.y);
}