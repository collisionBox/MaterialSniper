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

	Aim aim;
	Target target;
	Bullet bullet;
	//初期化
	aim.Init();
	target.Init(STOP);
	bullet.Init();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		
		//FPS計算
		nowTime = GetNowCount();
		deltaTime = (nowTime - prevTime) / 1000.0f;

		//画面初期化
		ClearDrawScreen();
		aim.Update(target,bullet);
		target.Update();
		bullet.Update(aim, target);
		// 裏画面の内容を表画面に反映
		DrawFormatString(200, 200, white, "%f", deltaTime);
		ScreenFlip();
		prevTime = nowTime;
	}
	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}