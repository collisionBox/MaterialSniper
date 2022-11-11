#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Game.h"
#include "Map.h"

class Player;     //�O�u�錾
class Map;

class Camera {
public:
					Camera();
				   ~Camera(){ };
	void			Init( int in_x, int in_y, int screen_offstX, int screen_offstY, int rangeWidth, int rangeHeight );
	void			move(Map* pMap , int targetX,int targetY);  //�J�����ړ������@�}�b�v�͈͂𒴂����ɒ��ړ_����ʓ��ɓ���悤�ɂ���
	int				GetCameraX() { return mx; }		
	int				GetCameraY() { return my; }
	void            screenPos2WorldPos(int scrPos_x, int scrPos_y, int *worldPos_X, int *worldPos_Y);	// �X�N���[�����W�n���烏�[���h���W�n�ւ̍��W�ϊ�
	void            worldPos2ScreenPos(int worldPos_x, int worldPos_y, int* scrPos_X, int* scrPos_Y);	// ���[���h���W�n����X�N���[�����W�n�ւ̍��W�ϊ�


private:
	int				mx , my;                      // �J�����E�ハ�[���h���W
	int				mRangeRectX, mRangeRectY;   // �X�N���[���p��`����@���̕\���̈�𒴂���Ƃ��̓X�N���[������B
	int				mRangeWidth, mRangeHeight;   // �X�N���[����`�E���E����
};


#endif
