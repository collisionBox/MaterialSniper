#include "Sequence.h"

#ifndef __Q4_H__
#define __Q4_H__

class Sequence; // ‘O’uéŒ¾ 

class Quest04Seq : public Sequence
{
public:
	Quest04Seq();
	~Quest04Seq();

	Sequence* move();
	void      draw();

private:
	int mImgHandle[16];

	int mAnimCounter;
	int mMaxAnimnum;
	int mInterval;
};


#endif
