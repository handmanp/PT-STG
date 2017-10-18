#include "global.h"


void my_Ship::init() {
	x = 200.0f;
	y = 360.0f;
	speed = 10.0f;
	collision_size = 3;
}

void my_Ship::draw() {
	DrawBox((int)x - collision_size, (int)y - collision_size, (int)x + collision_size, (int)y + collision_size, GetColor(255, 255, 255), FALSE);
}

void my_Ship::move() {

	int input_stats = 0;
	float rad = 0.0f;

	if (key[KEY_INPUT_UP]    == 1) input_stats += 2;
	if (key[KEY_INPUT_DOWN]  == 1) input_stats += 1;
	if (key[KEY_INPUT_LEFT]  == 1) input_stats += 4;
	if (key[KEY_INPUT_RIGHT] == 1) input_stats += 8;

	switch (input_stats) {
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

	if (rad != -1.0f) {
		x += sinf(rad) * speed;
		y += cosf(rad) * speed;
	}

}

