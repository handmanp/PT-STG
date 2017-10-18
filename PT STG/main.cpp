#define GLOBAL_VALIABLE_DEFINE
#include "global.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	ChangeWindowMode(TRUE);
	SetGraphMode(1280, 720, 32);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}



	stage.init(8096, 720);
	stage.set_StagePos(0, 0);

	ship.init();

	uni.init(5, 1100.0f, 720.0f, 200.0f, 200.0f, 5.0f, 8, 1);
	pine.init(5, 1300.0f, 700.0f, 500.0f, 4, 4, 1);
	shell.init(5, 1000.0f, 700.0f, 2.0f ,5, 1);
	banana.init(5 , 1200.0f, 360.0f, 5.0f, 5, 1);

	meat.init(5, 1200.0f, 100.0f, 5, 5, 1);
	statue.init(5, 1000.0f, 700.0f, 10.0f, 5, 1);
	ivy.init(5, 1000.0f, 710.0f, 2, 100, 1);
	beetle.init(5, 900.0f, 360.0f, 10, 128, 1);


	frame = 0;
	


	//メインループ
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		ship.key_Stats();
		ship.move();
		ship.draw();

		stage.move(2, 90);
		stage.draw();

		s_Data = stage.get_StageData(s_Data);

		DrawFormatString(0, 0, GetColor(255, 255, 255), "Data_1:%d / Data_2:%d", (int)GetNowCount(), (int)beetle.mode);

		//uni.move();
		//uni.draw();

		//banana.move();
		//banana.draw();

		//pine.move();
		//pine.draw();

		//shell.move();
		//shell.draw();

		//meat.move();
		//meat.draw();

		//statue.move();
		//statue.draw();

		//ivy.move();
		//ivy.draw();

		beetle.move();
		beetle.draw();



		//フレーム系
		frame++;
		if (frame >= UINT_MAX) {
			frame = 0;
		}
	}

	stage.del_Stage();
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}