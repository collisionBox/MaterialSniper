#include "DxLib.h"
#include "environment.h"
#include "aim.h"
#include "object.h"

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
	
	Aim aim;
	Target target;
	aim.Init();
	target.Init();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();
		aim.Update();
		target.Update();
		

		// 裏画面の内容を表画面に反映
		ScreenFlip();
	}
	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}