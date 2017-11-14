
#include "global.h"
#include "ship.h"

#define NORMAL (10)
#define BRO_ (11)

#define SHIP_BULLET_MAX 100

//���@������
//--------------------------------------------------------------------------------
void my_Ship::init() {
	x = 200.0f;
	y = 360.0f;
	speed = 4.0f;
	collision_size = 3;
	anim = 2;
	//type           = 0;		// ���@�̎�� menu.cpp �ɂĎw���
	powerup_select = -1;
	left = 5;
	stat = 0;
	//���@�e������
	for (int i = 0; i < 100; i++) {
		s[i].stats = 0;
		s[i].x = 0.0f;
		s[i].y = 0.0f;
		s[i].rad = 0.0f;
		s[i].speed = 0.0f;
		s[i].length = 0.0f;
	}

	for (int i = 0; i < 6; i++)
		powerup[i] = 0;
}

// ���@�`��
//--------------------------------------------------------------------------------
void my_Ship::draw() {
	if (stat == 0) {
		//�`��
		DrawGraph(x - 50, y - 25, ship_img[anim][type], TRUE);

		for (int i = 0; i < SHIP_BULLET_MAX; i++) {
			if (s[i].stats == 1) {
				DrawGraph(s[i].x - 8, s[i].y - 8, bullet16_img[2], TRUE);
			}
			// ���[�U�[
			if (s[i].stats == 2 || s[i].stats == 4) {
				DrawLine(s[i].x, s[i].y, s[i].x + s[i].length, s[i].y, GetColor(0, 122, 255));
			}
			// �~�T�C��
			if (s[i].stats == 3) {
				DrawGraph(s[i].x - 8, s[i].y - 8, bullet16_img[34], TRUE);
			}
			// �����O���[�U�[
			if (s[i].stats == 5) {
				DrawOvalAA(s[i].x, s[i].y, 16, 64, 20, GetColor(0, 100, 230), FALSE);
			}
			// �c�e
			if (s[i].stats == 6) {
				DrawGraph(s[i].x - 8, s[i].y - 8, bullet16_img[18], TRUE);
			}

		}
	}
	else if (frame % (int)(200.f * frame_Time) == 0) {
		DrawGraph(x - 50, y - 25, ship_img[anim][type], TRUE);

		for (int i = 0; i < SHIP_BULLET_MAX; i++) {
			if (s[i].stats == 1) {
				DrawGraph(s[i].x - 8, s[i].y - 8, bullet16_img[2], TRUE);
			}
		}
	}

	int m = 0;
	if (ship.y > 650) m = ship.y - 650;

	// POWER UP
	for (int i = 0; i < 6; i++) {
		if (i != powerup_select)
			DrawGraph((i * 128) + 256, 680 + m, pwrup_img[1], TRUE);
		else
			DrawGraph((i * 128) + 256, 680 + m, pwrup_img[0], TRUE);

		int str_x = 64 - (GetDrawFormatStringWidthToHandle(font_handle[FONT_PWUP], "%s", pwer_str[i]) / 2);
		DrawFormatStringToHandle((i * 128) + 256 + str_x, 683 + m, GetColor(222, 222, 222), font_handle[FONT_PWUP], "%s", pwer_str[i]);
	}
}

// ����
//--------------------------------------------------------------------------------
void my_Ship::shot() {
	// �ʏ�e
	if (powerup[1] == 0 && powerup[2] == 0) {
		shot_normal();
	}

	// �~�T�C��
	if (powerup[1] == 1) {
		if (powerup[2] == 1) {
			shot_missile();
			shot_raser();
		}
		else if (powerup[2] == 0) {
			shot_normal();
			shot_missile();
		}
	}
	// ���[�U�[
	if (powerup[2] == 1) {
		shot_raser();
		if (type == 0) {				// ���[�U�[2��Ń��j�[�N�V���b�g
			shot_vertical(180);
		}
		else {
			shot_vertical(0);
		}
	}
	else if (powerup[2] == 2) {
		if (type == 0) {
			shot_vertical(180);
			shot_double_raser();
		}
		else {
			shot_vertical(0);
			shot_ring_raser();
		}

	}

}

//���ˌ�̒e�ړ�
//--------------------------------------------------------------------------------
void my_Ship::shot_Move() {
	for (int i = 0; i < SHIP_BULLET_MAX; i++) {

		// �~�T�C���ȊO
		if (s[i].stats != 3) {
			s[i].x += sin(s[i].rad) * s[i].speed * frame_Time;
			s[i].y += cos(s[i].rad) * s[i].speed * frame_Time;
			if (s[i].x < -48 || s[i].x > WINDOW_SIZE_X + 48 ||
				s[i].y < -48 || s[i].y > WINDOW_SIZE_Y + 48) {
				s[i].stats = 0;
			}
		}
		// �~�T�C��
		else if (s[i].stats == 3) {
			s[i].x += sin(s[i].rad) * s[i].speed * frame_Time;
			s[i].y += cos(s[i].rad) * s[i].speed * frame_Time;
			for (int j = 0; j < test.stage_size_x; j++) {
				for (int k = 0; k < test.stage_size_y; k++) {
					if (test.stage_size[j][k] != -1) {
						//�u���b�N�̑��΍��W
						int dpx = (j * STAGE_TIP_SIZE) - test.x;
						int dpy = (k * STAGE_TIP_SIZE) - test.y;
						//�ʓ��̂ݕ`��
						if (dpx >= -STAGE_TIP_SIZE && dpx <= WINDOW_SIZE_X + STAGE_TIP_SIZE &&
							dpy >= -STAGE_TIP_SIZE && dpy <= WINDOW_SIZE_Y + STAGE_TIP_SIZE) {

							// �X�e�[�W�ƃ~�T�C���Ƃ̓����蔻��
							if (abs((dpx + (STAGE_TIP_SIZE / 2)) - s[i].x) < (STAGE_TIP_SIZE) / 2 &&
								abs((dpy + (STAGE_TIP_SIZE / 2)) - s[i].y) < (STAGE_TIP_SIZE + 50) / 2) {
								// �p�x�𕽍s�ɂ���
								s[i].rad = a2r(90);
							}
							else if (abs((dpx + (STAGE_TIP_SIZE / 2)) - s[i].x) < (STAGE_TIP_SIZE + 80) / 2 &&
								abs((dpy + (STAGE_TIP_SIZE / 2)) - s[i].y) < (STAGE_TIP_SIZE + 15) / 2 && s[i].rad == a2r(90)) {

								s[i].stats = 0;
							}
						}
					}
				}
			}
			if (s[i].x < -48 || s[i].x > WINDOW_SIZE_X + 48 ||
				s[i].y < -48 || s[i].y > WINDOW_SIZE_Y + 48) {
				s[i].stats = 0;
			}
		}

	}
}

//���@�S��
//--------------------------------------------------------------------------------
void my_Ship::move() {

	int input_stats = 0;
	float rad = 0.0f;

	speed = 4.f + (powerup[0] * 2.f);

	// �V���b�g�L�[
	if ((ctrl_key[KEY_INPUT_Z] == 2 || ctrl_pad.Buttons[XINPUT_BUTTON_X] == 1) && frame % ((((int)fps + 1) / 30) + 1) == 0) shot();
	if ((ctrl_key[KEY_INPUT_C] == 1 || ctrl_pad.Buttons[XINPUT_BUTTON_Y] == 1)) {
		powerup[powerup_select]++;
		powerup_select = -1;
	}

	if ((ctrl_key[KEY_INPUT_ESCAPE] == 1 || ctrl_key[KEY_INPUT_P] == 1 || ctrl_pad.Buttons[XINPUT_BUTTON_START] == 1)) {
		pause_flag = 1;
	}

	// �f�o�b�O
	if (ctrl_key[KEY_INPUT_V] == 1) {
		powerup_select++;
		if (powerup_select > 6) powerup_select = 0;
	}

	// ���k�ړ��֐�
	shot_Move();

	//�ړ��L�[
	if (ctrl_key[KEY_INPUT_UP] == 2 || ctrl_pad.Buttons[XINPUT_BUTTON_DPAD_UP] == 1) input_stats += 2;
	if (ctrl_key[KEY_INPUT_DOWN] == 2 || ctrl_pad.Buttons[XINPUT_BUTTON_DPAD_DOWN] == 1) input_stats += 1;
	if (ctrl_key[KEY_INPUT_LEFT] == 2 || ctrl_pad.Buttons[XINPUT_BUTTON_DPAD_LEFT] == 1) input_stats += 4;
	if (ctrl_key[KEY_INPUT_RIGHT] == 2 || ctrl_pad.Buttons[XINPUT_BUTTON_DPAD_RIGHT] == 1) input_stats += 8;

	//�ړ��L�[����p�x�����߂�
	switch (input_stats) {
	case 0:
		if (ctrl_pad.ThumbLY > 8192 || ctrl_pad.ThumbLY < -8192 || ctrl_pad.ThumbLX > 8192 || ctrl_pad.ThumbLX < -8192) {
			//��̎���̒l���傫���Ȃ肷���邩�璲��
			float trg_x = ctrl_pad.ThumbLX / 32767.0f;//������-1�ɂ��Ă�
			float trg_y = ctrl_pad.ThumbLY / -32767.0f;
			//�X�e�B�b�N�̓|������_�Ԃ̋����Ō���
			float trigger = sqrtf(trg_x * trg_x + trg_y * trg_y);
			//�p�x
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

	//�ړ�
	if (stat == 0) {
		if (rad != -1.0f) {
			x += (sinf(rad) * speed) * frame_Time;
			y += (cosf(rad) * speed) * frame_Time;
		}
	}
	else if (stat == -1) {
		rad = a2r(90);
		x += (sinf(rad) * speed) * frame_Time;
		y += (cosf(rad) * speed) * frame_Time;
		if (x > 200.f) stat = -2;
	}
	else if (stat == -2) {
		if (rad != -1.0f) {
			x += (sinf(rad) * speed) * frame_Time;
			y += (cosf(rad) * speed) * frame_Time;
			time += 30.f * frame_Time;
			if (time > 800.f) {
				stat = 0;
				time = 0.f;
			}
		}
	}

	if (input_stats != 0) {
		int old1 = 511, old2 = 512;
		for (int i = 0; i < 511; i++) {
			save_way_x[old2] = save_way_x[old1];
			save_way_y[old2] = save_way_y[old1];
			old1--;
			old2--;
		}
		save_way_x[0] = x;
		save_way_y[0] = y;
	}

	for (int i = 0; i < 3; i++) {
		DrawOvalAA(save_way_x[128 + (128 * i)], save_way_y[128 + (128 * i)], 30, 15, 128, 0xFFFFFF, TRUE);
	}

	//�A�j���[�V�����Ǘ�
	if (frame % (int)(2000.f * frame_Time) == 0) {

		//�A�j���[�V����
		if (rad != -1.0f) {
			if (cosf(rad) * speed > 1.5f) anim++;
			if (cosf(rad) * speed < -1.5f) anim--;
		}
		else {
			if (anim > 2) anim--;
			if (anim < 2) anim++;
		}

		//�͈͊O
		if (anim > 4) anim = 4;
		if (anim < 0) anim = 0;
	}

	// �V���_�[��
	if (ship.left < 0) {
		ship.left = 0;
		pause_flag = 2;
	}
}

// ���@�ƏՓ˂������ǂ���
//--------------------------------------------------------------------------------
bool my_Ship::ship_hit(int mx, int my, int col) {
	if (x > mx - col && x < mx + col && y > my - col && y < my + col) {
		return true;
	}
	return false;
}

void item_hit() {
	for (int i = 0; i < ITEM_MAX; i++) {
		if (ship.ship_hit(item[i].x, item[i].y, item[i].size)) {
			item[i].stats = 0;
			ship.powerup_select++;
			if (ship.powerup_select > 6) ship.powerup_select = 0;
		}
	}
}

// �A�C�e��������
//--------------------------------------------------------------------------------
void item_init() {
	for (int i = 0; i < ITEM_MAX; i++) {
		item[i].stats = 0;
		item[i].type = 0;
		item[i].x = 0;
		item[i].y = 0;
		item[i].size = 3;
	}
}

// �A�C�e���\���̂̋󂫔Ԓn������
//--------------------------------------------------------------------------------
int item_search_FreeAddress() {
	for (int i = 0; i < ITEM_MAX; i++) {
		if (item[i].stats == 0) {
			return i;
		}
	}
	return -1;
}

// �A�C�e���𐶐�
//--------------------------------------------------------------------------------
void item_drop(int x, int y, int type) {
	int free = item_search_FreeAddress();

	item[free].stats = 1;
	item[free].type = type;
	item[free].x = x;
	item[free].y = y;
}

// �X�e�ɍ��킹�Ĉړ�
//--------------------------------------------------------------------------------
void item_move() {

	for (int i = 0; i < ITEM_MAX; i++) {
		if (item[i].stats == 1) {

			// �ړ�
			item[i].x -= sinf(test.move_rad) * test.speed * frame_Time;
			item[i].y -= cosf(test.move_rad) * test.speed * frame_Time;

			// ��ʊO�ɂ������������
			if (item[i].x < -100 || item[i].y < -100 || item[i].x > WINDOW_SIZE_X + 100 || item[i].y > WINDOW_SIZE_Y + 100) {
				item[i].stats = 0;
			}
			if (ship.ship_hit(item[i].x, item[i].y, 10)) {
				item[i].stats = 0;
				ship.powerup_select++;
				if (ship.powerup_select > 6) ship.powerup_select = 0;
			}
		}
	}
}

// �A�C�e����`��
//--------------------------------------------------------------------------------
void item_draw() {
	for (int i = 0; i < ITEM_MAX; i++) {
		if (item[i].stats == 1) {

			// �A�C�e���̎�ނɂ��摜��I��
			switch (item[i].type) {
			case 1:
				// �摜�n���h��
				// item[i].image_handle = ???;
				// item[i].size = ???;
				break;
			case 2:
				// �摜�n���h��
				break;
			}

			//�`��
			DrawCircle(item[i].x, item[i].y, item[i].size, GetColor(255, 255, 255), FALSE);
			DrawFormatString(item[i].x, item[i].y, GetColor(0, 255, 255), "E");
			//DrawGraph(item[i].x - item[i].size, item[i].y - item[i].size, item[i].image_handle, TRUE);
		}
	}
}

// �m�[�}���e stats = 1
//--------------------------------------------------------------------------------
void my_Ship::shot_normal() {
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

		PlaySoundMem(game_sehnd[4], DX_PLAYTYPE_BACK, TRUE);
	}
}

// ���[�U�[ (����) stats = 2
//--------------------------------------------------------------------------------
void my_Ship::shot_raser() {
	int check_bullet = 0;
	int free = -1;
	for (int j = 0; j < SHIP_BULLET_MAX; j++) {
		if (s[j].stats == 4) check_bullet++;
		if (free == -1) {
			if (s[j].stats == 0) free = j;
		}
	}
	if (free != -1 && check_bullet <= 1) {
		s[free].stats = 4;
		s[free].x = x;
		s[free].y = y;
		s[free].rad = DX_PI_F / 2;
		s[free].speed = 24;
		s[free].length = 128;

		PlaySoundMem(game_sehnd[4], DX_PLAYTYPE_BACK, TRUE);
	}
}


// �~�T�C�� (����) stats = 3
//--------------------------------------------------------------------------------
void my_Ship::shot_missile() {
	int check_bullet = 0;
	int free = -1;
	for (int i = 0; i < SHIP_BULLET_MAX; i++) {
		if (s[i].stats == 3) check_bullet++;
		if (free == -1) {
			if (s[i].stats == 0) free = i;
		}
	}
	if (free != -1 && check_bullet <= 1) {
		s[free].stats = 3;
		s[free].x = x;
		s[free].y = y;
		s[free].rad = a2r(45);
		s[free].speed = 24;
		s[free].length = 0;

		PlaySoundMem(game_sehnd[4], DX_PLAYTYPE_BACK, TRUE);
	}
}

// �_�u�����[�U�[ (�t�������X) stats = 4
//--------------------------------------------------------------------------------
void my_Ship::shot_double_raser() {
	for (int i = 0; i < 2; i++) {
		int check_bullet = 0;
		int free = -1;
		for (int j = 0; j < SHIP_BULLET_MAX; j++) {
			if (s[j].stats == 4) check_bullet++;
			if (free == -1) {
				if (s[j].stats == 0) free = j;
			}
		}
		if (free != -1 && check_bullet <= 1) {
			s[free].stats = 4;
			s[free].x = x;
			s[free].y = y - 10 + (i * 20);
			s[free].rad = DX_PI_F / 2;
			s[free].speed = 24;
			s[free].length = 128;

			PlaySoundMem(game_sehnd[4], DX_PLAYTYPE_BACK, TRUE);
		}
	}
}

// �����O���[�U�[ (�A�����A) stats = 5
//--------------------------------------------------------------------------------
void my_Ship::shot_ring_raser() {
	int check_bullet = 0;
	int free = -1;
	for (int j = 0; j < SHIP_BULLET_MAX; j++) {
		if (s[j].stats == 5) check_bullet++;
		if (free == -1) {
			if (s[j].stats == 0) free = j;
		}
	}
	if (free != -1 && check_bullet <= 5) {
		s[free].stats = 5;
		s[free].x = x;
		s[free].y = y;
		s[free].rad = DX_PI_F / 2;
		s[free].speed = 24;
		s[free].length = 0;

		PlaySoundMem(game_sehnd[4], DX_PLAYTYPE_BACK, TRUE);
	}
}

// �c�̃V���b�g / deg : �p�x(�x���@)
//--------------------------------------------------------------------------------
void my_Ship::shot_vertical(float deg) {
	for (int i = 0; i < 2; i++) {
		int check_bullet = 0;
		int free = -1;
		for (int i = 0; i < SHIP_BULLET_MAX; i++) {
			if (s[i].stats == 6) check_bullet++;
			if (free == -1) {
				if (s[i].stats == 0) free = i;
			}
		}
		if (free != -1 && check_bullet <= 1) {
			s[free].stats = 6;
			s[free].x = x - 15 + (i * 30);
			s[free].y = y - 10;
			s[free].rad = a2r(deg);
			s[free].speed = 24;
			s[free].length = 0;

			PlaySoundMem(game_sehnd[4], DX_PLAYTYPE_BACK, TRUE);
		}
	}
}
