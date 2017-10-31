
#define STAGE_TIP_SIZE 24
#define EACH_ENEMY_MAX 40

typedef struct {
	int		start_x;
	int		enemy_type;

	int		var_1;
	int		var_2;
	int		var_3;
	int		var_4;
	int		var_5;
	int		var_6;
	int		var_7;

	int		stat;
}STAGE_DATA;

// �X�e�[�W�e�N���X
class my_Stage {
public:
	// �X�e�[�W�̑傫��
	int		stage_size_x;
	int		stage_size_y;

	// �X�e�[�W�̌��݂̍��W
	float	x;
	float	y;

	// ���̃X�e�[�W�ɏo�Ă���G�̍ő吔
	int		enemy_max;
	int		enemy_count[22];

	float	speed;

	// ���I�m�ۗp�|�C���^
	int        **stage_size;
	STAGE_DATA	stage_data[200];

	void	move(int s, int r);
	void	init(int sx, int sy);
	void	draw();
	void	del_Stage();
	void	set_StagePos(float sx, float sy);
	void	io_StageDataLoad();
	void	stage_Progression();
	void    stage_EnemyMove();

};

