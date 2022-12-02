#include "DxLib.h"
#include "environment.h"
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(TRUE);

	// 画面モードのセット
	//SetBackgroundColor(100, 100, 100);
	SetGraphMode(windowX, windowY, 32);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;	// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);
	//時間計測
	float nowTime = 0;
	float prevTime = nowTime;
	float deltaTime;
	float startTime = (float)(GetNowCount());
	float gameTime;
	//初期シーン設定
	GAMEINSTANCE.SetScene(new Game);

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		
		//FPS計算
		nowTime = (float)(GetNowCount());
		deltaTime = (nowTime - prevTime) / 1000.0f;
		gameTime = (nowTime - startTime) / 1000.0f;
		
		//画面初期化
		ClearDrawScreen();
		// 裏画面の内容を表画面に反映
		//DrawFormatString(200, 200, white, "delta:%f\ntime:%f", deltaTime,gameTime);
		GAMEINSTANCE.Update(gameTime, deltaTime);
		GAMEINSTANCE.Draw();
		ScreenFlip();

		prevTime = nowTime;
	}
	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}