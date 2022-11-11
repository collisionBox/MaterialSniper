#include "DxLib.h"
#include "Game.h"
#include "Sequence.h"

#include "qSelector.h"
//#include "SoftBodyTest.h"

int		WINAPI		myWinMain( HINSTANCE hInstance	,HINSTANCE hPreInst	,LPSTR     CmdLine	,int CmdShow ,
							   int screen_x, int screen_y, bool FullScreen)
{

	// スクリーンセット
	GAMEINSTANCE.setScreen(screen_x, screen_y, FullScreen);

	// 開始シーケンスを設定
	GAMEINSTANCE.setFirstSequence(new QuestSelector);

	// ゲーム開始
	GAMEINSTANCE.Run();

	return 0;
}


////////////////////////////////////////////////////////////////////////////////////////
// コンソール画面からWindowsのお作法に飛ぶためのコード
////////////////////////////////////////////////////////////////////////////////////////
void windowOpen(int screen_x, int screen_y, bool FullScreen)
{
	HINSTANCE	hInstance	= GetModuleHandle(0);
	int			iCmdShow	= SW_SHOWDEFAULT ;

	myWinMain( hInstance, NULL, NULL, iCmdShow, screen_x, screen_y, FullScreen);
}

// DOS窓時のエントリーポイント
int main(void)
{
	windowOpen(800, 600, false);
	return 0;
}

// ウィンドウシステムの時のエントリーポイント
int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{
	main();
	return 0;
}