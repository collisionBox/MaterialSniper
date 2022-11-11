#include "Sequence.h"

#ifndef __Q6_H__
#define __Q6_H__

class Sequence; // ‘O’uéŒ¾ 

class Quest06Seq : public Sequence
{
public:
	Quest06Seq();
	~Quest06Seq();

	Sequence* move();
	void      draw();

private:
	int mImgHandle1;
	int mImgHandle2;

};


#endif
