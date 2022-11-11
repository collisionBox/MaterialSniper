#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Game.h"
#include "Map.h"

class Player;     //前置宣言
class Map;

class Camera {
public:
					Camera();
				   ~Camera(){ };
	void			Init( int in_x, int in_y, int screen_offstX, int screen_offstY, int rangeWidth, int rangeHeight );
	void			move(Map* pMap , int targetX,int targetY);  //カメラ移動処理　マップ範囲を超えずに注目点が画面内に入るようにする
	int				GetCameraX() { return mx; }		
	int				GetCameraY() { return my; }
	void            screenPos2WorldPos(int scrPos_x, int scrPos_y, int *worldPos_X, int *worldPos_Y);	// スクリーン座標系からワールド座標系への座標変換
	void            worldPos2ScreenPos(int worldPos_x, int worldPos_y, int* scrPos_X, int* scrPos_Y);	// ワールド座標系からスクリーン座標系への座標変換


private:
	int				mx , my;                      // カメラ右上ワールド座標
	int				mRangeRectX, mRangeRectY;   // スクロール用矩形左上　この表示領域を超えるときはスクロールする。
	int				mRangeWidth, mRangeHeight;   // スクロール矩形・幅・高さ
};


#endif
