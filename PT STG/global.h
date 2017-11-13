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
#define FONT_PWUP    8

#define a2r(deg) (DX_PI_F / 180 * (deg))

#define ITEM_MAX 100
#define DEF_SPEED 4;

enum pu {
	SpeedUp,

};

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
	BossWarmin,		// 21 ���[�~��

	EneWarmBody
};


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
	float	time;
	int		collision_size;
	int		anim;
	int		type;
	int		stat;
	SHIP_SHOT s[100];

	int powerup[6];
	int powerup_select;

	void move();
	void init();
	void draw();
	void shot();
	void shot_Move();
	bool ship_hit(int mx, int my, int col);

	// �V���b�g
	void shot_normal();
	void shot_raser();
	void shot_missile();
	void shot_double_raser();
	void shot_upper();
	void shot_ring_raser();
	void shot_under();
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
GLOBAL int		design_img[5];

GLOBAL int		bullet14_img[84];
GLOBAL int		bullet16_img[48];

GLOBAL int		font_handle[16];
GLOBAL int		effects[16];
GLOBAL int		bg_handle;

GLOBAL int		title_img_1, title_img_2;
GLOBAL int		menu_bg_1, menu_bg_2;

GLOBAL int		title_selected;
GLOBAL int		menu_sehnd[3];
GLOBAL int		game_sehnd[6];
GLOBAL int		game_bgmhnd[4];
GLOBAL int		bgstar[8];

GLOBAL unsigned int frame;

GLOBAL int		mode_flag;
GLOBAL gui		button;
GLOBAL combo	com;
GLOBAL combo	com2;

GLOBAL int		gamemode;
GLOBAL bool		quit;
GLOBAL int		pause_flag;

GLOBAL float	stage_scroll_speed;
GLOBAL float	stage_scroll_rad;

GLOBAL float	to_stage_scroll_speed;
GLOBAL float	to_stage_scroll_rad;

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
void draw_Pause();
void draw_Over();

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
void item_move();

bool IsDetection_Square(int x1, int y1, int x2, int y2, int xr1, int yr1, int xr2, int yr2);
bool IsDetection_PointAndSquare(int sx, int sy, int w, int h, int x, int y);

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
GLOBAL enemy_detecrew	detecrew[EACH_ENEMY_MAX];
GLOBAL enemy_meatball	meat[EACH_ENEMY_MAX];

//debug my ship
GLOBAL my_Ship  ship;

//debug stage
GLOBAL my_Stage test;

#endif
