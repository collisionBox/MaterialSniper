#include "Sequence.h"

#ifndef __Q18_H__
#define __Q18_H__

class Sequence; // 前置宣言 

class Quest18Seq : public Sequence
{
public:
	Quest18Seq();
	~Quest18Seq();

	Sequence* move();
	void      draw();

private:
	int mImgPlayer[16];
	int mImgBG;

	//プレーヤーキャラ関連
	//キャラの状態
	typedef enum CHARA_STATE_ENUM
	{
		CHARA_STATE_ON_GROUND,   // 地面に居る
		CHARA_STATE_JUMP,        // ジャンプ中
		CHARA_STATE_RUN,         // 走っている
		CHARA_STATE_WAIT,        // 待機モーション
	}CHARA_STATE_ENUM;
	
	//キャラ座標
	int mPx, mPy;               // キャラ座標
	int mPVx, mPVy;             // キャラ速度
	int mPHeight;                // キャラ高さ
	int mPJumpPow;               // キャラジャンプ力
	int mPStartAnimNum[4];       // キャラアニメ開始番号
	int mPEndAnimNum[4];         // キャラアニメ終了番号
	int mPAnimNum;               // 再生中のアニメ番号

	CHARA_STATE_ENUM mPState;    // キャラの状態

	int mGroundY;
	bool mRightFlg ;

};


#endif