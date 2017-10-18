#ifndef GLOBAL_H_INCLUDED
 #define GLOBAL_H_INCLUDED

#ifdef GLOBAL_VALIABLE_DEFINE
 #define GLOBAL  
#else
 #define GLOBAL extern
#endif

#include "DxLib.h"
#include <Math.h>
#include "stage.h"
#include "enemy.h"

#define WINDOW_SIZE_X 1280
#define WINDOW_SIZE_Y 720

class my_Ship {
public:
	float x;
	float y;
	float speed;
	int left;
	int option;
	int collision_size;

	char key[256];
	void key_Stats() { GetHitKeyStateAll(key); }
	void move();
	void init();
	void draw();
};


GLOBAL my_Ship ship;
GLOBAL my_stage stage;
GLOBAL enemy_uni uni;
GLOBAL enemy_banana banana;
GLOBAL enemy_pine pine;
GLOBAL enemy_shell shell;
GLOBAL enemy_meatball meat;
GLOBAL enemy_statue statue;
GLOBAL enemy_ivy ivy;
GLOBAL enemy_stagbeetle beetle;

GLOBAL unsigned int frame;

#endif
