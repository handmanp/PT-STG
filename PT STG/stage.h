#pragma once
#include "global.h"
#define STAGE_TIP_SIZE 32

typedef struct {
	float x;
	float y;
}STAGE_DATA;


//ステージ親クラス
class my_stage {
public:
	//ステージの大きさ
	int stage_size_x;
	int stage_size_y;

	//ステージの現在の座標
	float x;
	float y;

	//動的確保用ポインタ
	int ***stage_size;

	void move(int s, int r);
	void init(int sx, int sy);
	void draw();
	void del_Stage();
	void set_StagePos(float sx, float sy);

	//ステージの状態を取得
	STAGE_DATA get_StageData(STAGE_DATA data);
	int move_per_second;
	int get_Second(int second);
};

GLOBAL STAGE_DATA s_Data;


