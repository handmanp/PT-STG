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
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <Windows.h>
#include <iostream>
#include <Shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")

#define WINDOW_SIZE_X 1280
#define WINDOW_SIZE_Y 720

#define FONT_NORMAL  0
#define FONT_BUTTON  1
#define FONT_HEADING 2
#define FONT_YELLOW  3
#define FONT_COMBOX  4
#define FONT_TI_MENU 5
#define FONT_INGAME  6
#define FONT_BIG     7

#define a2r(deg) (DX_PI_F / 180 * (deg))

#define ITEM_MAX 100

typedef struct {
	int		stats;
	float	x;
	float	y;
	float	rad;
	float	speed;
	float	length;
}SHIP_SHOT;

class my_Ship {
public:
	float	x;
	float	y;
	float	speed;
	int		left;
	int		option;
	int		collision_size;
	int		anim;
	int		type;
	SHIP_SHOT s[100];

	int powerup[6];
	int powerup_select;

	void move();
	void init();
	void draw();
	void shot();
	void shot_Move();
};

// �A�C�e���\����
typedef struct {
	float x;
	float y;
	int type;
	int stats;
	int image_handle;
	int size;
		
}ITEM;

GLOBAL int			score;
GLOBAL int			left;

//���͊֘A
GLOBAL char			ctrl_key[256];
GLOBAL int			mouse_x, mouse_y;
GLOBAL int			mouse_l, mouse_r;
GLOBAL XINPUT_STATE ctrl_pad;

//�摜�n���h���n
GLOBAL int		enemy_img[32];
GLOBAL int		ship_img[5][2];
GLOBAL int		maptip_img[880];
GLOBAL int		pwrup_img[2];
GLOBAL int		chara_img[2][4];
GLOBAL int		design_img[4];

GLOBAL int		bullet14_img[84];
GLOBAL int		bullet16_img[48];

GLOBAL int		font_handle[16];
GLOBAL int		effects[16];
GLOBAL int		bg_handle;

GLOBAL int		title_img_1, title_img_2;
GLOBAL int		menu_bg_1, menu_bg_2;

GLOBAL int		title_selected;
GLOBAL int		menu_sehnd[3];

GLOBAL unsigned int frame;

GLOBAL int		mode_flag;
GLOBAL gui		button;
GLOBAL combo	com;

GLOBAL int		gamemode;
GLOBAL bool		quit;

GLOBAL int b_anim_3, b_anim_4, b_anim_6, b_dir_6, b_dir_3;

//fps�֘A�ϐ�
GLOBAL int		fps_Time[2];
GLOBAL int		fps_Time_i;
GLOBAL double	fps;

GLOBAL float	frame_Time, frame_Time_2;
GLOBAL LONGLONG prev_Time;

GLOBAL ITEM item[ITEM_MAX];

void debug_Message();
void main_Editor();
void input_key();
void load_Img();
void load_Effect();
void make_FontData();
void ingame_GUI();

double fps_Calc();
float variable_Fps();

int		load_check_loop();
void	draw_Menu();

void	bullet_animation_14(int x, int y, int color, int type);
void	bullet_animation_16(int x, int y, int color, int type);
void	bullet_Animation_Update();

int  item_search_FreeAddress();
void item_init();
void item_drop(int x, int y, int type);
void item_draw();

//-------------------------------
//debug global area
//-------------------------------

// ���͂�f�o�b�O�ł͂Ȃ������Ă͂����Ȃ����̂ɂȂ�܂����B
GLOBAL enemy_uni		unis[EACH_ENEMY_MAX];
GLOBAL enemy_pine		pine[EACH_ENEMY_MAX];
GLOBAL enemy_brain		brain[EACH_ENEMY_MAX];
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
