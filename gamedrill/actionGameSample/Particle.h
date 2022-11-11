#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "Game.h"
#include "DxLib.h"
#include "map.h"
#include "camera.h"

class Particle
{
public:
	Particle() { mAlive = false; }
	~Particle() {}

	void        setGraph(int graphID) ;
	void        setStartPos(float x, float y, float vx, float vy);
	void        setLifeTime(int frameNum);
	void        move( Map *pMap )    ;

	bool        isAlive() 
				{ return mAlive; }

	void        draw( Camera *pCam ) ;
	static void toggleMortionBlur()  ;

	static int  getNumSubstance() 
				{ return mNumSubstance; }
private:
	bool        mAlive             ; // パーティクル生きているか？
	bool        mIsHit             ; // マップにぶつかった直後か？
	float       mx, my            ; // 現在座標
	float       mPrevX, mPrevY  ; // 過去座標
	int         mMaxLifeFrameTime  ; // パーティクル寿命（フレーム単位）
	int         mNowFrameTime      ; // 現在のフレーム時間（生きてきた年齢）
	int         mAlpha             ; // α値セット 
	static int  mGraphID           ; // 画像ID(クラス内ですべて共通）
	static int  mGraphSize         ; // 画像IDの画像サイズ
	static bool mMortionBlurOn     ; // 残像ON/OFF
	static int  mNumSubstance      ; // 実体の個数
	void        mapHit(Map *pMap)   ; // マップとのあたり判定計算
};

#endif