#include "SoftBodyTest.h"

SoftBodyTestSeq::SoftBodyTestSeq()
{
	mMaxParticleNum = 100;
	mMode = 0;

	// �v���[���[�A�J�����A�}�b�v�쐻
	pCam = new Camera;
	pMap = new Map;
	pParticle = new LinkedParticle[mMaxParticleNum];


	//�J�����X�N���[���͈͍��W�쐬
	const int scrHalfWidth  = 64;
	const int scrHalfHeight = 64;

	int scrhalfX = GAMEINSTANCE.getScreenWidth() / 2;
	int scrhalfY = GAMEINSTANCE.getScreenHeight() / 2;

	//�J����������
	pCam->Init(0, 0,                             // �J�����̊J�n�ʒu
		scrhalfX - scrHalfWidth, scrhalfY - scrHalfHeight, // �J�����̍��㋖�e���W
		scrHalfWidth * 2, scrHalfHeight * 2);              // ���㋖�e���W�𒆐S�ɁA���e���A�����Z�b�g
														   //�}�b�v������
	pMap->readMapdata("image/dungeon.csv", "image/dungeonSheet.png");

	//���_��`
	resetMassPoint();

	LinkedParticle::setGravity(1.0f);
	LinkedParticle::setMaxSpeed(16.0f);
}

SoftBodyTestSeq::~SoftBodyTestSeq()
{
	delete pCam;
	delete pMap;

}

Sequence * SoftBodyTestSeq::move()
{
	static bool allowParticleHit = false;
	// [H] key�������ꂽ��R���X�g���C���g�i�S���j�؂�
	if (INPUT_INSTANCE.getInput(KEY_INPUT_H) == KEY_STATE_PUSHDOWN)
	{
		for (int i = 0;i < mMaxParticleNum; i++)
		{
			if (pParticle[i].isConstraint())
			{
				pParticle[i].CutConstraint();
			}
		}
	}

	// S�L�[�ŏ����ʒu�߂�
	if (INPUT_INSTANCE.getInput(KEY_INPUT_S) == KEY_STATE_PUSHDOWN)
	{
		resetMassPoint();
		mMode++;

		if (mMode == 3)
		{
			mMode = 0;
		}
	}

	// �X�y�[�X�L�[�������ꂽ�玟�̃N�G�X�g�̃V�[�P���X���쐬���ăV�[�P���X�`�F���W
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest01Seq;
	}


	//�v���[���[�𒍎��_�Ƃ��ăJ�����쐬
	pCam->move(pMap, (int)(pParticle[6].getPosX()), (int)(pParticle[6].getPosY()));

	for (int k = 0; k < 5; k++)
	{
		for (int i = 0; i < mMaxParticleNum; i++)
		{
			pParticle[i].linkCalc(pMap);
		}
	}

	for (int i = 0; i < mMaxParticleNum; i++)
	{
		pParticle[i].move(pMap);
	}

	return this;
}

void SoftBodyTestSeq::draw()
{
	char buf[128];
	ClearDrawScreen();

	//�}�b�v�`��
	pMap->mapDraw(pCam);
	pMap->gridDraw(pCam);

	//�p�[�e�B�N���`��
	for (int i = 0; i < mMaxParticleNum; i++)
	{
		pParticle[i].debugDraw(pCam);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	SetDrawBright(255, 255, 255);

	GAMEINSTANCE.systemText.textDraw(10, 42, buf);
	GAMEINSTANCE.systemText.textDraw(10, 10, "SoftBodyTest.");
}

void SoftBodyTestSeq::resetMassPoint()
{

	for (int i = 0; i < mMaxParticleNum; i++)
	{
		pParticle[i].reset();
	}

	// ���[�h�O
	if (mMode == 0)
	{
		//���[�v
		for (int i = 0; i < 6; i++)
		{
			int startpos = 640;
			int distance = 60;
			pParticle[i].setMassPoint((float)(startpos - i * distance), 100, 2.0f + i * 0.5f);
		}

		//�{�b�N�X
		pParticle[6].setMassPoint(760, 100, 1.0f);
		pParticle[7].setMassPoint(860, 100, 1.0f);
		pParticle[8].setMassPoint(860, 120, 1.0f);
		pParticle[9].setMassPoint(760, 120, 3.0f);

		pParticle[0].setConstraint();
		pParticle[6].setConstraint();

		//���[�v
		pParticle[0].link(&pParticle[1], 1.0f);
		pParticle[1].link(&pParticle[2], 1.0f);
		pParticle[2].link(&pParticle[3], 1.0f);
		pParticle[3].link(&pParticle[4], 1.0f);
		pParticle[4].link(&pParticle[5], 1.0f);

		// �{�b�N�X
		pParticle[6].link(&pParticle[7]);
		pParticle[7].link(&pParticle[8]);
		pParticle[8].link(&pParticle[9]);
		pParticle[9].link(&pParticle[6]);

		pParticle[6].link(&pParticle[8]);
		pParticle[9].link(&pParticle[7]);
	}

	//���[�h�P
	if (mMode == 1)
	{
		for (int i = 0; i < mMaxParticleNum / 3; i++)
		{
			float tx, ty, len;
			tx = getRandom(100.0f, 1000.0f);
			ty = getRandom(120.0f, 300.0f);
			len = getRandom(10.0f, 80.0f);

			pParticle[i * 3 + 0].setMassPoint(tx - len / 2, ty);
			pParticle[i * 3 + 1].setMassPoint(tx + len / 2, ty);
			pParticle[i * 3 + 2].setMassPoint(tx, ty + len / 2);

			pParticle[i * 3 + 0].link(&pParticle[i * 3 + 1]);
			pParticle[i * 3 + 1].link(&pParticle[i * 3 + 2]);
			pParticle[i * 3 + 2].link(&pParticle[i * 3 + 0]);

			pParticle[i * 3 + 0].setConstraint();
		}
	}
	
	// ���[�h�Q
	if (mMode == 2)
	{
		float radius = 100.0f;
		float posx, posy;
		posx = 700;
		posy = 1000;
		float theta = 0.0f;
		int sepNum = 16;

		float thetaplus = 3.14159f * 2.0f / sepNum;

		pParticle[0].setMassPoint(posx, posy);
		for (int i = 1; i <= sepNum; i++)
		{
			pParticle[i].setMassPoint(posx + cosf(theta) * radius, posy + sinf(theta) * radius);
			pParticle[i].link(&pParticle[i - 1], 1.0f);
			theta += thetaplus;
		}
		pParticle[1].link(&pParticle[sepNum]);

		for (int i = 2; i <= sepNum; i++)
		{
			pParticle[i].link(&pParticle[0], 0.2f);
		}
	}
}
