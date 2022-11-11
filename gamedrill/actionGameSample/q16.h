#include "Sequence.h"

#ifndef __Q16_H__
#define __Q16_H__

class Sequence; // ‘O’uéŒ¾ 

class Quest16Seq : public Sequence
{
public:
	Quest16Seq();
	~Quest16Seq();

	Sequence* move();
	void      draw();

private:
	int mImgHandle;

	int mx, my;
	int mVx, mVy;

};


#endif
