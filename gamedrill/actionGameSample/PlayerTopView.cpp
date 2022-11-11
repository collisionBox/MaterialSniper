#include "playertopview.h"

const float player_accel = 0.2f;
const float player_maxSpeedX = 5.0f;
const float player_maxSpeedY = 5.0f;

const int   player_offsetX = -12;
const int   player_offsetY = -4;
const int   player_AnimWaitnum = 4;
const int   player_AnimWalknum = 4;
const int   player_AnimSpeed = 10; // 10�t���[���ɂP��A�j���[�V�����i�߂�


PlayerTopview::PlayerTopview()
{
	mState = PLAYER_WAIT;
	mx = 0;
	my = 0;
	mPrevX = 0;
	mPrevY = 0;

	mChipSizeX = 0;
	mChipSizeY = 0;
	mChipXnum = 0;
	mChipYnum = 0;
	mImg = 0;

	mAnimState = PLAYER_ANIM_WAIT;
	mAnimCount = 0;
	mAnimNum = 0;
	mDir = PLAYER_DIR_DOWN;

}

PlayerTopview::~PlayerTopview()
{
	DeleteGraph(mImg);
}

bool PlayerTopview::init(char* imgFilename, char* debugFilename, unsigned int chipsizeX, unsigned int chipsizeY)
{
	mImg = LoadGraph(imgFilename);

	if (!imgFilename)
		return false;

	// �f�o�b�O�摜�ǂݍ���
	mDebugImg = LoadGraph(debugFilename);
	if (!mDebugImg)
		return false;

	mChipSizeX = chipsizeX;
	mChipSizeY = chipsizeY;

	//�f�t�H���g���̓f�o�b�N�摜����R���W���������o��
	int w, h;
	GetGraphSize(mDebugImg, &w, &h);
	setCollision(0, 0, w, h);

	return true;
}

void PlayerTopview::setCollision(unsigned int offset_left_x, unsigned int offset_top_y, unsigned int w, unsigned int h)
{
	mOffsetDrawX = offset_left_x;
	mOffsetDrawY = offset_top_y;

	mh = h;
	mw = w;
}

void PlayerTopview::animation()
{
	//////////////////////////////////////////
	// �A�j���[�V�����֘A
	//////////////////////////////////////////
	mAnimCount++;

	// ����
	if (mAnimState == PLAYER_ANIM_RUN)
	{
		mAnimCount++;
		if (mAnimCount > player_AnimSpeed)
		{
			if (mAnimNum < player_AnimWalknum)
			{
				mAnimNum++;
				mAnimCount = 0;

				if (mAnimNum == player_AnimWalknum)
				{
					mAnimNum = 0;
				}
			}
		}
	}

}


void PlayerTopview::setDrawOffset(int ofsX, int ofsY)
{
	mOffsetDrawX = ofsX;
	mOffsetDrawY = ofsY;
}

void PlayerTopview::move(Map *pMap, Camera *pCam)
{
	// �v���[���[�ō����x
	const float maxSpeed = 16.0;

	//���x
	float vx = mx - mPrevX;
	float vy = my - mPrevY;

	//�����x
	const float friction = 0.5f;
	float ax = 0.0f;
	float ay = 0.0f;

	// �L�����A�j������
	animation();

	bool inputLRflg = false;
	bool inputUDflg = false;

	////////////////////////////////////////////////
	// �L�[����
	////////////////////////////////////////////////
	// ���L�[����������
	if (INPUT_INSTANCE.getInput(KEY_INPUT_LEFT) == KEY_STATE_PRESSED)
	{
		ax += -player_accel;
		mAnimState = PLAYER_ANIM_RUN;
		mDir = PLAYER_DIR_LEFT;
		inputLRflg = true;
	}

	// �E�L�[��������
	if (INPUT_INSTANCE.getInput(KEY_INPUT_RIGHT) == KEY_STATE_PRESSED)
	{
		ax += player_accel;
		mAnimState = PLAYER_ANIM_RUN;
		mDir = PLAYER_DIR_RIGHT;
		inputLRflg = true;
	}
	// ��L�[�������Ƃ�
	if (INPUT_INSTANCE.getInput(KEY_INPUT_UP) == KEY_STATE_PRESSED)
	{
		ay -= player_accel;
		mAnimState = PLAYER_ANIM_RUN;
		mDir = PLAYER_DIR_UP;
		inputUDflg = true;
	}
	// ���L�[�������Ƃ�
	if (INPUT_INSTANCE.getInput(KEY_INPUT_DOWN) == KEY_STATE_PRESSED)
	{
		ay += player_accel;
		mAnimState = PLAYER_ANIM_RUN;
		mDir = PLAYER_DIR_DOWN;
		inputUDflg = true;
	}

	// �L�[���͂������Ƃ��̓E�F�C�g�A�j���Ɉڍs
	if (!inputUDflg && !inputLRflg)
	{
		mAnimState = PLAYER_ANIM_WAIT;
	}
	//�㉺�L�[�̓��͂��Ȃ��Ƃ�
	if (!inputUDflg)
	{
		vy *= friction;
	}
	//���E�L�[�̓��͂��Ȃ��Ƃ�
	if (!inputLRflg)
	{
		vx *= friction;
	}

	// ���x�ɉ����x�����Z
	vx += ax;
	vy += ay;

	// �ō����x�𒴂��Ȃ��悤�ɃN�����v�i-player_maxSpeed �` +player_maxSpeed�͈̔͂����悤�ɂ���j
	vx = clamp(player_maxSpeedX, -player_maxSpeedX, vx);
	vy = clamp(player_maxSpeedY, -player_maxSpeedY, vy);

	//�O�̍��W���L��
	mPrevX = mx;
	mPrevY = my;

	//�����蔻����W�v�Z 
	mx = mx + vx;
	my = my + vy;

	// ���x�����ɂ���Ă����蔻��������Ȃ�
	int ixL, ixR, iy, iy2; // �������������W�̃}�b�v�̃C���f�b�N�X�ԍ�

	ixL = pMap->getCollisionMapIndex_X((int)mx);           //��
	ixR = pMap->getCollisionMapIndex_X((int)(mx + mw));  //�E

	// ��Ɍ������Ă���Ƃ�(���さ�E��̂Q�_�Ŕ���)
	if (vy < 0.0f)
	{
		iy  = pMap->getCollisionMapIndex_Y((int)(my - 1));   // ��

		//�㕔2�_�͕ǂɓ������Ă��邩�H�����̉��͋󔒃u���b�N���H
		if ((pMap->getCollisionMapIdFromIndex(ixL, iy) != 0 && pMap->getCollisionMapIdFromIndex(ixL, iy + 1) == 0 )||
			(pMap->getCollisionMapIdFromIndex(ixR, iy) != 0 && pMap->getCollisionMapIdFromIndex(ixR, iy + 1) == 0 ))
		{
 
			//�������Ă����Ƃ��͂߂荞�܂Ȃ��ʒu�ɖ߂�
			my = (float)((iy + 1) * pMap->getMapChipSizeY()) + 1;
			mPrevY = my; //���x�[����
		}
	}

	// ���Ɍ������Ă���Ƃ�(�����A�E����2�_�Ŕ���)
	if (vy > 0.0f)
	{
		iy  = pMap->getCollisionMapIndex_Y((int)(my + mh + 1)); //��

		// �����E���͕ǂɓ������Ă��邩�H�����̉��͋󔒃u���b�N���H
		if ((pMap->getCollisionMapIdFromIndex(ixL, iy) != 0 && pMap->getCollisionMapIdFromIndex(ixL, iy - 1) == 0) ||
			(pMap->getCollisionMapIdFromIndex(ixR, iy) != 0 && pMap->getCollisionMapIdFromIndex(ixR, iy - 1) == 0))
		{
			my = (float)(iy * pMap->getMapChipSizeY() - mh) - 1;
			mPrevY = my; //���x�[����
		}
	}

	iy = pMap->getCollisionMapIndex_Y((int)(my));
	iy2 = pMap->getCollisionMapIndex_Y((int)(my + mh));

	// �E�Ɍ������Ă���Ƃ� 
	if (vx > 0.0f)
	{
		ixR = pMap->getCollisionMapIndex_X((int)(mx + mw + 1));  //�E

		if ((pMap->getCollisionMapIdFromIndex(ixR,  iy) != 0 && pMap->getCollisionMapIdFromIndex(ixR - 1, iy) == 0 )||
			(pMap->getCollisionMapIdFromIndex(ixR, iy2) != 0 && pMap->getCollisionMapIdFromIndex(ixR - 1, iy2) == 0))
		{
			mx = (float)(ixR * pMap->getMapChipSizeX() - mw) - 1;
			mPrevX = mx;
		}
	}

	// ���Ɍ������Ă���Ƃ�
	if (vx < 0.0f)
	{
		ixL  = pMap->getCollisionMapIndex_X((int)(mx - 1));       //��

		if ((pMap->getCollisionMapIdFromIndex(ixL,  iy) != 0 && pMap->getCollisionMapIdFromIndex(ixL + 1 , iy) == 0) ||
			(pMap->getCollisionMapIdFromIndex(ixL, iy2) != 0 && pMap->getCollisionMapIdFromIndex(ixL + 1, iy2) == 0))
		{
			mx = (float)((ixL + 1) * pMap->getMapChipSizeX()) + 1;
			mPrevX = mx;
		}
	}

	printf("[%d, %d] prev[%d, %d] anim %d [%d] vx %.2f ax %.2f\n", (int)mx, (int)my, (int)mPrevX, (int)mPrevY, mAnimState, mAnimNum, vx, ax);
}

void PlayerTopview::draw(Camera *pCam)
{
	//�J�����̃I�t�Z�b�g�擾
	int camx, camy;

	camx = pCam->GetCameraX();
	camy = pCam->GetCameraY();

	//��Ԃɉ����ĕ`��`�@TODO
	DrawRectGraph((int)mx - camx + mOffsetDrawX,
		(int)my - camy + mOffsetDrawY,
		mAnimNum * mChipSizeX,
		mDir     * mChipSizeY,
		mChipSizeX, mChipSizeY, mImg, TRUE, FALSE);

	// �f�o�b�O�i�����蔻��摜�j�`��@�����[�X���ɏ����B
	DrawRectGraph((int)mx - camx, (int)my - camy, 0, 0, mChipSizeX, mChipSizeY, mDebugImg, TRUE, FALSE);
}



