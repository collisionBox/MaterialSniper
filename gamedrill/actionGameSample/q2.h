#include "Sequence.h"

#ifndef __Q2_H__
#define __Q2_H__

class Sequence; // ‘O’uéŒ¾ 

class Quest02Seq : public Sequence
{
public:
	Quest02Seq();
	~Quest02Seq();

	Sequence* move();
	void      draw();

private:
	int mImgHandle[2];

};


#endif
