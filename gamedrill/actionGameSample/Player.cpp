#include "player.h"

const float player_accel              = 0.2f  ;
const float player_accel_inAir        = 0.08f ;
const float player_maxSpeedX          = 9.0f  ;
const float player_maxSpeedY          = 32.0f ;

const float player_jumpVel            = -13.0f;
const float pleyer_brakeRatio         = 2.0f  ;  //1�t���[��������̃u���[�L�W���@ 
const float player_gravity            = 0.3f  ;
const int   player_offsetX            = -12   ;
const int   player_offsetY            = -4    ;
const int   player_AnimWaitnum        = 4     ;
const int   player_AnimWalknum        = 4     ;
const int   player_AnimAttackPowernum = 2     ;
const int   player_AnimAttackShootnum = 4     ;
const int   player_AnimSpeed          = 10    ; // 10�t���[���ɂP��A�j���[�V�����i�߂�

								   // �E�F�C�g�@�@            RUN                  ATTACK_POWER       ATTACK_SHOOT          JUMP/UP JUMP/DOWN 
int animationImageX[][4] = { { 0, 64, 128, 192, },{ 0,  64, 128,192, },{ 0,  64,  0, 0, },{ 128, 192,   0, 64 },{ 128, 192, 0, 0, } };
int animationImageY[][4] = { { 0,  0,   0,   0, },{ 64,  64,  64, 64, },{ 128, 128,  0, 0, },{ 128, 128, 192,192 },{ 192, 192, 0, 0, } };

Player::Player()
{
	mState     = PLAYER_WAIT     ;
	mx         = 0               ;
	my         = 0               ;
	mPrevX    = 0               ;
	mPrevY    = 0               ;

	mChipSizeX = 0               ;
	mChipSizeY = 0               ;
	mChipXnum  = 0               ;
	mChipYnum  = 0               ;
	mImg = 0;

	mAnimState = PLAYER_ANIM_WAIT;
	mAnimCount = 0               ;
	mAnimNum   = 0               ;
	mDir       = PLAYER_DIR_LEFT ;

}

Player::~Player()
{
	DeleteGraph( mImg );
}

bool Player::init(char* imgFilename, char* debugFilename, unsigned int chipsizeX, unsigned int chipsizeY)
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

void Player::setCollision(unsigned int offset_left_x, unsigned int offset_top_y, unsigned int w, unsigned int h)
{
	mOffsetDrawX = offset_left_x;
	mOffsetDrawY = offset_top_y;

	mh = h;
	mw = w;
}

void Player::animation()
{
	//////////////////////////////////////////
	// �A�j���[�V�����֘A
	//////////////////////////////////////////
	mAnimCount++;

	// �E�F�C�g
	if (mAnimState == PLAYER_ANIM_WAIT)
	{
		if (mAnimCount > player_AnimSpeed)
		{
			mAnimNum++;
			mAnimCount = 0;

			if (mAnimNum == player_AnimWaitnum)
			{
				mAnimNum = 0;
			}
		}
	}
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
	// �W�����v
	if (mState == PLAYER_JUMP)
	{
		mAnimState = PLAYER_ANIM_JUMP;
		if (mx - mPrevY < 0)
		{
			mAnimNum = 0;  // �㏸��
		}
		else {
			mAnimNum = 1;  // ���~��
		}
	}

	// ��̃p���[���߂�
	if (mState == PLAYER_ATTACK_POWER)
	{
		if (mAnimCount > player_AnimSpeed)
		{
			if (mAnimNum < player_AnimAttackPowernum)
			{
				mAnimNum++;
				mAnimCount = 0;

				if (mAnimNum == player_AnimAttackPowernum)
				{
					mAnimNum = 0;
				}
			}
		}
	}

	// ����͂Ȃ�
	if (mState == PLAYER_ATTACK_SHOOT)
	{
		if (mAnimCount > player_AnimSpeed)
		{
			if (mAnimNum < player_AnimAttackShootnum)
			{
				mAnimNum++;
				mAnimCount = 0;

				if (mAnimNum == player_AnimAttackShootnum)
				{
					mAnimNum = 0;
					mState = PLAYER_WAIT;
					mAnimState = PLAYER_ANIM_WAIT;
				}
			}
		}
	}

}


void Player::move(Map *pMap, Camera *pCam)
{
	// �v���[���[�ō����x
	const float maxSpeed = 16.0;

	//���x
	float vx = mx - mPrevX;
	float vy = my - mPrevY;

	//�����x
	const float friction = 0.5f;
	float ax = 0; 
	float ay = player_gravity;

	// �L�����A�j������
	animation();

	bool inputflg = false;


	////////////////////////////////////////////////
	// �L�[����
	////////////////////////////////////////////////
	// ���L�[����������
	if (INPUT_INSTANCE.getInput(KEY_INPUT_LEFT) == KEY_STATE_PRESSED && mState != PLAYER_ATTACK_POWER)
	{
		//�n�ʂ̏ォ�H
		if (mState == PLAYER_ONGROUND)
		{
			ax += -player_accel;
			mAnimState = PLAYER_ANIM_RUN;
		}
		else {
			ax += -player_accel_inAir;
		}

		mDir       = PLAYER_DIR_LEFT ;
		inputflg    = true            ;
	}

	// �E�L�[��������
	if (INPUT_INSTANCE.getInput(KEY_INPUT_RIGHT) == KEY_STATE_PRESSED && mState != PLAYER_ATTACK_POWER)
	{
		if (mState == PLAYER_ONGROUND)
		{
			ax += player_accel;
			mAnimState = PLAYER_ANIM_RUN;
		}
		else {
			ax += player_accel_inAir;
		}
		mDir       = PLAYER_DIR_RIGHT ;
		inputflg    = true             ;
		
	}

	// �W�����v
	if (INPUT_INSTANCE.getInput(KEY_INPUT_Z) == KEY_STATE_PUSHDOWN)
	{
		if (mState & PLAYER_ONGROUND)
		{
			mState = PLAYER_JUMP;
			mAnimState = PLAYER_ANIM_JUMP;
			vy = player_jumpVel;
		}
	}

	if (!inputflg)
	{
		//�n�ʂɂ���Ƃ��̖��C
		if (mState == PLAYER_ONGROUND)
		{
			//�����Ă��Ȃ��Ƃ��A�Î~���C������
			if (mState != PLAYER_RUN)
			{
				ax = -friction * vx;
			}
		}
		else
		{
			ax = -friction / 2.0f * vx;
		}
	}

	// �󒆂łȂ����L�[���͂������Ƃ��̓E�F�C�g�A�j���Ɉڍs
	if (mState & PLAYER_ONGROUND && !inputflg )
	{
		mAnimState = PLAYER_ANIM_WAIT;
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

	// ��Ɍ������Ă���Ƃ��i����E��A����2�������}�b�v�ɓ������ĂȂ����m�F)
	if (vy < 0)
	{
		//����̃`�b�v�ԍ��Z�o
		int ix1 = pMap->getCollisionMapIndex_X((int)(mx + 4));
		int ix2 = pMap->getCollisionMapIndex_X((int)(mx + mw - 4));
		int iy = pMap->getCollisionMapIndex_Y((int)(my - 1));

		//�V��ɏՓ˂��Ă����ꍇ
		if (( pMap->getCollisionMapIdFromIndex(ix1, iy) != 0) ||
			  pMap->getCollisionMapIdFromIndex(ix2, iy) != 0 )
		{
			// ����u���b�N���W�����Ƃɂ߂荞�܂Ȃ��悤�ʒu�C��
			my = (float)(iy + 1) * pMap->getMapChipSizeY();
		}
	}

	// ���Ɍ������Ă���Ƃ��i�����@�E������2�������}�b�v�ɓ������Ă��Ȃ����m�F�j
	if (vy > 0)
	{
		//�����̃`�b�v�ԍ��̍��[�ƉE�[2�����Z�o
		int ix1 = pMap->getCollisionMapIndex_X((int)(mx + 4));
		int ix2 = pMap->getCollisionMapIndex_X((int)(mx + mw - 4));
		int iy = pMap->getCollisionMapIndex_Y((int)(my + mh + 1));
		//�n�ʂɏՓ˂��Ă��邩
		if (pMap->getCollisionMapIdFromIndex(ix1, iy) != 0 ||
			pMap->getCollisionMapIdFromIndex(ix2, iy) != 0 )
		{
			//���A�����̐^���Ƀu���b�N�����݂��Ă��Ȃ���
			if (pMap->getCollisionMapIdFromIndex(ix1, iy - 1) == 0 &&
				pMap->getCollisionMapIdFromIndex(ix2, iy - 1) == 0)
			{
				//�Փ˂��Ă������͉��n�ʂ���Ƀv���[���[�𗧂�����ʒu�ɏC��
				my = (float)iy * pMap->getMapChipSizeY() - mh;

				// ���x���[���ɂ��邽�߂ɉߋ�y���W�������ʒu��
				mPrevY = my;

				//�v���[����ڒn��ԂɈڍs
				mState = PLAYER_ONGROUND;
			}
		}
	}

	// �E�Ɍ������Ă���Ƃ� (�v���[���[�E�[�㉺�����̑�\�_�ƃ}�b�v������m�F)
	if (vx > 0)
	{
		int ix = pMap->getCollisionMapIndex_X((int)(mx + mw - 1));
		int iy = pMap->getCollisionMapIndex_Y((int)(my + mh / 2));
		if ( pMap->getCollisionMapIdFromIndex(ix, iy) != 0)
		{
			mx = (float)(ix * pMap->getMapChipSizeX() - mw);
		}
	}

	// ���Ɍ������Ă���Ƃ��i�v���[�����[�A�㉺�����̑�\�_�ƃ}�b�v������m�F�j
	if (vx < 0 )
	{
		int ix = pMap->getCollisionMapIndex_X((int)(mx + 1));
		int iy = pMap->getCollisionMapIndex_Y((int)(my + mh / 2));
		if ( pMap->getCollisionMapIdFromIndex(ix, iy) != 0)
		{
			mx = (float)((ix + 1) * pMap->getMapChipSizeX());
		}
	}

	// ���͋󒆂ɂ��Ȃ����H
	if (mState == PLAYER_ONGROUND)
	{
		//�����̃`�b�v�ԍ��̍��[�ƉE�[2�����Z�o
		int ix1 = pMap->getCollisionMapIndex_X((int)(mx + 1));
		int ix2 = pMap->getCollisionMapIndex_X((int)(mx + mw - 1));
		int iy = pMap->getCollisionMapIndex_Y((int)(my + mh + 1));

		// 2�_�Ƃ��󒆂��H
		if (pMap->getCollisionMapIdFromIndex(ix1, iy) == 0 &&
			pMap->getCollisionMapIdFromIndex(ix2, iy) == 0)
		{
			//�v���[�����󒆏�ԂɈڍs
			mState = PLAYER_JUMP;
		}
	}
	printf("[%d, %d] prev[%d, %d] anim %d [%d] vx %.2f ax %.2f\n", (int)mx, (int)my, (int)mPrevX, (int)mPrevY, mAnimState, mAnimNum, vx, ax);
}

void Player::draw( Camera *pCam )
{
	//�J�����̃I�t�Z�b�g�擾
	int camx, camy;

	camx = pCam->GetCameraX();
	camy = pCam->GetCameraY();

	//��Ԃɉ����ĕ`��`�@TODO
	DrawRectGraph((int)mx - camx - mOffsetDrawX,
		          (int)my - camy - mOffsetDrawY,
		          animationImageX[mAnimState][mAnimNum],
		          animationImageY[mAnimState][mAnimNum],
		          64, 64, mImg, TRUE, mDir);

	// �f�o�b�O�i�����蔻��摜�j�`��@�����[�X���ɏ����B
	DrawRectGraph((int)mx - camx, (int)my - camy, 0, 0, mChipSizeX, mChipSizeY, mDebugImg, TRUE, FALSE);
}



