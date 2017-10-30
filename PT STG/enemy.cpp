
#include "global.h"

#define SHIP_BULLET_MAX 100
#define a2r(deg) (DX_PI_F / 180 * (deg))

// --------------------------------------------------------------------------------
// 何も当たらなかったら -1 が返る
// 自機と敵本体が当たったら -2 が返る
// 自機弾と敵本体が当たったら -3 が返る
// 自機と弾が当たったら 弾構造体の配列番号 が返る
// --------------------------------------------------------------------------------
int enemy::collision_Check() {

	// 弾の枠外初期化
	// ----------------------------------------------------------------------------
	bool flag = init_OutRangeBullets();
	if (stats == 2 && flag == false) {
		stats = 0; // 弾も実態も無かったら消す
		init_Bullets();
	}

	// 自機と敵本体の当たり判定
	// ----------------------------------------------------------------------------
	if (ship.x >= x - collision_size && ship.x <= x + collision_size &&
		ship.y >= y - collision_size && ship.y <= y + collision_size) {
		return -2;
	}
	// 自機の弾と敵の当たり判定
	// ----------------------------------------------------------------------------
	for (int i = 0; i < SHIP_BULLET_MAX; i++) {
		if (ship.s[i].stats == 1 && stats == 1) {
			if (ship.s[i].x > x - collision_size && ship.s[i].x < x + collision_size &&
				ship.s[i].y > y - collision_size && ship.s[i].y < y + collision_size) {
				ship.s[i].stats = 0;
				hp--;
				// 敵死亡時
				if (hp <= 0) {
					// エフェクトの再生開始
					effect_hnd = PlayEffekseer2DEffect(effects[0]);
					// スケール変更
					SetScalePlayingEffekseer2DEffect(effect_hnd, 25.0f, 25.0f, 25.0f);
					// 敵の位置にエフェクトをあわせる
					SetPosPlayingEffekseer2DEffect(effect_hnd, x, y, 0);
					// 敵が死んでも弾が残ってたら存在させたままにする(stats = 2)
					if (flag == false) {
						stats = 0;
						init_Bullets();
					}
					else {
						stats = 2;
					}
				}
			}
		}
	}
	// 自機と敵弾の当たり判定
	// ----------------------------------------------------------------------------
	for (int i = 0; i < MAX_BULLET; i++) {
		if (stats == 1) {
			if (ship.x + 25 >= bullets[i].x - bullets[i].collision_size && ship.x - 25 <= bullets[i].x + bullets[i].collision_size &&
				ship.y + 10 >= bullets[i].y - bullets[i].collision_size && ship.y - 10 <= bullets[i].y + bullets[i].collision_size) {
				return i;
			}
		}
	}
	// めちゃくちゃ画面外いったら敵は死ぬ（今後解決策求む）
	// ----------------------------------------------------------------------------
	if (x <= -1024) {
		stats = 0;
		init_Bullets();
	}

	return -1;
}
// ----------------------------------------------------------------------------
// 配列の空き番地検索
// ----------------------------------------------------------------------------
int enemy::search_FreeAddress() {
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 0) {
			return i;
		}
	}
	return -1;
}
// ----------------------------------------------------------------------------
// 弾の初期化
// ----------------------------------------------------------------------------
void enemy::init_Bullets() {
	for (int i = 0; i < MAX_BULLET; i++) {
		bullets[i].stats = 0;
		bullets[i].x = 0.f;
		bullets[i].y = 0.f;
		bullets[i].rad = 0.f;
		bullets[i].speed = 0.f;
		bullets[i].collision_size = 2;
	}
}
// ----------------------------------------------------------------------------
// 画面外に行った弾を初期化
// ----------------------------------------------------------------------------
bool enemy::init_OutRangeBullets() {
	bool flag = false;
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 1) {
			flag = true;
			if (bullets[i].x < -48 || bullets[i].x > WINDOW_SIZE_X + 48 ||
				bullets[i].y < -48 || bullets[i].y > WINDOW_SIZE_Y + 48) {
				bullets[i].stats = 0;
				bullets[i].x     = 0.f;
				bullets[i].y     = 0.f;
				bullets[i].rad   = 0.f;
				bullets[i].speed = 0.f;
			}
		}
	}
	return flag;
}

// ----------------------------------------------------------------------------
// 敵弾アニメーション
// ----------------------------------------------------------------------------
// type 0 ~ 2 / color 0 ~ 5
void bullet_animation_14(int x, int y, int color, int type) {

	int a = (type * 4) + (color * 14) + b_anim_4;
	DrawGraph(x - 7, y - 7, bullet14_img[a], TRUE);
}
// type 0 or 1 / color 0 ~ 5
void bullet_animation_16(int x, int y, int color, int type) {

	int a = (type * 30) + (b_anim_3 * 6) + color;
	DrawGraph(x - 8, y - 8, bullet16_img[a], TRUE);
}

// anim update
void bullet_Animation_Update() {

	b_anim_3 += b_dir_3;
	if (b_anim_3 > 3 || b_anim_3 < 0) b_dir_3 *= -1;

	b_anim_4++;
	if (b_anim_4 > 4) b_anim_4 = 0;

	b_anim_6 += b_dir_6;
	if (b_anim_6 > 6 || b_anim_6 < 0) b_dir_6 *= -1;
}


/*----------------------------------------------------------*/
/*--------------------------BOSSES--------------------------*/
/*----------------------------------------------------------*/

void boss_stage1::init() {
	hp = 10000;
	x = 1000.f;
	y = 360.f;
	stats = 1;
}





/*----------------------------------------------------------*/
/*--------------------------STAGE1--------------------------*/
/*----------------------------------------------------------*/

/*
ウニズ：二次関数的動き（壊れる）6

バナナのヤツ：ランダム秒ごとに自機の高さに合わせてきてバナナ（弾）を発射する（壊れる）7

ピネ爆弾：上に上がって円形弾幕を発射して数秒したら下に戻る（一応たまぶち込んだら壊れる）8

カイ：固定砲台で自機狙いの玉をランダム秒の間隔（1～3秒くらい？）で打ってくる（壊れる）9

*/
// ========================================================================================
// ----------------------------------------------------------------------------------------
//  ナッツ
// ----------------------------------------------------------------------------------------
// ========================================================================================
void enemy_nuts::init(float start_x, float start_y, float s, int rad, int stat) {

	x     = start_x;
	y     = 0.0f;
	r     = rad;
	hp    = 10;
	py    = start_y;
	speed = s;
	stats = stat;
	width = 60;
	collision_size = 24;
	effect_hnd     = -1;

	init_Bullets();
}

// ----------------------------------------------------------------------------
// 描画
// ----------------------------------------------------------------------------
void enemy_nuts::draw() {
	if (stats == 1) {
		DrawGraph(x - 24, y - 24, enemy_img[2], TRUE);
	}
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 1) {
			DrawBox(bullets[i].x - 3, bullets[i].y - 3, bullets[i].x + 3, bullets[i].y + 3, GetColor(255, 255, 255), TRUE);
		}
	}
}
// ----------------------------------------------------------------------------
// 弾発射
// ----------------------------------------------------------------------------
void enemy_nuts::shot() {
	int max = 6;
	for (int i = 0; i < max; i++) {
		int free = search_FreeAddress();
		bullets[free].stats = 1;
		bullets[free].x = x;
		bullets[free].y = y;
		bullets[free].rad = ((2 * DX_PI_F) / max) * i;
		bullets[free].speed = 4;
	}
}
// ----------------------------------------------------------------------------
// 弾の移動
// ----------------------------------------------------------------------------
void enemy_nuts::move_shot() {
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats != 0) {
			bullets[i].x += sin(bullets[i].rad) * bullets[i].speed;
			bullets[i].y += cos(bullets[i].rad) * bullets[i].speed;
		}
	}
}
// ----------------------------------------------------------------------------
// 移動
// ----------------------------------------------------------------------------
void enemy_nuts::move() {

	if (stats != 0) {
		// 横移動
		x -= speed;
		// 正弦波移動
		r += 10;
		if (r >= 360) r = 0;
		y = py + cosf((DX_PI_F / 180) * r) * width;
		// 画面外に行ったら消す
		// if (x < collision_size * -2) stats = 0;

		if (frame % 120 == 0 && stats == 1) {
			shot();
		}
		move_shot();
	}
	collision_Check();
	draw();
}

// ========================================================================================
// ----------------------------------------------------------------------------------------
// 　ウニズ
// ----------------------------------------------------------------------------------------
// ========================================================================================
void enemy_uni::init(int HP, float start_x, float start_y, float reverse_x, float reverse_y, float s, int stat) {
	x = start_x;
	y = start_y;
	hp = HP;
	rx = reverse_x;
	ry = reverse_y;
	speed = s;
	collision_size = 24;
	stats = stat;

}

void enemy_uni::move() {
	if (stats == 1) {
		y -= speed;

		// 2次関数的動き Quadratic functionally Moving
		x = ((y - ry) * (y - ry)) / 100.0f + rx;
	}
	draw();
	collision_Check();
}

void enemy_uni::draw() {
	if (stats == 1) {
		DrawGraph(x, y, enemy_img[0], TRUE);
	}
}


// ========================================================================================
// ----------------------------------------------------------------------------------------
//  ジェノサイドバナナ
// ----------------------------------------------------------------------------------------
// ========================================================================================
void enemy_banana::init(int HP, float start_x, float start_y, int stat) {
	x = start_x;
	y = start_y;
	hp = HP;
	speed = 0;
	collision_size = 64;
	stats = stat;
	mode = 0;
}

void enemy_banana::shot() {
	int max = 12;
	if (stats == 1) {
		for (int i = 0; i < max; i++) {
			int free = search_FreeAddress();
			bullets[free].rad = DX_PI_F;
			bullets[free].speed = 10;
			bullets[free].x = x;
			bullets[free].y = y;
			bullets[free].stats = 1;
		}
	}

}

void enemy_banana::move_shot() {
	for (int i = 0; i < MAX_BULLET; i++) {
		bullets[i].x += cos(bullets[i].rad) * bullets[i].speed;
		bullets[i].y += sin(bullets[i].rad) * bullets[i].speed;
	}
}

void enemy_banana::move() {
	if (stats == 1) {
		x -= test.speed;
		// mode=1:静止状態
		if (mode == 0 && frame % (GetRand(299) + 1) == 0) {
			mode = 1;
		}

		// mode=2:移動中
		if (mode == 1) {
			if (y < ship.y) {
				y += 10;
			}
			else if (y > ship.y) {
				y -= 10;
			}

			// 自機付近の高さになったら弾を生成
			if (y >= ship.y - 10 && y <= ship.y + 10) {
				shot();
				mode = 0;
			}
		}
	}
	move_shot();
	draw();
	collision_Check();
}

void enemy_banana::draw() {
	if (stats == 1) {
		DrawGraph(x , y, enemy_img[5], TRUE);
	}
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 1) {
			DrawBox(bullets[i].x - 10, bullets[i].y - 10, bullets[i].x + 10, bullets[i].y + 10, GetColor(255, 255, 0), TRUE);
			DrawFormatString(bullets[i].x - 8, bullets[i].y - 8, GetColor(0, 0, 0), "バ");
		}
	}
	init_OutRangeBullets();
}


// ========================================================================================
// ----------------------------------------------------------------------------------------
//  ピネ
// ----------------------------------------------------------------------------------------
// ========================================================================================
void enemy_pine::init(int HP, float s_x, float s_y, float up_y,int stat) {
	x = s_x;
	y = s_y;
	hp = HP;
	start_y = s_y;
	upper_y = up_y;
	speed = 0;
	collision_size = 24;
	stats = stat;
	mode = 0;
	attack_flag = 0;
}

void enemy_pine::shot() {
	int max = 12;
	if (stats == 1) {
		for (int i = 0; i < max; i++) {
			int free = search_FreeAddress();
			bullets[free].rad = ((2.0f * DX_PI_F) / max) * i;
			bullets[free].speed = 10;
			bullets[free].x = x;
			bullets[free].y = y;
			bullets[free].stats = 1;
		}
		attack_flag = 1;
	}
}

void enemy_pine::move_shot() {
	for (int i = 0; i < MAX_BULLET; i++) {
		bullets[i].x += sin(bullets[i].rad) * bullets[i].speed;
		bullets[i].y += cos(bullets[i].rad) * bullets[i].speed;
	}
}

void enemy_pine::move() {
	if (stats == 1) {
		x -= test.speed;

		// mode=0:上昇
		// ステージ座標が100になったら(仮) upper_y まで上昇
		if (mode == 0 && y >= upper_y && x - ship.x <= 256 && x - ship.x >= -256) {
			y -= 10.0f;
			if (y == upper_y) { mode = 1; }  //  upper_y に達したら静止状態に移行
		}

		// mode=1:静止
		if (mode == 1) {
			if (attack_flag == 0 && frame % (GetRand(119) + 1) == 0) {
				shot();
			}
			if (attack_flag == 1 && frame % 60 == 0) {
				mode = 2;
			}
		}

		// mode=2:下降
		if (mode == 2 && y != start_y) {
			y += 10;
		}

	}
	move_shot();
	draw();
	collision_Check();
}

void enemy_pine::draw() {
	if (stats == 1) {
		DrawGraph(x, y, enemy_img[6], TRUE);
	}
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 1) {
			// DrawBox(bullets[i].x - 10, bullets[i].y - 10, bullets[i].x + 10, bullets[i].y + 10, GetColor(255, 255, 255), TRUE);
			// DrawFormatString(bullets[i].x - 8, bullets[i].y - 8, GetColor(0, 0, 0), "ピ");
			bullet_animation_14(bullets[i].x, bullets[i].y, 0, 0);

		}
	}
	init_OutRangeBullets();
}


// ========================================================================================
// ----------------------------------------------------------------------------------------
//  カイ
// ----------------------------------------------------------------------------------------
// ========================================================================================
void enemy_shell::init(int HP, float start_x, float start_y, int stat) {
	x = start_x;
	y = start_y;
	hp = HP;
	collision_size = 24;
	stats = stat;
	mode = 0;
}

void enemy_shell::shot() {
	int max = 10;
	for (int i = 0; i < max; i++) {
		int free = search_FreeAddress();
		bullets[free].rad = atan2(ship.x - x, ship.y - y);
		bullets[free].speed = 10;
		bullets[free].x = x;
		bullets[free].y = y;
		bullets[free].stats = 1;
	}
}

void enemy_shell::move_shot() {
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 1) {
			bullets[i].x += sin(bullets[i].rad) * bullets[i].speed;
			bullets[i].y += cos(bullets[i].rad) * bullets[i].speed;
		}
	}
}

void enemy_shell::move() {
	if (stats == 1) {
		speed = test.speed;
		x -= speed;

		// 1~180フレーム間(0~3秒)ランダムで弾を生成
		if (frame % (GetRand(179) + 1) == 0) {
			shot();
		}

	}
	move_shot();
	draw();
	collision_Check();
}

void enemy_shell::draw() {
	if (stats == 1) {
		DrawGraph(x, y, enemy_img[4], TRUE);
	}
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 1) {
			DrawBox(bullets[i].x - 10, bullets[i].y - 10, bullets[i].x + 10, bullets[i].y + 10, GetColor(255, 255, 255), TRUE);
			DrawFormatString(bullets[i].x - 8, bullets[i].y - 8, GetColor(0, 0, 0), "貝");
		}
	}
	init_OutRangeBullets();
}


void enemy_brain::init(int HP, float start_x, float start_y, int stat) {
	mode = 0;
	counter = 0;
	speed_max = 30;
	speed = 0;
	collision_size = 32;
	for (int i = 0; i < MAX_BULLET; i++) {
		t[i] = 0;
	}
	hp = HP;
	x = start_x;
	y = start_y;
	stats = stat;
}

void enemy_brain::shot() {
	int max;
	int count = 0;

	// 動きの種類によって弾丸の最大数を決定
	if (mode == 1 || mode == 2) {
		max = GetRand(20) + 1;
	}
	else if (mode == 3) {
		max = 80;
	}
	else if (mode == 5) {
		max = 80;
	}

	for (int i = 0; i < max; i++) {
		int free = search_FreeAddress();

		// データの入っている添字を代入する(動きを分けるため)
		if (mode == 1 || mode == 2) {
			bullets[free].rad = ((2.0f * DX_PI_F) / max) * i;


			// 円形弾
			if (mode == 1) {
				circle[free] = free;
				bullets[free].speed = 10;
				bullets[free].x = x;
				bullets[free].y = y;
				bullets[free].stats = 1;
			}
			// じわる弾
			else if (mode == 2) {
				circle2[free] = free;
				bullets[free].speed = 10;
				bullets[free].x = x;
				bullets[free].y = y;
				bullets[free].stats = 1;
			}
		}
		// レーザー
		else if (mode == 5) {
			lazer[free] = free;
			bullets[free].speed = 0;
			count += 1;
			bullets[free].x = x - (count * 16);
			bullets[free].y = y;
			bullets[free].stats = 1;
		}
		// すごい弾
		else if (mode == 3) {
			bullets[free].rad = 0;
			super[free] = free;
			t[free] = 0.0f;

			// ベジェ曲のデータ
			p1_x[free] = GetRand(WINDOW_SIZE_X);
			p2_x[free] = GetRand(WINDOW_SIZE_X);
			p1_y[free] = GetRand(WINDOW_SIZE_Y);
			p2_y[free] = GetRand(WINDOW_SIZE_Y);

			bullets[free].speed = 10;
			bullets[free].x = x;
			bullets[free].y = y;
			bullets[free].stats = 1;
		}

		if (mode != 3) {
			bullets[i].collision_size = 4;
		}
	}
}

void enemy_brain::move_shot() {
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 1) {
			// 円形弾の移動
			if (circle[i] == i) {
				if (bullets[i].speed <= speed_max) {
					bullets[i].speed -= 0.5;
				}
				if (circle[i] != 0) {
					bullets[i].x += sin(bullets[i].rad) * bullets[i].speed;
					bullets[i].y += cos(bullets[i].rad) * bullets[i].speed;
				}
			}

			// じわる弾
			if (circle2[i] == i) {
				if (bullets[i].speed < speed_max) {
					bullets[i].speed += 0.5;
				}

				if (circle2[i] != 0) {
					bullets[i].x += sin(atan2f(ship.x - bullets[i].x, ship.y - bullets[i].y)) * bullets[i].speed;
					bullets[i].y += cos(atan2f(ship.x - bullets[i].x, ship.y - bullets[i].y)) * bullets[i].speed;
				}
			}

			// レーザー ~ Black Widow ~
			if (lazer[i] == i) {
				speed += 1;
				if (speed >= 3000) {
					bullets[i].stats = 0;
					lazer[i] = 0;
				}
			}

			// すごい弾の移動
			if (super[i] == i) {
				if (t[i] >= 1.0f) {
					bullets[i].x += sinf(atan2f(p2_x[i] - p1_x[i], p2_y[i] - p1_y[i])) * bullets[i].speed;
					bullets[i].y += cosf(atan2f(p2_x[i] - p1_x[i], p2_y[i] - p1_y[i])) * bullets[i].speed;

				}
				else {
					t[i] += 0.001f;
					bullets[i].x = (1 - t[i]) * bullets[i].x + 2 * (1 - t[i]) * t[i] * p1_x[i] + t[i] * t[i] * p2_x[i];
					bullets[i].y = (1 - t[i]) * bullets[i].y + 2 * (1 - t[i]) * t[i] * p1_y[i] + t[i] * t[i] * p2_y[i];
				}
			}
		}

	}
}

void enemy_brain::move() {
	if (stats == 1) {

		if (mode == 0 && frame % 120 == 0) {
			// 円形弾
			if (counter == 0) {
				mode = 1;
			}
			// じわる弾
			else if (counter == 1) {
				mode = 2;
			}
			// レーザー
			else if (counter == 2) {
				mode = 3;
			}
			// すごい弾
			else if (counter == 3) {
				mode = 4;
			}
		}

		if (mode == 1) {
			shot();
			mode = 0;
			counter++;
		}
		else if (mode == 2) {
			shot();
			mode = 0;
			counter++;
		}
		else if (mode == 3) {
			shot();
			mode = 0;
			counter++;
		}
		else if (mode == 4) {
			if (frame % 180 == 0) {
				// エフェクトの再生開始
				effect_hnd = PlayEffekseer2DEffect(effects[1]);
				// スケール変更
				SetScalePlayingEffekseer2DEffect(effect_hnd, -50.0f, 50.0f, 50.0f);
				// 敵の位置にエフェクトをあわせる
				SetPosPlayingEffekseer2DEffect(effect_hnd, x, y, 0);
				mode = 5;
			}
		}
		else if (mode == 5) {
			shot();
			mode = 0;
			counter = 0;
		}
	}
	move_shot();
	draw();
	int remove = collision_Check();

	if (remove >= 0 ) {

		bullets[remove].stats = 0;
	}
}


// 0.0 <= t && t <= 1.0 とする。この値を変化させて曲線を作る
//2次のベジエ曲線
//(p_x,p_y)はそのtの値でのベジエ曲線の点の位置
//	p_x = (1 - t)*(1 - t)*p0_x + 2 * (1 - t)*t*p1_x + t*t*p2_x;
//	p_y = (1 - t)*(1 - t)*p0_y + 2 * (1 - t)*t*p1_y + t*t*p2_y;

void enemy_brain::draw() {
	if (stats == 1) {
		DrawGraph(x, y - 128, enemy_img[20], TRUE);
	}
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 1) {
			if (lazer[i] == i) {
				//DrawBox(bullets[i].x - 10, bullets[i].y - 10, bullets[i].x + 10, bullets[i].y + 10, GetColor(255, 255, 255), TRUE);
				//DrawFormatString(bullets[i].x - 8, bullets[i].y - 8, GetColor(0, 0, 0), "脳");
				//bullet_animation_16(bullets[i].x, bullets[i].y, 0, 0);

			}
			else {
				bullet_animation_14(bullets[i].x, bullets[i].y, 0, 2);
			}
		}
		else {
			if (circle[i] == i && circle[i] != 0) {
				circle[i] = 0;
			}
			if (circle2[i] == i && circle2[i] != 0) {
				circle2[i] = 0;
			}
			if (lazer[i] == i && lazer[i] != 0) {
				lazer[i] = 0;
			}
		}
	}
	init_OutRangeBullets();

}

/*----------------------------------------------------------*/
/*--------------------------STAGE2--------------------------*/
/*----------------------------------------------------------*/

/*
Stage2
ミートボールスパム:"２"みたいな動き

ムービングスタチュー:普段は見えない。自機の半径180pxになったらいきなり能われて自機狙いで突進してくる

ワーム:最初はいない　地面ニョキニョキ
地面からある程度生えて体をくねらせながら6弾からなる円形弾を発射

胞子コア:地面に生えていて、一定間隔で胞子を放つ(差分あり)。　胞子は範囲攻撃

ツタ:壊されても一定時間経過でまた生える(statsを0にする)

クワガタン:一定間隔で上下に移動(イージング)

O
O		こんなの撃ってくる
O
O

*/



// meatball
void enemy_meatball::init(int HP, float start_x, float start_y, int stat) {
	mode = 0;
	hp = HP;
	x = start_x;
	y = start_y;
	speed = 0;
	collision_size = 48;
	stats = stat;
	deg = 180;
	r = 0;
	sh_x = 0.0f;
	sh_y = 0.0f;
	temp = 0;
}

void enemy_meatball::move() {
	if (stats == 1) {

		// version 0:回転を続ける 1:半円分移動後に直進
		int version = 1;

		// 自機と x がhobo同じになるまで直進
		if (mode == 0 && x >= ship.x) {
			x -= speed;

			if (x <= ship.x + 10.0f && x > ship.x) {
				mode = 1;
				sh_x = ship.x;
				sh_y = ship.y;
				r = sqrtf(powf(x - ship.x, 2) + powf(y - ship.y, 2));

				// 自機と敵の位置により上回転か下回転か決める
				if (y <= ship.y) {
					temp = 1;	//  -> 上回転
				}
				else {
					temp = -1;	//  -> 下回転
				}

				mode = 1;
			}
		}

		// 円運動
		if (mode == 1) {
			deg -= 5 * temp;
			x = r * sinf(a2r(deg)) * temp + sh_x;
			y = r * cosf(a2r(deg)) * temp + sh_y;

			if (deg > 360) {
				deg = 0;
			}

			if (deg == 0 && version == 1) {
				mode = 3;
			}
		}

		// 円運動終了後直進
		if (mode == 3) {
			x -= speed;
		}
	}
	draw();
	collision_Check();
}

void enemy_meatball::draw() {
	if (stats == 1) {
		DrawGraph(x - 24, y - 24, enemy_img[8], TRUE);
	}
}

// statue
void enemy_statue::init(int HP, float start_x, float start_y, int stat) {
	hidden = 1;
	mode = 0;
	rad = 0;
	hp = HP;
	x = start_x;
	y = start_y;
	speed = 0;
	collision_size = 48;
	stats = stat;
}

void enemy_statue::move() {
	if (stats == 1) {
		x -= test.speed;
		// 静止状態(hidden = 1)
		if (mode == 0) {
			collision_size = 0;

			// 自機-敵間の距離が 180 以下になった時に戦闘モードに変更し正体を現す
			if (sqrtf(powf(x - ship.x, 2) + powf(y - ship.y, 2)) <= 512) {
				mode = 1;
				hidden = 0;
			}
		}

		// 移動前の準備(とりあえず2秒後)
		if (mode == 1) {
			if (frame % 120 == 0) {
				rad = atan2f(ship.x - x, ship.y - y);
				mode = 2;
				collision_size = 48;
			}
		}

		// 実際の移動
		if (mode == 2) {
			speed += 0.3f;
			x += sinf(rad) * speed;
			y += cosf(rad) * speed;
		}
	}
	draw();
	collision_Check();
}

void enemy_statue::draw() {
	if (stats == 1) {
		if (hidden == 0) {
			DrawGraph(x, y, enemy_img[7], TRUE);
		}
		else {
			DrawBox(x - 24, y - 24, x + 24, y + 24, GetColor(255, 255, 255), TRUE);
		}
	}
}

// warm
void enemy_worm::init(int HP, float start_x, float start_y, int stat) {
	mode = 0;
	hp = HP;
	x = start_x;
	y = start_y;
	speed = 0;
	stats = stat;

	for (int i = 0; i < 6; i++) {
		ball[i].x = x;
		ball[i].y = y - i * (2 * 24);
		ball[i].speed = 0;
		ball[i].rad = 0;
		ball[i].collision_size = 24;
		ball[i].stats = 1;
	}
}

void enemy_worm::shot() {
	int max = 6;
	if (stats == 1) {
		for (int i = 0; i < max; i++) {
			int free = search_FreeAddress();
			bullets[free].rad = ((2.0f * DX_PI_F) / max) * i;
			bullets[free].speed = 10;
			bullets[free].x = ball[5].x;
			bullets[free].y = ball[5].y;
			bullets[free].stats = 1;
		}
	}
}

void enemy_worm::move_shot() {
	for (int i = 0; i < MAX_BULLET; i++) {
		bullets[i].x += sin(bullets[i].rad) * bullets[i].speed;
		bullets[i].y += cos(bullets[i].rad) * bullets[i].speed;
	}
}

void enemy_worm::move() {
	if (stats == 1) {
		if (mode == 0 && frame % 120 == 0) {
			mode = 1;
		}

		/*
		クネル動き
		*/
		if (mode == 1) {
			for (int i = 1; i < 6; i++) {
				if (GetRand(1) == 0) {
					deg += 1;
				}
				else {
					deg -= 1;
				}
				
				ball[i].x = 48 * sinf(a2r(deg * i)) + ball[i-1].x;
				ball[i].y = 48 * cosf(a2r(deg * i)) + ball[i-1].y;

				if (deg > 360) {
					deg = 0;
				}
				if (deg < 0) {
					deg = 360;
				}
			}

			if (frame % 30 == 0) {
				shot();
			}
		}

	}
	move_shot();
	draw();
	collision_Check();
}

void enemy_worm::draw() {
	if (stats == 1) {
		for (int i = 0; i < 6; i++) {
			switch (i) {
			// case 0:	// 尻尾
				// DrawGraph(ball[0].x + ball[0].collision_size, ball[0].y + ball[0].collision_size, enemy_img[13], TRUE);
				// break;
			case 5:		// 頭
				DrawGraph(ball[5].x - ball[5].collision_size, ball[5].y - ball[5].collision_size, enemy_img[12], TRUE);
				break;
			default:	// 胴体
				DrawGraph(ball[i].x - 24, ball[i].y - 24, enemy_img[14], TRUE);
				DrawCircle(ball[i].x, ball[i].y, ball[i].collision_size, GetColor(255, 255, 255), TRUE, 1);
				break;
			}

		}
	}
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 1) {
			DrawBox(bullets[i].x - 10, bullets[i].y - 10, bullets[i].x + 10, bullets[i].y + 10, GetColor(255, 255, 255), TRUE);
			DrawFormatString(bullets[i].x - 8, bullets[i].y - 8, GetColor(0, 0, 0), "虫");
		}
	}
	init_OutRangeBullets();
}

// sporecore
void enemy_sporecore::init(int HP, float start_x, float start_y, int stat) {
	hp = HP;
	x = start_x;
	y = start_y;
	speed = 0;
	collision_size = 48;
	stats = stat;
	mode = 0;
}

void enemy_sporecore::shot() {
	if (stats == 1) {
		for (int i = 0; i < 1; i++) {
			int free = search_FreeAddress();
			// bullets[free].rad = 5 * DX_PI_F / 3 * 0.4f * i;
			bullets[free].speed = 10;
			bullets[free].x = x;
			bullets[free].y = y;
			bullets[free].stats = 1;
			bullets[free].collision_size = 48;
		}
	}

}

void enemy_sporecore::move_shot() {
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 1) {
			bullets[i].x -= test.speed;
			if (bullets[i].y >= y - 50) {
				bullets[i].y -= test.speed;
			}
		}
	}

}

void enemy_sporecore::move() {
	x -= test.speed;

	if (stats == 1) {

		if (mode == 0 && frame % 180 == 0) {
			mode = 1;
		}

		if (mode == 1) {
			shot();
			mode = 0;
		}

	}
	move_shot();
	draw();
	collision_Check();
}

void enemy_sporecore::draw() {
	if (stats == 1) {
		DrawGraph((int)x - 10, (int)y - 30, enemy_img[10], TRUE);
	}
	for (int i = 0; i < MAX_BULLET; i++) {
		DrawBox(bullets[i].x - bullets[i].collision_size, bullets[i].y - bullets[i].collision_size, bullets[i].x + bullets[i].collision_size, bullets[i].y + bullets[i].collision_size, GetColor(255, 255, 255), TRUE);
		DrawFormatString(bullets[i].x - 8, bullets[i].y - 8, GetColor(0, 0, 0), "胞死");
	}
	init_OutRangeBullets();

}

// ivy
// y は最大時のツタの最下部
void enemy_ivy::init(int HP, float start_x, float start_y, int stat) {
	hp = HP;
	x = start_x;
	y = start_y;
	prev_x = (int)start_x;
	prev_y = (int)start_y;
	speed = 0;
	collision_size = 64;
	height = 128;
	stats = stat;
	mode = 0; // 0:地中 1:伸びてる最中 2:破壊時
}

void enemy_ivy::move() {
	x -= test.speed;

	// 生存
	if (stats == 1) {

		// とりあえず1秒後に育つ
		if (mode == 0 && frame % 60 == 0) {
			mode = 1;
		}
		if (mode == 1) {
			speed = test.speed;
			if (y >= prev_y - height) {
				y -= speed;
			}

			// HPがゼロになったら死状態
			if (hp <= 0) {
				temp = x;
				stats = 0;
			}
		}
	}

	// 死 = 復活
	if (stats == 0) {
		if (frame % 180 == 0) {
			stats = 1;
			hp = 5;
			mode = 0;
			y = (float)prev_y;
		}
	}
	draw();
	collision_Check();

}

void enemy_ivy::draw() {
	if (stats == 1) {
		if (prev_y >= WINDOW_SIZE_Y / 2) {
			DrawGraph((int)x - 24, (int)y, enemy_img[9],TRUE);
		}
		else {
			DrawGraph((int)x - 24, (int)y, enemy_img[9], TRUE);
		}
	}
}

// stagbeetle
void enemy_stagbeetle::init(int HP, float start_x, float start_y, int stat) {
	hp = HP;
	x = start_x;
	y = start_y;
	speed = 0;
	collision_size = 48;
	stats = stat;
	temp_x = start_x;
	temp_y = start_y;
	mode = 0;
}

void enemy_stagbeetle::shot() {
	int max = 8;
	if (stats == 1) {
		for (int i = 0; i < max; i++) {
			int free = search_FreeAddress();
			bullets[free].rad = 5 * DX_PI_F / 3 * 0.4f * i;
			bullets[free].speed = 10;
			bullets[free].x = x;
			bullets[free].y = y;
			bullets[free].stats = 1;
		}
	}
}

void enemy_stagbeetle::move_shot() {
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 1) {
			bullets[i].x += -sin(bullets[i].rad) * bullets[i].speed;
			bullets[i].y += -cos(bullets[i].rad) * bullets[i].speed;
			if (bullets[i].x <= 0 || bullets[i].y <= 0 || bullets[i].x >= 1270 || bullets[i].y >= 710) {
				bullets[i].rad *= DX_PI_F;
			}
		}
	}

}

void enemy_stagbeetle::move() {
	if (stats == 1) {
		if (mode == 0 && frame % 60 == 0) {
			if (y >= temp_y) {
				speed = test.speed;
				mode = 1;	// to up
			}
			else {
				mode = 2;	// to down
			}
		}

		// 上に上がる
		if (mode == 1) {
			if (y >= temp_y - 128) {
				y -= speed;
			}
			else {
				mode = 0;
				shot();
			}
		}

		// 下に下る
		if (mode == 2) {
			if (y <= temp_y + 128) {
				y += speed;
			}
			else {
				mode = 0;
				shot();
			}

		}

	}
	move_shot();
	draw();
	collision_Check();
}

void enemy_stagbeetle::draw() {
	if (stats == 1) {
		DrawGraph((int)x - collision_size, (int)y - collision_size, enemy_img[11], TRUE);
	}
	for (int i = 0; i < MAX_BULLET; i++) {
		DrawBox(bullets[i].x - 10, bullets[i].y - 10, bullets[i].x + 10, bullets[i].y + 10, GetColor(255, 255, 255), TRUE);
		DrawFormatString(bullets[i].x - 8, bullets[i].y - 8, GetColor(0, 0, 0), "鍬");
	}
	init_OutRangeBullets();
}

// genocide : WORK IN PROGRESS
void enemy_genocide::init(int HP, float start_x, float start_y, int stat) {
	mode = 1;
	collision_size = 128;
	speed = 0;
	x = start_x;
	y = start_y;
	prev_y = start_y;
	stats = stat;
}

void enemy_genocide::shot() {
	int max = 2;
	if (stats == 1) {
		for (int i = 0; i < max; i++) {
			int free = search_FreeAddress();
			bullets[free].speed = test.speed;
			bullets[free].x = x + 195;
			bullets[free].y = y + 230;
			bullets[free].stats = 1;
			bullets[free].collision_size = 24;
		}
	}

}

void enemy_genocide::move_shot() {
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 1) {
			bullets[i].x = x - 180 + (70 * i);
			bullets[i].y = y + 85;
		}
	}

}

void enemy_genocide::move() {
	if (stats == 1) {

		// サインカーブの幅
		int width = 150;

		x -= test.speed / 2;
		deg += 2;
		y = (width * sinf(a2r(deg))) + prev_y;
		if (deg > 360) {
			deg = 0;
		}

		// 2-4秒の間で噴射
		if (frame % (120 + random) == 0) {
			if (mode == 1) {
				shot();
				mode = 0;
				random = GetRand(120);
			}

			// 消滅
			else if (mode == 0) {
				for (int i = 0; i < MAX_BULLET; i++) {
					bullets[i].stats = 0;
				}
				mode = 1;
			}
		}


	}
	move_shot();
	draw();
	collision_Check();
}

void enemy_genocide::draw() {
	if (stats == 1) {
		DrawGraph(x - 370, y - 140, enemy_img[15], TRUE);
	}
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 1) {
			DrawBox(bullets[i].x, bullets[i].y, bullets[i].x + 20, bullets[i].y + 40, GetColor(255, 255, 255), TRUE);
			DrawFormatString(bullets[i].x + 1, bullets[i].y + 15, GetColor(0, 0, 0), "ｱﾌ");
		}

		
	}

	init_OutRangeBullets();
}

// kimobako : WORK IN PROGRESS
void enemy_kimobako::init(int HP, float start_x, float start_y, int stat) {

}

void enemy_kimobako::shot() {

}

void enemy_kimobako::move_shot() {

}

void enemy_kimobako::move() {

}

void enemy_kimobako::draw() {
	if (stats == 1) {
		DrawGraph(x - 128, y - 128, enemy_img[16], TRUE);
	}
}

// shindarla
void enemy_shindarla::init(int HP, float start_x, float start_y, int stat) {
	mode = 0;
	collision_size = 32;
	hp = HP;
	x = start_x;
	y = start_y;
	stats = stat;

}

void enemy_shindarla::shot() {
	int max = 4;
	for (int i = 0; i < max; i++) {
		int free = search_FreeAddress();
		bullets[free].rad = ((2.0f * DX_PI_F) / max) * i;
		bullets[free].speed = 6;
		bullets[free].x = x;
		bullets[free].y = y;
		bullets[free].stats = 1;
	}

}

void enemy_shindarla::move_shot() {
	for (int i = 0; i < MAX_BULLET; i++) {
		// 直進
		if (bullets[i].stats == 1 && mode == 2) {
			bullets[i].rad = ((2.0f * DX_PI_F) / 4) * i;
		}
		// ホーミング
		else if (bullets[i].stats == 1 && mode == 3) {
			rad = bullets[i].rad; // 最終角度取得用
			bullets[i].rad = atan2f(ship.x - bullets[i].x, ship.y - bullets[i].y) - a2r(45);
		}
		// 最終角度で直進
		else if (bullets[i].stats == 1 && mode == 4) {
			bullets[i].rad = rad;
		}
		bullets[i].x += sinf(bullets[i].rad) * bullets[i].speed;
		bullets[i].y += cosf(bullets[i].rad) * bullets[i].speed;
	}
}

void enemy_shindarla::move() {

	// alive
	if (stats == 1) {
		x -= test.speed;
	}
	
	// dead
	if (stats != 1) {
		if (mode == 0) {
			mode = 1;
		}

		// 一旦十字に出てくる
		if (mode == 1) {
			shot();
			mode = 2;
		}

		// すぐホーミングを始める
		if (frame % 30 == 0 && mode == 2) {
			mode = 3;
		}

		// 時間が経ったら最終角度で直進
		if (frame % 300 == 0 && mode == 3) {
			mode = 4;
		}
	}
	move_shot();
	draw();
	collision_Check();
}

void enemy_shindarla::draw() {
	if (stats == 1) {
		DrawGraph((int)x - collision_size, (int)y - collision_size, enemy_img[17], TRUE);
		DrawBox(x - collision_size, y - collision_size, x + collision_size, y + collision_size, GetColor(255, 255, 255), FALSE);
	}
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 1) {
			DrawBox(bullets[i].x - 10, bullets[i].y - 10, bullets[i].x + 10, bullets[i].y + 10, GetColor(255, 255, 255), TRUE);
			DrawFormatString(bullets[i].x - 8, bullets[i].y - 8, GetColor(0, 0, 0), "死");
		}
	}
	init_OutRangeBullets();

}

// detecrew : WORK IN PROGRESS
void enemy_detecrew::init(int HP, float start_x, float start_y, int stat) {
	mode = 0;
	speed = 16;
	hp = HP;
	x = start_x;
	y = start_y;
	prev_x = start_x;
	prev_y = start_y;
	stats = stat;
	collision_size = 24;
}

void enemy_detecrew::shot() {

}

void enemy_detecrew::move_shot() {

}

void enemy_detecrew::move() {
	if (stats == 1) {
		x -= test.speed;

		if (mode == 1) {


		}

		if (mode == 2) {

		}

	}
	move_shot();
	draw();
	collision_Check();
}

void enemy_detecrew::draw() {
	if (stats == 1) {
		DrawGraph(x - collision_size, y - collision_size, enemy_img[18], TRUE);

	}
	init_OutRangeBullets();
}
