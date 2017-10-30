#define GLOBAL_VALIABLE_DEFINE
#include "global.h"

#define TOP_MENU 1
#define GAME     2
#define EDITOR   3

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
	LPSTR lpCmdLine, int nCmdShow){

	// �ݒ�
	ChangeWindowMode(true);
	SetGraphMode(WINDOW_SIZE_X, WINDOW_SIZE_Y, 32);

	SetDrawScreen( DX_SCREEN_BACK ); 

	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// ������
	if (DxLib_Init() == -1) {
		return -1;
	}
	if (Effkseer_Init(2000) == -1) { // �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
		DxLib_End();
		return -1;
	}

	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ�
	// Effekseer_SetGraphicsDeviceLostCallbackFunctions();
	Effekseer_Set2DSetting(WINDOW_SIZE_X, WINDOW_SIZE_Y); // Effekseer��2D�`��̐ݒ������B

	// Z�o�b�t�@(�G�t�F�N�g�p)
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	//--------------------------------------
	//�I�I�I�I�I�f�o�b�O�p�֐��I�I�I�I�I
	//--------------------------------------
	void debug_Init();
	void debug_GameMain();

	// �摜�ǂݍ���
	load_Img();
	load_Effect();

	// �t�H���g�f�[�^
	make_FontData();

	// �f�o�b�O
	debug_Init();



	// �Q�[�����[�h : TOP_MENU / GAME / EDITOR
	int gamemode = GAME;
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

		//DrawFormatString(0, 30, GetColor(255, 255, 255), "%d / %d / %d / %d", detecrew[0].mode, (int)genocide[0].mode, nuts[2].stats, nuts[3].stats);

		// Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
		UpdateEffekseer2D();
		DrawEffekseer2D();
	}
	test.del_Stage();
	Effkseer_End();
	DxLib_End();

	return 0;
}

// �摜���~�RP�g
void load_Img() {

	// �w�i
	bg_handle = LoadGraph(_T("data/img/bg/bg000.png"));

	// �G�摜
	// stage:1
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
	enemy_img[12] = LoadGraph("data/img/enemy/st1/worm_head.png");//���[���w�b�h
	//enemy_img[13] �\�� <���[���K��>
	//enemy_img[14] �\�� <���[������>
	enemy_img[15] = LoadGraph("data/img/enemy/st1/genocide.png"); //�W�F�m�T�C�h
	//enemy_img[16] = LoadGraph("data/img/enemy/st1/????");		  //�L���o�R
	//enemy_img[17] = LoadGraph("data/img/enemy/st1/????");		  //�V���_�[��
	//enemy_img[18] = LoadGraph("data/img/enemy/st1/????");		  //�f�e�N���[


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

	// bg�ʉ摜
	LoadDivGraph("data/img/tip/obj.png", 880, 88, 10, 24, 24, maptip_img);

	// pwup�摜
	LoadDivGraph("data/img/gui/powerup.png", 2, 2, 1, 128, 30, pwrup_img);

	// �e�摜
	LoadDivGraph("data/img/bullet/14x14.png", 84, 14, 6, 14, 14, bullet14_img);
	LoadDivGraph("data/img/bullet/16x16.png", 48,  6, 7, 14, 14, bullet16_img);
}

// �G�t�F�N�g�̓ǂݍ���
void load_Effect() {
	effects[0] = LoadEffekseerEffect(_T("data/effect/laser.efk"));
}

void make_FontData() {
	font_handle[FONT_BUTTON]  = CreateFontToHandle("Meiryo", 18, 2, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	font_handle[FONT_HEADING] = CreateFontToHandle("Meiryo", 40, 5, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	font_handle[FONT_COMBOX]  = CreateFontToHandle("Meiryo", 10, 2, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
}

void debug_Init() {
	
	// debug ship
	ship.init();

	// debug stage
	test.init(500, 40);
	test.set_StagePos(0, 0);

	// CSV���[�_
	test.io_StageDataLoad();

	// �e�֐��p������
	b_anim_3 = b_anim_4 = b_anim_6 = 0;
	b_dir_3 = b_dir_6 = 1;
}

void debug_GameMain() {

	// �G�t�F�N�g�p�w�i�k��
	DrawGraph(0, 0, bg_handle, TRUE);

	// debug stage move and draw.
	test.move(2, 90);
	test.draw();

	// �X�e�[�W�i�s
	test.stage_Progression(); // CSV���
	test.stage_EnemyMove();   // �G����

	// debug my ship move and draw
	ship.move();
	ship.draw();

	// draw debug message
	debug_Message();

	// bullet update
	bullet_Animation_Update();
}

void debug_Message() {
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Scroll_X:%d / Scroll_Y:%d", (int)test.x, (int)test.y);
}