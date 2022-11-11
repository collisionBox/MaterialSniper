#ifndef __PLAYER_TOPVIEW_H__
#define __PLAYER_TOPVIEW_H__

#include "DxLib.h"
#include "Game.h"

#include "camera.h"
#include "map.h"

class PlayerTopview {
public:
	PlayerTopview();
	~PlayerTopview();
	bool		 init(char* imgFilename, char* debugFilename, unsigned int chipsizeX, unsigned int chipsizeY);
	void		 setCollision(unsigned int offset_left_x, unsigned int offset_top_y, unsigned int w, unsigned int h);
	void         setGameStartPos(float x, float y) { mx = mPrevX = x; my = mPrevY = y; }
	void         setDrawOffset(int ofsX, int ofsY);
	void		 move(Map *pMap, Camera *pCam);
	void		 draw(Camera *pCamera);
	int          getPlayerPosX() { return (int)mx; }
	int          getPlayerPosY() { return (int)my; }

private:
	float        mx, my;                     // �v���C���[�ʒu
	float        mPrevX, mPrevY;           // �ߋ��ʒu
	unsigned int mw, mh;                     // �v���[���`�敝����
	int          mOffsetDrawX, mOffsetDrawY; // �v���[���[�̕`��ʒu�I�t�Z�b�g
	unsigned int mChipSizeX, mChipSizeY;     // �L�����`��`�b�v�T�C�Y
	unsigned int mChipXnum, mChipYnum;       // �L�����`�b�v2�����z��Y����
	unsigned int mImg, mDebugImg;            // �L�����̉摜�n���h��

	typedef enum PLAYER_DIR_ENUM
	{
		PLAYER_DIR_UP = 0,
		PLAYER_DIR_LEFT  ,
		PLAYER_DIR_DOWN  ,
		PLAYER_DIR_RIGHT ,
	}PLAYER_DIR_ENUM;

	PLAYER_DIR_ENUM mDir; //�L�����̌���

						   //�v���[���[�A�j���[�V�������
	typedef enum PLAYER_ANIM_ENUM
	{
		PLAYER_ANIM_WAIT = 0,
		PLAYER_ANIM_RUN,
	}PLAYER_ANIM_ENUM;

	PLAYER_ANIM_ENUM mAnimState; // �A�j���[�V�������
	unsigned int     mAnimCount; // �A�j���[�V�����J�E���^�[
	unsigned int     mAnimNum;   // �A�j���[�V�����\���ԍ�

	typedef enum PLAYER_STATE     // 4�r�b�g = 1 �n�� ,4�r�b�g�� = 0 ��
	{
		PLAYER_WAIT = 9,          // ( 1001)
		PLAYER_RUN = 10,          // ( 1010)
	}PLAYER_STATE;

	PLAYER_STATE mState;

	void animation();
};


#endif#pragma once
