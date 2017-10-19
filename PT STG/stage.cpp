#include "global.h"

// �X�e�[�W�̏�����
// sx:�X�e�[�W�� sy:�X�e�[�W����
void my_Stage::init(int sx, int sy) {
	// �N���X�p�Ē�`
	stage_size_x = sx; //�T�C�Y
	stage_size_y = sy;

	// 3�����z��̓��I�m�ہi�J�b�R�C�C�j
	stage_size = new int**[stage_size_x];
	for (int i = 0; i < stage_size_x; i++) {
		stage_size[i] = new int*[stage_size_y];
		for (int j = 0; j < stage_size_y; j++) {
			stage_size[i][j] = new int[2];
		}
	}
	// ������
	for (int i = 0; i < stage_size_x; i++) {
		for (int j = 0; j < stage_size_y; j++) {
			stage_size[i][j][0] = 0;
			stage_size[i][j][1] = 0;
		}
	}
}

// �X�e�[�W�̔j��
// ���R���ʂ��Ȃ��Ǝ��ʂ��璍��
void my_Stage::del_Stage() {
	for (int i = 0; i < stage_size_x; i++) {
		for (int j = 0; j < stage_size_y; j++) {
			delete[] stage_size[i][j];
		}
		delete[] stage_size[i];
	}
	delete[] stage_size;
}

// �X�e�[�W�̈ړ�
// s:�ړ��X�s�[�g r:�ړ��p�x
void my_Stage::move(int s, int r) {
	// �X�s�[�h�������o�ɒǉ�
	speed = s;
	//���W�A���ɂ���
	float move_rad = (DX_PI_F / 180.0f) * r;
	// �ړ�����
	x += sinf(move_rad) * s;
	y += cosf(move_rad) * s;
}

// �X�e�[�W��`��(��)
void my_Stage::draw() {
	for (int i = 0; i < stage_size_x; i++) {
		for (int j = 0; j < stage_size_y; j++) {
			if (stage_size[i][j][1] == 0) {
				//�u���b�N�̑��΍��W
				int dpx = (i * STAGE_TIP_SIZE) - x;
				int dpy = (j * STAGE_TIP_SIZE) - y;
				//�ʓ��̂ݕ`��
				if (dpx >= -STAGE_TIP_SIZE && dpx <= WINDOW_SIZE_X + STAGE_TIP_SIZE &&
					dpy >= -STAGE_TIP_SIZE && dpy <= WINDOW_SIZE_Y + STAGE_TIP_SIZE) {
					DrawBox(dpx, dpy, dpx + STAGE_TIP_SIZE, dpy + STAGE_TIP_SIZE, GetColor(40, 40, 40), FALSE);
				}
			}
		}
	}
}

// �X�e�[�W�̏�Ԃ��擾
STAGE_DATA my_Stage::get_StageData(STAGE_DATA data) {
	data.x = x;
	data.y = y;
	return data;
}

// �X�e�[�W�̈ʒu���ړ�����
void my_Stage::set_StagePos(float sx, float sy) {
	x = sx;
	y = sy;
}