#include "Sequence.h"

#ifndef __Q1_H__
#define __Q1_H__

class Sequence; // ‘O’uéŒ¾ 

class Quest01Seq : public Sequence
{
public:
	Quest01Seq();
	~Quest01Seq();

	Sequence* move();
	void      draw();

private:
	int mImgHandle;

};


#endif
