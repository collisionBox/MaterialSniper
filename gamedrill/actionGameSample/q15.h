#include "Sequence.h"

#ifndef __Q15_H__
#define __Q15_H__

class Sequence; // ‘O’uéŒ¾ 

class Quest15Seq : public Sequence
{
public:
	Quest15Seq();
	~Quest15Seq();

	Sequence* move();
	void      draw();

private:

	int mImgHandle;

	int mVal;
	int mValInc;
	static const int mMaxval = 150;
};


#endif
