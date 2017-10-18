#define GLOBAL_VALIABLE_DEFINE
#include "global.h"

#define TOP_MENU 1
#define GAME     2
#define EDITOR   3

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
	LPSTR lpCmdLine, int nCmdShow){

	//設定
	ChangeWindowMode(true);
	SetGraphMode(WINDOW_SIZE_X, WINDOW_SIZE_Y, 32);

	SetDrawScreen( DX_SCREEN_BACK ); 

	SetUseDirect3DVersion(DX_DIRECT3D_9);

	//初期化
	if (DxLib_Init() == -1) {
		return -1;
	}
	if (Effkseer_Init(2000) == -1) { // 引数には画面に表示する最大パーティクル数を設定する。
		DxLib_End();
		return -1;
	}

	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DXライブラリのデバイスロストした時のコールバックを設定
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();
	Effekseer_Set2DSetting(WINDOW_SIZE_X, WINDOW_SIZE_Y); // Effekseerに2D描画の設定をする。

	//Zバッファ(エフェクト用)
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	//--------------------------------------
	//！！！！！デバッグ用関数！！！！！
	//--------------------------------------
	void debug_Init();
	void debug_GameMain();

	//画像読み込み
	load_Img();
	load_Effect();

	//フォントデータ
	make_FontData();

	//デバッグ
	debug_Init();



	//ゲームモード
	int gamemode  = GAME;
	mode_flag = 0;
	frame = 0;

	//----------メインループ------------------------------------------------------------
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {

		input_key();

		switch (gamemode) {
		//------トップ画面------------------------------------------------------------
		case TOP_MENU:
			break;

		//------ゲーム進行------------------------------------------------------------
		case GAME:

			debug_GameMain();
			break;

		//------エディタモード------------------------------------------------------------
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

		DrawFormatString(0, 30, GetColor(255, 255, 255), "%d / %d / %d / %d", nuts[0].stats, nuts[1].stats, nuts[2].stats, nuts[3].stats);

		// Effekseerにより再生中のエフェクトを更新する。
		UpdateEffekseer2D();
		DrawEffekseer2D();
	}
	test.del_Stage();
	Effkseer_End();
	DxLib_End();

	return 0;
}

//画像ヨミコP身
void load_Img() {

	//背景
	bg_handle = LoadGraph(_T("data/img/bg/bg000.png"));

	//敵画像
	//stage:1
	enemy_img[0] = LoadGraph("data/img/enemy/st1/unis.png");     //ウニズ
	enemy_img[1] = LoadGraph("data/img/enemy/st1/edamamen.png"); //エダマメン
	enemy_img[2] = LoadGraph("data/img/enemy/st1/nuts.png");     //ナッツ
	enemy_img[3] = LoadGraph("data/img/enemy/st1/pine.png");     //ピネ
	enemy_img[4] = LoadGraph("data/img/enemy/st1/kai.png");		 //カイ

	//自機画像
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

	//bg面画像
	LoadDivGraph("data/img/tip/obj.png", 105, 21, 5, 32, 32, maptip_img);

	//pwup画像
	LoadDivGraph("data/img/gui/powerup.png", 2, 2, 1, 128, 30, pwrup_img);

	//弾画像
	LoadDivGraph("data/img/bullet/14x14.png", 84, 14, 6, 14, 14, bullet14_img);
	LoadDivGraph("data/img/bullet/16x16.png", 48,  6, 7, 14, 14, bullet16_img);
}

//エフェクトの読み込み
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
	unis[0].init(3, 1000, 700, 300, 360, 10, 1);
	unis[1].init(3, 1050, 700, 300, 360, 10, 1);
	unis[2].init(3, 1100, 700, 300, 360, 10, 1);
	unis[3].init(3, 1150, 700, 300, 360, 10, 1);


	//debug nuts 4tai
	nuts[0].init(1280, 360, 2, 0, 1);
	nuts[1].init(1380, 360, 2, 90, 1);
	nuts[2].init(1480, 360, 2, 180, 1);
	nuts[3].init(1580, 360, 2, 270, 1);

	//debug shell 4tai
	shell[0].init(5, 700, 650, 1);
	shell[1].init(5, 740, 650, 1);
	shell[2].init(5, 780, 650, 1);
	shell[3].init(5, 820, 650, 1);

}

void debug_GameMain() {

	//エフェクト用背景ヌリ
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
		unis[i].move();
	}

	for (int i = 0; i < 4; i++) {
		nuts[i].move();
	}

	for (int i = 0; i < 4; i++) {
		shell[i].move();
	}
}

void debug_Message() {
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Scroll_X:%d / Scroll_Y:%d", (int)test.x, (int)test.y);
}