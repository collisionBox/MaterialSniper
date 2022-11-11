#include "Sequence.h"

#ifndef __Q5_H__
#define __Q5_H__

class Sequence; // ‘O’uéŒ¾ 

class Quest05Seq : public Sequence
{
public:
	Quest05Seq();
	~Quest05Seq();

	Sequence* move();
	void      draw();

private:
	int mImgHandle1;
	int mImgHandle2;

};


#endif
