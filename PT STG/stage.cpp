#include "global.h"

using namespace std;

// ステージの初期化
// sx:ステージ幅 sy:ステージ高さ
void my_Stage::init(int sx, int sy) {
	// クラス用再定義
	stage_size_x = sx; //サイズ
	stage_size_y = sy;

	// 3次元配列の動的確保（カッコイイ）
	stage_size = new int**[stage_size_x];
	for (int i = 0; i < stage_size_x; i++) {
		stage_size[i] = new int*[stage_size_y];
		for (int j = 0; j < stage_size_y; j++) {
			stage_size[i][j] = new int[2];
		}
	}
	// 初期化
	for (int i = 0; i < stage_size_x; i++) {
		for (int j = 0; j < stage_size_y; j++) {
			stage_size[i][j][0] = 0;
			stage_size[i][j][1] = 0;
		}
	}
}

// ステージの破棄
// ※コレ通さないと死ぬから注意
void my_Stage::del_Stage() {
	for (int i = 0; i < stage_size_x; i++) {
		for (int j = 0; j < stage_size_y; j++) {
			delete[] stage_size[i][j];
		}
		delete[] stage_size[i];
	}
	delete[] stage_size;
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
			if (stage_size[i][j][1] == 0) {
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
}

// ステージの位置を移動する
void my_Stage::set_StagePos(float sx, float sy) {
	x = sx;
	y = sy;
}

// CSV読み込み
void my_Stage::io_StageDataLoad() {

	const int BufMax = 64;
	char buf[BufMax];

	FILE *fp = NULL;

	int  lineCount = 0;
	char (*data)[BufMax];

	if ((fp = fopen("data/maps/stage_1/stagedata.csv", "r")) != NULL) {
		while (fgets(buf, sizeof(buf), fp) != NULL){
			lineCount++;
		}
	}


}

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