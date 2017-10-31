
#include "global.h"
#include "ship.h"

#define NORMAL (10)
#define BRO_ (11)

#define SHIP_BULLET_MAX 100

//自機初期化
//--------------------------------------------------------------------------------
void my_Ship::init() {
	x              = 200.0f;
	y              = 360.0f;
	speed          = 10.0f;
	collision_size = 3;
	anim           = 2;
	type           = 0;
	powerup_select = -1;

	//自機弾初期化
	for (int i = 0; i < 100; i++) {
		s[i].stats  = 0;
		s[i].x      = 0.0f;
		s[i].y      = 0.0f;
		s[i].rad    = 0.0f;
		s[i].speed  = 0.0f;
		s[i].length = 0.0f;
	}
}

// 自機描画
//--------------------------------------------------------------------------------
void my_Ship::draw() {
	//描画
	DrawGraph(x - 50, y - 25, ship_img[anim][type], TRUE);

	for (int i = 0; i < SHIP_BULLET_MAX; i++) {
		if (s[i].stats == 1) {
			DrawGraph(s[i].x - 8, s[i].y - 8, bullet16_img[2], TRUE);
		}
	}

	for (int i = 0; i < 6; i++) {
		DrawGraph((i * 128) + 256, 680, pwrup_img[1], TRUE);
	}
}

// 発射
//--------------------------------------------------------------------------------
void my_Ship::shot() {

	int check_bullet = 0;
	int free = -1;

	for (int i = 0; i < SHIP_BULLET_MAX; i++) {
		if (s[i].stats == 1) check_bullet++;
		if (free == -1) {
			if (s[i].stats == 0) free = i;
		}
	}
	if (free != -1 && check_bullet <= 5) {
		s[free].stats = 1;
		s[free].x = x;
		s[free].y = y;
		s[free].rad = DX_PI_F / 2;
		s[free].speed = 24;
		s[free].length = 0;
	}
}

//発射後の弾移動
//--------------------------------------------------------------------------------
void my_Ship::shot_Move() {
	for (int i = 0; i < SHIP_BULLET_MAX; i++) {
		if (s[i].stats == 1) {
			s[i].x += sin(s[i].rad) * s[i].speed * frame_Time;
			s[i].y += cos(s[i].rad) * s[i].speed * frame_Time;
			if (s[i].x < -48 || s[i].x > WINDOW_SIZE_X + 48 ||
				s[i].y < -48 || s[i].y > WINDOW_SIZE_Y + 48) {
				s[i].stats = 0;
			}
		}
	}
}

//自機全般
//--------------------------------------------------------------------------------
void my_Ship::move() {

	int input_stats = 0;
	float rad = 0.0f;

	//ショットキー
	if ((ctrl_key[KEY_INPUT_Z] == 2 || ctrl_pad.Buttons[XINPUT_BUTTON_X] == 1) && frame % ((((int)fps + 1) / 30) + 1) == 0) shot();

	shot_Move();

	//移動キー
	if (ctrl_key[KEY_INPUT_UP]    == 2 || ctrl_pad.Buttons[XINPUT_BUTTON_DPAD_UP]    == 1) input_stats += 2;
	if (ctrl_key[KEY_INPUT_DOWN]  == 2 || ctrl_pad.Buttons[XINPUT_BUTTON_DPAD_DOWN]  == 1) input_stats += 1;
	if (ctrl_key[KEY_INPUT_LEFT]  == 2 || ctrl_pad.Buttons[XINPUT_BUTTON_DPAD_LEFT]  == 1) input_stats += 4;
	if (ctrl_key[KEY_INPUT_RIGHT] == 2 || ctrl_pad.Buttons[XINPUT_BUTTON_DPAD_RIGHT] == 1) input_stats += 8;

	//移動キーから角度を求める
	switch (input_stats) {
		case 0:
			if (ctrl_pad.ThumbLY > 8192 || ctrl_pad.ThumbLY < -8192 || ctrl_pad.ThumbLX > 8192 || ctrl_pad.ThumbLX < -8192) {
				//後の自乗の値が大きくなりすぎるから調整
				float trg_x = ctrl_pad.ThumbLX / 32767.0f;//あえて-1にしてる
				float trg_y = ctrl_pad.ThumbLY / -32767.0f;
				//スティックの倒し具合を二点間の距離で見る
				float trigger = sqrtf(trg_x * trg_x + trg_y * trg_y);
				//角度
				rad = atan2f(trg_x, trg_y);
			}
			else {
				rad = -1.0f;
			}
			break;
		case 1:
			rad = 0.0f;
			break;
		case 2:
			rad = DX_PI_F;
			break;
		case 4:
			rad = DX_PI_F / 2.0f * 3.0f;
			break;
		case 5:
			rad = DX_PI_F / 4.0f * 7.0f;
			break;
		case 6:
			rad = DX_PI_F / 4.0f * 5.0f;
			break;
		case 8:
			rad = DX_PI_F / 2.0f;
			break;
		case 9:
			rad = DX_PI_F / 4.0f;
			break;
		case 10:
			rad = DX_PI_F / 4.0f * 3.0f;
			break;
		default:
			rad = -1.0f;
			break;
	}

	//移動
	if (rad != -1.0f) {
		x += (sinf(rad) * speed) * frame_Time;
		y += (cosf(rad) * speed) * frame_Time;
	}

	//アニメーション管理
	if (frame % ((int)fps + 1 / 60) == 0) {

		//アニメーション
		if (rad != -1.0f) {
			if (cosf(rad) * speed > 1.5f) anim++;
			if (cosf(rad) * speed < -1.5f) anim--;
		}
		else {
			if (anim > 2) anim--;
			if (anim < 2) anim++;
		}

		//範囲外
		if (anim > 4) anim = 4;
		if (anim < 0) anim = 0;
	}

}


// アイテム初期化
//--------------------------------------------------------------------------------
void item_init() {
	for (int i = 0; i < ITEM_MAX; i++) {
		item[i].stats = 0;
		item[i].type = 0;
		item[i].x = 0;
		item[i].y = 0;
		item[i].size = 0;
	}
}

// アイテム構造体の空き番地を検索
//--------------------------------------------------------------------------------
int item_search_FreeAddress() {
	for (int i = 0; i < ITEM_MAX; i++) {
		if (item[i].stats == 0) {
			return i;
		}
	}
	return -1;
}

// アイテムを生成
//--------------------------------------------------------------------------------
void item_drop(int x, int y, int type) {
	int free = item_search_FreeAddress();

	item[free].stats = 1;
	item[free].type = type;
	item[free].x = x;
	item[free].y = y;
}

// アイテムを描画
//--------------------------------------------------------------------------------
void item_draw() {
	for (int i = 0; i < ITEM_MAX; i++) {
		if (item[i].stats == 1) {

			// アイテムの種類により画像を選択
			switch (item[i].type) {
			case 1:
				// 画像ハンドル
				// item[i].image_handle = ???;
				// item[i].size = ???;
				break;
			case 2:
				// 画像ハンドル
				break;
			}

			//描画
			DrawCircle(item[i].x, item[i].y, item[i].size, GetColor(255, 255, 255), FALSE);
			DrawFormatString(item[i].x, item[i].y, GetColor(0, 255, 255), "E");
			//DrawGraph(item[i].x - item[i].size, item[i].y - item[i].size, item[i].image_handle, TRUE);
		}
	}
}