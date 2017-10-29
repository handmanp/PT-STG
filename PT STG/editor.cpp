
/* editor.cpp  ??top */

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

using namespace std;

//-------------------------------------------------------------------------------
//
// エディターメインループ ??emain
//
//-------------------------------------------------------------------------------

void main_Editor() {

	int menu_b = -1;
	char path[128];

	switch (mode_flag) {
	case 0: // エディタメニュー画面

		menu_b = draw_EditorMainMenu();

		if (menu_b != -1) {

			sprintf_s(path, 128, "data/maps/stage_%d/mapmeta.txt", menu_b + 1);

			if (PathFileExists(path)) {

				io_LoadMetaData(path);

				char a[128];
				sprintf_s(a, 128, "%d,%d", stage_size_x, stage_size_y);

				io_MapdataFileLoad();
				mode_flag = 2;
			}
			else {
				mode_flag++;
			}
		}

		break;
	case 1: // 新規作成画面
		draw_NewProjectMenu();
		break;
	case 2: // エディタ画面
		draw_StageEditor();
		break;
	default:
		break;
	}
}

void io_LoadMetaData(char *path) {

	FILE *fp_meta;
	fopen_s(&fp_meta, path, "r");

	STAGE_META meta;

	fread_s(&meta, sizeof(STAGE_META), sizeof(STAGE_META), 1, fp_meta);

	stage_size_x = meta.x;
	stage_size_y = meta.y;
}

//-------------------------------------------------------------------------------
//
//   エディタ  ??tsmain
//
//-------------------------------------------------------------------------------
// エディタ本体のメイン
int draw_StageEditor() {

	for (int i = 0; i < stage_size_x; i++) {
		for (int j = 0; j < stage_size_y; j++) {
			switch (stage_editor[i][j]) {
			case -1:
				DrawBox(stage_left_x + (i * STAGE_TIP_SIZE), stage_left_y + (j * STAGE_TIP_SIZE), stage_left_x + (i * STAGE_TIP_SIZE) + STAGE_TIP_SIZE, stage_left_y + (j * STAGE_TIP_SIZE) + STAGE_TIP_SIZE, GetColor(20, 20, 20), FALSE);
				break;
			default:
				DrawGraph(stage_left_x + (i * STAGE_TIP_SIZE), stage_left_y + (j * STAGE_TIP_SIZE), maptip_img[stage_editor[i][j]], TRUE);
				break;
			}
		}
	}

	move_StageEditor();
	draw_StageEditorRuler();
	draw_StageEditorMenu();

	unsigned int nc = GetColor(100, 100, 100);
	unsigned int oc = GetColor(150, 150, 150);

	if (button.draw_Button(1010, 40, 200, 28, nc, oc, "ステージを上書き保存")) {
		io_MapdataFileOutput();
	}

	return 0;
}


// メニュー類の描画 ??tsm
// *------------------------------------------------------------------------------------*
void draw_StageEditorMenu() {

	DrawBox(1000, 0, 1280, 720, GetColor(100, 100, 100), TRUE);

	if (button.draw_Button(1000, 200, 70, 30, GetColor(100,   0,   0), GetColor(55,  0,  0), "ｽﾃｰｼﾞ")    == true) editor_mode = 0;
	if (button.draw_Button(1070, 200, 70, 30, GetColor(  0, 100,   0), GetColor( 0, 55,  0), "ｴﾈﾐｰ")     == true) editor_mode = 1;
	if (button.draw_Button(1140, 200, 70, 30, GetColor(  0,   0, 100), GetColor( 0,  0, 55), "フラグ")   == true) editor_mode = 2;
	if (button.draw_Button(1210, 200, 70, 30, GetColor(100, 100,   0), GetColor(55, 55,  0), "工事中")   == true) editor_mode = 3;

	char *list_str2[4] = {"ステージ１の敵", "ステージ２の敵", "ステージ３の敵", "ボス", };

	switch (editor_mode) {
	case 0:
		DrawBox(1000, 230, 1280, 720, GetColor(100, 0, 0), TRUE);
		draw_StageEditorMenuStage();
		break;
	case 1:
		DrawBox(1000, 230, 1280, 720, GetColor(0, 100, 0), TRUE);
		com.draw_Combo(1010, 300, 250, 4, list_str2);
		break;
	case 2:
		DrawBox(1000, 230, 1280, 720, GetColor(0, 0, 100), TRUE);
		break;
	case 3:
		DrawBox(1000, 230, 1280, 720, GetColor(100, 100, 0), TRUE);
		break;
	}
}

// ステージタブ ??tst
// *------------------------------------------------------------------------------------*
void draw_StageEditorMenuStage() {

	DrawFormatStringToHandle(1010, 250, GetColor(255, 255, 255), font_handle[FONT_BUTTON], "マップチップ");

	unsigned int nc = GetColor(100, 100, 100);
	unsigned int oc = GetColor(150, 150, 150);

	if (button.draw_Button(1010, 600, 100, 28, nc, oc, "消しゴム")) {
		selected_item = -1;
	}

	if (selected_item != -1) {
		DrawFormatStringToHandle(1110, 300, GetColor(255, 255, 255), font_handle[FONT_BUTTON], "選択ﾌﾞﾛｯｸ:");
		DrawGraph(1220, 295, maptip_img[selected_item], TRUE);
	}

	// チップ定数
	const int tip_x = 1010;
	const int tip_y = 280;

	// マップチップパレットの背景
	DrawBox(tip_x, tip_y, tip_x + 96, tip_y + 160, GetColor(0, 0, 0), TRUE);

	// コンボボックスの中を指定して描画して戻り値取得
	char *list_str[22] = { "宇宙窓1", "宇宙窓2", "宇宙窓3", "回路1", "回路2", "ハイテク1", "ハイテク2", "ロステク", "細胞1", "細胞2", "細胞3", "LSI1", "壁", "LSI2", "ハイテク3", "ハイテク4", "宇宙窓4", "MATRIX", "ロステク2", "壊死1", "壊死2", "ロステク壁" };
	int margin = com.draw_Combo(1150, 250, 100, 22, list_str) * 4;

	// マップチップパレット描画用
	int margin_m = margin;

	// マップチップ描画
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 4; j++) {
			DrawGraph(tip_x + (j * STAGE_TIP_SIZE), tip_y + (i * STAGE_TIP_SIZE), maptip_img[margin_m + j], TRUE);
		}
		margin_m += 88;
	}

	// マップチップクリック判定
	if (mouse_l == 1) {

		// マップチップパレットの操作
		if (mouse_x > tip_x && mouse_x < tip_x + (STAGE_TIP_SIZE * 4) &&
			mouse_y > tip_y && mouse_y < tip_y + (STAGE_TIP_SIZE * 10)) {

			// 相対座標
			int mpx = mouse_x - tip_x;
			int mpy = mouse_y - tip_y;

			// 画像ハンドルの添字
			selected_item = ((mpy / STAGE_TIP_SIZE) * 88) + (mpx / STAGE_TIP_SIZE) + margin;
		}

		// ステージエディタの操作
		if (mouse_x < 1000) {

			// エディタ用の座標取得
			int mpx = (mouse_x - stage_left_x) / STAGE_TIP_SIZE;
			int mpy = (mouse_y - stage_left_y) / STAGE_TIP_SIZE;

			DrawFormatString(0, 0, 0xFFFFFF, "%d %d", mpx, mpy);

			// エディタの範囲内か調べる
			if (mpx >= 0 && mpx < stage_size_x &&
				mpy >= 0 && mpy < stage_size_y) {
				stage_editor[mpx][mpy] = selected_item;
			}
		}
	}
}

// ルーラの描画 ??tsru
// *------------------------------------------------------------------------------------*
void draw_StageEditorRuler() {

	// X軸ルーラ
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

	// Y軸ルーラ
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

// エディタの移動
// *------------------------------------------------------------------------------------*
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

// 出力  true = 多分成功してる, false = 多分失敗してる
// *------------------------------------------------------------------------------------*

bool io_MapdataFileOutput() {

	char path[128];
	//sprintf_s(path, 128, "data/editor/saves/0%d/mapdata.txt", map_slot);
	sprintf_s(path, 128, "data/maps/stage_%d/mapdata.txt", map_slot);

	char path_meta[128];
	//sprintf_s(path, 128, "data/editor/saves/0%d/mapdata.txt", map_slot);
	sprintf_s(path_meta, 128, "data/maps/stage_%d/mapmeta.txt", map_slot);

	FILE *fp_meta;

	errno_t error_2 = fopen_s(&fp_meta, path_meta, "w+");
	if (error_2 == 0) {
		STAGE_META meta;
		meta.stats = 0;
		meta.x = stage_size_x;
		meta.y = stage_size_y;

		fwrite(&meta, sizeof(meta), 1, fp_meta);

		fclose(fp_meta);
	}

	ofstream ofs; ofs.open(path);
	for (int i = 0; i < stage_size_x; i++) {
		for (int j = 0; j < stage_size_y; j++) {
			ofs << stage_editor[i][j] << endl;
		}
	}
	ofs.close();

	return true;
}

// 入力  true = 多分成功してる, false = 多分失敗してる
// *------------------------------------------------------------------------------------*

bool io_MapdataFileLoad() {

	init_EditorStage();

	char path[128];
	//sprintf_s(path, 128, "data/editor/saves/0%d/mapdata.txt", map_slot);
	sprintf_s(path, 128, "data/maps/stage_%d/mapdata.txt", map_slot);

	ifstream ifs; ifs.open(path);
	for (int i = 0; i < stage_size_x; ++i) {
		for (int j = 0; j < stage_size_y; ++j) {
			ifs >> stage_editor[i][j];
		}
	}
	ifs.close();

	return true;
}



//-------------------------------------------------------------------------------
//
//   メニュー
//
//-------------------------------------------------------------------------------

// 新規作成画面の描画
// *------------------------------------------------------------------------------------*
int draw_NewProjectMenu() {

	DrawBox(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y, GetColor(10, 10, 10), TRUE);

	unsigned int nc = GetColor(100, 100, 100);
	unsigned int oc = GetColor(150, 150, 150);

	DrawFormatStringToHandle(100, 60,  GetColor(255, 255, 255), font_handle[FONT_HEADING], "新規ステージ作成");
	DrawFormatStringToHandle(100, 130, GetColor(255, 255, 255), font_handle[FONT_BUTTON], "■ステージサイズを設定しよう(500x50以下には設定できません)");

	DrawFormatStringToHandle(100, 210, GetColor(255, 255, 255), font_handle[FONT_HEADING], "X:        Block × Y:        Block");

	// X+
	if (button.draw_Button(150, 170, 28, 28, nc, oc, "▲") == true) ss_x[3]++;
	if (button.draw_Button(180, 170, 28, 28, nc, oc, "▲") == true) ss_x[2]++;
	if (button.draw_Button(210, 170, 28, 28, nc, oc, "▲") == true) ss_x[1]++;
	if (button.draw_Button(240, 170, 28, 28, nc, oc, "▲") == true) ss_x[0]++;

	// X-
	if (button.draw_Button(150, 260, 28, 28, nc, oc, "▼") == true) ss_x[3]--;
	if (button.draw_Button(180, 260, 28, 28, nc, oc, "▼") == true) ss_x[2]--;
	if (button.draw_Button(210, 260, 28, 28, nc, oc, "▼") == true) ss_x[1]--;
	if (button.draw_Button(240, 260, 28, 28, nc, oc, "▼") == true) ss_x[0]--;

	// Y+
	if (button.draw_Button(490, 170, 28, 28, nc, oc, "▲") == true) ss_y[3]++;
	if (button.draw_Button(520, 170, 28, 28, nc, oc, "▲") == true) ss_y[2]++;
	if (button.draw_Button(550, 170, 28, 28, nc, oc, "▲") == true) ss_y[1]++;
	if (button.draw_Button(580, 170, 28, 28, nc, oc, "▲") == true) ss_y[0]++;

	// Y-
	if (button.draw_Button(490, 260, 28, 28, nc, oc, "▼") == true) ss_y[3]--;
	if (button.draw_Button(520, 260, 28, 28, nc, oc, "▼") == true) ss_y[2]--;
	if (button.draw_Button(550, 260, 28, 28, nc, oc, "▼") == true) ss_y[1]--;
	if (button.draw_Button(580, 260, 28, 28, nc, oc, "▼") == true) ss_y[0]--;

	// ハミリ処理
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

	// 最低値
	if (stage_size_x < 500) {
		ss_x[0] = 0;
		ss_x[1] = 0;
		ss_x[2] = 5;
	}
	if (stage_size_y < 50) {
		ss_y[0] = 0;
		ss_y[1] = 5;
	}

	// 作成ボタン
	if (button.draw_Button(860, 550, 300, 100, nc, oc, "作成") == true) {
		init_EditorStage();
		mode_flag++;
	}

	return 0;
}

// エディターのメインメニュー描画
// *------------------------------------------------------------------------------------*
int draw_EditorMainMenu() {

	DrawBox(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y, GetColor(10, 10, 10), TRUE);

	unsigned int nc = GetColor(100, 100, 100);
	unsigned int oc = GetColor(150, 150, 150);

	bool return_data[5];

	for (int i = 0; i < 5; i++) {
		return_data[i] = button.draw_Button(750, 60 + (i * 120), 450, 100, nc, oc, "ステージセーブデータ：Ｎｏｎｅ");
		if (return_data[i] == true) {
			return i;
		}
	}

	DrawFormatStringToHandle(100, 60,  GetColor(255, 255, 255), font_handle[FONT_HEADING], "ステージエディター");
	DrawFormatStringToHandle(100, 130, GetColor(255, 255, 255), font_handle[FONT_BUTTON],  "本編に出てきた素材を使って自らステージを作るモードだよ！\n想像力を活かして自分だけのオリジナルステージをプレイしよう！");

	return -1;
}

// エディター用BG面配列の初期化
// *------------------------------------------------------------------------------------*
void init_EditorStage() {

	// 3次元配列の動的確保（カッコイイ）
	stage_editor = new int*[stage_size_x];
	for (int i = 0; i < stage_size_x; i++) {
		stage_editor[i] = new int[stage_size_y];
	}
	// 初期化
	for (int i = 0; i < stage_size_x; i++) {
		for (int j = 0; j < stage_size_y; j++) {
			stage_editor[i][j] = -1;
			stage_editor[i][j] = -1;
		}
	}
}

// ステージの破棄
// *------------------------------------------------------------------------------------*

// ※コレ通さないと死ぬから注意
void delete_EditorStage() {
	for (int i = 0; i < stage_size_x; i++) {
		delete[] stage_editor[i];
	}
	delete[] stage_editor;
}