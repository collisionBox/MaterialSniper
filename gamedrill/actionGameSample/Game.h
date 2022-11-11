#include "DxLib.h"
#include "Sequence.h"
#include "mapManager.h"
#include "player.h"
#include "input.h"
#include "bitmapText.h"

#ifndef __GAME_H__
#define __GAME_H__

// コメントにするとウィンドウのみモードに
#define DEBUG_CONSOLE

#ifdef DEBUG_CONSOLE
#pragma comment(linker, "/SUBSYSTEM:CONSOLE" )
#else
#pragma comment(linker, "/SUBSYSTEM:WINDOWS" )
#endif

class Sequence;    // 前置処理
class BitmapText;


// 矩形構造体
typedef struct rectangle
{
	int sx, sy;
	int width, height; 
}rectangle;

bool isHitRect( rectangle *rect1, rectangle *rect2 ); 


// ゲームクラス
class Game
{
private:
	Game();      //シングルトン

	void      input();// 入力
	void      draw(); // 描画
	int       move(); // 移動
	int       update();// 状態遷移のアップデート
	void      init(); // 初期化
	
	// システム内部変数周り
	Sequence *mNowState;  // 現在のステート
	Sequence *mNextState; // 次のステート

	int       mMouseX, mMouseY;         // マウス座標
	int       mMouseButton;
	int       mScreenWidth, mScreenHeight ;// ウィンドウ幅・高さ
	bool      mFullScreen ;
	bool      mIsGameQuit ;
	SHELLEXECUTEINFO *mAppInfo;                //ゲーム終了時アプリ起動情報
	// リソース定義



public:
	static Game& GameInstance()
	{
		static Game GameSys;
		return GameSys;
	}

	~Game();

	BitmapText systemText;

	void Run();  // ゲーム実行
	void setScreen( int width, int height, bool Fullscreen );
	int  getScreenWidth() { return mScreenWidth ;}
	int  getScreenHeight(){ return mScreenHeight;}
	int  getMouseX()      { return mMouseX ; }
	int  getMouseY()      { return mMouseY ; }
	int  getMouseButton() { return mMouseButton ; } 
	
	void ResourceInit();
	void setFirstSequence( Sequence *Seq ) { mNowState = mNextState = Seq; }

	void      callQuit( char *nextappPath, char* nextexename );


};

// クランプ関数
float clamp(float clampMax, float clampMin, float val);
// 値域ランダム関数
float getRandom(float min, float max);


#define GAMEINSTANCE Game::GameInstance()

#endif __GAME_H__