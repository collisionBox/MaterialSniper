#pragma once
#include "Sequence.h"

#ifndef __Q8_H__
#define __Q8_H__

class Sequence; // ‘O’uéŒ¾ 

class Quest08Seq : public Sequence
{
public:
	Quest08Seq();
	~Quest08Seq();

	Sequence* move();
	void      draw();

private:
	int mImgHandle;
	int fade;

};


#endif
