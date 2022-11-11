#include "Sequence.h"

#ifndef __Q3_H__
#define __Q3_H__

class Sequence; // 前置宣言 

typedef struct vec2
{
	int x, y;
}vec2;

class Quest03Seq : public Sequence
{
public:
	Quest03Seq();
	~Quest03Seq();

	Sequence* move();
	void      draw();

private:
	int mImgHandle;

	vec2 pos[4]; // 上下左右それぞれに動くキャラ座標保存

};


#endif
