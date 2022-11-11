#ifndef __PLAYER_TOPVIEW_H__
#define __PLAYER_TOPVIEW_H__

#include "DxLib.h"
#include "Game.h"

#include "camera.h"
#include "map.h"

class PlayerTopview {
public:
	PlayerTopview();
	~PlayerTopview();
	bool		 init(char* imgFilename, char* debugFilename, unsigned int chipsizeX, unsigned int chipsizeY);
	void		 setCollision(unsigned int offset_left_x, unsigned int offset_top_y, unsigned int w, unsigned int h);
	void         setGameStartPos(float x, float y) { mx = mPrevX = x; my = mPrevY = y; }
	void         setDrawOffset(int ofsX, int ofsY);
	void		 move(Map *pMap, Camera *pCam);
	void		 draw(Camera *pCamera);
	int          getPlayerPosX() { return (int)mx; }
	int          getPlayerPosY() { return (int)my; }

private:
	float        mx, my;                     // プレイヤー位置
	float        mPrevX, mPrevY;           // 過去位置
	unsigned int mw, mh;                     // プレーヤ描画幅高さ
	int          mOffsetDrawX, mOffsetDrawY; // プレーヤーの描画位置オフセット
	unsigned int mChipSizeX, mChipSizeY;     // キャラ描画チップサイズ
	unsigned int mChipXnum, mChipYnum;       // キャラチップ2次元配列添え字
	unsigned int mImg, mDebugImg;            // キャラの画像ハンドル

	typedef enum PLAYER_DIR_ENUM
	{
		PLAYER_DIR_UP = 0,
		PLAYER_DIR_LEFT  ,
		PLAYER_DIR_DOWN  ,
		PLAYER_DIR_RIGHT ,
	}PLAYER_DIR_ENUM;

	PLAYER_DIR_ENUM mDir; //キャラの向き

						   //プレーヤーアニメーション状態
	typedef enum PLAYER_ANIM_ENUM
	{
		PLAYER_ANIM_WAIT = 0,
		PLAYER_ANIM_RUN,
	}PLAYER_ANIM_ENUM;

	PLAYER_ANIM_ENUM mAnimState; // アニメーション種類
	unsigned int     mAnimCount; // アニメーションカウンター
	unsigned int     mAnimNum;   // アニメーション表示番号

	typedef enum PLAYER_STATE     // 4ビット = 1 地上 ,4ビット目 = 0 空中
	{
		PLAYER_WAIT = 9,          // ( 1001)
		PLAYER_RUN = 10,          // ( 1010)
	}PLAYER_STATE;

	PLAYER_STATE mState;

	void animation();
};


#endif#pragma once
