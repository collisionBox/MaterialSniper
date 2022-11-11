#include "Sequence.h"

#ifndef __Q7_H__
#define __Q7_H__

class Sequence; // ‘O’uéŒ¾ 

class Quest07Seq : public Sequence
{
public:
	Quest07Seq();
	~Quest07Seq();

	Sequence* move();
	void      draw();

private:
	int mImgHandle;

};


#endif
