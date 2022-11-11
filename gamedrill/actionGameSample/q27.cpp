#include "q27.h"

Quest27Seq::Quest27Seq()
{
	// �v���[���[�A�J�����A�}�b�v�쐻
	pPlayer = new Player;
	pCam    = new Camera;
	pMap    = new Map;

	//�v���[���[������
	pPlayer->init("image/chara3.png", "image/player.png", 64, 64);
	pPlayer->setGameStartPos(500, 100);
	pPlayer->setCollision( 10, 0, 40, 56);

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

	//�}�b�v�̃f�o�b�O�\��
	showDebugMap = false;

}

Quest27Seq::~Quest27Seq()
{
	delete pCam;
	delete pMap;
	delete pPlayer;

}

Sequence * Quest27Seq::move()
{
	static bool allowParticleHit = false;
	// [H] key�������ꂽ��p�[�e�B�N���ƃ}�b�v�Ƃ̂����蔻������邩�؂�ւ���
	if (INPUT_INSTANCE.getInput(KEY_INPUT_H) == KEY_STATE_PUSHDOWN)
	{
		allowParticleHit = !allowParticleHit;
	}
	// [M] key�������ꂽ��f�o�b�O�}�b�v�`�悷�邩�̐؂�ւ�
	if (INPUT_INSTANCE.getInput(KEY_INPUT_M) == KEY_STATE_PUSHDOWN)
	{
		showDebugMap = !showDebugMap;
	}

	// �X�y�[�X�L�[�������ꂽ�玟�̃N�G�X�g�̃V�[�P���X���쐬���ăV�[�P���X�`�F���W
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest28Seq;
	}

	//�v���[���[����
	pPlayer->move(pMap, pCam);

	//�v���[���[�𒍎��_�Ƃ��ăJ�����쐬
	pCam->move(pMap, pPlayer->getPlayerPosX(), pPlayer->getPlayerPosY());

	if (INPUT_INSTANCE.getInput(KEY_INPUT_B) == KEY_STATE_PUSHDOWN)
	{
		Particle::toggleMortionBlur();
	}

	return this;
}

void Quest27Seq::draw()
{
	ClearDrawScreen();
	
	// �}�b�v�`��
	pMap->mapDraw(pCam);

	// �}�b�v�f�o�b�O�`��
	if (showDebugMap)
	{
		pMap->gridDraw(pCam);
	}

	// �v���[���[�`��
	pPlayer->draw(pCam);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	SetDrawBright(255, 255, 255);

	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #28.");
	GAMEINSTANCE.systemText.textDraw(10, GAMEINSTANCE.getScreenHeight() - 90, "HOW TO PLAY\nALLOW KEY - MOVE / [Z] KEY - JUMP\n[M] - Map Debug Show");
	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Question.");
}
