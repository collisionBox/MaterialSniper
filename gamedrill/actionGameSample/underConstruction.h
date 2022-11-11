#include "Sequence.h"

#ifndef __UNDERCONSTRUCTION_H__
#define __UNDERCONSTRUCTION_H__

class Sequence; // ëOíuêÈåæ 

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
