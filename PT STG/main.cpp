#define GLOBAL_VALIABLE_DEFINE
#include "global.h"

#define LOADING  0
#define TOP_MENU 1
#define GAME     2
#define EDITOR   3

class bg_star {
public:
	float x[50];
	float y[50];
	int   layer[50];
	void init() {
		for (int i = 0; i < 50; i++) {
			x[i] = (float)GetRand(WINDOW_SIZE_X);
			y[i] = (float)GetRand(WINDOW_SIZE_Y);
			layer[i] = GetRand(3);
		}
	}
	void move() {
		for (int i = 0; i < 50; i++) {
			float speed = 0.5f + (stage_scroll_speed * (float)layer[i]);
			x[i] -= speed * frame_Time;
			if (x[i] < -30) {
				x[i] = WINDOW_SIZE_X + 30;
				y[i] = (float)GetRand(WINDOW_SIZE_Y);
				layer[i] = GetRand(3);
			}
		}
	}
	void draw() {
		// DrawGraph(-400, 300, bg_handle[1], TRUE);
		for (int i = 0; i < 50; i++) {
			DrawRotaGraph2(x[i], y[i],
				10, 10,
				0.6 / (3.0 - (double)layer[i]), a2r(GetRand(360)),
				bgstar[GetRand(3)], TRUE, FALSE);
		}
	}
};
bg_star star;

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
	LPSTR lpCmdLine, int nCmdShow){

	// 設定
	ChangeWindowMode(true);
	SetGraphMode(WINDOW_SIZE_X, WINDOW_SIZE_Y, 32);
	SetMainWindowText("LUNETTE \t <Project Trial Edition v1.0.0>");

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
	//debug_Init();

	// ゲームモード : TOP_MENU / GAME / EDITOR
	gamemode  = TOP_MENU;
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
		if (frame % (int)((200.f * frame_Time) + 1) == 0) UpdateEffekseer2D();
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
	bg_handle[0] = LoadGraph(_T("data/img/bg/bg000.png"));
	bg_handle[1] = LoadGraph(_T("data/img/bg/bg.png"));

	// 敵画像
	// stage:1
	enemy_img[EneUnis]       = LoadGraph("data/img/enemy/st1/unis.png");			// ウニズ
	enemy_img[EneEdamamen]   = LoadGraph("data/img/enemy/st1/edamamen.png");		// エダマメン
	enemy_img[EneNuts]       = LoadGraph("data/img/enemy/st1/nuts.png");			// ナッツ
	enemy_img[EnePine]       = LoadGraph("data/img/enemy/st1/pine.png");			// ピネ
	enemy_img[EneKai]        = LoadGraph("data/img/enemy/st1/kai.png");				// カイ
	enemy_img[EneBanana]     = LoadGraph("data/img/enemy/st1/genocide_banana.png"); // ジェノサイドバナナ
	enemy_img[EneStatue]     = LoadGraph("data/img/enemy/st1/moving_statue.png");	// moving statue
	enemy_img[EneMeatball]   = LoadGraph("data/img/enemy/st1/meatball_spam.png");	// ミートボールスパム
	enemy_img[EneTutan]      = LoadGraph("data/img/enemy/st1/ivy_1.png");			// ツタ
	enemy_img[EneHoushi]     = LoadGraph("data/img/enemy/st1/sporecore.png");		// 胞子コア
	enemy_img[EneKuwagatan]  = LoadGraph("data/img/enemy/st1/kuwagatan.png");		// クワガタん
	enemy_img[EneWarm]       = LoadGraph("data/img/enemy/st1/worm_head.png");		// ワームヘッド
	//enemy_img[13] 予約 <ワーム尻尾>
	enemy_img[EneWarmBody]   = LoadGraph("data/img/enemy/st1/worm_body.png");		// ワームボディ
	enemy_img[EneGenocide]   = LoadGraph("data/img/enemy/st1/genocide.png");		// ジェノサイド
	enemy_img[EneKimobako]   = LoadGraph("data/img/enemy/st1/kimobako");			// キモバコ
	enemy_img[EneTamautsu]   = LoadGraph("data/img/enemy/st1/sindarla.png");		// シンダーラ
	enemy_img[EneDetekuruno] = LoadGraph("data/img/enemy/st1/detecrewno.png");		// デテクルーノ本体
	enemy_img[EneDetekuki]   = LoadGraph("data/img/enemy/st1/detecrewno_kuki.png");// デテクルーノ茎
	enemy_img[BossNoumison]  = LoadGraph("data/img/enemy/st1/noumison.png");		// ノウミソン

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
	design_img[4] = LoadGraph("data/img/design/menu.png");

	// タイトルの画像読み込み
	title_img_1 = LoadGraph("data/img/title/title_1.png");
	title_img_2 = LoadGraph("data/img/title/title_2.png");

	menu_bg_1 = LoadGraph("data/img/title/bg_1.png");
	menu_bg_2 = LoadGraph("data/img/title/bg_2.png");

	title_selected = LoadGraph("data/img/title/selected.png");

	menu_sehnd[0] = LoadSoundMem("data/sound/se/menu/sele_u.wav");
	menu_sehnd[1] = LoadSoundMem("data/sound/se/menu/sele_d.wav");
	menu_sehnd[2] = LoadSoundMem("data/sound/se/menu/sele_c.wav");

	game_sehnd[0] = LoadSoundMem("data/sound/se/game/beam1.mp3");
	game_sehnd[1] = LoadSoundMem("data/sound/se/game/bomb.mp3");
	game_sehnd[2] = LoadSoundMem("data/sound/se/game/dest.mp3");
	game_sehnd[3] = LoadSoundMem("data/sound/se/game/laser.mp3");
	game_sehnd[4] = LoadSoundMem("data/sound/se/game/shot1.mp3");
	game_sehnd[5] = LoadSoundMem("data/sound/se/game/shot2.mp3");

	game_bgmhnd[0] = LoadSoundMem("data/sound/bgm/awake.mp3");
	game_bgmhnd[1] = LoadSoundMem("data/sound/bgm/ang.mp3");
	game_bgmhnd[2] = LoadSoundMem("data/sound/bgm/fly.mp3");
	game_bgmhnd[3] = LoadSoundMem("data/sound/bgm/pump.mp3");

	// bg面画像
	LoadDivGraph("data/img/tip/obj.png", 880, 88, 10, 24, 24, maptip_img);

	// pwup画像
	LoadDivGraph("data/img/gui/powerup.png", 2, 2, 1, 128, 30, pwrup_img);

	// 弾画像
	LoadDivGraph("data/img/bullet/14x14.png", 84, 14, 6, 14, 14, bullet14_img);
	LoadDivGraph("data/img/bullet/16x16.png", 48,  6, 7, 14, 14, bullet16_img);

	LoadDivGraph("data/img/bullet/star.png", 8, 8, 1, 20, 14, bgstar);

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
	font_handle[FONT_PWUP]    = CreateFontToHandle("Voyager Grotesque Light", 22, 2, DX_FONTTYPE_ANTIALIASING_4X4);
}

void debug_Init() {
	
	// debug ship
	ship.init();
	star.init();

	// debug stage
	test.init(500, 40);
	test.set_StagePos(0, 0);

	// 敵構造体初期化
	memset(&unis[0], 0x00, sizeof(unis));
	memset(&pine[0], 0x00, sizeof(pine));
	memset(&brain[0], 0x00, sizeof(brain));
	memset(&nuts[0], 0x00, sizeof(nuts));
	memset(&shell[0], 0x00, sizeof(shell));
	memset(&banana[0], 0x00, sizeof(banana));
	memset(&statue[0], 0x00, sizeof(statue));
	memset(&ivy[0], 0x00, sizeof(ivy));
	memset(&kuwagatan[0], 0x00, sizeof(kuwagatan));
	memset(&houshi[0], 0x00, sizeof(houshi));
	memset(&genocide[0], 0x00, sizeof(genocide));
	memset(&sindarla[0], 0x00, sizeof(sindarla));
	memset(&detecrew[0], 0x00, sizeof(detecrew));
	memset(&meat[0], 0x00, sizeof(meat));

	// CSVリーダ
	test.io_StageDataLoad();
	test.io_MapdataFileLoad();

	// 弾関数用初期化
	b_anim_3 = b_anim_4 = b_anim_6 = 0;
	b_dir_3 = b_dir_6 = 1;

	frame_Time = 1.0f / 60.0f;
	frame_Time_2 = 1.0f;
	prev_Time = GetNowHiPerformanceCount();

	stage_scroll_speed = to_stage_scroll_speed = 2.0f;
	stage_scroll_rad   = to_stage_scroll_rad   = 90.f;

	for (int i = 0; i < 22; i++) {
		test.enemy_count[i] = 0;
	}

	//for (int i = 0; i < EACH_ENEMY_MAX; i++) {

	//}

	// スコアと残基
	score = 0;
	pause_flag = 0;
}

void debug_GameMain() {

	// エフェクト用背景ヌリ
	//DrawGraph(0, 0, bg_handle, TRUE);
	if (pause_flag == 0) {
		// debug stage move and draw.
		if (stage_scroll_speed != to_stage_scroll_speed) {
			if (stage_scroll_speed > to_stage_scroll_speed) stage_scroll_speed--;
			if (stage_scroll_speed < to_stage_scroll_speed) stage_scroll_speed++;
		}
		if (stage_scroll_rad != to_stage_scroll_rad) {
			if (stage_scroll_rad > to_stage_scroll_rad) stage_scroll_rad--;
			if (stage_scroll_rad < to_stage_scroll_rad) stage_scroll_rad++;
		}
		test.move(stage_scroll_speed, stage_scroll_rad);

		// ステージ進行
		test.stage_Progression(); // CSV解析
		test.stage_EnemyMove();   // 敵動作

		// debug my ship move and draw
		item_move();
		star.move();
		ship.move();

		// draw debug message
		debug_Message();

		// bullet update
		bullet_Animation_Update();
	}

	// 描画関連
	star.draw();
	test.draw();
	ingame_GUI();
	ship.draw();

	if (pause_flag == 1) draw_Pause();
	if (pause_flag == 2) draw_Over();
}

void debug_Message() {
	 // DrawFormatString(600, 0, GetColor(255, 255, 255), "Scroll_X:%f / Scroll_Y:%f", test.x, test.y);
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