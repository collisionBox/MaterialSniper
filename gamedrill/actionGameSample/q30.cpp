#include "q30.h"

Quest30Seq::Quest30Seq()
{
	// �v���[���[�A�J�����A�}�b�v�쐻
	pPlayer = new Player;
	pCam = new Camera;
	pMap = new Map;

	//�v���[���[������
	pPlayer->init("image/chara3.png", "image/player.png", 64, 64);
	pPlayer->setGameStartPos(500, 100);
	pPlayer->setCollision(10, 0, 40, 56);

	//�J�����X�N���[���͈͍��W�쐬
	const int scrHalfWidth = 64;
	const int scrHalfHeight = 64;

	int scrhalfX = GAMEINSTANCE.getScreenWidth() / 2;
	int scrhalfY = GAMEINSTANCE.getScreenHeight() / 2;

	//�J����������
	pCam->Init(0, 0,                             // �J�����̊J�n�ʒu
		scrhalfX - scrHalfWidth, scrhalfY - scrHalfHeight, // �J�����̍��㋖�e���W
		scrHalfWidth * 2, scrHalfHeight * 2);              // ���㋖�e���W�𒆐S�ɁA���e���A�����Z�b�g
														   //�}�b�v������
	pMap->readMapdata("image/dungeon.csv", "image/dungeonSheet.png");

	int perticleImg = LoadGraph("image/perticle.png");
	mPerticleMax = 512;
	mPerticleArray = new Particle[mPerticleMax];
	mPerticleArray->setGraph(perticleImg);

}

Quest30Seq::~Quest30Seq()
{
	delete pCam;
	delete pMap;
	delete pPlayer;

	delete[] mPerticleArray;
}

Sequence * Quest30Seq::move()
{
	static bool allowParticleHit = false;
	// [H] key�������ꂽ��p�[�e�B�N���ƃ}�b�v�Ƃ̂����蔻������邩�؂�ւ���
	if (INPUT_INSTANCE.getInput(KEY_INPUT_H) == KEY_STATE_PUSHDOWN)
	{
		allowParticleHit = !allowParticleHit;
	}

	// �X�y�[�X�L�[�������ꂽ�玟�̃N�G�X�g�̃V�[�P���X���쐬���ăV�[�P���X�`�F���W
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest01Seq;
	}

	//�v���[���[����
	pPlayer->move(pMap, pCam);

	//�v���[���[�𒍎��_�Ƃ��ăJ�����쐬
	pCam->move(pMap, pPlayer->getPlayerPosX(), pPlayer->getPlayerPosY());

	if (INPUT_INSTANCE.getInput(KEY_INPUT_B) == KEY_STATE_PUSHDOWN)
	{
		Particle::toggleMortionBlur();
	}

	// �p�[�e�B�N���̒ǉ�
	// �p�[�e�B�N���z����̋󂫂������Ė��t���[��5�ǉ�
	int cnt = 0;
	int createParticleNumInFrame = 10;
	for (int i = 0; i < mPerticleMax; i++)
	{
		if (!mPerticleArray[i].isAlive())
		{
			mPerticleArray[i].setStartPos(360.0f, 200.0f, getRandom(-15.0f, +15.0f), getRandom(-30.0f, -5.0f));
			mPerticleArray[i].setLifeTime((int)getRandom(20, 40));
			cnt++;
			if (cnt > createParticleNumInFrame)
				break;
		}
	}

	// ���ݐ����Ă���S�Ẵp�[�e�B�N���̈ړ�����
	for (int i = 0; i < mPerticleMax; i++)
	{
		if (mPerticleArray[i].isAlive())
		{
			if (allowParticleHit)
			{
				mPerticleArray[i].move(pMap);
			}
			else
			{
				mPerticleArray[i].move(NULL);
			}
		}
	}
	return this;
}

void Quest30Seq::draw()
{
	char buf[128];
	ClearDrawScreen();

	//�}�b�v�`��
	pMap->mapDraw(pCam);
	pMap->gridDraw(pCam);

	//�v���[���[�`��
	pPlayer->draw(pCam);

	//�p�[�e�B�N���`��
	for (int i = 0; i < mPerticleMax; i++)
	{
		if (mPerticleArray[i].isAlive())
		{
			mPerticleArray[i].draw(pCam);
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	SetDrawBright(255, 255, 255);

	sprintf(buf, "PARTICLES NUM [%3d]", Particle::getNumSubstance());
	GAMEINSTANCE.systemText.textDraw(10, 42, buf);
	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #30.");
	GAMEINSTANCE.systemText.textDraw(10, GAMEINSTANCE.getScreenHeight() - 90, "ALLOW KEY - MOVE / [Z] KEY - JUMP \n[H]KEY - PARTICLE HIT ON / OFF\n[B]KEY - BLUR ON / OFF");
	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Question.");
}
