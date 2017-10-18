
#define STAGE_TIP_SIZE 32

typedef struct {
	float x;
	float y;
}STAGE_DATA;

//�X�e�[�W�e�N���X
class my_Stage {
public:
	//�X�e�[�W�̑傫��
	int stage_size_x;
	int stage_size_y;

	//�X�e�[�W�̌��݂̍��W
	float x;
	float y;

	//���I�m�ۗp�|�C���^
	int ***stage_size;

	void move(int s, int r);
	void init(int sx, int sy);
	void draw();
	void del_Stage();
	void set_StagePos(float sx, float sy);
	STAGE_DATA get_StageData(STAGE_DATA data);

};
GLOBAL STAGE_DATA s_Data;