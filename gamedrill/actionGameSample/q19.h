#include "Sequence.h"

#ifndef __Q19_H__
#define __Q19_H__

class Sequence; // �O�u�錾 

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

	int mZoneX, mZoneY;  // �����蔻�� �E��
	int mZoneW, mZoneH;  // ���E����

	int mZoneAnim;           // �A�j���[�V�����l
	int mZoneAnimInc;

	bool mNowHit;

	bool hitCheck(int leftx1, int topy1, int rightx1, int bottomy1,
		          int leftx2, int topy2, int rightx2, int bottomy2);
};


#endif
