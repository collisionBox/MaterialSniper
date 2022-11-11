#include "Sequence.h"

#ifndef __Q19_H__
#define __Q19_H__

class Sequence; // 前置宣言 

class Quest19Seq : public Sequence
{
public:
	Quest19Seq();
	~Quest19Seq();

	Sequence* move();
	void      draw();

private:
	int mImgHandle;

	int mx, my;
	int mVx, mVy;

	int mZoneX, mZoneY;  // あたり判定 右上
	int mZoneW, mZoneH;  // 幅・高さ

	int mZoneAnim;           // アニメーション値
	int mZoneAnimInc;

	bool mNowHit;

	bool hitCheck(int leftx1, int topy1, int rightx1, int bottomy1,
		          int leftx2, int topy2, int rightx2, int bottomy2);
};


#endif
