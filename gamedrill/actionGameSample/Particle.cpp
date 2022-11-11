#include "Particle.h"

//�ÓI�����o��`
int  Particle::mGraphID     ;  
int  Particle::mGraphSize   ;
int  Particle::mNumSubstance;
bool Particle::mMortionBlurOn = true;

void Particle::setGraph(int graphID)
{
	mGraphID = graphID;
	GetGraphSize(graphID, &mGraphSize, &mGraphSize);
}

void Particle::setStartPos(float x, float y, float vx, float vy)
{
	//�������W�Z�b�g
	mx = x;
	my = y;

	// ���x���O���W�Z�o
	mPrevX = mx - vx;
	mPrevY = my - vy;

	mIsHit = false;
}

void Particle::setLifeTime(int frameNum)
{
	mMaxLifeFrameTime = frameNum;
	mNowFrameTime     = mMaxLifeFrameTime;
	mAlive = true;
	mAlpha = 255;
	mNumSubstance++;
}

void Particle::move(Map *pMap)
{
	//�ߋ����W�ƌ��ݍ��W���瑬�x�Z�o
	float vx, vy;
	vx = mx - mPrevX;
	vy = my - mPrevY;

	//�����x 
	float ax, ay;
	ax = 0;
	ay = 2.0f; //�d�͉����x

	vx += ax;
	vy += ay;

	mPrevX = mx;
	mPrevY = my;

	//�ō����x�ŃN�����v
	mx += clamp( 32.0f , -32.0f, vx );
	my += clamp( 32.0f , -32.0f, vy );

	// �}�b�v�̃|�C���^�������Ă����炠���蔻��l��
	if (pMap)
	{
		//�}�b�v�Ƃ����蔻����l���������W�Z�o
		mapHit(pMap);
	}

	// �������炷
	mNowFrameTime--;

	if (mNowFrameTime < mMaxLifeFrameTime / 4)
	{
		mAlpha = (int)(255.0f * mNowFrameTime / (mMaxLifeFrameTime / 4) );
	}

	// �������s�������H
	if (mNowFrameTime < 0)
	{
		mAlive = false;
		mNumSubstance--;
	}
}

// �p�[�e�B�N���`��
void Particle::draw(Camera *pCam)
{
	int camX, camY;
	camX = pCam->GetCameraX();
	camY = pCam->GetCameraY();

	SetDrawBright(255, mAlpha / 4, 0);
	SetDrawBlendMode(DX_BLENDMODE_ADD, mAlpha);
	DrawGraph((int)mx - camX,
		      (int)my - camY, mGraphID, TRUE);


	// �c���`��
	if (mMortionBlurOn)
	{
		// �q�b�g��������Ȃ�c���`�悵�Ȃ�
		if (mIsHit)
		{
			mIsHit = false;
			return;
		}

		float sx, sy;
		sx = mPrevX;
		sy = mPrevY;

		//�p�[�e�B�N�����x�Z�o
		float ax, ay;
		ax = (mx - mPrevX) ;
		ay = (my - mPrevY) ;

		float length2 = ax * ax + ay * ay;

		// �c�������Z�o
		float length = sqrtf(length2);

		// �c�����Ȃ����x�Ȃ烊�^�[��
		if (length < 5.0f)
			return;

		int  maxLen = (int)length / (mGraphSize / 4);

		//�c���p���W������
		ax /= maxLen;
		ay /= maxLen;

		//�c���X�^�[�g���l�ƃ��̑����l���Z�o
		int alphaStart = mAlpha / 3;
		int alphaStep = (mAlpha - alphaStart) / maxLen;

		// �O���W����A�����_�̍��W�܂Ő�����`���悤�ɕ`��
		int i = 0;

		//�c���̕`��
		for (int i = 0; i < maxLen; i++)
		{
			SetDrawBlendMode(DX_BLENDMODE_ADD, alphaStart + alphaStep * i);
			DrawGraph((int)sx - camX,
				(int)sy - camY,
				mGraphID, TRUE);
			    sx += ax;
			    sy += ay;
		}
	}

}

// �c�����ʂ���Ȃ��̐؂�ւ�
void Particle::toggleMortionBlur()
{
	if (mMortionBlurOn)
	{
		mMortionBlurOn = false;
	}
	else
	{
		mMortionBlurOn = true;
	}
}

// �p�[�e�B�N�����}�b�v�ƂԂ��������H
void Particle::mapHit(Map * pMap)
{
	// �ǂ���̌�������u���b�N�ɓ��������̂��H
	// ���x�Z�o
	float vx = mx - mPrevX;
	float vy = my - mPrevY;

	bool ishit = false;

	// ��Ɍ������Ă���Ƃ�
	if (vy < 0)
	{
		int ix1 = pMap->getCollisionMapIndex_X((int)mx + mGraphSize / 2 );
		int iy  = pMap->getCollisionMapIndex_Y((int)my - 1);

		//�V��ɏՓ˂��Ă����ꍇ�߂荞�ݖh�~�ʒu�␳
		if (pMap->getCollisionMapIdFromIndex(ix1, iy) != 0)
		{
			my = (float)(iy + 1) * pMap->getMapChipSizeY();
			ishit = true;
		}
	}
	// ���Ɍ������Ă���Ƃ�
	if (vy > 0)
	{
		int ix1 = pMap->getCollisionMapIndex_X((int)mx + mGraphSize / 2);
		int iy = pMap->getCollisionMapIndex_Y((int)my + mGraphSize);

		// �n�ʂɏՓ˂��Ă��邩
		if (pMap->getCollisionMapIdFromIndex(ix1, iy) != 0)
		{

			//�������̐^���Ƀu���b�N���݂��Ă��Ȃ��Ȃ�n�ʏՓ�
			if (pMap->getCollisionMapIdFromIndex(ix1, iy - 1) == 0)
			{
				mPrevY = my;
				my = (float(iy) * pMap->getMapChipSizeY()) - 8;
				ishit = true;
			}
		}
	}
	//�E�Ɍ������Ă���Ƃ�
	if (vx > 0)
	{
		int ix = pMap->getCollisionMapIndex_X((int)mx + mGraphSize);
		int iy = pMap->getCollisionMapIndex_Y((int)my + mGraphSize / 2);
		if (pMap->getCollisionMapIdFromIndex(ix, iy) != 0)
		{
			mPrevX = mx;
			mx = (float)(ix * pMap->getMapChipSizeX() - 8);
			ishit = true;
		}
	}

	// ���Ɍ������Ă���Ƃ�
	if (vx < 0)
	{
		int ix = pMap->getCollisionMapIndex_X((int)mx);
		int iy = pMap->getCollisionMapIndex_Y((int)my + mGraphSize / 2 );
		if (pMap->getCollisionMapIdFromIndex(ix, iy) != 0)
		{
			mPrevX = mx;
			mx = (float)((ix + 1) * pMap->getMapChipSizeX() + 2 );
			ishit = true;
		}
	}
	// �Ԃ�������������k��
	if (ishit)
	{
		//�P�O�̃t���[���ł��Փ˂��A������Փ˂����ꍇ�͑���
		if (mIsHit)
		{
			mAlive = false;
		} 
		else 
		{
			//����̏Փ˂����̏ꍇ�͎���������
			mIsHit = true;
			mNowFrameTime -= mNowFrameTime / 4;
		}
	}
}
