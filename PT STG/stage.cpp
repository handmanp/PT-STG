#include "global.h"

using namespace std;

// �G��
enum ene_type {
	// *---Stage 1---*
	EneNuts,		// 0 �i�b�c
	EneEdamamen,	// 1 �G�_�}����
	EneUnis,		// 2 �E�j�Y
	EneBanana,		// 3 �W�F�m�T�C�h�o�i�i
	EnePine,		// 4 �s�l
	EneKai,			// 5 �J�C
	EneTakenokon,	// 6 �^�P�m�R��
	EneKinokon,		// 7 �L�m�R��

	// *---Stage 2---*
	EneKuwagatan,	// 8  �N���K�^��
	EneMeatball,	// 9  �~�[�g�{�[���X�p��
	EneHoushi,		// 10 �E�q
	EneWarm,		// 11 ���[��
	EneTutan,		// 12 �c�^��
	EneStatue,		// 13 ���[�r���O�X�^�`���[

	// *---Stage 3---*
	EneKimobako,	// 14 �L����
	EneDetekuruno,	// 15 �f�e�N���[�m�i�t�j
	EneDetekuki,	// 16 �f�e�N���[�m�i�s�j
	EneTamautsu,	// 17 �V���_�[���^�}�E�c
	EneGenocide,	// 18 ��̓W�F�m�T�C�h

	// *--- Boss ---*
	BossTacos,		// 19 �^�R�X
	BossNoumison,	// 20 �m�E�~�\��
	BossWarmin		// 21 ���[�~��
};

// �X�e�[�W�̏�����
// sx:�X�e�[�W�� sy:�X�e�[�W����
void my_Stage::init(int sx, int sy) {

	// �N���X�p�Ē�`
	stage_size_x = sx; //�T�C�Y
	stage_size_y = sy;

	// 3�����z��̓��I�m�ہi�J�b�R�C�C�j
	stage_size = new int*[stage_size_x];
	for (int i = 0; i < stage_size_x; i++) {
		stage_size[i] = new int[stage_size_y];
	}
	// ������
	for (int i = 0; i < stage_size_x; i++) {
		for (int j = 0; j < stage_size_y; j++) {
			stage_size[i][j] = 0;
		}
	}
	memset(enemy_count, 0, sizeof(enemy_count));
}

// �X�e�[�W�̔j��
// ���R���ʂ��Ȃ��Ǝ��ʂ��璍��
void my_Stage::del_Stage() {
	for (int i = 0; i < stage_size_x; i++) {
		delete[] stage_size[i];
	}
	delete[] stage_size;
	//delete[] stage_data;
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
			if (stage_size[i][j] == 0) {
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
	for (int i = 0; i < enemy_max; i++) {
		DrawFormatString(10, 100 + (i * 20), GetColor(200, 200, 200), "%d, %d, %d, %d, %d, %d, %d",
			stage_data[i].start_x, stage_data[i].enemy_type,
			stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3,
			stage_data[i].var_4, stage_data[i].var_5, stage_data[i].var_6,
			stage_data[i].var_7);
	}
}

// �X�e�[�W�̈ʒu���ړ�����
void my_Stage::set_StagePos(float sx, float sy) {
	x = sx;
	y = sy;
}

// �X�e�[�W�̐i�s
void my_Stage::stage_Progression() {

	// *================ CSV��͕� ==================* //

	for (int i = 0; i < enemy_max; i++) {

		// �o��X���W���}������
		if (stage_data[i].start_x == x) {

			// �G�̃C���X�^���X�쐬
			switch (stage_data[i].enemy_type) {

				// *------------------------ Stage 1 ------------------------*

				// [0] �i�b�c
			case EneNuts:
				nuts[enemy_count[EneNuts]].init(stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3, stage_data[i].var_4, stage_data[i].var_5);
				enemy_count[EneNuts]++;
				break;

				// [1] �G�_�}���� wip
			case EneEdamamen:
				// wip
				break;

				// [2] �E�j�Y
			case EneUnis:
				unis[enemy_count[EneUnis]].init(stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3, stage_data[i].var_4, stage_data[i].var_5, stage_data[i].var_6, stage_data[i].var_7);
				enemy_count[EneUnis]++;
				break;

				// [3] �W�F�m�T�C�h�o�i�i
			case EneBanana:
				banana[enemy_count[EneBanana]].init(stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3, stage_data[i].var_4);
				enemy_count[EneBanana]++;
				break;

				// [4] �s�l
			case EnePine:
				pine[enemy_count[EnePine]].init(stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3, stage_data[i].var_4, stage_data[i].var_5);
				enemy_count[EnePine]++;
				break;

				// [5] �J�C
			case EneKai:
				shell[enemy_count[EneKai]].init(stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3, stage_data[i].var_4);
				enemy_count[EneKai]++;
				break;

				// [6] �^�P�m�R�� wip
			case EneTakenokon:
				break;

				// [7] �L�m�R�� wip
			case EneKinokon:
				break;

				// *------------------------ Stage 2 ------------------------*

				// [8] �N���K�^��
			case EneKuwagatan:
				kuwagatan[enemy_count[EneKuwagatan]].init(stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3, stage_data[i].var_4);
				enemy_count[EneKuwagatan]++;
				break;

				// [9] �~�[�g�{�[���X�p��
			case EneMeatball:
				meat[enemy_count[EneMeatball]].init(stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3, stage_data[i].var_4);
				enemy_count[EneMeatball]++;
				break;

				// [10] �E�q
			case EneHoushi:
				houshi[enemy_count[EneHoushi]].init(stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3, stage_data[i].var_4);
				enemy_count[EneHoushi]++;
				break;

				// [11] ���[��
			case EneWarm:
				worm[enemy_count[EneWarm]].init(stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3, stage_data[i].var_4);
				enemy_count[EneWarm]++;
				break;

				// [12] �c�^��
			case EneTutan:
				ivy[enemy_count[EneTutan]].init(stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3, stage_data[i].var_4);
				enemy_count[EneTutan]++;
				break;

				// [13] ���[�r���O�X�^�`���[
			case EneStatue:
				statue[enemy_count[EneStatue]].init(stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3, stage_data[i].var_4);
				enemy_count[EneStatue]++;
				break;

				// *------------------------ Stage 3 ------------------------*

				// [14] �L���� wip
			case EneKimobako:
				break;

				// [15] �f�e�N���[�m�i�ԁj wip
			case EneDetekuruno:
				break;

				// [16] �f�e�N���[�m�i�s�j wip
			case EneDetekuki:
				break;

				// [17] �V���_�[���^�}�E�c
			case EneTamautsu:
				sindarla[enemy_count[EneTamautsu]].init(stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3, stage_data[i].var_4);
				enemy_count[EneTamautsu]++;
				break;

				// [18] ��̓W�F�m�T�C�h wip
			case EneGenocide:
				break;

				// *------------------------ Stage 3 ------------------------*

				// [19] �^�R�X wip
			case BossTacos:
				break;

				// [20] �m�E�~�\�� wip
			case BossNoumison:
				brain[enemy_count[BossNoumison]].init(stage_data[i].var_1, stage_data[i].var_2, stage_data[i].var_3, stage_data[i].var_4);
				enemy_count[BossNoumison]++;
				break;

				// [21] ���[�~�� wip
			case BossWarmin:
				break;
			}
		}
	}
}

void my_Stage::stage_EnemyMove() {

	// *------------------------ Stage 1 ------------------------*

	for (int i = 0; i < enemy_count[EneNuts]; i++) {
		nuts[i].move();
	}
	for (int i = 0; i < enemy_count[EneEdamamen]; i++) {
		//edamamen[i].move(); wip
	}
	for (int i = 0; i < enemy_count[EneUnis]; i++) {
		unis[i].move();
	}
	for (int i = 0; i < enemy_count[EneBanana]; i++) {
		banana[i].move();
	}
	for (int i = 0; i < enemy_count[EnePine]; i++) {
		pine[i].move();
	}
	for (int i = 0; i < enemy_count[EneKai]; i++) {
		shell[i].move();
	}
	for (int i = 0; i < enemy_count[EneTakenokon]; i++) {
		//takenokon[i].move(); wip
	}
	for (int i = 0; i < enemy_count[EneKinokon]; i++) {
		//nokonoko[i].move(); wip
	}

	// *------------------------ Stage 2 ------------------------*

	for (int i = 0; i < enemy_count[EneKuwagatan]; i++) {
		kuwagatan[i].move();
	}
	for (int i = 0; i < enemy_count[EneMeatball]; i++) {
		meat[i].move();
	}
	for (int i = 0; i < enemy_count[EneHoushi]; i++) {
		houshi[i].move();
	}
	for (int i = 0; i < enemy_count[EneWarm]; i++) {
		worm[i].move();
	}
	for (int i = 0; i < enemy_count[EneTutan]; i++) {
		ivy[i].move();
	}
	for (int i = 0; i < enemy_count[EneStatue]; i++) {
		statue[i].move();
	}

	// *------------------------ Stage 3 ------------------------*

	for (int i = 0; i < enemy_count[EneKimobako]; i++) {
		//kimobako[i].move(); wip
	}
	for (int i = 0; i < enemy_count[EneDetekuruno]; i++) {
		//detekuruno[i].move(); wip
	}
	for (int i = 0; i < enemy_count[EneDetekuki]; i++) {
		//detekuki[i].move(); wip
	}
	for (int i = 0; i < enemy_count[EneTamautsu]; i++) {
		sindarla[i].move();
	}
	for (int i = 0; i < enemy_count[EneGenocide]; i++) {
		//genocide[i].move(); wip
	}

	// *------------------------ Stage 3 ------------------------*
	for (int i = 0; i < enemy_count[BossNoumison]; i++) {
		brain[i].move();
	}
}

// CSV�ǂݍ���
void my_Stage::io_StageDataLoad() {

	// ����Ȃ������Ȃ�K�����₷
	const int BufMax = 128;
	char buf[BufMax];

	FILE *fp = NULL;

	int  line_count = 0;
	char (*data)[BufMax];

	// CSV���J��
	errno_t err;
	err = fopen_s(&fp, _T("data/maps/stage_1/stagedata.csv"), "r");
	if (err == 0) {
		while (fgets(buf, sizeof(buf), fp) != NULL){
			line_count++;
		}
	}
	// ����̃��[�v�p��
	enemy_max = line_count;

	fp = NULL;
	// CSV���J��(�ǂݍ��܂Ȃ���FP�̃|�C���^������������Ȃ��ĂȂ񂩂��܂������Ȃ����ǉ������)
	err = fopen_s(&fp, _T("data/maps/stage_1/stagedata.csv"), "r");

	// �i�[���Ɏg���ϐ�������
	int c;
	int col = 1;
	int row = 0;

	memset(buf, 0, sizeof(buf));

	// ���������͌��\�}�W�b�N
	// �w�b�_�ǂݔ�΂�
	//while (fgetc(fp) != '\n');
	while (1) {
		while (1) {

			c = fgetc(fp);

			// �����Ȃ烋�[�v�𔲂���B
			if (c == EOF) goto LOOP_OUT;

			// �J���}�����s�łȂ���΁A�����Ƃ��ĂȂ���
			if (c != ',' && c != '\n') {
				strcat_s(buf, (const char*)&c);
			}
			// �J���}�����s�Ȃ烋�[�v������B
			else { break; }
		}
		// �����ɗ����Ƃ������Ƃ́A1�Z�����̕����񂪏o���オ�����Ƃ�������
		switch (col) {
			// �C���X�^���X����X���W
			case 1:	
				stage_data[row].start_x = atoi(buf); 
				break;
			// �G�̎��
			case 2: 
				stage_data[row].enemy_type = atoi(buf); 
				break;
			// �e�C���X�^���X�̈���
			case 3: 
				stage_data[row].var_1 = atoi(buf); 
				break;
			case 4: 
				stage_data[row].var_2 = atoi(buf); 
				break;
			case 5: 
				stage_data[row].var_3 = atoi(buf); 
				break;
			case 6: 
				stage_data[row].var_4 = atoi(buf); 
				break;
			case 7: 
				stage_data[row].var_5 = atoi(buf); 
				break;
			case 8: 
				stage_data[row].var_6 = atoi(buf); 
				break;
			case 9: 
				stage_data[row].var_7 = atoi(buf); 
				break;
		}
		// �o�b�t�@��������
		memset(buf, 0, sizeof(buf));
		// �񐔂𑫂�
		col++;

		// �����ǂݍ��񂾕��������s��������񐔂����������čs���𑝂₷
		if (c == '\n') {
			col = 1;
			row++;
		}
	}
LOOP_OUT: // ���[�v�p�X�p�̃��x��
	fclose(fp);

}

/*
// ������𕪊�����
vector<string> split(string& input, char delimiter){

	istringstream stream(input);
	string field;
	vector<string> result;
	while (getline(stream, field, delimiter)) {
		result.push_back(field);
	}
	return result;
}
*/