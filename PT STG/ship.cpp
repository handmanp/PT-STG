#include "global.h"

#define NORMAL (10)
#define BRO_ (11)

#define SHIP_BULLET_MAX 100

//���@������
//--------------------------------------------------------------------------------
void my_Ship::init() {
	x              = 200.0f;
	y              = 360.0f;
	speed          = 4.0f;
	collision_size = 3;
	anim           = 2;
	type           = 0;
	powerup_select = -1;

	//���@�e������
	for (int i = 0; i < 100; i++) {
		s[i].stats  = 0;
		s[i].x      = 0.0f;
		s[i].y      = 0.0f;
		s[i].rad    = 0.0f;
		s[i].speed  = 0.0f;
		s[i].length = 0.0f;
	}
}

//���@�`��
//--------------------------------------------------------------------------------
void my_Ship::draw() {
	//�`��
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

//����
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

//���ˌ�̒e�ړ�
//--------------------------------------------------------------------------------
void my_Ship::shot_Move() {
	for (int i = 0; i < SHIP_BULLET_MAX; i++) {
		if (s[i].stats == 1) {
			s[i].x += sin(s[i].rad) * s[i].speed;
			s[i].y += cos(s[i].rad) * s[i].speed;
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

	//�V���b�g�L�[
	if (ctrl_key[KEY_INPUT_X] == 1 && frame % 2 == 0) shot();

	shot_Move();

	//�ړ��L�[
	if (ctrl_key[KEY_INPUT_UP]    == 1 || ctrl_pad.Buttons[XINPUT_BUTTON_DPAD_UP]    == 1) input_stats += 2;
	if (ctrl_key[KEY_INPUT_DOWN]  == 1 || ctrl_pad.Buttons[XINPUT_BUTTON_DPAD_DOWN]  == 1) input_stats += 1;
	if (ctrl_key[KEY_INPUT_LEFT]  == 1 || ctrl_pad.Buttons[XINPUT_BUTTON_DPAD_LEFT]  == 1) input_stats += 4;
	if (ctrl_key[KEY_INPUT_RIGHT] == 1 || ctrl_pad.Buttons[XINPUT_BUTTON_DPAD_RIGHT] == 1) input_stats += 8;

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
	if (rad != -1.0f) {
		x += sinf(rad) * speed;
		y += cosf(rad) * speed;
	}

	//�A�j���[�V�����Ǘ�
	if (frame % 5 == 0) {

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

}