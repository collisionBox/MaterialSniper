#include "Sequence.h"

#ifndef __Q10_H__
#define __Q10_H__

class Sequence; // ‘O’uéŒ¾ 

class Quest10Seq : public Sequence
{
public:
	Quest10Seq();
	~Quest10Seq();

	Sequence* move();
	void      draw();

private:
	int  mSndHandle1;
	int  mSndHandle2;
	bool mbNowPlay1;
	bool mbNowPlay2;

};


#endif
