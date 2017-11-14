
#include "global.h"

#define SHIP_BULLET_MAX 100

// --------------------------------------------------------------------------------
// ����������Ȃ������� -1 ���Ԃ�
// ���@�ƓG�{�̂����������� -2 ���Ԃ�
// ���@�e�ƓG�{�̂����������� -3 ���Ԃ�
// ���@�ƒe������������ �e�\���̂̔z��ԍ� ���Ԃ�
// --------------------------------------------------------------------------------
int enemy::collision_Check() {

	// �e�̘g�O������
	// ----------------------------------------------------------------------------
	bool flag = init_OutRangeBullets();
	if (stats == 2 && flag == false) {
		stats = 0; // �e�����Ԃ��������������
		init_Bullets();
	}

	// ���@�ƓG�{�̂̓����蔻��
	// ----------------------------------------------------------------------------
	if (ship.x >= x - collision_size && ship.x <= x + collision_size &&
		ship.y >= y - collision_size && ship.y <= y + collision_size) {

		if (ship.stat == 0 && stats == 1) {

			ship.stat = -1;
			ship.x = -120.f;
			ship.y = 340.f;
			ship.left -= 1;

			if (flag == false) {
				stats = 0;
				init_Bullets();
			}
			else {
				stats = 2;
			}
		}
		return -2;
	}
	// ���@�̒e�ƓG�̓����蔻��
	// ----------------------------------------------------------------------------
	for (int i = 0; i < SHIP_BULLET_MAX; i++) {
		if (ship.s[i].stats == 1 && stats == 1) {
			if (ship.s[i].x > x - collision_size && ship.s[i].x < x + collision_size &&
				ship.s[i].y > y - collision_size && ship.s[i].y < y + collision_size) {
				ship.s[i].stats = 0;
				hp--;
				// �G���S��
				if (hp <= 0) {

					// �G�t�F�N�g�̍Đ��J�n
					effect_hnd = PlayEffekseer2DEffect(effects[0]);
					// �X�P�[���ύX
					SetScalePlayingEffekseer2DEffect(effect_hnd, 25.0f, 25.0f, 25.0f);
					// �G�̈ʒu�ɃG�t�F�N�g�����킹��
					SetPosPlayingEffekseer2DEffect(effect_hnd, x, y, 0);

					// ���Đ�
					PlaySoundMem(game_sehnd[1], DX_PLAYTYPE_BACK, TRUE);

					// �����_���ŃA�C�e��
					if (GetRand(10) == 1) {
						item_drop(x, y, 0);
					}
					score += 100;

					// �G������ł��e���c���Ă��瑶�݂������܂܂ɂ���(stats = 2)
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
	// ���@�ƓG�e�̓����蔻��
	// ----------------------------------------------------------------------------
	for (int i = 0; i < MAX_BULLET; i++) {
		if (stats == 1) {
			if (ship.x + 25 >= bullets[i].x - bullets[i].collision_size && ship.x - 25 <= bullets[i].x + bullets[i].collision_size &&
				ship.y + 10 >= bullets[i].y - bullets[i].collision_size && ship.y - 10 <= bullets[i].y + bullets[i].collision_size) {
				if (ship.stat == 0 && bullets[i].stats != 0) {
					ship.stat = -1;
					ship.x = -120.f;
					ship.y = 340.f;
					ship.left -= 1;
					bullets[i].stats = 0;
				}
				return i;
			}
		}
	}
	// �߂��Ⴍ�����ʊO��������G�͎��ʁi��������􋁂ށj
	// ----------------------------------------------------------------------------
	if (x <= -1024) {
		stats = 0;
		init_Bullets();
	}

	return -1;
}
// ----------------------------------------------------------------------------
// �z��̋󂫔Ԓn����
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
// �e�̏�����
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
// ��ʊO�ɍs�����e��������
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
// �G�e�A�j���[�V����
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
�E�j�Y�F�񎟊֐��I�����i����j6

�o�i�i�̃��c�F�����_���b���ƂɎ��@�̍����ɍ��킹�Ă��ăo�i�i�i�e�j�𔭎˂���i����j7

�s�l���e�F��ɏオ���ĉ~�`�e���𔭎˂��Đ��b�����牺�ɖ߂�i�ꉞ���܂Ԃ����񂾂����j8

�J�C�F�Œ�C��Ŏ��@�_���̋ʂ������_���b�̊Ԋu�i1�`3�b���炢�H�j�őł��Ă���i����j9

*/
// ========================================================================================
// ----------------------------------------------------------------------------------------
//  �G�_�}����
// ----------------------------------------------------------------------------------------
// ========================================================================================

void enemy_edamamen::init(float start_x, float start_y, int HP, float rad, int stat) {
	stats = stat;
	hp = HP;
	x = start_x;
	y = start_y - test.y;
	r = rad;

	init_Bullets();
}

// ----------------------------------------------------------------------------
// �`��
// ----------------------------------------------------------------------------
void enemy_edamamen::draw() {
	if (stats == 1) {
		DrawGraph(x - 24, y - 24, enemy_img[1], TRUE);
	}
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 1) {
			bullet_animation_14(bullets[i].x, bullets[i].y, 2, 1);
		}
	}
}
// ----------------------------------------------------------------------------
// �e����
// ----------------------------------------------------------------------------
void enemy_edamamen::shot() {
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
// �e�̈ړ�
// ----------------------------------------------------------------------------
void enemy_edamamen::move_shot() {
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats != 0) {
			bullets[i].x += sin(bullets[i].rad) * bullets[i].speed * frame_Time;
			bullets[i].y += cos(bullets[i].rad) * bullets[i].speed * frame_Time;
		}
	}
}
// ----------------------------------------------------------------------------
// �ړ�
// ----------------------------------------------------------------------------
void enemy_edamamen::move() {
	if (stats != 0) {
		// �ړ�
		x -= sinf(test.move_rad) * test.speed * frame_Time;
		y -= cosf(test.move_rad) * test.speed * frame_Time;

		// ��ʊO�ɍs���������
		// if (x < collision_size * -2) stats = 0;

		if (frame % (2 * (int)fps) == 0 && stats == 1) {
			shot();
		}
		move_shot();
	}
	collision_Check();
	draw();
}



// ========================================================================================
// ----------------------------------------------------------------------------------------
//  �i�b�c
// ----------------------------------------------------------------------------------------
// ========================================================================================

void enemy_nuts::init(float start_x, float start_y, float s, int rad, int stat) {

	x     = start_x;
	y     = 0.0f;
	r     = rad;
	hp    = 10;
	py    = start_y - test.y;
	speed = s;
	stats = stat;
	width = 60;
	collision_size = 24;
	effect_hnd     = -1;

	init_Bullets();
}



// ----------------------------------------------------------------------------
// �`��
// ----------------------------------------------------------------------------
void enemy_nuts::draw() {
	if (stats == 1) {
		DrawGraph(x - 24, y - 24, enemy_img[EneNuts], TRUE);
	}
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 1) {
			bullet_animation_14(bullets[i].x, bullets[i].y, 2, 1);
		}
	}
}
// ----------------------------------------------------------------------------
// �e����
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
// �e�̈ړ�
// ----------------------------------------------------------------------------
void enemy_nuts::move_shot() {
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats != 0) {
			bullets[i].x += sin(bullets[i].rad) * bullets[i].speed * frame_Time;
			bullets[i].y += cos(bullets[i].rad) * bullets[i].speed * frame_Time;
		}
	}
}
// ----------------------------------------------------------------------------
// �ړ�
// ----------------------------------------------------------------------------
void enemy_nuts::move() {
	if (stats != 0) {
		// ���ړ�
		if (x < WINDOW_SIZE_X + 200) {
			x -= (test.speed + speed) * frame_Time;
		}
		else {
			x -= test.speed * frame_Time;
		}

		// �����g�ړ�
		r += 10 * frame_Time;
		if (r >= 360) r = 0;
		y = py + cosf((DX_PI_F / 180) * r) * width;
		// ��ʊO�ɍs���������
		// if (x < collision_size * -2) stats = 0;

		if (frame % (2 * (int)fps) == 0 && stats == 1) {
			shot();
		}
		move_shot();
	}
	collision_Check();
	draw();
}

// ========================================================================================
// ----------------------------------------------------------------------------------------
// �@�E�j�Y
// ----------------------------------------------------------------------------------------
// ========================================================================================
void enemy_uni::init(float start_x, float start_y, int HP, float s, int stat) {
	x = start_x;
	y = start_y - test.y;
	hp = HP;
	speed = s;
	r = -90;
	deg = 0.f;
	collision_size = 24;
	stats = stat;
	init_Bullets();

}

void enemy_uni::move() {
	if (stats == 1) {

		if (x < WINDOW_SIZE_X + 200) {
			x += sin(a2r(r)) * (test.speed + speed) * frame_Time;
		}
		else {
			x += sin(a2r(r)) * test.speed * frame_Time;
		}

		y += cos(a2r(r)) * speed * frame_Time;
		if (x < ship.x + 200 && r < 90) {
			r += 5.0f * frame_Time;
		}

		deg += 10.0f * frame_Time;

		if (deg >= 360) {
			deg = 0.f;
		}
	}
	draw();
	collision_Check();
}

void enemy_uni::draw() {
	if (stats == 1) {
		DrawRotaGraph(x, y, 1.0, a2r(deg), enemy_img[EneUnis], TRUE);
	}
}


// ========================================================================================
// ----------------------------------------------------------------------------------------
//  �W�F�m�T�C�h�o�i�i
// ----------------------------------------------------------------------------------------
// ========================================================================================
void enemy_banana::init(float start_x, float start_y, int HP, int stat) {
	x = start_x;
	y = start_y - test.y;
	hp = HP;
	speed = 0;
	collision_size = 32;
	stats = stat;
	mode = 0;
	init_Bullets();

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
			bullets[free].collision_size = 8;
		}
	}
}

void enemy_banana::move_shot() {
	for (int i = 0; i < MAX_BULLET; i++) {
		bullets[i].x += cos(bullets[i].rad) * bullets[i].speed * frame_Time;
		bullets[i].y += sin(bullets[i].rad) * bullets[i].speed * frame_Time;
	}
}

void enemy_banana::move() {
	if (stats == 1) {

		x -= sinf(test.move_rad) * test.speed * frame_Time;
		y -= cosf(test.move_rad) * test.speed * frame_Time;

		// mode=1:�Î~���
		if (mode == 0 && frame % ((GetRand(2) + 1) * (int) fps) == 0) {
			mode = 1;
		}

		// mode=2:�ړ���
		if (mode == 1) {
			if (y < ship.y) {
				y += 10 * frame_Time;
			}
			else if (y > ship.y) {
				y -= 10 * frame_Time;
			}

			// ���@�t�߂̍����ɂȂ�����e�𐶐�
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
		DrawGraph(x - 64, y - 64, enemy_img[EneBanana], TRUE);
	}
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 1) {
			bullet_animation_16(bullets[i].x, bullets[i].y, 0, 0);
		}
	}
	init_OutRangeBullets();
}


// ========================================================================================
// ----------------------------------------------------------------------------------------
//  �s�l
// ----------------------------------------------------------------------------------------
// ========================================================================================
void enemy_pine::init(float s_x, float s_y, int HP, float up_y,int stat) {
	x = s_x;
	y = s_y - test.y;
	hp = HP;
	start_y = s_y - test.y;
	upper_y = up_y - test.y;
	speed = 0;
	collision_size = 24;
	stats = stat;
	mode = 0;
	attack_flag = 0;
	init_Bullets();

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
			bullets[free].collision_size = 8;
		}
		attack_flag = 1;
	}
}

void enemy_pine::move_shot() {
	for (int i = 0; i < MAX_BULLET; i++) {
		bullets[i].x += (sin(bullets[i].rad) * bullets[i].speed) * frame_Time;
		bullets[i].y += (cos(bullets[i].rad) * bullets[i].speed) * frame_Time;
	}
}

void enemy_pine::move() {
	if (stats == 1) {

		x -= sinf(test.move_rad) * test.speed * frame_Time;
		y -= cosf(test.move_rad) * test.speed * frame_Time;

		//DrawFormatString(300, 10, GetColor(0, 0, 0), "%d", x);
		// mode=0:�㏸
		// upper_y �܂ŏ㏸
		if (mode == 0 && y >= upper_y && x - ship.x <= 256 && x - ship.x >= -256) {
			y -= 10.0f * frame_Time;

			if (y <= upper_y)  mode = 1;  //  upper_y �ɒB������Î~��ԂɈڍs
		}

		// mode=1:�Î~
		if (mode == 1) {
			if (attack_flag == 0 && frame % (int)(1555.f * frame_Time) == 0) {
				shot();
			}
			if (attack_flag == 1 && (frame % (int)(1933.f * frame_Time)) == 0) {
				mode = 2;
			}
		}

		// mode=2:���~
		if (mode == 2 && y != start_y) {
			y += 10 * frame_Time;
		}
	}
	move_shot();
	draw();
	collision_Check();
}

void enemy_pine::draw() {
	if (stats == 1) {
		DrawGraph(x - 24, y - 24, enemy_img[EnePine], TRUE);
	}
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 1) {
			// DrawBox(bullets[i].x - 10, bullets[i].y - 10, bullets[i].x + 10, bullets[i].y + 10, GetColor(255, 255, 255), TRUE);
			// DrawFormatString(bullets[i].x - 8, bullets[i].y - 8, GetColor(0, 0, 0), "�s");
			bullet_animation_14(bullets[i].x, bullets[i].y, 1, 1);
		}
	}
	init_OutRangeBullets();
}


// ========================================================================================
// ----------------------------------------------------------------------------------------
//  �J�C
// ----------------------------------------------------------------------------------------
// ========================================================================================
void enemy_shell::init(float start_x, float start_y, int HP, int stat) {
	x = start_x;
	y = start_y - test.y;
	hp = HP;
	collision_size = 24;
	stats = stat;
	mode = 0;
	init_Bullets();

}

void enemy_shell::shot() {
	int max = 10;
	for (int i = 0; i < max; i++) {
		int free = search_FreeAddress();
		bullets[free].rad = atan2(ship.x - x, ship.y - y);
		bullets[free].speed = 7;
		bullets[free].x = x;
		bullets[free].y = y;
		bullets[free].stats = 1;
	}
}

void enemy_shell::move_shot() {
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 1) {
			bullets[i].x += sin(bullets[i].rad) * bullets[i].speed * frame_Time;
			bullets[i].y += cos(bullets[i].rad) * bullets[i].speed * frame_Time;
		}
	}
}

void enemy_shell::move() {
	if (stats == 1) {
		x -= sinf(test.move_rad) * test.speed * frame_Time;
		y -= cosf(test.move_rad) * test.speed * frame_Time;

		// 1~180�t���[����(0~3�b)�����_���Œe�𐶐�
		if (frame % (((GetRand(2) + 1) * (int)fps)) == 0) {
			shot();
		}

	}
	move_shot();
	draw();
	collision_Check();
}

void enemy_shell::draw() {
	if (stats == 1) {
		//DrawGraph(x - 24, y - 24, enemy_img[4], TRUE);
		DrawRotaGraph(x, y, 1.0, -atan2(ship.x - x, ship.y - y) + a2r(180), enemy_img[EneKai], TRUE, TRUE);
	}
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 1) {
			bullet_animation_16(bullets[i].x, bullets[i].y, 4, 0);
		}
	}
	init_OutRangeBullets();
}

// ========================================================================================
// ----------------------------------------------------------------------------------------
// �@�m�E�~�\��
// ----------------------------------------------------------------------------------------
// ========================================================================================
void enemy_brain::init(float start_x, float start_y, int HP, int stat) {
	mode = 0;
	mode_move = 0;
	counter = 0;
	speed_max = 30;
	speed_move = 4;
	speed = 0;
	collision_size = 32;
	temp_y = start_y;
	for (int i = 0; i < MAX_BULLET; i++) {
		t[i] = 0;
		circle[i] = 0;
		circle2[i] = 0;
		super[i] = 0;
		lazer[i] = 0;
	}

	hp = HP;
	x = start_x;
	y = start_y - test.y;
	stats = stat;
	init_Bullets();

}

void enemy_brain::shot() {
	int count = 0;
	// �����̎�ނɂ���Ēe�ۂ̍ő吔������
	if (mode == 1 || mode == 2) {
		max = GetRand(10) + 5;
	}
	else if (mode == 3) {
		max = 12;
	}
	else if (mode == 5) {
		max = 40;
	}

	for (int i = 0; i < max; i++) {
		int free = search_FreeAddress();

		// �f�[�^�̓����Ă���Y����������(�����𕪂��邽��)
		if (mode == 1 || mode == 2) {
			// �~�`�e
			if (mode == 1) {
				bullets[free].rad = ((2.0f * DX_PI_F) / (float)max) * i;
				circle[free] = free;
				bullets[free].speed = 10;
				bullets[free].x = x - 128;
				bullets[free].y = y;
				bullets[free].stats = 1;
			}
			// �����e
			else if (mode == 2) {
				bullets[free].rad = test.move_rad;
				circle2[free] = free;
				bullets[free].speed = 5;
				bullets[free].x = x;
				bullets[free].y = WINDOW_SIZE_Y - ((WINDOW_SIZE_Y / max) * i);
				bullets[free].stats = 1;
				bullets[free].collision_size = 3;
			}
		}
		// �������e
		else if (mode == 3) {
			bullets[free].rad = atan2f(ship.x - x, ship.y - y);
			super[free] = free;
			t[free] = 0.0f;

			// �x�W�F�Ȃ̃f�[�^
			p1_x[free] = GetRand(WINDOW_SIZE_X);
			p2_x[free] = GetRand(WINDOW_SIZE_X);
			p1_y[free] = GetRand(WINDOW_SIZE_Y);
			p2_y[free] = GetRand(WINDOW_SIZE_Y);

			bullets[free].speed = 12;
			bullets[free].x = x;
			bullets[free].y = y;
			bullets[free].stats = 1;
		}
		// ���[�U�[
		else if (mode == 5) {
			lazer[free] = free;
			bullets[free].speed = 0;
			count += 1;
			bullets[free].x = x - (count * 24);
			bullets[free].y = y;
			bullets[free].stats = 1;
			bullets[free].collision_size = 24;
		}

		if (mode != 2 || mode != 3) {
			bullets[i].collision_size = 7;
		}
	}
}

void enemy_brain::move_shot() {
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 1) {
			// �~�`�e�̈ړ�
			if (circle[i] == i) {
				if (bullets[i].speed * frame_Time <= speed_max * frame_Time) {
					bullets[i].speed -= 0.5 * frame_Time;
				}
				if (circle[i] != 0) {
					bullets[i].x += sin(bullets[i].rad) * bullets[i].speed * frame_Time;
					bullets[i].y += cos(bullets[i].rad) * bullets[i].speed * frame_Time;
				}
			}

			// �����e
			if (circle2[i] == i) {
				if (circle2[i] != 0) {
					bullets[i].x -= sinf(bullets[i].rad) * bullets[i].speed * frame_Time;
					bullets[i].y -= cosf(bullets[i].rad) * bullets[i].speed * frame_Time;
				}

			}

			// ���[�U�[ ~ Black Widow ~
			if (lazer[i] == i) {
				speed += 1 * frame_Time;
				if (speed >= 3 * (int)fps) {
					bullets[i].stats = 0;
					lazer[i] = 0;
					speed = 0;
				}
			}

			// �������e�̈ړ�
			if (super[i] == i) {
				bullets[i].x += sin(bullets[i].rad) * bullets[i].speed * frame_Time;
				bullets[i].y += cos(bullets[i].rad) * bullets[i].speed * frame_Time;
			}
		}
	}
}

void enemy_brain::move() {
	if (stats == 1) {
		//x -= test.speed * frame_Time;

		//����ŃX�e�[�W�Ɠ��������Ɉړ�����
		//x -= sinf(test.move_rad) * test.speed * frame_Time;
		//y -= cosf(test.move_rad) * test.speed * frame_Time;

		if (mode == 0 && frame % (3 * (int)fps) == 0) {
			// �~�`�e
			if (counter == 0) {
				mode = 1;
			}
			// �����e
			else if (counter == 1) {
				mode = 2;
			}
			// ���[�U�[
			else if (counter == 2) {
				mode = 3;
			}
			// �������e
			else if (counter == 3) {
				mode = 4;
			}
		}

		if (mode == 1) {
			for (int i = 0; i < MAX_BULLET; i++) {
				bullets[lazer[i]].stats = 0;
			}
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
			// �G�t�F�N�g�̍Đ��J�n
			effect_hnd = PlayEffekseer2DEffect(effects[1]);
			// �X�P�[���ύX
			SetScalePlayingEffekseer2DEffect(effect_hnd, -50.0f, 50.0f, 50.0f);
			// �G�̈ʒu�ɃG�t�F�N�g�����킹��
			SetPosPlayingEffekseer2DEffect(effect_hnd, x - 128, y, 0);
			if (frame % (1 * (int)fps) == 0) {
				mode = 5;
			}
		}
		else if (mode == 5) {
			shot();
			mode = 0;
			counter = 0;
		}
	}

	// �㉺�Ɉړ��n
	if (mode_move == 0 && frame % (3 * (int)fps) == 0 && (mode != 4 || mode != 5)) {
		if (y >= temp_y) {
			mode_move = 1;	// to up
		}
		else {
			mode_move = 2;	// to down
		}
	}

	// ��ɏオ��
	if (mode_move == 1) {
		if (y >= temp_y - 128) {
			y -= speed_move * frame_Time;
		}
		else {
			mode_move = 0;
		}
	}

	// ���ɉ���
	if (mode_move == 2) {
		if (y <= temp_y + 128) {
			y += speed_move * frame_Time;
		}
		else {
			mode_move = 0;
		}
	}

	move_shot();
	draw();
	int remove = collision_Check();

	if (remove >= 0 ) {
		bullets[remove].stats = 0;
	}
}


// 0.0 <= t && t <= 1.0 �Ƃ���B���̒l��ω������ċȐ������
//2���̃x�W�G�Ȑ�
//(p_x,p_y)�͂���t�̒l�ł̃x�W�G�Ȑ��̓_�̈ʒu
//	p_x = (1 - t)*(1 - t)*p0_x + 2 * (1 - t)*t*p1_x + t*t*p2_x;
//	p_y = (1 - t)*(1 - t)*p0_y + 2 * (1 - t)*t*p1_y + t*t*p2_y;

void enemy_brain::draw() {
	if (stats == 1) {
		DrawGraph(x - 128, y - 128, enemy_img[BossNoumison], TRUE);
	}
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 1) {
			DrawBox(bullets[i].x - 10, bullets[i].y - 10, bullets[i].x + 10, bullets[i].y + 10, 0xFFFFFF, TRUE);
			if (lazer[i] != i) {
				bullet_animation_14(bullets[i].x, bullets[i].y, 0, 2);
			}
		}
		else {
			if (circle[i] == i && circle[i] != 0) {
				circle[i] = 0;
			}
			if (circle2[i] == i && circle2[i] != 0) {
				circle2[i] = 0;
				t[i] = 0;
			}
			if (super[i] == i && super[i] != 0) {
				super[i] = 0;
			}
			if (lazer[i] == i && lazer[i] != 0) {
				lazer[i] = 0;
			}
		}
		DrawBox(bullets[i].x - 10, bullets[i].y - 10, bullets[i].x + 10, bullets[i].y + 10, 0xFFFFFF, FALSE);
	}
	init_OutRangeBullets();

}

/*----------------------------------------------------------*/
/*--------------------------STAGE2--------------------------*/
/*----------------------------------------------------------*/

/*
Stage2
�~�[�g�{�[���X�p��:"�Q"�݂����ȓ���

���[�r���O�X�^�`���[:���i�͌����Ȃ��B���@�̔��a180px�ɂȂ����炢���Ȃ�\���Ď��@�_���œːi���Ă���

���[��:�ŏ��͂��Ȃ��@�n�ʃj���L�j���L
�n�ʂ��炠����x�����đ̂����˂点�Ȃ���6�e����Ȃ�~�`�e�𔭎�

�E�q�R�A:�n�ʂɐ����Ă��āA���Ԋu�ŖE�q�����(��������)�B�@�E�q�͔͈͍U��

�c�^:�󂳂�Ă���莞�Ԍo�߂ł܂�������(stats��0�ɂ���)

�N���K�^��:���Ԋu�ŏ㉺�Ɉړ�(�C�[�W���O)

O
O		����Ȃ̌����Ă���
O
O

*/



// ========================================================================================
// ----------------------------------------------------------------------------------------
// �@�~�[�g�{�[���X�p��
// ----------------------------------------------------------------------------------------
// ========================================================================================
void enemy_meatball::init(float start_x, float start_y, int HP, int stat) {
	mode = 0;
	hp = HP;
	x = start_x;
	y = start_y - test.y;
	speed = 0;
	collision_size = 48;
	stats = stat;
	deg = 180;
	r = 0;
	sh_x = 0.0f;
	sh_y = 0.0f;
	temp = 0;
	init_Bullets();

}

void enemy_meatball::move() {
	if (stats == 1) {

		// version 0:��]�𑱂��� 1:���~���ړ���ɒ��i
		int version = 1;

		// ���@�� x ��hobo�����ɂȂ�܂Œ��i
		if (mode == 0 && x >= ship.x) {
			x -= sinf(test.move_rad) * 1.5 * test.speed * frame_Time;
			y -= cosf(test.move_rad) * 1.5 * test.speed * frame_Time;

			if (x <= ship.x + 10.0f && x > ship.x) {
				mode = 1;
				sh_x = ship.x;
				sh_y = ship.y;
				r = sqrtf(powf(x - ship.x, 2) + powf(y - ship.y, 2));

				// ���@�ƓG�̈ʒu�ɂ����]������]�����߂�
				if (y <= ship.y) {
					temp = 1;	//  -> ���]
				}
				else {
					temp = -1;	//  -> ����]
				}

				mode = 1;
			}
		}

		// �~�^��
		if (mode == 1) {
			deg -= 5 * temp * frame_Time;
			x = r * sinf(a2r(deg)) * temp + sh_x;
			y = r * cosf(a2r(deg)) * temp + sh_y;

			if (deg > 360) {
				deg = 0;
			}

			if (deg == 0 && version == 1) {
				mode = 3;
			}
		}

		// �~�^���I���㒼�i
		if (mode == 3) {
			x -= sinf(test.move_rad) * 1.5 * test.speed * frame_Time;
			y -= cosf(test.move_rad) * 1.5 * test.speed * frame_Time;
		}
	}
	draw();
	collision_Check();
}

void enemy_meatball::draw() {
	if (stats == 1) {
		DrawGraph(x - 24, y - 24, enemy_img[EneMeatball], TRUE);
	}
}

// ========================================================================================
// ----------------------------------------------------------------------------------------
// �@���[�r���O�X�^�`���[
// ----------------------------------------------------------------------------------------
// ========================================================================================
void enemy_statue::init(float start_x, float start_y, int HP, int stat) {
	hidden = 1;
	mode = 0;
	rad = 0;
	hp = HP;
	x = start_x;
	y = start_y - test.y;
	speed = 0;
	collision_size = 48;
	stats = stat;
}

void enemy_statue::move() {
	if (stats == 1) {

		x -= sinf(test.move_rad) * test.speed * frame_Time;
		y -= cosf(test.move_rad) * test.speed * frame_Time;
		// �Î~���(hidden = 1)
		if (mode == 0) {
			collision_size = 0;

			// ���@-�G�Ԃ̋����� 180 �ȉ��ɂȂ������ɐ퓬���[�h�ɕύX�����̂�����
			if (sqrtf(powf(x - ship.x, 2) + powf(y - ship.y, 2)) <= 512) {
				mode = 1;
				hidden = 0;
			}
		}

		// �ړ��O�̏���(�Ƃ肠����2�b��)
		if (mode == 1) {
			if (frame % (2 * (int)fps) == 0) {
				rad = atan2f(ship.x - x, ship.y - y);
				mode = 2;
				collision_size = 48;
			}
		}

		// ���ۂ̈ړ�
		if (mode == 2) {
			speed += 0.3f * frame_Time;
			x += sinf(rad) * speed * frame_Time;
			y += cosf(rad) * speed * frame_Time;
		}
	}
	draw();
	collision_Check();
}

void enemy_statue::draw() {
	if (stats == 1) {
		if (hidden == 0) {
			DrawGraph(x, y, enemy_img[EneStatue], TRUE);
		}
		else {
			// DrawBox(x - 24, y - 24, x + 24, y + 24, GetColor(255, 255, 255), TRUE);
		}
	}
}

// ========================================================================================
// ----------------------------------------------------------------------------------------
// �@���[��
// ----------------------------------------------------------------------------------------
// ========================================================================================
void enemy_worm::init(float start_x, float start_y, int HP, int stat) {
	mode = 0;
	minus = 1;
	hp = HP;
	x = start_x;
	y = start_y - test.y;
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
	init_Bullets();

}

void enemy_worm::shot() {
	int max = 6;
	if (stats == 1) {
		for (int i = 0; i < max; i++) {
			int free = search_FreeAddress();
			bullets[free].rad = ((2.0f * DX_PI_F * a2r(deg)) / max) * i;
			bullets[free].speed = 10;
			bullets[free].x = ball[5].x;
			bullets[free].y = ball[5].y;
			bullets[free].stats = 1;
			bullets[free].collision_size = 7;
		}
	}
}

void enemy_worm::move_shot() {
	for (int i = 0; i < MAX_BULLET; i++) {
		bullets[i].x += sin(bullets[i].rad) * bullets[i].speed * frame_Time;
		bullets[i].y += cos(bullets[i].rad) * bullets[i].speed * frame_Time;
	}
}

void enemy_worm::move() {
	for (int i = 0; i < 6; i++) {
		ball[i].x -= sinf(test.move_rad) * test.speed * frame_Time;
		ball[i].y -= cosf(test.move_rad) * test.speed * frame_Time;
	}
	if (stats == 1) {

		/*
		�N�l������
		*/

		if (mode == 0) {
			deg -= 0.5 * minus * frame_Time;

			if (deg <= -40.f || deg >= 40.f) {
				minus *= -1;
			}

			for (int i = 1; i < 6; i++) {
				
				ball[i].x = 32 * sinf(a2r(deg * i)) + ball[i-1].x; //48
				ball[i].y = 32 * cosf(a2r(deg * i)) + ball[i-1].y;
			}

			if (frame % ((int)fps / 2) == 0) {
				shot();
			}
		}
	}
	move_shot();
	draw();
	collision_Check();
}

void enemy_worm::draw() {
	DrawFormatString(10, 200, 0xFFFFFF, "%f , %f:%f", deg, x, y);
	if (stats == 1) {
		for (int i = 0; i < 6; i++) {
			switch (i) {
			 case 0:	// �K��:13
				// DrawGraph(ball[0].x + ball[0].collision_size, ball[0].y + ball[0].collision_size, enemy_img[13], TRUE);
				 DrawRotaGraph(ball[i].x, ball[i].y, 1.0, -a2r(deg + 90), enemy_img[EneWarmBody], TRUE, 1);
				// break;
			case 5:		// ��:12
				//DrawGraph(ball[5].x - ball[5].collision_size, ball[5].y - ball[5].collision_size, enemy_img[12], TRUE);
				//DrawRotaGraph(ball[i].x, ball[i].y, 1.0, -a2r(deg+90), enemy_img[12], TRUE, 1); //success
				DrawRotaGraph(ball[i].x, ball[i].y, 1.0, -atan2(ball[i].x - ball[i-1].x, ball[i].y - ball[i-1].y) + a2r(90), enemy_img[EneWarm], TRUE, 1);
				x = ball[i].x;
				y = ball[i].y;

				break;
			default:	// ����:14
				//DrawGraph(ball[i].x - 24, ball[i].y - 24, enemy_img[14], TRUE);
				//DrawRotaGraph(ball[i].x, ball[i].y, 1.0, -a2r(deg+90), enemy_img[14], TRUE, 1); // success
				DrawRotaGraph(ball[i].x, ball[i].y, 1.0, -atan2(ball[i].x - ball[i-1].x, ball[i].y - ball[i-1].y) + a2r(90), enemy_img[EneWarmBody], TRUE, 1);
				//DrawCircle(ball[i].x, ball[i].y, ball[i].collision_size, GetColor(255, 255, 255), TRUE, 1);
				break;
			}
		}
	}
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 1) {
			bullet_animation_14(bullets[i].x, bullets[i].y, 4, 1);
		}
	}
	init_OutRangeBullets();
}

// ========================================================================================
// ----------------------------------------------------------------------------------------
// �@�E�q
// ----------------------------------------------------------------------------------------
// ========================================================================================
void enemy_sporecore::init(float start_x, float start_y, int HP, int stat) {
	hp = HP;
	x = start_x;
	y = start_y - test.y;
	speed = 0;
	collision_size = 48;
	stats = stat;
	mode = 0;
	init_Bullets();

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
			bullets[i].x -= test.speed * frame_Time;
			if (bullets[i].y >= y - 50) {
				bullets[i].y -= test.speed * frame_Time;
			}
		}
	}

}

void enemy_sporecore::move() {
	x -= sinf(test.move_rad) * test.speed * frame_Time;
	y -= cosf(test.move_rad) * test.speed * frame_Time;

	if (stats == 1) {

		if (mode == 0 && frame % (int)(3230.f * frame_Time) == 0) {
			mode = 1;
		}

		if (mode == 1) {
			shot();
			mode = 2;
		}

		if (mode == 2 && frame % (int)(2000.f * frame_Time) == 0) {
			for (int i = 0; i < MAX_BULLET; i++) {
				bullets[i].stats = 0;
			}
			mode = 0;
		}
	}
	move_shot();
	draw();
	collision_Check();
}

void enemy_sporecore::draw() {
	if (stats == 1) {
		DrawGraph((int)x - 48, (int)y - 48, enemy_img[EneHoushi], TRUE);
	}
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 1) {
			DrawBox(bullets[i].x - bullets[i].collision_size, bullets[i].y - bullets[i].collision_size, bullets[i].x + bullets[i].collision_size, bullets[i].y + bullets[i].collision_size, GetColor(255, 255, 255), TRUE);
			DrawFormatString(bullets[i].x - 8, bullets[i].y - 8, GetColor(0, 0, 0), "�E��");
		}
	}
	init_OutRangeBullets();

}

// ========================================================================================
// ----------------------------------------------------------------------------------------
// �@�c�^��
// ----------------------------------------------------------------------------------------
// ========================================================================================
// y �͍ő厞�̃c�^�̍ŉ���
void enemy_ivy::init(float start_x, float start_y, int HP, int stat) {
	hp = HP;
	x = start_x;
	y = start_y;
	prev_x = (int)start_x;
	prev_y = (int)start_y;
	speed = 0;
	collision_size = 64;
	height = 128;
	stats = stat;
	mode = 0; // 0:�n�� 1:�L�тĂ�Œ� 2:�j��
	init_Bullets();

}

void enemy_ivy::move() {
	x -= sinf(test.move_rad) * test.speed * frame_Time;
	y -= cosf(test.move_rad) * test.speed * frame_Time;

	// ����
	if (stats == 1) {

		// �Ƃ肠����1�b��Ɉ��
		if (mode == 0 && frame % 60 == 0) {
			mode = 1;
		}
		if (mode == 1) {
			speed = test.speed * frame_Time;
			if (y >= prev_y - height) {
				y -= speed * frame_Time;
			}

			// HP���[���ɂȂ����玀���
			if (hp <= 0) {
				temp = x;
				stats = 0;
			}
		}
	}

	// �� = ����
	if (stats == 0) {
		if (frame % (3 * (int)fps) == 0) {
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
			DrawGraph((int)x - 24, (int)y, enemy_img[EneTutan],TRUE);
		}
		else {
			DrawGraph((int)x - 24, (int)y, enemy_img[EneTutan], TRUE);
		}
	}
}

// ========================================================================================
// ----------------------------------------------------------------------------------------
// �@�N���K�^��
// ----------------------------------------------------------------------------------------
// ========================================================================================
void enemy_stagbeetle::init(float start_x, float start_y, int HP, int stat) {
	hp = HP;
	x = start_x;
	y = start_y;
	speed = 0;
	collision_size = 48;
	stats = stat;
	temp_x = start_x;
	temp_y = start_y;
	mode = 0;
	for (int i = 0; i < MAX_BULLET; i++) {
		count[i] = 0;
	}
	init_Bullets();

}

void enemy_stagbeetle::shot() {
	int max = 6;
	if (stats == 1) {
		for (int i = 1; i <= max; i++) {
			int free = search_FreeAddress();
			bullets[free].rad = 5 * DX_PI_F / 3 * 0.4f * i;
			bullets[free].speed = 10;
			bullets[free].x = x;
			bullets[free].y = y;
			bullets[free].stats = 1;
			bullets[free].collision_size = 7;
			count[free] = 0;
		}
	}
}

void enemy_stagbeetle::move_shot() {
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 1) {
			bullets[i].x += -sin(bullets[i].rad) * bullets[i].speed * frame_Time;
			bullets[i].y += -cos(bullets[i].rad) * bullets[i].speed * frame_Time;
			if ((bullets[i].x <= 0 || bullets[i].y <= 0 || bullets[i].x >= 1270 || bullets[i].y >= 710) && count[i] <= 2) {
				count[i]++;
				bullets[i].rad *= DX_PI_F;
			}
		}
	}

}

void enemy_stagbeetle::move() {
	x -= sinf(test.move_rad) * test.speed * frame_Time;
	y -= cosf(test.move_rad) * test.speed * frame_Time;
	if (stats == 1) {
		if (mode == 0 && frame % (int)fps == 0) {
			if (y >= temp_y) {
				speed = test.speed;
				mode = 1;	// to up
			}
			else {
				mode = 2;	// to down
			}
		}

		// ��ɏオ��
		if (mode == 1) {
			if (y >= temp_y - 128) {
				y -= speed * frame_Time;
			}
			else {
				mode = 0;
				shot();
			}
		}

		// ���ɉ���
		if (mode == 2) {
			if (y <= temp_y + 128) {
				y += speed * frame_Time;
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
		DrawGraph((int)x - 48, (int)y - 48, enemy_img[EneKuwagatan], TRUE);
	}
	for (int i = 0; i < MAX_BULLET; i++) {
		bullet_animation_14(bullets[i].x, bullets[i].y, 3, 0);
	}
	init_OutRangeBullets();
}

// ========================================================================================
// ----------------------------------------------------------------------------------------
// �@�W�F�m�T�C�h
// ----------------------------------------------------------------------------------------
// ========================================================================================
void enemy_genocide::init(float start_x, float start_y, int HP, int stat) {
	mode = 1;
	collision_size = 128;
	speed = 0;
	x = start_x;
	y = start_y - test.y;
	prev_y = start_y;
	stats = stat;
	init_Bullets();

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

		// �T�C���J�[�u�̕�
		int width = 150;

		x -= test.speed / 2 * frame_Time;
		deg += 2;
		y = (width * sinf(a2r(deg))) + prev_y;
		if (deg > 360) {
			deg = 0;
		}

		// 2-4�b�̊Ԃŕ���
		if (frame % ((2 + random) * (int)fps) == 0) {
			if (mode == 1) {
				shot();
				mode = 0;
				random = GetRand(2);
			}

			// ����
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
		DrawGraph(x - 370, y - 140, enemy_img[EneGenocide], TRUE);
	}
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 1) {
			bullet_animation_14(bullets[i].x, bullets[i].y, 5, 2);
		}		
	}

	init_OutRangeBullets();
}

// kimobako : WORK IN PROGRESS
void enemy_kimobako::init(float start_x, float start_y, int HP, int stat) {

}

void enemy_kimobako::shot() {

}

void enemy_kimobako::move_shot() {

}

void enemy_kimobako::move() {

}

void enemy_kimobako::draw() {
	if (stats == 1) {
		DrawGraph(x - 128, y - 128, enemy_img[EneKimobako], TRUE);
	}
}

// ========================================================================================
// ----------------------------------------------------------------------------------------
// �@�V���_�[���^�}�E�c
// ----------------------------------------------------------------------------------------
// ========================================================================================
void enemy_shindarla::init(float start_x, float start_y, int HP, int stat) {
	mode = 0;
	collision_size = 32;
	hp = HP;
	x = start_x;
	y = start_y - test.y;
	stats = stat;
	init_Bullets();

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
		bullets[free].collision_size = 8;
	}

}

void enemy_shindarla::move_shot() {
	for (int i = 0; i < MAX_BULLET; i++) {
		// ���i
		if (bullets[i].stats == 1 && mode == 2) {
			bullets[i].rad = ((2.0f * DX_PI_F) / 4) * i;
		}
		// �z�[�~���O
		else if (bullets[i].stats == 1 && mode == 3) {
			rad = bullets[i].rad; // �ŏI�p�x�擾�p
			bullets[i].rad = atan2f(ship.x - bullets[i].x, ship.y - bullets[i].y) - a2r(45);
		}
		// �ŏI�p�x�Œ��i
		else if (bullets[i].stats == 1 && mode == 4) {
			bullets[i].rad = rad;
		}
		bullets[i].x += sinf(bullets[i].rad) * bullets[i].speed * frame_Time;
		bullets[i].y += cosf(bullets[i].rad) * bullets[i].speed * frame_Time;
	}
}

void enemy_shindarla::move() {

	// alive
	if (stats == 1) {
		x -= sinf(test.move_rad) * test.speed * frame_Time;
		y -= cosf(test.move_rad) * test.speed * frame_Time;
	}
	
	// dead
	if (stats != 1) {
		if (mode == 0) {
			mode = 1;
		}

		// ��U�\���ɏo�Ă���
		if (mode == 1) {
			shot();
			mode = 2;
		}

		// �����z�[�~���O���n�߂�
		if (frame % (1 * (int)fps) == 0 && mode == 2) {
			mode = 3;
		}

		// ���Ԃ��o������ŏI�p�x�Œ��i
		if (frame % (3 * (int)fps) == 0 && mode == 3) {
			mode = 4;
		}
	}
	move_shot();
	draw();
	collision_Check();
}

void enemy_shindarla::draw() {
	if (stats == 1) {
		DrawGraph((int)x - 32, (int)y - 32, enemy_img[EneTamautsu], TRUE);
	}
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 1) {
			bullet_animation_16(bullets[i].x, bullets[i].y, 3, 0);
		}
	}
	init_OutRangeBullets();

}

// ========================================================================================
// ----------------------------------------------------------------------------------------
// �@�f�e�N���[�m�@WIP
// ----------------------------------------------------------------------------------------
// ========================================================================================
void enemy_detecrew::init(float start_x, float start_y, int HP, int stat) {
	mode = 0;
	speed = 16;
	count = 0;
	dir = 0;
	hp = HP;
	x = start_x;
	y = start_y - test.y;
	prev_x = start_x;
	prev_y = start_y;
	stats = stat;
	collision_size = 24;
	init_Bullets();
}

void enemy_detecrew::shot() {
	int max = 20;
	for (int i = 0; i < max; i++) {
		int free = search_FreeAddress();
		bullets[free].rad = ((2.0f * DX_PI_F) / max) * dir;
		bullets[free].speed = 6;
		bullets[free].stats = 1;
		bullets[free].collision_size = 16;

		int var_x;
		int var_y;

		switch (dir) {
		// �� 
		case 0:
			var_x = x;
			var_y = y + (bullets[free].collision_size * 2 * i);
			break;
		// �E
		case 1:
			var_x = x + (bullets[free].collision_size * 2 * i);
			var_y = y;
			break;
		// ��
		case 2:
			var_x = x;
			var_y = y - (bullets[free].collision_size * 2 * i);
			break;
		// ��
		case 3:
			var_x = x - (bullets[free].collision_size * 2 * i);
			var_y = y;
			break;
		}

		bullets[free].x = var_x;
		bullets[free].y = var_y;
		
	}
}

void enemy_detecrew::move_shot() {
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 1) {
			bullets[i].x -= sinf(test.move_rad);
			bullets[i].y += cosf(test.move_rad);

			// �s�ƒe�̔��蕔
			if (mode == 2 /* && �_�Ƌ�`�̓����蔻*/ || stats != 1) {
				bullets[i].stats = 0;
			}
		}
	}


}

void enemy_detecrew::move() {
	if (stats == 1) {
		x -= sinf(test.move_rad) * test.speed * frame_Time;
		y -= cosf(test.move_rad) * test.speed * frame_Time;

		// ���@�Ƃ̋���
		if (sqrtf(powf(x - ship.x, 2) + powf(y - ship.y, 2)) <= 100) {
			dir = GetRand(3);	// 4�������烉���_��
			mode = 1;
		}

		// �ˏo��
		if (mode == 1) {
			shot();
			mode = 2;
		}



	}
	move_shot();
	draw();
	collision_Check();
}

void enemy_detecrew::draw() {
	if (stats == 1) {
		DrawGraph(x - 24, y - 24, enemy_img[EneDetekuruno], TRUE);
	}
	if (count <= 2000) {
		count += 1 * frame_Time;
	}

	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 1) {
			if (count == 100 * i) {
				DrawGraph(bullets[i].x, bullets[i].y, enemy_img[19], TRUE);
			}
		}
	}
	init_OutRangeBullets();
}
