
#define MAX_BULLET 100
#define BX         0
#define BY         1

//弾構造体
typedef struct {
	int   stats;  //弾の状態
	float x;      //弾の座標
	float y;
	float rad;    //弾の角度
	float speed;  //弾のスピード
	float collision_size;
}BULLET;

//親クラス
class enemy {
public:
	float x;
	float y;
	float speed;
	float tospeed;
	int   stats;
	float r;
	int   width;
	int   collision_size;
	int   count;
	int   hp;
	int   effect_hnd;

	BULLET bullets[MAX_BULLET];

	void init_Bullets();
	int  collision_Check();
	int  search_FreeAddress();
	bool init_OutRangeBullets();
};

/*----------------------------------------------------------*/
/*--------------------------BOSSES--------------------------*/
/*----------------------------------------------------------*/

class boss_stage1 : public enemy {
	void init();
	void move_1();
	void move_2();
	void move_3();
	void move_4();
};

/*----------------------------------------------------------*/
/*--------------------------STAGE1--------------------------*/
/*----------------------------------------------------------*/

//なっつ
class enemy_nuts : public enemy {
public:
	float py;
	void init(float start_x, float start_y, float s, int rad, int stat);
	void move();
	void draw();
	void shot();
	void move_shot();
};

//エダマメン
class enemy_edamamen : public enemy {
public:
	void init(float start_x, float start_y, int HP, float s, int stat);
	void move();
	void draw();
	void shot();
	void move_shot();
};

//ウニズ
class enemy_uni : public enemy {
public:
	float rx;
	float ry;
	void init(float start_x, float start_y, int HP, float s, int stat);
	void move();
	void draw();
};

//ジェノサイドバナナン
class enemy_banana : public enemy {
public:
	int mode;
	void init(float start_x, float start_y, int HP, int stat);
	void move();
	void move_shot();
	void shot();
	void draw();
};

//ピネ
class enemy_pine : public enemy {
public:
	int mode;
	int attack_flag;
	float start_y;
	float upper_y;
	void init(float s_x, float s_y, int HP, float up_y, int stat);
	void shot();
	void move();
	void move_shot();
	void draw();
};

//かい
class enemy_shell : public enemy {
public:
	int mode;
	void init(float start_x, float start_y, int HP, int stat);
	void shot();
	void move_shot();
	void move();
	void draw();
};

class enemy_brain : public enemy {
public:
	int mode;
	int mode_move;
	int temp_y;
	int max;
	int counter;
	int speed_max;
	int speed_move;
	int circle[MAX_BULLET];
	int circle2[MAX_BULLET];
	int lazer[MAX_BULLET];
	int super[MAX_BULLET];
	int p1_x[MAX_BULLET];
	int p2_x[MAX_BULLET];
	int p1_y[MAX_BULLET];
	int p2_y[MAX_BULLET];
	float t[MAX_BULLET];
	float s_x, s_y;
	void init(float start_x, float start_y, int HP, int stat);
	void shot();
	void move_shot();
	void move();
	void draw();
};

/*----------------------------------------------------------*/
/*--------------------------STAGE2--------------------------*/
/*----------------------------------------------------------*/

class enemy_meatball : public enemy {
public:
	int mode;
	int temp;
	float deg;
	float sh_x;	//自機の座標を保存 
	float sh_y;
	void init(float start_x, float start_y, int HP, int stat);
	void move();
	void draw();

};


class enemy_statue : public enemy {
public:
	int hidden;
	int mode;
	float rad;
	void init(float start_x, float start_y, int HP, int stat);
	void move();
	void draw();
};


class enemy_worm : public enemy {
public:
	int mode;
	float deg;
	int minus;
	BULLET ball[6];
	void init(float start_x, float start_y, int HP, int stat);
	void shot();
	void move_shot();
	void move();
	void draw();



};


class enemy_sporecore : public enemy {
public:
	int mode;
	void init(float start_x, float start_y, int HP, int stat);
	void shot();
	void move_shot();
	void move();
	void draw();
};


class enemy_ivy : public enemy {
public:
	int mode;
	int temp;
	int height;
	int prev_x;
	int prev_y;
	void init(float start_x, float start_y, int HP, int stat);
	void move();
	void draw();
};


class enemy_stagbeetle : public enemy {
public:
	int mode;
	int temp_x;
	int temp_y;
	void init(float start_x, float start_y, int HP, int stat);
	void shot();
	void move_shot();
	void move();
	void draw();
};


class enemy_genocide : public enemy {
public:
	int mode;
	int deg;
	int random;
	float prev_y;
	void init(float start_x, float start_y, int HP, int stat);
	void shot();
	void move_shot();
	void move();
	void draw();
};


class enemy_kimobako : public enemy {
public:
	int mode;
	float prev_y;
	void init(float start_x, float start_y, int HP, int stat);
	void shot();
	void move_shot();
	void move();
	void draw();
};


class enemy_shindarla : public enemy {
public:
	int mode;
	float rad;
	float prev_y;
	void init(float start_x, float start_y, int HP, int stat);
	void shot();
	void move_shot();
	void move();
	void draw();

};


class enemy_detecrew : public enemy {
public:
	BULLET kuki[MAX_BULLET];
	int mode;
	int random;
	int dir;
	float count;
	float rad;
	float prev_x;
	float prev_y;
	float temp_x;
	void init(float start_x, float start_y, int HP, int stat);
	void shot();
	void move_shot();
	void move();
	void draw();
};
