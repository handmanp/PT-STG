#pragma once
#define MAX_BULLET 100
#define BX         0
#define BY         1
#define a2r(deg) (DX_PI_F / 180 * (deg))

typedef struct {
	int   stats;  //íeÇÃèÛë‘
	float x;      //íeÇÃç¿ïW
	float y;
	float rad;    //íeÇÃäpìx
	float speed;  //íeÇÃÉXÉsÅ[Éh
}BULLET;


class enemy {
public:
	float x;
	float y;
	float speed;
	float   r;
	int	  hp;
	int   stats;
	int   width;
	int   collision_size;
	int   count;
	int   effect_hnd;
	int   bullet_pos[MAX_BULLET][2];
	BULLET bullets[MAX_BULLET];
	int collision_Check();
	void init_Bullets();
	bool init_OutRangeBullets();
	int search_FreeAddress();
};


  /*----------------------------------------------------------*/
 /*--------------------------STAGE1--------------------------*/
/*----------------------------------------------------------*/

class enemy_uni : public enemy {
public:
	float rx;
	float ry;
	void init(int HP, float start_x, float start_y, float reverse_x, float reverse_y, float s, int coll_size, int stat);
	void move();
	void draw();
};


class enemy_banana : public enemy {
public:
	int mode;
	void init(int HP, float start_x, float start_y, float s, int coll_size, int stat);
	void move();
	void move_shot();
	void shot();
	void draw();
};


class enemy_pine : public enemy {
public:
	//mode 1:è„è∏ 2:ê√é~ 3:â∫ç~
	int mode;
	int attack_flag;
	float start_y;
	float upper_y;
	void init(int HP, float s_x, float s_y, float up_y, float s, int coll_size, int stat);
	void shot();
	void move();
	void move_shot();
	void draw();
};


class enemy_shell : public enemy {
public:
	int mode;
	void init(int HP, float start_x, float start_y, float s, int coll_size, int stat);
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
	float sh_x;	//é©ã@ÇÃç¿ïWÇï€ë∂ 
	float sh_y;
	void init(int HP, float start_x, float start_y, float s, int coll_size, int stat);
	void move();
	void draw();

};


class enemy_statue : public enemy {
public:
	int hidden;
	int mode;
	float rad;
	void init(int HP, float start_x, float start_y, float s, int coll_size, int stat);
	void move();
	void draw();
};


class enemy_warm : public enemy {
public:
	int mode;
	int ball;
	void init(int HP, float start_x, float start_y, float s, int coll_size, int stat);
	void shot();
	void move_shot();
	void move();
	void draw();
};


class enemy_sporecore : public enemy {
public:
	int mode;
	void init(int HP, float start_x, float start_y, float s, int coll_size, int stat);
	void shot();
	void move_shot();
	void move();
	void draw();
};


class enemy_ivy : public enemy {
public:
	int mode;
	int height;
	int prev_x;
	int prev_y;
	void init(int HP, float start_x, float start_y, float s, int Height, int stat);
	void move();
	void draw();
};


class enemy_stagbeetle : public enemy {
public:
	int mode;
	int temp_x;
	void init(int HP, float start_x, float start_y, float s, int coll_size, int stat);
	void shot();
	void move_shot();
	void move();
	void draw();
};
