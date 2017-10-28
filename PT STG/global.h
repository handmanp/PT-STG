#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#ifdef GLOBAL_VALIABLE_DEFINE
#define GLOBAL
#else
#define GLOBAL extern
#endif

#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "stage.h"
#include "enemy.h"
#include "gui.h"

#include <cmath>
#include <cstring>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#define WINDOW_SIZE_X 1280
#define WINDOW_SIZE_Y 720

#define FONT_NORMAL  0
#define FONT_BUTTON  1
#define FONT_HEADING 2
#define FONT_YELLOW  3

typedef struct {
	int stats;
	float x;
	float y;
	float rad;
	float speed;
	float length;
}SHIP_SHOT;

class my_Ship {
public:
	float x;
	float y;
	float speed;
	int left;
	int option;
	int collision_size;
	int anim;
	int type;
	SHIP_SHOT s[100];

	int powerup[6];
	int powerup_select;

	void move();
	void init();
	void draw();
	void shot();
	void shot_Move();
};

//入力関連
GLOBAL char ctrl_key[256];
GLOBAL int  mouse_x, mouse_y;
GLOBAL int  mouse_l, mouse_r;
GLOBAL XINPUT_STATE ctrl_pad;

//画像ハンドル系
GLOBAL int enemy_img[32];
GLOBAL int ship_img[5][2];
GLOBAL int maptip_img[105];
GLOBAL int pwrup_img[2];

GLOBAL int bullet14_img[84];
GLOBAL int bullet16_img[48];

GLOBAL int font_handle[16];

GLOBAL int effects[16];

GLOBAL int bg_handle;

GLOBAL unsigned int frame;

GLOBAL int mode_flag;
GLOBAL gui button;
GLOBAL combo com;

void debug_Message();
void main_Editor();
void input_key();
void load_Img();
void load_Effect();
void make_FontData();

//-------------------------------
//debug global area
//-------------------------------

// もはやデバッグではなく消してはいけないものになりました。
GLOBAL enemy_uni		unis[EACH_ENEMY_MAX];
GLOBAL enemy_pine		pine[EACH_ENEMY_MAX];
GLOBAL enemy_nuts		nuts[EACH_ENEMY_MAX];
GLOBAL enemy_shell		shell[EACH_ENEMY_MAX];
GLOBAL enemy_banana		banana[EACH_ENEMY_MAX];
GLOBAL enemy_statue		statue[EACH_ENEMY_MAX];
GLOBAL enemy_ivy		ivy[EACH_ENEMY_MAX];
GLOBAL enemy_stagbeetle kuwagatan[EACH_ENEMY_MAX];
GLOBAL enemy_sporecore	houshi[EACH_ENEMY_MAX];
GLOBAL enemy_worm		worm[EACH_ENEMY_MAX];
GLOBAL enemy_genocide	genocide[EACH_ENEMY_MAX];
GLOBAL enemy_shindarla	sindarla[EACH_ENEMY_MAX];
//GLOBAL enemy_detecrew	detecrew[EACH_ENEMY_MAX];
GLOBAL enemy_meatball	meat[EACH_ENEMY_MAX];

//debug my ship
GLOBAL my_Ship  ship;

//debug stage
GLOBAL my_Stage test;

#endif
