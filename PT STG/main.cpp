#define GLOBAL_VALIABLE_DEFINE
#include "global.h"

#define LOADING  0
#define TOP_MENU 1
#define GAME     2
#define EDITOR   3



// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
	LPSTR lpCmdLine, int nCmdShow){

	// 設定
	ChangeWindowMode(true);
	SetGraphMode(WINDOW_SIZE_X, WINDOW_SIZE_Y, 32);
	SetMainWindowText("LUNETTE <Presentation Edition v0.9.1>");

	SetDrawScreen( DX_SCREEN_BACK ); 

	SetUseDirect3DVersion(DX_DIRECT3D_11);
	SetWaitVSyncFlag(FALSE);
	// 初期化
	if (DxLib_Init() == -1) {
		return -1;
	}
	if (Effkseer_Init(2000) == -1) { // 引数には画面に表示する最大パーティクル数を設定する。
		DxLib_End();
		return -1;
	}

	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DXライブラリのデバイスロストした時のコールバックを設定
	// Effekseer_SetGraphicsDeviceLostCallbackFunctions();
	Effekseer_Set2DSetting(WINDOW_SIZE_X, WINDOW_SIZE_Y); // Effekseerに2D描画の設定をする。

	// Zバッファ(エフェクト用)
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	//--------------------------------------
	//！！！！！デバッグ用関数！！！！！
	//--------------------------------------
	void debug_Init();
	void debug_GameMain();

	// 画像読み込み
	load_Img();
	load_Effect();

	// フォントデータ
	make_FontData();

	// デバッグ
	debug_Init();

	// ゲームモード : TOP_MENU / GAME / EDITOR
	gamemode  = LOADING;
	mode_flag = 0;
	frame     = 0;
	quit      = true;

	int logo = LoadGraph("data/img/title/Logo.png");

	//----------メインループ------------------------------------------------------------
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && quit) {

		input_key();

		switch (gamemode) {
		//------読み込み画面------------------------------------------------------------
		case LOADING:
			// 描画
			DrawBox(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y, 0xFFFFFF, TRUE);
			DrawGraph((WINDOW_SIZE_X / 2) - (683 / 2), (WINDOW_SIZE_Y / 2) - (400 / 2), logo, TRUE);

			// 処理
			if (frame >= 2500000 * frame_Time) {
				
				gamemode = TOP_MENU;
			}
			break;
		//------トップ画面------------------------------------------------------------
		case TOP_MENU:
			draw_Menu();
			break;

		//------ゲーム進行------------------------------------------------------------
		case GAME:

			debug_GameMain();
			ingame_GUI();
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

		//DrawFormatString(0, 30, GetColor(255, 255, 255), "%d / %d / %d / %d", detecrew[0].mode, (int)genocide[0].mode, nuts[2].stats, nuts[3].stats);

		// Effekseerにより再生中のエフェクトを更新する。
		UpdateEffekseer2D();
		DrawEffekseer2D();

		fps_Calc();
		variable_Fps();
	}

	test.del_Stage();

	Effkseer_End();
	DxLib_End();

	return 0;
}


// 画像ヨミコP身
void load_Img() {

	// 背景
	bg_handle = LoadGraph(_T("data/img/bg/bg000.png"));

	// 敵画像
	// stage:1
	enemy_img[0] = LoadGraph("data/img/enemy/st1/unis.png");			// ウニズ
	enemy_img[1] = LoadGraph("data/img/enemy/st1/edamamen.png");		// エダマメン
	enemy_img[2] = LoadGraph("data/img/enemy/st1/nuts.png");			// ナッツ
	enemy_img[3] = LoadGraph("data/img/enemy/st1/pine.png");			// ピネ
	enemy_img[4] = LoadGraph("data/img/enemy/st1/kai.png");				// カイ
	enemy_img[5] = LoadGraph("data/img/enemy/st1/genocide_banana.png"); // ジェノサイドバナナ
	enemy_img[6] = LoadGraph("data/img/enemy/st1/pine.png");			// ぴ根
	enemy_img[7] = LoadGraph("data/img/enemy/st1/moving_statue.png");	// moving statue
	enemy_img[8] = LoadGraph("data/img/enemy/st1/meatball_spam.png");	// ミートボールスパム
	enemy_img[9] = LoadGraph("data/img/enemy/st1/ivy_1.png");			// ツタ
	enemy_img[10] = LoadGraph("data/img/enemy/st1/sporecore.png");		// 胞子コア
	enemy_img[11] = LoadGraph("data/img/enemy/st1/kuwagatan.png");		// クワガタん
	enemy_img[12] = LoadGraph("data/img/enemy/st1/worm_head.png");		// ワームヘッド
	//enemy_img[13] 予約 <ワーム尻尾>
	enemy_img[14] = LoadGraph("data/img/enemy/st1/worm_body.png");		// ワームボディ
	enemy_img[15] = LoadGraph("data/img/enemy/st1/genocide.png");		// ジェノサイド
	enemy_img[16] = LoadGraph("data/img/enemy/st1/kimobako");			// キモバコ
	enemy_img[17] = LoadGraph("data/img/enemy/st1/sindarla.png");		// シンダーラ
	enemy_img[18] = LoadGraph("data/img/enemy/st1/detecrewno.png");		// デテクルーノ本体
	enemy_img[19] = LoadGraph("data/img/enemy/st1/detecrewno_kuki.png");// デテクルーノ茎
	enemy_img[20] = LoadGraph("data/img/enemy/st1/noumison.png");		// ノウミソン

	// キャラ画像
	chara_img[0][0] = LoadGraph("data/img/chara/c001_1.png");
	chara_img[0][1] = LoadGraph("data/img/chara/c001_2.png");
	chara_img[0][2] = LoadGraph("data/img/chara/c001_3.png");
	chara_img[0][3] = LoadGraph("data/img/chara/c001_4.png");

	chara_img[1][0] = LoadGraph("data/img/chara/c002_1.png");
	chara_img[1][1] = LoadGraph("data/img/chara/c002_2.png");
	chara_img[1][2] = LoadGraph("data/img/chara/c002_3.png");
	chara_img[1][3] = LoadGraph("data/img/chara/c002_4.png");

	// デザイン系
	design_img[0] = LoadGraph("data/img/design/bar.png");
	design_img[1] = LoadGraph("data/img/design/bar2.png");
	design_img[2] = LoadGraph("data/img/design/circle.png");
	design_img[3] = LoadGraph("data/img/design/dialog.png");

	// タイトルの画像読み込み
	title_img_1 = LoadGraph("data/img/title/title_1.png");
	title_img_2 = LoadGraph("data/img/title/title_2.png");

	menu_bg_1 = LoadGraph("data/img/title/bg_1.png");
	menu_bg_2 = LoadGraph("data/img/title/bg_2.png");

	title_selected = LoadGraph("data/img/title/selected.png");

	menu_sehnd[0] = LoadSoundMem("data/sound/se/menu/sele_u.wav");
	menu_sehnd[1] = LoadSoundMem("data/sound/se/menu/sele_d.wav");
	menu_sehnd[2] = LoadSoundMem("data/sound/se/menu/sele_c.wav");

	// bg面画像
	LoadDivGraph("data/img/tip/obj.png", 880, 88, 10, 24, 24, maptip_img);

	// pwup画像
	LoadDivGraph("data/img/gui/powerup.png", 2, 2, 1, 128, 30, pwrup_img);

	// 弾画像
	LoadDivGraph("data/img/bullet/14x14.png", 84, 14, 6, 14, 14, bullet14_img);
	LoadDivGraph("data/img/bullet/16x16.png", 48,  6, 7, 14, 14, bullet16_img);

	// 最後に1/2
	for (int i = 0; i < 2; i++)
		GraphFilter(chara_img[i][0], DX_GRAPH_FILTER_DOWN_SCALE, 2);

	// 軽いやつ読み込み
	LPCSTR font_path = "data/font/Veger(light).ttf";
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// フォント読込エラー処理
		MessageBox(NULL, "フォントの読込に失敗しちゃった...", "ごめんね＞＜", MB_OK);
	}

	// 自機画像
	for (int i = 0; i < 2; i++) {
		int buf[5];
		if (i == 0) {
			LoadDivGraph("data/img/ship/ship_bro.png", 5, 1, 5, 100, 50, buf);
		}
		else {
			//LoadDivGraph("data/img/ship/ship_bro.png", 5, 1, 5, 100, 50, buf);
		}
		for (int j = 0; j < 5; j++) {
			ship_img[j][i] = buf[j];
		}
	}
}

// エフェクトの読み込み
void load_Effect() {
	effects[0] = LoadEffekseerEffect(_T("data/effect/laser.efk"));
	effects[1] = LoadEffekseerEffect(_T("data/effect/noumison_Laser.efk"));
}

void make_FontData() {
	font_handle[FONT_BUTTON]  = CreateFontToHandle("Meiryo", 18, 2, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	font_handle[FONT_HEADING] = CreateFontToHandle("Meiryo", 40, 5, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	font_handle[FONT_COMBOX]  = CreateFontToHandle("Meiryo", 10, 2, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	font_handle[FONT_TI_MENU] = CreateFontToHandle("Voyager Grotesque Light", 40, 2, DX_FONTTYPE_ANTIALIASING_4X4);
	font_handle[FONT_BIG]     = CreateFontToHandle("Voyager Grotesque Light", 60, 2, DX_FONTTYPE_ANTIALIASING_4X4);
	font_handle[FONT_INGAME]  = CreateFontToHandle("Voyager Grotesque Light", 28, 2, DX_FONTTYPE_ANTIALIASING_4X4);
}

void debug_Init() {
	
	// debug ship
	ship.init();

	// debug stage
	test.init(500, 40);
	test.set_StagePos(0, 0);

	// CSVリーダ
	test.io_StageDataLoad();

	// 弾関数用初期化
	b_anim_3 = b_anim_4 = b_anim_6 = 0;
	b_dir_3 = b_dir_6 = 1;

	frame_Time = 1.0f / 60.0f;
	frame_Time_2 = 1.0f;
	prev_Time = GetNowHiPerformanceCount();

	// スコアと残基
	score = 0;
	left = 3;
}

void debug_GameMain() {

	// エフェクト用背景ヌリ
	//DrawGraph(0, 0, bg_handle, TRUE);

	// debug stage move and draw.
	test.move(2, 90);
	test.draw();

	// ステージ進行
	test.stage_Progression(); // CSV解析
	test.stage_EnemyMove();   // 敵動作

	// debug my ship move and draw
	ship.move();
	ship.draw();

	// draw debug message
	debug_Message();

	// bullet update
	bullet_Animation_Update();
}

void debug_Message() {
	// DrawFormatString(0, 0, GetColor(255, 255, 255), "Scroll_X:%d / Scroll_Y:%d", (int)test.x, (int)test.y);
}

double fps_Calc() {

	if (fps_Time_i == 0) fps_Time[0] = GetNowCount();
	if (fps_Time_i == 49) {
		fps_Time[1] = GetNowCount();
		fps = 1000.0f / ((fps_Time[1] - fps_Time[0]) / 50.0f);
		fps_Time_i = 0;
	}
	else {
		fps_Time_i++;
	}
	return fps;
}

float variable_Fps() {

	//可変フレーム計算
	frame_Time_2 = (float)(GetNowHiPerformanceCount() - prev_Time);
	frame_Time = frame_Time_2 / 25600.0f;
	prev_Time = GetNowHiPerformanceCount();

	return 0;
}