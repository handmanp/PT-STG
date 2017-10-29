#include "global.h"

using namespace std;

// 敵列挙
enum ene_type {
	// *---Stage 1---*
	EneNuts,		// 0 ナッツ
	EneEdamamen,	// 1 エダマメン
	EneUnis,		// 2 ウニズ
	EneBanana,		// 3 ジェノサイドバナナ
	EnePine,		// 4 ピネ
	EneKai,			// 5 カイ
	EneTakenokon,	// 6 タケノコン
	EneKinokon,		// 7 キノコン

	// *---Stage 2---*
	EneKuwagatan,	// 8  クワガタン
	EneMeatball,	// 9  ミートボールスパム
	EneHoushi,		// 10 胞子
	EneWarm,		// 11 ワーム
	EneTutan,		// 12 ツタン
	EneStatue,		// 13 ムービングスタチュー

	// *---Stage 3---*
	EneKimobako,	// 14 キモ箱
	EneDetekuruno,	// 15 デテクルーノ（葉）
	EneDetekuki,	// 16 デテクルーノ（茎）
	EneTamautsu,	// 17 シンダーラタマウツ
	EneGenocide,	// 18 戦艦ジェノサイド

	// *--- Boss ---*
	BossTacos,		// 19 タコス
	BossNoumison,	// 20 ノウミソン
	BossWarmin		// 21 ワーミン
};

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
			stage_size[i][j] = 0;
		}
	}
	memset(enemy_count, 0, sizeof(enemy_count));
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
	float move_rad = (DX_PI_F / 180.0f) * r;
	// 移動処理
	x += sinf(move_rad) * s;
	y += cosf(move_rad) * s;
}

// ステージを描画(仮)
void my_Stage::draw() {
	for (int i = 0; i < stage_size_x; i++) {
		for (int j = 0; j < stage_size_y; j++) {
			if (stage_size[i][j] == 0) {
				//ブロックの相対座標
				int dpx = (i * STAGE_TIP_SIZE) - x;
				int dpy = (j * STAGE_TIP_SIZE) - y;
				//面内のみ描画
				if (dpx >= -STAGE_TIP_SIZE && dpx <= WINDOW_SIZE_X + STAGE_TIP_SIZE &&
					dpy >= -STAGE_TIP_SIZE && dpy <= WINDOW_SIZE_Y + STAGE_TIP_SIZE) {
					DrawBox(dpx, dpy, dpx + STAGE_TIP_SIZE, dpy + STAGE_TIP_SIZE, GetColor(40, 40, 40), FALSE);
				}
			}
		}
	}
	for (int i = 0; i < enemy_max; i++) {
		DrawFormatString(10, 100 + (i * 20), GetColor(200, 200, 200), "%d, %d, %d, %d, %d, %d, %d",
			stage_data[i].start_x, stage_data[i].enemy_type,
			stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3,
			stage_data[i].var_4, stage_data[i].var_5, stage_data[i].var_6,
			stage_data[i].var_7);
	}
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
		if (stage_data[i].start_x == x) {

			// 敵のインスタンス作成
			switch (stage_data[i].enemy_type) {

				// *------------------------ Stage 1 ------------------------*

				// [0] ナッツ
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
				unis[enemy_count[EneUnis]].init(stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3, stage_data[i].var_4, stage_data[i].var_5, stage_data[i].var_6, stage_data[i].var_7);
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

				// [5] カイ
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
				break;

				// [16] デテクルーノ（茎） wip
			case EneDetekuki:
				break;

				// [17] シンダーラタマウツ
			case EneTamautsu:
				sindarla[enemy_count[EneTamautsu]].init(stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3, stage_data[i].var_4);
				enemy_count[EneTamautsu]++;
				break;

				// [18] 戦艦ジェノサイド wip
			case EneGenocide:
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
		//genocide[i].move(); wip
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