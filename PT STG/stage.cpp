#include "global.h"

using namespace std;

// ステージの初期化
// sx:ステージ幅 sy:ステージ高さ
void my_Stage::init(int sx, int sy) {

	// クラス用再定義
	stage_size_x = sx; //サイズ
	stage_size_y = sy;

	// 3次元配列の動的確保（カッコイイ）
	stage_size = new int*[stage_size_x];
	for (int i = 0; i < stage_size_x; i++) {
		stage_size[i] = new int[stage_size_y];
	}
	// 初期化
	for (int i = 0; i < stage_size_x; i++) {
		for (int j = 0; j < stage_size_y; j++) {
			stage_size[i][j] = -1;
		}
	}
	memset(enemy_count, 0, sizeof(enemy_count));
}

// メタ入力  true = 多分成功してる, false = 多分失敗してる
// *------------------------------------------------------------------------------------*
void  my_Stage::io_LoadMetaData(char *path) {

	FILE *fp_meta;
	fopen_s(&fp_meta, path, "r");

	STAGE_METAS meta;

	fread_s(&meta, sizeof(STAGE_METAS), sizeof(STAGE_METAS), 1, fp_meta);

	stage_size_x = meta.x;
	stage_size_y = meta.y;
}

// 入力  true = 多分成功してる, false = 多分失敗してる
// *------------------------------------------------------------------------------------*

bool my_Stage::io_MapdataFileLoad() {

	char paths[128];
	sprintf_s(paths, 128, "data/maps/stage_%d/mapmeta.txt", 1);
	io_LoadMetaData(paths);

	init(stage_size_x, stage_size_y);

	char path[128];
	//sprintf_s(path, 128, "data/editor/saves/0%d/mapdata.txt", map_slot);
	sprintf_s(path, 128, "data/maps/stage_%d/mapdata.txt", 1);

	ifstream ifs; ifs.open(path);
	for (int i = 0; i < stage_size_x; ++i) {
		for (int j = 0; j < stage_size_y; ++j) {
			ifs >> stage_size[i][j];
		}
	}
	ifs.close();

	return true;
}


// ステージの破棄
// ※コレ通さないと死ぬから注意
void my_Stage::del_Stage() {
	for (int i = 0; i < stage_size_x; i++) {
		delete[] stage_size[i];
	}
	delete[] stage_size;
	//delete[] stage_data;
}

// ステージの移動
// s:移動スピート r:移動角度
void my_Stage::move(int s, int r) {
	// スピードをメンバに追加
	speed = s;
	//ラジアンにする
	move_rad = (DX_PI_F / 180.0f) * r;
	// 移動処理
	x += sinf(move_rad) * s * frame_Time;
	y += cosf(move_rad) * s * frame_Time;
}

// ステージを描画
void my_Stage::draw() {
	for (int i = 0; i < stage_size_x; i++) {
		for (int j = 0; j < stage_size_y; j++) {
			if (stage_size[i][j] != -1) {
				//ブロックの相対座標
				int dpx = (i * STAGE_TIP_SIZE) - x;
				int dpy = (j * STAGE_TIP_SIZE) - y;
				//面内のみ描画
				if (dpx >= -STAGE_TIP_SIZE && dpx <= WINDOW_SIZE_X + STAGE_TIP_SIZE &&
					dpy >= -STAGE_TIP_SIZE && dpy <= WINDOW_SIZE_Y + STAGE_TIP_SIZE) {
					
					DrawGraph(dpx, dpy, maptip_img[stage_size[i][j]], TRUE);

					// ステージと自機との当たり判定
					if (abs((dpx + (STAGE_TIP_SIZE / 2)) - ship.x) < (STAGE_TIP_SIZE + 80) / 2 &&
						abs((dpy + (STAGE_TIP_SIZE / 2)) - ship.y) < (STAGE_TIP_SIZE + 15) / 2) {
						if (ship.stat == 0) {
							ship.stat = -1;
							ship.x = -120.f;
							ship.y = 340.f;
							ship.left -= 1;
						}
					}
				}
			}
		}
	}
	/*for (int i = 0; i < enemy_max; i++) {
		DrawFormatString(10, 100 + (i * 20), GetColor(200, 200, 200), "%d, %d, %d, %d, %d, %d, %d",
			stage_data[i].start_x, stage_data[i].enemy_type,
			stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3,
			stage_data[i].var_4, stage_data[i].var_5, stage_data[i].var_6,
			stage_data[i].var_7);
	}*/
}




// ステージの位置を移動する
void my_Stage::set_StagePos(float sx, float sy) {
	x = sx;
	y = sy;
}

// ステージの進行
void my_Stage::stage_Progression() {

	// *================ CSV解析部 ==================* //

	for (int i = 0; i < enemy_max; i++) {

		// 登場X座標を迎えたら
		if ((int)x >= stage_data[i].start_x && stage_data[i].stat != -1) {

			stage_data[i].stat = -1;

			// 敵のインスタンス作成
			switch (stage_data[i].enemy_type) {

				// *------------------------ Stage 1 ------------------------*

				// [0] ナッツ OK
			case EneNuts:
				nuts[enemy_count[EneNuts]].init(stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3, stage_data[i].var_4, stage_data[i].var_5);
				enemy_count[EneNuts]++;
				break;

				// [1] エダマメン wip
			case EneEdamamen:
				// wip
				break;

				// [2] ウニズ
			case EneUnis:
				unis[enemy_count[EneUnis]].init(stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3, stage_data[i].var_4, stage_data[i].var_5);
				enemy_count[EneUnis]++;
				break;

				// [3] ジェノサイドバナナ
			case EneBanana:
				banana[enemy_count[EneBanana]].init(stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3, stage_data[i].var_4);
				enemy_count[EneBanana]++;
				break;

				// [4] ピネ
			case EnePine:
				pine[enemy_count[EnePine]].init(stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3, stage_data[i].var_4, stage_data[i].var_5);
				enemy_count[EnePine]++;
				break;

				// [5] カイ OK
			case EneKai:
				shell[enemy_count[EneKai]].init(stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3, stage_data[i].var_4);
				enemy_count[EneKai]++;
				break;

				// [6] タケノコン wip
			case EneTakenokon:
				break;

				// [7] キノコン wip
			case EneKinokon:
				break;

				// *------------------------ Stage 2 ------------------------*

				// [8] クワガタン
			case EneKuwagatan:
				kuwagatan[enemy_count[EneKuwagatan]].init(stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3, stage_data[i].var_4);
				enemy_count[EneKuwagatan]++;
				break;

				// [9] ミートボールスパム
			case EneMeatball:
				meat[enemy_count[EneMeatball]].init(stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3, stage_data[i].var_4);
				enemy_count[EneMeatball]++;
				break;

				// [10] 胞子
			case EneHoushi:
				houshi[enemy_count[EneHoushi]].init(stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3, stage_data[i].var_4);
				enemy_count[EneHoushi]++;
				break;

				// [11] ワーム
			case EneWarm:
				worm[enemy_count[EneWarm]].init(stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3, stage_data[i].var_4);
				enemy_count[EneWarm]++;
				break;

				// [12] ツタン
			case EneTutan:
				ivy[enemy_count[EneTutan]].init(stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3, stage_data[i].var_4);
				enemy_count[EneTutan]++;
				break;

				// [13] ムービングスタチュー
			case EneStatue:
				statue[enemy_count[EneStatue]].init(stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3, stage_data[i].var_4);
				enemy_count[EneStatue]++;
				break;

				// *------------------------ Stage 3 ------------------------*

				// [14] キモ箱 wip
			case EneKimobako:
				break;

				// [15] デテクルーノ（花） wip
			case EneDetekuruno:
				detecrew[enemy_count[EneDetekuruno]].init(stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3, stage_data[i].var_4);
				enemy_count[EneDetekuruno]++;
				break;

				// [16] デテクルーノ（茎） wip
			case EneDetekuki:
				break;

				// [17] シンダーラタマウツ
			case EneTamautsu:
				sindarla[enemy_count[EneTamautsu]].init(stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3, stage_data[i].var_4);
				enemy_count[EneTamautsu]++;
				break;

				// [18] 戦艦ジェノサイド
			case EneGenocide:
				genocide[enemy_count[EneGenocide]].init(stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3, stage_data[i].var_4);
				enemy_count[EneGenocide]++;
				break;

				// *------------------------ Stage 3 ------------------------*

				// [19] タコス wip
			case BossTacos:
				break;

				// [20] ノウミソン wip
			case BossNoumison:
				brain[enemy_count[BossNoumison]].init(stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3, stage_data[i].var_4);
				enemy_count[BossNoumison]++;
				break;

				// [21] ワーミン wip
			case BossWarmin:
				break;

				// 100 マップの移動速度・角度変更
			case 100:
				to_stage_scroll_speed = stage_data[i].var_1;
				to_stage_scroll_rad   = stage_data[i].var_2;
				break;
				// 110 楽曲の再生
			case 110:
				PlaySoundMem(game_bgmhnd[stage_data[i].var_1], DX_PLAYTYPE_BACK, TRUE);
				break;
			}
		}
	}
}

void my_Stage::stage_EnemyMove() {

	// *------------------------ Stage 1 ------------------------*

	for (int i = 0; i < enemy_count[EneNuts]; i++) {
		nuts[i].move();
	}
	for (int i = 0; i < enemy_count[EneEdamamen]; i++) {
		//edamamen[i].move(); wip
	}
	for (int i = 0; i < enemy_count[EneUnis]; i++) {
		unis[i].move();
	}
	for (int i = 0; i < enemy_count[EneBanana]; i++) {
		banana[i].move();
	}
	for (int i = 0; i < enemy_count[EnePine]; i++) {
		pine[i].move();
	}
	for (int i = 0; i < enemy_count[EneKai]; i++) {
		shell[i].move();
	}
	for (int i = 0; i < enemy_count[EneTakenokon]; i++) {
		//takenokon[i].move(); wip
	}
	for (int i = 0; i < enemy_count[EneKinokon]; i++) {
		//nokonoko[i].move(); wip
	}

	// *------------------------ Stage 2 ------------------------*

	for (int i = 0; i < enemy_count[EneKuwagatan]; i++) {
		kuwagatan[i].move();
	}
	for (int i = 0; i < enemy_count[EneMeatball]; i++) {
		meat[i].move();
	}
	for (int i = 0; i < enemy_count[EneHoushi]; i++) {
		houshi[i].move();
	}
	for (int i = 0; i < enemy_count[EneWarm]; i++) {
		worm[i].move();
	}
	for (int i = 0; i < enemy_count[EneTutan]; i++) {
		ivy[i].move();
	}
	for (int i = 0; i < enemy_count[EneStatue]; i++) {
		statue[i].move();
	}

	// *------------------------ Stage 3 ------------------------*

	for (int i = 0; i < enemy_count[EneKimobako]; i++) {
		//kimobako[i].move(); wip
	}
	for (int i = 0; i < enemy_count[EneDetekuruno]; i++) {
		//detekuruno[i].move(); wip
	}
	for (int i = 0; i < enemy_count[EneDetekuki]; i++) {
		//detekuki[i].move(); wip
	}
	for (int i = 0; i < enemy_count[EneTamautsu]; i++) {
		sindarla[i].move();
	}
	for (int i = 0; i < enemy_count[EneGenocide]; i++) {
		genocide[i].move();
	}

	// *------------------------ Stage 3 ------------------------*
	for (int i = 0; i < enemy_count[BossNoumison]; i++) {
		brain[i].move();
	}
}

// CSV読み込み
void my_Stage::io_StageDataLoad() {

	// たりなさそうなら適時増やす
	const int BufMax = 128;
	char buf[BufMax];

	FILE *fp = NULL;

	int  line_count = 0;
	char (*data)[BufMax];

	// CSVを開く
	errno_t err;
	err = fopen_s(&fp, _T("data/maps/stage_1/stagedata.csv"), "r");
	if (err == 0) {
		while (fgets(buf, sizeof(buf), fp) != NULL){
			line_count++;
		}
	}
	// 今後のループ用に
	enemy_max = line_count;
	fclose(fp);

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
				stage_data[row].start_x = atoi(buf); 
				break;
			// 敵の種類
			case 2: 
				stage_data[row].enemy_type = atoi(buf); 
				break;
			// 各インスタンスの引数
			case 3: 
				stage_data[row].var_1 = atoi(buf); 
				break;
			case 4: 
				stage_data[row].var_2 = atoi(buf); 
				break;
			case 5: 
				stage_data[row].var_3 = atoi(buf); 
				break;
			case 6: 
				stage_data[row].var_4 = atoi(buf); 
				break;
			case 7: 
				stage_data[row].var_5 = atoi(buf); 
				break;
			case 8: 
				stage_data[row].var_6 = atoi(buf); 
				break;
			case 9: 
				stage_data[row].var_7 = atoi(buf); 
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

/*
// 文字列を分割する
vector<string> split(string& input, char delimiter){

	istringstream stream(input);
	string field;
	vector<string> result;
	while (getline(stream, field, delimiter)) {
		result.push_back(field);
	}
	return result;
}
*/