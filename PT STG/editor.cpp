
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

void main_Editor(void) {

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
				io_LoadStageData();
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

void io_SaveStageData(void) {

	char path[128];
	sprintf_s(path, 128, "data/maps/stage_1/stagedata.csv");

	ofstream ofs(path);

	for (int i = 0; i < enemy_max; i++) {
		char buf[128];
		sprintf_s(buf, 128, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", editor[i].start_x, editor[i].enemy_type, editor[i].var_1, editor[i].var_2, editor[i].var_3, editor[i].var_4, editor[i].var_5, editor[i].var_6, editor[i].var_7);
		ofs << buf << endl;
	}
	ofs.close();
}

void io_LoadStageData(void) {

	for (int i = 0; i < 300; i++) {
		editor[i].enemy_type = -1;
	}

	// たりなさそうなら適時増やす
	const int BufMax = 128;
	char buf[BufMax];

	FILE *fp = NULL;

	int  line_count = 0;
	char(*data)[BufMax];

	// CSVを開く
	errno_t err;
	err = fopen_s(&fp, _T("data/maps/stage_1/stagedata.csv"), "r");
	if (err == 0) {
		while (fgets(buf, sizeof(buf), fp) != NULL) {
			line_count++;
		}
	}
	// 今後のループ用に
	enemy_max = line_count;

	fp = NULL;
	// CSVを開く(読み込まないとFPのポインタが初期化されなくてなんかうまくいかないけど汚いよね)
	err = fopen_s(&fp, _T("data/maps/stage_1/stagedata.csv"), "r");

	// 格納時に使う変数初期化
	int c;
	int col = 1;
	int row = 0;

	memset(buf, 0, sizeof(buf));

	// ここから先は結構マジック
	// ヘッダ読み飛ばし
	//while (fgetc(fp) != '\n');
	while (1) {
		while (1) {

			c = fgetc(fp);

			// 末尾ならループを抜ける。
			if (c == EOF) goto LOOP_OUT;

			// カンマか改行でなければ、文字としてつなげる
			if (c != ',' && c != '\n') {
				strcat_s(buf, (const char*)&c);
			}
			// カンマか改行ならループ抜ける。
			else { break; }
		}
		// ここに来たということは、1セル分の文字列が出来上がったということ
		switch (col) {
			// インスタンス生成X座標
		case 1:
			editor[row].start_x = atoi(buf);
			break;
			// 敵の種類
		case 2:
			editor[row].enemy_type = atoi(buf);
			break;
			// 各インスタンスの引数
		case 3:
			editor[row].var_1 = atoi(buf);
			break;
		case 4:
			editor[row].var_2 = atoi(buf);
			break;
		case 5:
			editor[row].var_3 = atoi(buf);
			break;
		case 6:
			editor[row].var_4 = atoi(buf);
			break;
		case 7:
			editor[row].var_5 = atoi(buf);
			break;
		case 8:
			editor[row].var_6 = atoi(buf);
			break;
		case 9:
			editor[row].var_7 = atoi(buf);
			break;
		}
		// バッファを初期化
		memset(buf, 0, sizeof(buf));
		// 列数を足す
		col++;

		// もし読み込んだ文字が改行だったら列数を初期化して行数を増やす
		if (c == '\n') {
			col = 1;
			row++;
		}
	}
LOOP_OUT: // ループパス用のラベル
	fclose(fp);

}



//-------------------------------------------------------------------------------
//
//   エディタ  ??tsmain
//
//-------------------------------------------------------------------------------
// エディタ本体のメイン
int draw_StageEditor(void) {

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

	unsigned int nc = GetColor(150, 150, 150);
	unsigned int oc = GetColor(180, 180, 180);

	// 保存ボタン
	if (button.draw_Button(1010, 40, 260, 28, nc, oc, "ステージを上書き保存")) {
		io_MapdataFileOutput();
	}
	// タイトルに戻るボタン
	if (button.draw_Button(1010, 75, 260, 28, nc, oc, "保存してタイトルへ")) {
		io_MapdataFileOutput();
		gamemode  = 1; // タイトルに戻るフラグ
		mode_flag = 0; // エディタのメニュー初期化
	}

	return 0;
}







// メニュー類の描画 ??tsm
// *------------------------------------------------------------------------------------*
void draw_StageEditorMenu(void) {

	DrawBox(1000, 0, 1280, 720, GetColor(200, 200, 200), TRUE);

	if (button.draw_Button(1000, 200, 70, 30, GetColor(100,   0,   0), GetColor(55,  0,  0), "ｽﾃｰｼﾞ")    == true) editor_mode = 0;
	if (button.draw_Button(1070, 200, 70, 30, GetColor(  0, 100,   0), GetColor( 0, 55,  0), "ｴﾈﾐｰ")     == true) editor_mode = 1;
	if (button.draw_Button(1140, 200, 70, 30, GetColor(  0,   0, 100), GetColor( 0,  0, 55), "フラグ")   == true) editor_mode = 2;
	if (button.draw_Button(1210, 200, 70, 30, GetColor(100, 100,   0), GetColor(55, 55,  0), "工事中")   == true) editor_mode = 3;

	switch (editor_mode) {
	case 0:
		DrawBox(1000, 230, 1280, 720, GetColor(100, 0, 0), TRUE);
		draw_StageEditorMenuStage();
		break;
	case 1:
		DrawBox(1000, 230, 1280, 720, GetColor(0, 100, 0), TRUE);
		draw_StageEditorMenuEnemy();
		break;
	case 2:
		DrawBox(1000, 230, 1280, 720, GetColor(0, 0, 100), TRUE);
		break;
	case 3:
		DrawBox(1000, 230, 1280, 720, GetColor(100, 100, 0), TRUE);
		break;
	}
}






// エネミタブ ??tst
// *------------------------------------------------------------------------------------*
void draw_StageEditorMenuEnemy(void) {

	unsigned int nc = GetColor(100, 100, 100);
	unsigned int oc = GetColor(150, 150, 150);

	DrawFormatStringToHandle(1010, 250, GetColor(255, 255, 255), font_handle[FONT_BUTTON], "エネミー");

	char *list_str2[22] = { "ナッツ", "エダマメン", "ウニズ", "ジェノサイドバナナ", "ピネ", "カイ", "タケノコん", "キノコン", "クワガタん", "ミートボールスパム", "胞子", "ワーム", "ツタン", "ムービングスタチュ", "キモ箱", "出て来るーの", "出て来るーの", "ｼﾝﾀﾞｰﾗﾀﾏｳﾂ", "戦艦ジェノサイド", "タコス", "能美村", "ワーミン" };
	int select_enemy = com2.draw_Combo(1010, 280, 250, 22, list_str2);

	if (button.draw_Button(1010, 610, 260, 28, nc, oc, "消しゴム")) {
		select_erase *= -1;
	}

	// 設置されている敵を表示させる
	for (int i = 0; i < 300; i++) {
		if (editor[i].enemy_type != -1) {
			int gsx, gsy;
			GetGraphSize(enemy_img[editor[i].enemy_type], &gsx, &gsy);
			DrawGraph(editor[i].var_1 - (gsx / 2), editor[i].var_2 - (gsy / 2), enemy_img[editor[i].enemy_type], TRUE);
			DrawBox(editor[i].var_1 - (gsx / 2), editor[i].var_2 - (gsy / 2), editor[i].var_1 + (gsx / 2), editor[i].var_2 + (gsy / 2), 0x00FF00, TRUE);
		}
	}

	// クリック時
	if (mouse_l == 1 && mouse_x < 1000) {
		for (int i = 0; i < 300; i++) {
			if (editor[i].enemy_type == -1) {
				//editor[i].
			}
		}
	}
}





// ステージタブ ??tst
// *------------------------------------------------------------------------------------*
void draw_StageEditorMenuStage(void) {

	DrawFormatStringToHandle(1010, 250, GetColor(255, 255, 255), font_handle[FONT_BUTTON], "マップチップ");

	unsigned int nc = GetColor(100, 100, 100);
	unsigned int oc = GetColor(150, 150, 150);

	// 消しゴムツール-----------------------------------------------------------------
	if (button.draw_Button(1010, 550, 100, 28, nc, oc, "消しゴム")) {
		selected_item = -1;
	}

	// 2x2ペンツール-----------------------------------------------------------------
	if (button.draw_Button(1010, 580, 100, 28, nc, oc, "2x2 Mode")) {
		select_mode *= -1;
		selected_item = -1; // バグ防止で一旦消しゴムに
	}

	// バケツツール-----------------------------------------------------------------
	/*if (button.draw_Button(1010, 610, 100, 28, nc, oc, "塗り潰し")) {
		select_stac   = -1;
		select_fill  *= -1;
		selected_item = -1; // バグ防止で一旦消しゴムに
	}*/

	// 選択されているブロックの表示
	if (selected_item != -1) {
		DrawFormatStringToHandle(1110, 300, GetColor(255, 255, 255), font_handle[FONT_BUTTON], "選択ﾌﾞﾛｯｸ:");
		if (select_mode == 1) {
			DrawGraph(1220, 295, maptip_img[selected_item], TRUE);
		}
		else {
			DrawGraph(1220, 295, maptip_img[selected_item], TRUE);
			DrawGraph(1220 + STAGE_TIP_SIZE, 295, maptip_img[selected_item + 1], TRUE);
			DrawGraph(1220, 295 + STAGE_TIP_SIZE, maptip_img[selected_item + 88], TRUE);
			DrawGraph(1220 + STAGE_TIP_SIZE, 295 + STAGE_TIP_SIZE, maptip_img[selected_item + 89], TRUE);
		}
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
	// ==== クリックされている時 ===============================================================
	if (mouse_l == 1) {

		int palette_x = 4;
		int palette_y = 10;

		// マップチップパレットの操作
		if (select_mode != 1) {
			palette_x = 3;
			palette_y = 9;
		}

		if (mouse_x > tip_x && mouse_x < tip_x + (STAGE_TIP_SIZE * palette_x) &&
			mouse_y > tip_y && mouse_y < tip_y + (STAGE_TIP_SIZE * palette_y)) {

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
			
				if (select_mode == 1) {
					stage_editor[mpx][mpy] = selected_item;
				}
				else {
					if (selected_item != -1) {
						stage_editor[mpx][mpy] = selected_item;
						stage_editor[mpx + 1][mpy] = selected_item + 1;
						stage_editor[mpx][mpy + 1] = selected_item + 88;
						stage_editor[mpx + 1][mpy + 1] = selected_item + 89;
					}
					else {
						stage_editor[mpx][mpy] = selected_item;
						stage_editor[mpx + 1][mpy] = selected_item;
						stage_editor[mpx][mpy + 1] = selected_item;
						stage_editor[mpx + 1][mpy + 1] = selected_item;
					}
				}
			}
		}
	}
	else {
		// ==== クリックされていない時 ===============================================================
		
		int palette_x = 4;
		int palette_y = 10;

		// マップチップパレットの操作
		if (select_mode != 1) {
			palette_x = 3;
			palette_y = 9;
		}
		if (mouse_x > tip_x && mouse_x < tip_x + (STAGE_TIP_SIZE * palette_x) &&
			mouse_y > tip_y && mouse_y < tip_y + (STAGE_TIP_SIZE * palette_y)) {

			// 相対座標
			int mpx = tip_x + (((mouse_x - tip_x) / STAGE_TIP_SIZE) * STAGE_TIP_SIZE);
			int mpy = tip_y + (((mouse_y - tip_y) / STAGE_TIP_SIZE) * STAGE_TIP_SIZE);

			// 画像ハンドルの添字
			if (select_mode == 1) {
				DrawBox(mpx, mpy, mpx + STAGE_TIP_SIZE, mpy + STAGE_TIP_SIZE, 0x00FF00, FALSE);
			}
			else {
				DrawBox(mpx, mpy, mpx + (STAGE_TIP_SIZE * 2), mpy + (STAGE_TIP_SIZE * 2), 0x00FF00, FALSE);
			}
		}
	}
}

// 塗り潰し
// *------------------------------------------------------------------------------------*
void fill(int vx, int vy) {
	
	int fx = vx;
	int fy = vy;
	int fdigx = 0;
	int fdigy = 0;

	for (int i = 0; i < 100; i++) {

		int x = fx + fdigx;
		int y = fy + fdigy;

		stage_editor[x][y] = selected_item;

		if (y - 1 >= 0)          
			if (stage_editor[x][y - 1] == select_stac) fdigy -= 1;
		if (y + 1 < stage_size_y)
			if (stage_editor[x][y + 1] == select_stac) fdigy += 1;
		if (x - 1 >= 0)          
			if (stage_editor[x - 1][y] == select_stac) fdigx -= 1;
		if (x + 1 < stage_size_x)
			if (stage_editor[x + 1][y] == select_stac) fdigx += 1;

	}
}

// ルーラの描画 ??tsru
// *------------------------------------------------------------------------------------*
void draw_StageEditorRuler(void) {

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
void move_StageEditor(void) {
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

bool io_MapdataFileOutput(void) {

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

bool io_MapdataFileLoad(void) {

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
int draw_NewProjectMenu(void) {

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
int draw_EditorMainMenu(void) {

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
void init_EditorStage(void) {

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

	/*/ Editor Global
	stage_size_x = 0,  stage_size_y = 0;
	stage_left_x = 20, stage_left_y = 20;

	mouse_diff_x = 0,  mouse_diff_y = 0;

	editor_mode   = 0;
	selected_item = -1;
	select_mode   = 1;
	select_fill   = 1;
	select_stac   = -1;*/
}

// ステージの破棄
// *------------------------------------------------------------------------------------*

// ※コレ通さないと死ぬから注意
void delete_EditorStage(void) {
	for (int i = 0; i < stage_size_x; i++) {
		delete[] stage_editor[i];
	}
	delete[] stage_editor;
}