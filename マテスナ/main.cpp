#include "DxLib.h"
#include "environment.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(TRUE);

	// 画面モードのセット
	SetBackgroundColor(100, 100, 100);
	SetGraphMode(windowX, windowY, 32);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;	// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);

	float nowTime = 0;
	float prevTime = nowTime;
	float deltaTime;
	float startTime = GetNowCount();
	float gameTime;
	Aim aim;
	Target target;
	Bullet bullet;
	Director director;
	//初期化
	aim.Init();
	target.Init();
	bullet.Init();
	Game game;
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		
		//FPS計算
		nowTime = GetNowCount();
		deltaTime = (nowTime - prevTime) / 1000.0f;
		gameTime = (nowTime - startTime) / 1000.0f;

		//画面初期化
		ClearDrawScreen();
		game.game(gameTime, deltaTime);
		/*aim.Update(target,bullet,gameTime, deltaTime);
		target.Update(gameTime);
		bullet.Update(aim, target);
		director.Update(target, bullet, aim, gameTime);*/
		// 裏画面の内容を表画面に反映
		DrawFormatString(200, 200, white, "%f\n%f", deltaTime,gameTime);
		
		ScreenFlip();

		prevTime = nowTime;
	}
	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}