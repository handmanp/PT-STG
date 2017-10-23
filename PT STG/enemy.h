
#define MAX_BULLET 100
#define BX         0
#define BY         1

//�e�\����
typedef struct {
	int   stats;  //�e�̏��
	float x;      //�e�̍��W
	float y;
	float rad;    //�e�̊p�x
	float speed;  //�e�̃X�s�[�h
	float collision_size;
}BULLET;

//�e�N���X
class enemy {
public:
	float x;
	float y;
	float speed;
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

//�Ȃ���
class enemy_nuts : public enemy {
public:
	float py;
	void init(float start_x, float start_y, float s, int rad, int stat);
	void move();
	void draw();
	void shot();
	void move_shot();
};

//�G�_�}����
class enemy_edamamen : public enemy {
public:
	void init();
};

//�E�j�Y
class enemy_uni : public enemy {
public:
	float rx;
	float ry;
	void init(int HP, float start_x, float start_y, float reverse_x, float reverse_y, float s, int stat);
	void move();
	void draw();
};

//�W�F�m�T�C�h�o�i�i��
class enemy_banana : public enemy {
public:
	int mode;
	void init(int HP, float start_x, float start_y, int stat);
	void move();
	void move_shot();
	void shot();
	void draw();
};

//�s�l
class enemy_pine : public enemy {
public:
	int mode;
	int attack_flag;
	float start_y;
	float upper_y;
	void init(int HP, float s_x, float s_y, float up_y, int stat);
	void shot();
	void move();
	void move_shot();
	void draw();
};

//����
class enemy_shell : public enemy {
public:
	int mode;
	void init(int HP, float start_x, float start_y, int stat);
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
	float sh_x;	//���@�̍��W��ۑ� 
	float sh_y;
	void init(int HP, float start_x, float start_y, int stat);
	void move();
	void draw();

};


class enemy_statue : public enemy {
public:
	int hidden;
	int mode;
	float rad;
	void init(int HP, float start_x, float start_y, int stat);
	void move();
	void draw();
};


class enemy_worm : public enemy {
public:
	int mode;
	int deg;
	BULLET ball[6];
	void init(int HP, float start_x, float start_y, int stat);
	void shot();
	void move_shot();
	void move();
	void draw();



};


class enemy_sporecore : public enemy {
public:
	int mode;
	void init(int HP, float start_x, float start_y, int stat);
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
	void init(int HP, float start_x, float start_y, int stat);
	void move();
	void draw();
};


class enemy_stagbeetle : public enemy {
public:
	int mode;
	int temp_x;
	int temp_y;
	void init(int HP, float start_x, float start_y, int stat);
	void shot();
	void move_shot();
	void move();
	void draw();
};
