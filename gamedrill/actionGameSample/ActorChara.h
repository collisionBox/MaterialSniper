#pragma once

#include "Game.h"
typedef enum ACT_ENUM
{
	ACT_ENUM_WAIT,
	ACT_ENUM_LEFTWALK,
	ACT_ENUM_JUMP,
	ACT_ENUM_RIGHTWALK,
}ACT_ENUM;

class ActorChara
{
public:
	ActorChara();
	~ActorChara();

	void init(char* imgFilename, unsigned int chipsizeX, unsigned int chipsizeY);
	void setStartPos(int x, int y);
	bool isNowAnimEnd() { return mbAnimEnd; }
	void setActMode( ACT_ENUM act, int count);
	ACT_ENUM getNowAction() { return mMode; }

	void update();
	void draw();


private:
	int      mx, my;
	int      mPrevX, mPrevY;
	bool     mbAnimEnd;
	int      mAnimTime;
	int      mAnimEndTime;
	int      mImg;
		     
	int      mChipSizeX;
	int      mChipSizeY;
	int      mAnimNum;
	ACT_ENUM mMode;

	void jump();
	void wait();
	void rightwalk();


};