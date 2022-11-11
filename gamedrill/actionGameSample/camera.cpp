#include "camera.h"

Camera::Camera()
{
	mx = my = 0;
}

void Camera::Init( int in_startx, int in_starty, int screen_offstX, int screen_offstY, int rangeWidth, int rangeHeight  )
{
	mx = in_startx; my = in_starty;
	mRangeRectX = screen_offstX;
	mRangeRectY = screen_offstY;
	mRangeWidth  = rangeWidth;
	mRangeHeight = rangeHeight;
	
}

void Camera::move(Map *pMap, int targetX, int targetY )
{
	int tmpx,tmpy;

	tmpx = targetX - mx;
	tmpy = targetY - my;

	// �X�N���[���͈͂𒴂��Ă�����J�������W���ړ�����
	// x����
	if( tmpx < mRangeRectX )
	{
		mx -= mRangeRectX - tmpx;
	}
	if( tmpx > mRangeRectX + mRangeWidth )
	{
		mx += tmpx - ( mRangeRectX + mRangeWidth);  
	}

	// y����
	if( tmpy < mRangeRectY )
	{
		my -= mRangeRectY - tmpy;
	}

	if( tmpy > mRangeRectY + mRangeHeight )	
	{
		my += tmpy - (mRangeRectY + mRangeHeight);
	}

	//�J�������}�b�v�͈͒����Ȃ�
	if( mx < 0 )
	{
		mx = 0;
	}
	if( my < 0 )
	{
		my = 0;
	}

	if( mx > pMap->getMapWidth() - GAMEINSTANCE.getScreenWidth() )
	{
		mx = pMap->getMapWidth() - GAMEINSTANCE.getScreenWidth();
	}

	if( my > pMap->getMapHeight() - GAMEINSTANCE.getScreenHeight() )
	{
		my = pMap->getMapHeight() - GAMEINSTANCE.getScreenHeight();
	}
}


// �X�N���[�����W�n���烏�[���h���W�n�ւ̍��W�ϊ�
void Camera::screenPos2WorldPos(int scrPos_x, int scrPos_y, int *worldPos_X, int *worldPos_Y)
{
	*worldPos_X = scrPos_x + mx;
	*worldPos_Y = scrPos_y + my;
}

// ���[���h���W�n����X�N���[�����W�n�ւ̍��W�ϊ�
void Camera::worldPos2ScreenPos(int worldPos_x, int worldPos_y, int* scrPos_X, int* scrPos_Y)
{
	*scrPos_X = worldPos_x - mx;
	*scrPos_Y = worldPos_y - my;
}
