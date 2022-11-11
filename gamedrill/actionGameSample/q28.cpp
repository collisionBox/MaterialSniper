#include "q28.h"

Quest28Seq::Quest28Seq()
{
	// �v���[���[�A�J�����A�}�b�v�쐻
	pCam = new Camera;
	pMap = new Map;
	pPlayer = new PlayerTopview;

	//�v���[���[������
	pPlayer->init("image/greenboy.png", "image/debugtopview.png", 48, 48);
	pPlayer->setGameStartPos(100, 100);
	pPlayer->setDrawOffset(-3, -22);

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
	pMap->readMapdata("image/topviewmap.csv", "image/topview.png");

	//�}�b�v�̃f�o�b�O�\��
	showDebugMap = false;

}

Quest28Seq::~Quest28Seq()
{
	delete pCam;
	delete pMap;
	delete pPlayer;

}

Sequence * Quest28Seq::move()
{

	// [M] key�������ꂽ��f�o�b�O�}�b�v�`�悷�邩�̐؂�ւ�
	if (INPUT_INSTANCE.getInput(KEY_INPUT_M) == KEY_STATE_PUSHDOWN)
	{
		showDebugMap = !showDebugMap;
	}

	// �X�y�[�X�L�[�������ꂽ�玟�̃N�G�X�g�̃V�[�P���X���쐬���ăV�[�P���X�`�F���W
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest30Seq;
	}

	//�v���[���[����
	pPlayer->move(pMap, pCam);


	//�v���[���[�𒍎��_�Ƃ��ăJ�����쐬
	pCam->move(pMap,
		   	   pPlayer->getPlayerPosX(),
		       pPlayer->getPlayerPosY());

	
	return this;
}

void Quest28Seq::draw()
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

	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #29.");
	GAMEINSTANCE.systemText.textDraw(10, GAMEINSTANCE.getScreenHeight() - 90, "HOW TO PLAY\nALLOW KEY - MOVE / [M] - Map Debug Show");
	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Question.");
}
