#include "Sequence.h"

#ifndef __Q11_14_H__
#define __Q11_14_H__

class Sequence; // 前置宣言 

class Quest11_14Seq : public Sequence
{
public:
	Quest11_14Seq();
	~Quest11_14Seq();

	Sequence* move();
	void      draw();

private:
	int mScore;      // スコア
	int mAimScore;   // 目標スコア（増加減に使用）
	int mCountdown;  // カウントダウンタイマー
	int mCountup;    // カウントアップタイマー
	int mMiliSec;    // １秒以下の秒数を計算（小数点第二位まで）
	int mMin;        // 分

	DWORD mTime;
	DWORD mNowTime;

};


#endif
