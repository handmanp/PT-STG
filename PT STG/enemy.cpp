
#include "global.h"

#define SHIP_BULLET_MAX 100
#define a2r(deg) (DX_PI_F / 180 * (deg))

//--------------------------------------------------------------------------------
//����������Ȃ������� -1 ���Ԃ�
//���@�ƓG�{�̂����������� -2 ���Ԃ�
//���@�e�ƓG�{�̂����������� -3 ���Ԃ�
//���@�ƒe������������ �e�\���̂̔z��ԍ� ���Ԃ�
//--------------------------------------------------------------------------------
int enemy::collision_Check() {

	//�e�̘g�O������
	//----------------------------------------------------------------------------
	bool flag = init_OutRangeBullets();
	if (stats == 2 && flag == false) {
		stats = 0; //�e�����Ԃ��������������
		init_Bullets();
	}

	//���@�ƓG�{�̂̓����蔻��
	//----------------------------------------------------------------------------
	if (ship.x >= x - collision_size && ship.x <= x + collision_size &&
		ship.y >= y - collision_size && ship.y <= y + collision_size) {
		return -2;
	}
	//���@�̒e�ƓG�̓����蔻��
	//----------------------------------------------------------------------------
	for (int i = 0; i < SHIP_BULLET_MAX; i++) {
		if (ship.s[i].stats == 1 && stats == 1) {
			if (ship.s[i].x > x - collision_size && ship.s[i].x < x + collision_size &&
				ship.s[i].y > y - collision_size && ship.s[i].y < y + collision_size) {
				ship.s[i].stats = 0;
				hp--;
				//�G���S��
				if (hp <= 0) {
					//�G�t�F�N�g�̍Đ��J�n
					effect_hnd = PlayEffekseer2DEffect(effects[0]);
					//�X�P�[���ύX
					SetScalePlayingEffekseer2DEffect(effect_hnd, 25.0f, 25.0f, 25.0f);
					//�G�̈ʒu�ɃG�t�F�N�g�����킹��
					SetPosPlayingEffekseer2DEffect(effect_hnd, x, y, 0);
					//�G������ł��e���c���Ă��瑶�݂������܂܂ɂ���(stats = 2)
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
	//���@�ƓG�e�̓����蔻��
	//----------------------------------------------------------------------------
	for (int i = 0; i < MAX_BULLET; i++) {
		if (stats == 1) {
			if (ship.x + 25 >= bullets[i].x - bullets[i].collision_size && ship.x - 25 <= bullets[i].x + bullets[i].collision_size &&
				ship.y + 10 >= bullets[i].y - bullets[i].collision_size && ship.y - 10 <= bullets[i].y + bullets[i].collision_size) {
				return i;
			}
		}
	}
	//�߂��Ⴍ�����ʊO��������G�͎��ʁi��������􋁂ށj
	//----------------------------------------------------------------------------
	if (x <= -1024) {
		stats = 0;
		init_Bullets();
	}

	return -1;
}
//----------------------------------------------------------------------------
//�z��̋󂫔Ԓn����
//----------------------------------------------------------------------------
int enemy::search_FreeAddress() {
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 0) {
			return i;
		}
	}
	return -1;
}
//----------------------------------------------------------------------------
//�e�̏�����
//----------------------------------------------------------------------------
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
//----------------------------------------------------------------------------
//��ʊO�ɍs�����e��������
//----------------------------------------------------------------------------
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
/*----------------------------------------------------------*/
/*--------------------------STAGE1--------------------------*/
/*----------------------------------------------------------*/

/*
�E�j�Y�F�񎟊֐��I�����i����j6

�o�i�i�̃��c�F�����_���b���ƂɎ��@�̍����ɍ��킹�Ă��ăo�i�i�i�e�j�𔭎˂���i����j7

�s�l���e�F��ɏオ���ĉ~�`�e���𔭎˂��Đ��b�����牺�ɖ߂�i�ꉞ���܂Ԃ����񂾂����j8

�J�C�F�Œ�C��Ŏ��@�_���̋ʂ������_���b�̊Ԋu�i1�`3�b���炢�H�j�őł��Ă���i����j9

*/
//========================================================================================
//----------------------------------------------------------------------------------------
// �i�b�c
//----------------------------------------------------------------------------------------
//========================================================================================
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

//----------------------------------------------------------------------------
//�`��
//----------------------------------------------------------------------------
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
//----------------------------------------------------------------------------
//�e����
//----------------------------------------------------------------------------
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
//----------------------------------------------------------------------------
//�e�̈ړ�
//----------------------------------------------------------------------------
void enemy_nuts::move_shot() {
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats != 0) {
			bullets[i].x += sin(bullets[i].rad) * bullets[i].speed;
			bullets[i].y += cos(bullets[i].rad) * bullets[i].speed;
		}
	}
}
//----------------------------------------------------------------------------
//�ړ�
//----------------------------------------------------------------------------
void enemy_nuts::move() {

	if (stats != 0) {
		//���ړ�
		x -= speed;
		//�����g�ړ�
		r += 10;
		if (r >= 360) r = 0;
		y = py + cosf((DX_PI_F / 180) * r) * width;
		//��ʊO�ɍs���������
		//if (x < collision_size * -2) stats = 0;

		if (frame % 120 == 0 && stats == 1) {
			shot();
		}
		move_shot();
	}
	collision_Check();
	draw();
}

//========================================================================================
//----------------------------------------------------------------------------------------
//�@�E�j�Y
//----------------------------------------------------------------------------------------
//========================================================================================
void enemy_uni::init(int HP, float start_x, float start_y, float reverse_x, float reverse_y, float s, int coll_size, int stat) {
	x = start_x;
	y = start_y;
	hp = HP;
	rx = reverse_x;
	ry = reverse_y;
	speed = s;
	collision_size = coll_size;
	stats = stat;

}

void enemy_uni::move() {
	if (stats == 1) {
		y -= speed;

		//2���֐��I���� Quadratic functionally Moving
		x = ((y - ry) * (y - ry)) / 320.0f + rx;
	}
}

void enemy_uni::draw() {
	DrawBox(x + collision_size, y + collision_size, x - collision_size, y - collision_size, GetColor(255, 255, 255), FALSE);
}


//========================================================================================
//----------------------------------------------------------------------------------------
// �W�F�m�T�C�h�o�i�i
//----------------------------------------------------------------------------------------
//========================================================================================
void enemy_banana::init(int HP, float start_x, float start_y, float s, int coll_size, int stat) {
	x = start_x;
	y = start_y;
	hp = HP;
	speed = s;
	collision_size = coll_size;
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
		//mode=1:�Î~���
		if (mode == 0 && frame % (GetRand(299) + 1) == 0) {
			mode = 1;
		}

		//mode=2:�ړ���
		if (mode == 1) {
			if (y < ship.y) {
				y += 10;
			}
			else if (y > ship.y) {
				y -= 10;
			}

			//���@�t�߂̍����ɂȂ�����e�𐶐�
			if (y >= ship.y - 10 && y <= ship.y + 10) {
				shot();
				mode = 0;
			}
		}
		move_shot();
	}
}

void enemy_banana::draw() {
	DrawBox(x - 10, y - 10, x + 10, y + 10, GetColor(255, 255, 255), FALSE);
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 1) {
			DrawBox(bullets[i].x - 10, bullets[i].y - 10, bullets[i].x + 10, bullets[i].y + 10, GetColor(255, 255, 0), TRUE);
			DrawFormatString(bullets[i].x - 8, bullets[i].y - 8, GetColor(0, 0, 0), "�o");
		}
	}
	init_OutRangeBullets();
}


//========================================================================================
//----------------------------------------------------------------------------------------
// �s�l
//----------------------------------------------------------------------------------------
//========================================================================================
void enemy_pine::init(int HP, float s_x, float s_y, float up_y, float s, int coll_size, int stat) {
	x = s_x;
	y = s_y;
	hp = HP;
	start_y = s_y;
	upper_y = up_y;
	speed = s;
	collision_size = coll_size;
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
	int down;
	if (stats == 1) {
		x -= speed;

		//mode=0:�㏸
		//�X�e�[�W���W��100�ɂȂ�����(��) upper_y �܂ŏ㏸
		if (mode == 0 && y >= upper_y && x - ship.x <= 256 && x - ship.x >= -256) {
			y -= 10.0f;
			if (y == upper_y) { mode = 1; }  // upper_y �ɒB������Î~��ԂɈڍs
		}

		//mode=1:�Î~
		if (mode == 1) {
			if (attack_flag == 0 && frame % (GetRand(119) + 1) == 0) {
				shot();
			}
			if (attack_flag == 1 && frame % 60 == 0) {
				mode = 2;
			}
		}

		//mode=2:���~
		if (mode == 2 && y != start_y) {
			y += 10;
		}

		move_shot();
	}
}

void enemy_pine::draw() {
	DrawBox(x, y, x + 10, y + 10, GetColor(255, 255, 255), FALSE);
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i].stats == 1) {
			DrawBox(bullets[i].x - 10, bullets[i].y - 10, bullets[i].x + 10, bullets[i].y + 10, GetColor(255, 255, 255), TRUE);
			DrawFormatString(bullets[i].x - 8, bullets[i].y - 8, GetColor(0, 0, 0), "�s");
		}
	}
	init_OutRangeBullets();
}


//========================================================================================
//----------------------------------------------------------------------------------------
// �J�C
//----------------------------------------------------------------------------------------
//========================================================================================
void enemy_shell::init(int HP, float start_x, float start_y, float s, int coll_size, int stat) {
	x = start_x;
	y = start_y;
	hp = HP;
	speed = s;
	collision_size = coll_size;
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
		x -= speed;

		//1~180�t���[����(0~3�b)�����_���Œe�𐶐�
		if (frame % (GetRand(179) + 1) == 0) {
			shot();
		}
		move_shot();
	}
}

void enemy_shell::draw() {
	DrawBox(x, y, x + 10, y + 10, GetColor(255, 255, 250), FALSE);
	for (int i = 0; i < MAX_BULLET; i++) {
		DrawBox(bullets[i].x - 10, bullets[i].y - 10, bullets[i].x + 10, bullets[i].y + 10, GetColor(255, 255, 255), TRUE);
		DrawFormatString(bullets[i].x - 8, bullets[i].y - 8, GetColor(0, 0, 0), "�L");
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



//meatball
void enemy_meatball::init(int HP, float start_x, float start_y, float s, int coll_size, int stat) {
	mode = 0;
	hp = HP;
	x = start_x;
	y = start_y;
	speed = s;
	collision_size = coll_size;
	stats = stat;
	deg = 180;
	r = 0;
	sh_x = 0.0f;
	sh_y = 0.0f;
	temp = 0;
}

void enemy_meatball::move() {
	if (stats == 1) {

		//version 0:��]�𑱂��� 1:���~���ړ���ɒ��i
		int version = 1;

		//���@�� x ��hobo�����ɂȂ�܂Œ��i
		if (mode == 0 && x >= ship.x) {
			x -= speed;

			if (x <= ship.x + 10.0f && x > ship.x) {
				mode = 1;
				sh_x = ship.x;
				sh_y = ship.y;
				r = sqrtf(powf(x - ship.x, 2) + powf(y - ship.y, 2));

				//���@�ƓG�̈ʒu�ɂ����]������]�����߂�
				if (y <= ship.y) {
					temp = 1;	// -> ���]
				}
				else {
					temp = -1;	// -> ����]
				}

				mode = 1;
			}
		}

		//�~�^��
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

		//�~�^���I���㒼�i
		if (mode == 3) {
			x -= speed;
		}
	}
}

void enemy_meatball::draw() {
	DrawBox((int)x - 10, (int)y - 10, (int)x + 10, (int)y + 10, GetColor(255, 255, 255), FALSE);
}

//statue
void enemy_statue::init(int HP, float start_x, float start_y, float s, int coll_size, int stat) {
	hidden = 1;
	mode = 0;
	rad = 0;
	hp = HP;
	x = start_x;
	y = start_y;
	speed = s;
	collision_size = coll_size;
	stats = stat;
}

void enemy_statue::move() {
	if (stats == 1) {
		//�Î~���(hidden = 1)
		if (mode == 0) {
			/*�Ȃ�*/

			//���@-�G�Ԃ̋����� 180 �ȉ��ɂȂ������ɐ퓬���[�h�ɕύX�����̂�����
			if (sqrtf(powf(x - ship.x, 2) + powf(y - ship.y, 2)) <= 180) {
				mode = 1;
				hidden = 0;
			}
		}

		//�ړ��O�̏���(�Ƃ肠����2�b��)
		if (mode == 1) {
			if (frame % 120 == 0) {
				rad = atan2f(ship.x - x, ship.y - y);
				mode = 2;
			}
		}

		//���ۂ̈ړ�
		if (mode == 2) {
			speed += 0.2f;
			x += sinf(rad) * speed;
			y += cosf(rad) * speed;
		}
	}
}

void enemy_statue::draw() {
	if (hidden == 0) {
		DrawBox((int)x - 10, (int)y - 30, (int)x + 10, (int)y + 30, GetColor(255, 255, 255), FALSE);
	}
	else {
		DrawBox((int)x - 10, (int)y - 30, (int)x + 10, (int)y + 30, GetColor(255, 255, 255), TRUE);
	}
}

//warm
void enemy_warm::init(int HP, float start_x, float start_y, float s, int coll_size, int stat) {
	mode = 0;
	ball = 6;
	hp = HP;
	x = start_x;
	y = start_y;
	speed = s;
	collision_size = coll_size;
	stats = stat;
}

void enemy_warm::shot() {

}

void enemy_warm::move_shot() {

}

void enemy_warm::move() {
	if (stats == 1) {

	}
}

void enemy_warm::draw() {
	DrawCircle(x + collision_size, y + collision_size, collision_size, GetColor(255, 255, 255), FALSE, 1);
}

//sporecore
void enemy_sporecore::init(int HP, float start_x, float start_y, float s, int coll_size, int stat) {
	hp = HP;
	x = start_x;
	y = start_y;
	speed = s;
	collision_size = coll_size;
	stats = stat;
}

void enemy_sporecore::shot() {

}

void enemy_sporecore::move_shot() {

}

void enemy_sporecore::move() {
	x -= 10.0f;
}

void enemy_sporecore::draw() {
	DrawBox((int)x - 10, (int)y - 30, (int)x + 10, (int)y + 30, GetColor(255, 255, 255), FALSE);

}

//ivy
//y �͍ő厞�̃c�^�̍ŉ���
void enemy_ivy::init(int HP, float start_x, float start_y, float s, int Height, int stat) {
	hp = HP;
	x = start_x;
	y = start_y;
	prev_x = (int)start_x;
	prev_y = (int)start_y;
	speed = s;
	collision_size = Height;
	height = Height;
	stats = stat;
	mode = 0; //0:�n�� 1:�L�тĂ�Œ� 2:�j��
}

void enemy_ivy::move() {
	x -= speed;

	//����
	if (stats == 1) {

		//�Ƃ肠����1�b��Ɉ��
		if (frame % 60 == 0 && mode == 0) {
			mode = 1;
		}
		if (mode == 1) {
			if (y >= prev_y - height) {

				//��ɐݒu�o�[�W�����Ɖ��ɐݒu�o�[�W����
				if (y <= WINDOW_SIZE_Y / 2) {
					y += speed;
				}
				else {
					y -= speed;
				}
			}

			//HP���[���ɂȂ����玀���
			if (hp <= 0) {
				stats = 0;
			}
		}
	}

	//�� = ����
	if (stats == 0) {
		if (frame % 60 == 0) {
			stats = 1;
			hp = 5;
			mode = 0;
			y = (float)prev_y;
		}
	}
}

void enemy_ivy::draw() {
	if (stats == 1) {
		if (prev_y >= WINDOW_SIZE_Y / 2) {
			DrawBox((int)x - 15, (int)y + height, (int)x + 15, (int)y, GetColor(255, 255, 255), FALSE);
		}
		else {
			DrawBox((int)x - 15, (int)y - height, (int)x + 15, (int)y, GetColor(255, 255, 255), FALSE);
		}
	}
}

//stagbeetle
void enemy_stagbeetle::init(int HP, float start_x, float start_y, float s, int coll_size, int stat) {
	hp = HP;
	x = start_x;
	y = start_y;
	speed = s;
	collision_size = coll_size;
	stats = stat;
	temp_x = start_x;
	mode = 0;
}

void enemy_stagbeetle::shot() {

}

void enemy_stagbeetle::move_shot() {

}

void enemy_stagbeetle::move() {
	if (stats == 1) {

		if (mode == 0) {
			if (y >= WINDOW_SIZE_Y / 2) {
				mode = 1;
			}
			else {
				mode = 2;
			}
		}

		if (mode == 1) {
			if (y >= (WINDOW_SIZE_Y / 3)) {

				temp_x -= speed;
				if (temp_x >= x + collision_size) {
					speed *= -1;
				}
				else if (temp_x <= x - collision_size) {
					speed *= -1;
				}

				y = (pow(temp_x - x, 2)) / 320.0f + (WINDOW_SIZE_Y / 3);
			}
			else {
				mode = 0;
			}
		}


	}
}

void enemy_stagbeetle::draw() {
	DrawBox((int)x - collision_size, (int)y - collision_size, (int)x + collision_size, (int)y + collision_size, GetColor(255, 255, 255), FALSE);
}