
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

// ステージ親クラス
class my_Stage {
public:
	// ステージの大きさ
	int		stage_size_x;
	int		stage_size_y;

	// ステージの現在の座標
	float	x;
	float	y;

	// そのステージに出てくる敵の最大数
	int		enemy_max;
	int		enemy_count[22];

	float	speed;
	float   move_rad;

	// 動的確保用ポインタ
	int        **stage_size;
	STAGE_DATA	stage_data[300];

	void	move(int s, int r);
	void	init(int sx, int sy);
	void	draw();
	void	del_Stage();
	void	set_StagePos(float sx, float sy);
	void	io_StageDataLoad();
	void	stage_Progression();
	void    stage_EnemyMove();
	bool    io_MapdataFileLoad();
	void    io_LoadMetaData(char *path);

};

typedef struct {
	bool stats;
	int x;
	int y;
}STAGE_METAS;


