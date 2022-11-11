#include "Sequence.h"

#ifndef __UNDERCONSTRUCTION_H__
#define __UNDERCONSTRUCTION_H__

class Sequence; // �O�u�錾 

class UnderConstructionSeq : public Sequence
{
public:
	UnderConstructionSeq();
	~UnderConstructionSeq();

	Sequence* move();
	void      draw();

private:
	int mImgHandle;

};


#endif
