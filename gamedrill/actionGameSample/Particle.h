#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "Game.h"
#include "DxLib.h"
#include "map.h"
#include "camera.h"

class Particle
{
public:
	Particle() { mAlive = false; }
	~Particle() {}

	void        setGraph(int graphID) ;
	void        setStartPos(float x, float y, float vx, float vy);
	void        setLifeTime(int frameNum);
	void        move( Map *pMap )    ;

	bool        isAlive() 
				{ return mAlive; }

	void        draw( Camera *pCam ) ;
	static void toggleMortionBlur()  ;

	static int  getNumSubstance() 
				{ return mNumSubstance; }
private:
	bool        mAlive             ; // �p�[�e�B�N�������Ă��邩�H
	bool        mIsHit             ; // �}�b�v�ɂԂ��������ォ�H
	float       mx, my            ; // ���ݍ��W
	float       mPrevX, mPrevY  ; // �ߋ����W
	int         mMaxLifeFrameTime  ; // �p�[�e�B�N�������i�t���[���P�ʁj
	int         mNowFrameTime      ; // ���݂̃t���[�����ԁi�����Ă����N��j
	int         mAlpha             ; // ���l�Z�b�g 
	static int  mGraphID           ; // �摜ID(�N���X���ł��ׂċ��ʁj
	static int  mGraphSize         ; // �摜ID�̉摜�T�C�Y
	static bool mMortionBlurOn     ; // �c��ON/OFF
	static int  mNumSubstance      ; // ���̂̌�
	void        mapHit(Map *pMap)   ; // �}�b�v�Ƃ̂����蔻��v�Z
};

#endif