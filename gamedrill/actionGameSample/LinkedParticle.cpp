#include "LinkedParticle.h"

float LinkedParticle::mGravity       = 0.0f   ;
float LinkedParticle::mMaxSpeed      = 5.0f   ;
float LinkedParticle::mFrictionRatio = 0.95f  ;
float LinkedParticle::mEpsiron       = 0.0001f;

unsigned int ColPallete[] = 
{ 
                   0xff0000ff, // CONSTRAINT
                   0xff00aa00, // SLEEP
                   0xffffff00, // ACTIVE
                   0xffffaa00, // ONGROUND
				   0xffff0000, // HIT
				   0xff000000, // RESERVED
};

LinkedParticle::LinkedParticle()
{
	mx           = 0.0f ; // �p�[�e�B�N���ʒu
	my           = 0.0f ; // 
	mPrevX      = 0.0f ; // �p�[�e�B�N���O��ʒu 
	mPrevY      = 0.0f ; // 
	mFx          = 0.0f ; // �p�[�e�B�N���ɂ������
	mFy          = 0.0f ; // 
	mWeight      = 1.0f ; // �p�[�e�B�N���d��
	mbConstraint = false; // �S���p�[�e�B�N�����H
	mbHitWall    = false; // �ǂɌ��ݓ������Ă��邩�H
	mbActive     = false; // �v�Z�Ώۂ��H
}

LinkedParticle::~LinkedParticle()
{
	//�p�[�e�B�N���A���z��폜
	if (!mParticleArray.empty())
	{
		mParticleArray.clear();
	}
}

// ���_�̒�`
void LinkedParticle::setMassPoint(float posx, float posy, float weight)
{
	mx = mPrevX = posx                 ;
	my = mPrevY = posy                 ;
	mFx = mFy    = 0.0f                 ;
	mbConstraint  = false                ;
	mbHitWall     = false                ;
	mbActive      = true                 ;
	mWeight       = weight               ;
	mState        = LP_STATE_ENUM_ACTIVE ;
}

void LinkedParticle::setConstraint()
{
	mbConstraint = true                     ;
	mState       = LP_STATE_ENUM_CONSTRAINT ;
}

void LinkedParticle::CutConstraint()
{
	 mbConstraint = false                   ; 
	 mState       = LP_STATE_ENUM_ACTIVE    ;
}

void LinkedParticle::linkCalc(Map* pMap)
{
	// �A�N�e�B�u���H
	if (!mbActive)
	{
		return;
	}

	//�������Ă���͂��N���A
	mFx = 0.0f;
	mFy = 0.0f;

	//�R���X�g���C���g�i�S���j����Ă���Ƃ��͌v�Z�X�L�b�v
	if (mbConstraint)
	{
		return;
	}

	// �����ɂ����邷�ׂĂ̗͂̌v�Z

	float px, py;    // ����p�[�e�B�N���̍��W

	float nowLen;    //���݂̒���

	//���̃p�[�e�B�N�����󂯂�͂̑��a���v�Z
	for (unsigned int i = 0; i < mParticleArray.size(); i++)
	{
		//�p�[�e�B�N���Ԃ̒����Z�o
		px = mParticleArray[i].m_particle->mx;
		py = mParticleArray[i].m_particle->my;

		nowLen = (px - mx) * (px - mx) +
			(py - my) * (py - my);
		nowLen = sqrt(nowLen);

		//�p�[�e�B�N���Ԃ̒��͂��v�Z
		// �΂˒萔 * (���݂̒���) / (�ʏ풷��)
		float tention = mParticleArray[i].m_springConstant * (nowLen - mParticleArray[i].m_springLen) / mParticleArray[i].m_springLen;
		tention *= mParticleArray[i].m_particle->mWeight * 0.5f;

		// ���e�l�ȉ��͗͂̌v�Z�؂�̂�
		if (tention > -mEpsiron && tention < mEpsiron)
		{
			mFx += 0.0f;
			mFy += 0.0f;
		}
		else
		{
			//���e�ʈȏ�Ȃ̂ŗ͂𑫂�
			mFx += (px - mx) * tention / 2.0f;
			mFy += (py - my) * tention / 2.0f;
		}
	}
	mx += mFx;
	my += mFy;

	// �����_�ŕǂɂԂ����Ă��邩�H�Ԃ����Ă�����C��
	if (pMap)
	{
		mapHit(pMap);

		//�Ԃ����Ă����瑬�x�[����
		if (mbHitWall)
		{
			mPrevX = mx;
			mPrevY = my;
		}
	}


}

// �ړ�����
void LinkedParticle::move(Map* pMap)
{
	// �A�N�e�B�u���H
	if (!mbActive)
	{
		return;
	}

	//�R���X�g���C���g�i�S���j����Ă���Ƃ��͌v�Z�X�L�b�v
	if (mbConstraint)
		return;

	//���̃p�[�e�B�N���̑��x���Z�o
	float vx, vy;
	vx = mx - mPrevX;
	vy = my - mPrevY;

	vx += 0.0f ;
	vy += mGravity; 

	mPrevX = mx;
	mPrevY = my;

	//�ō����x�ŃN�����v�������x�ňʒu�X�V
	mx += clamp(mMaxSpeed, -mMaxSpeed, vx * mFrictionRatio);
	my += clamp(mMaxSpeed, -mMaxSpeed, vy * mFrictionRatio);

	//�}�b�v�Ƃ̂����蔻��
	if ( mbHitWall && pMap )
	{
		mapHit(pMap);
	}
}

//�f�o�b�O�`��
void LinkedParticle::debugDraw(Camera * pCam)
{
	// �A�N�e�B�u���H
	if (!mbActive)
	{
		return;
	}

	//�X�N���[�����W�𓾂�
	int x, y;
	pCam->worldPos2ScreenPos((int)mx, (int)my, &x, &y);

	//���_�`��
	DrawCircle(x, y, 5, ColPallete[mState]);


	//��������ڑ�����Ă���p�[�e�B�N���ւ̐ڑ���`��
	for (unsigned int i = 0; i < mParticleArray.size(); i++)
	{
		int px, py;

		pCam->worldPos2ScreenPos((int)mParticleArray[i].m_particle->mx,
			                     (int)mParticleArray[i].m_particle->my,
			                     &px, &py);

		DrawLine(x, y, px, py, 0xffffffff);
	}

}

//�p�[�e�B�N���̘A��
void LinkedParticle::link(LinkedParticle *p, float springStrengthRatio)
{
	if (springStrengthRatio > 1.0f)
	{
		springStrengthRatio = 1.0f;
	}
	if (springStrengthRatio < 0.0f)
	{
		springStrengthRatio = 0.001f;
	}

	//�p�[�e�B�N���Ԃ̋������v�Z
	float len;

	len = (p->mx - mx) * (p->mx - mx) +
		  (p->my - my) * (p->my - my);
	len = sqrtf(len);

	//�����N�����
	LinkedParticleConnectionInfo linkinfo;
	linkinfo.m_springLen      = len                 ; // ���Ƃ��Ƃ̒���
	linkinfo.m_particle       = p                   ; // �����N��
	linkinfo.m_springConstant = springStrengthRatio ; // �����N��Ƃ̂΂ˌW��

	//�����N���o�^
	mParticleArray.push_back(linkinfo);

	//����ɂ������̃����N���o�^
	linkinfo.m_particle = this;
	p->mParticleArray.push_back(linkinfo);
}

void LinkedParticle::mapHit(Map * pMap)
{
	//�}�b�v�C���f�b�N�X�Z�o
	int ix, iy;
	ix = pMap->getCollisionMapIndex_X((int)mx);
	iy = pMap->getCollisionMapIndex_Y((int)my);

	// ���̃}�b�v�ʒu�͕ǂłȂ��Ȃ甲����
	if (pMap->getCollisionMapIdFromIndex(ix, iy) == 0)
	{
		mbHitWall = false;
		mState    = LP_STATE_ENUM_ACTIVE;
		return;
	}

	// �ǂɂ߂荞��ł��邱�Ƃ��m��
	// �ŒZ�����ŕǂ���̒E�o���v�Z
	mbHitWall = true;
	mState = LP_STATE_ENUM_HIT;

	//������u���b�N�̋�`�͈͍��W�Z�o
	int b_min_x, b_min_y;
	int b_max_x, b_max_y;

	b_min_x =       ix * pMap->getMapChipSizeX();
	b_min_y =       iy * pMap->getMapChipSizeY();
	b_max_x = (ix + 1) * pMap->getMapChipSizeX();
	b_max_y = (iy + 1) * pMap->getMapChipSizeY();

	// �߂荞�݋��e�͈͓����H
	int fixedX, fixedY;
	const int intrudeAcceseptable = 20;

	fixedX = (int)mx;
	fixedY = (int)my;

	// �c�����߂荞�݋��e�͈͓��Ȃ�߂�
	if (my - b_min_y < intrudeAcceseptable && my - b_min_y > 0)
	{
		fixedY = b_min_y - 1;
		mState = LP_STATE_ENUM_ON_GROUND;
	}

	if (b_max_y - my < intrudeAcceseptable && b_max_y - my > 0)
	{
		fixedY = b_max_y + 1;
	}

	// �㉺������OK�Ȃ��ɔ�����
	iy = pMap->getCollisionMapIndex_Y(fixedY);
	if (pMap->getCollisionMapIdFromIndex(ix, iy) == 0)
	{
		my = (float)fixedY;

		return ;
	}

	// �������߂荞�݋��e�͈͓��Ȃ�߂�
	if (mx - b_min_x < intrudeAcceseptable && mx - b_min_x > 0)
	{
		fixedX = b_min_x ;
	}

	if (b_max_x - mx < intrudeAcceseptable && b_max_x - mx > 0)
	{
		fixedX = b_max_x + 1;
	}

	mx = (float)fixedX;
	my = (float)fixedY;


}

void LinkedParticle::addForce(float addFx, float addFy)
{
	mFx += addFx;
	mFy += addFy;
}

void LinkedParticle::reset()
{
	mbConstraint = false;
	mbHitWall    = false;
	mFx = 0.0f;
	mFy = 0.0f;
	mPrevX = 0.0f;
	mPrevY = 0.0f;
	mx = 0.0f;
	my = 0.0f;

	if (mParticleArray.size() > 0)
	{
		mParticleArray.clear();
	}
}

// �ō����x�Z�b�g
void LinkedParticle::setMaxSpeed(float speed)
{
	mMaxSpeed = speed;
}

// �d�͂̃Z�b�g
void LinkedParticle::setGravity(float gravity)
{
	mGravity = gravity;
}

// �����l�؂�̂Ă������l
void LinkedParticle::setEpsiron(float epsiron)
{
	mEpsiron = epsiron;
}


