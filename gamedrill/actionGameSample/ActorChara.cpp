#include "ActorChara.h"

                                //ウエイト              LEFTRUN                 UP                RIGHT_RUN                
int actor_animationImageX[][4] = { { 0,   0,   0,   0, },{48,  48,  48,  48 },{ 96,  96,  96,  96, },{ 144, 144, 144, 144 } };
int actor_animationImageY[][4] = { { 0,  48,  96, 144, },{ 0,  48,  96, 144 },{  0,  48,  96, 144, },{   0,  48,  96, 144, } };

const int playerAnimSpeed = 10;

ActorChara::ActorChara()
{
	mbAnimEnd  =  false;
	mAnimTime  =  0 ;
	mx         =  0 ;
	my         =  0 ;
	mPrevX     =  0 ;
	mPrevY     =  0 ;
	mImg       = -1 ;
	mChipSizeX =  0 ;
	mChipSizeY =  0 ;
	mMode      =  ACT_ENUM_JUMP;
	mAnimNum   =  0 ;
}

ActorChara::~ActorChara()
{
	if (mImg != -1)
	{
		DeleteGraph(mImg);
	}
}

void ActorChara::init(char * imgFilename, unsigned int chipsizeX, unsigned int chipsizeY)
{
	mImg = LoadGraph(imgFilename);
	mChipSizeX = chipsizeX;
	mChipSizeY = chipsizeY;
}

void ActorChara::setStartPos(int x, int y)
{
	mx = x;
	my = y;
}

void ActorChara::setActMode(ACT_ENUM act, int count)
{
	mAnimEndTime = count;
	mMode = act;
	mbAnimEnd = false;

}

void ActorChara::update()
{
	mAnimTime++;
	switch (mMode)
	{
	case ACT_ENUM_WAIT:
		wait();
		break;

	case ACT_ENUM_JUMP:
		jump();
		break;

	case ACT_ENUM_RIGHTWALK:
		rightwalk();
		break;

	default:
		break;
	}
}

void ActorChara::draw()
{
	int pattern;
	pattern = mMode;

	if (pattern == ACT_ENUM_JUMP)
	{
		pattern = 0;
	}

	DrawRectGraph(mx, my,
		          actor_animationImageX[pattern][mAnimNum],
		          actor_animationImageY[pattern][mAnimNum],
                  48, 48, mImg, TRUE, FALSE);
}

void ActorChara::wait()
{
	static int animCount=0;
	animCount++;

	if (animCount > playerAnimSpeed)
	{
		if (mAnimNum < 4)
		{
			mAnimNum++;
			animCount = 0;

			if (mAnimNum == 4)
			{
				mAnimNum = 0;
			}
		}
	}
	
}

void ActorChara::rightwalk()
{
	static int animCount = 0;
	animCount++;
	
	if (animCount > playerAnimSpeed)
	{
		if (mAnimNum < 4)
		{
			mAnimNum++;
			animCount = 0;

			if (mAnimNum == 4)
			{
				mAnimNum = 0;
			}
		}
	}

	mx++;

	if (mAnimTime > mAnimEndTime)
	{
		mAnimTime = 0;
		this->setActMode(ACT_ENUM_WAIT, 1000);
	}
}

void ActorChara::jump()
{
	static int animCount = 0;
	animCount++;

 
	if (animCount > playerAnimSpeed)
	{
		if (mAnimNum < 4)
		{
			mAnimNum++;
			animCount = 0;

			if (mAnimNum == 4)
			{
				mAnimNum = 0;
			}
		}
	}
	static float anim = 0.0f;
	anim += 0.08f;

	my = 380 + (int)(fabs(sinf(anim)) * -200.0f);

}
