#include "Sequence.h"

#ifndef __Q20_21_H__
#define __Q20_21_H__

class Sequence; // ‘O’uéŒ¾ 

class Quest20_21Seq : public Sequence
{
public:
	Quest20_21Seq();
	~Quest20_21Seq();

	Sequence* move();
	void      draw();

private:
	int mImgHandle;

};


#endif
