#include "questions.h"

Quest06Seq::Quest06Seq()
{
	mImgHandle1 = LoadGraph("image/block0.bmp");
	mImgHandle2 = LoadGraph("image/block1.bmp");
}


Quest06Seq::~Quest06Seq()
{
	if (mImgHandle1 != -1)
	{
		DeleteGraph(mImgHandle1);
	}

	if (mImgHandle2 != -1)
	{
		DeleteGraph(mImgHandle2);
	}
}
Sequence* Quest06Seq::move()
{
	// �X�y�[�X�L�[�������ꂽ�玟�̃N�G�X�g�̃V�[�P���X���쐬���ăV�[�P���X�`�F���W
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest07Seq;
	}

	// ���s�V�[�P���X���s
	return this;
}


void Quest06Seq::draw()
{
	static int alpha = 0;
	const int maxcolor = 255;

	const int blockSize = 64;
	const int maxWidthIndex = GAMEINSTANCE.getScreenWidth() / blockSize + 1;
	const int maxHeightIndex = GAMEINSTANCE.getScreenHeight() / blockSize + 1;

	static int alphainc = 1;

	//�����x�A�j���[�V����
	alpha += alphainc;
	if (alphainc > 0 && alpha > 255)
	{
		alphainc = -1;
		alpha = 255;
	}

	if (alphainc < 0 && alpha < 0)
	{
		alpha = 0;
		alphainc = 1;
	}


	ClearDrawScreen();


	int i, j;

	// �w�i������
	for (i = 0; i < maxHeightIndex; i++)
	{
		for (j = 0; j < maxWidthIndex; j++)
		{
			DrawGraph(j * blockSize, i* blockSize, mImgHandle1, false);
		}
	}

	//���������̂�`��(���Z�������j
	SetDrawBlendMode(DX_BLENDMODE_ADD, alpha);
	DrawGraph(150, 100, mImgHandle2, true);

	//���������̂�`��(��Z�������j
	SetDrawBlendMode(DX_BLENDMODE_MUL, alpha);
	DrawGraph(150, 200, mImgHandle2, true);

	//���������̂�`��(��Z���������j
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawGraph(150, 300, mImgHandle2, true);

	//���������̂�`��(���Z���������j
	SetDrawBlendMode(DX_BLENDMODE_SUB, alpha);
	DrawGraph(150, 400, mImgHandle2, true);


	//�������`�惂�[�h��ʏ탂�[�h�֖߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	char buf[256];
	sprintf(buf, "ALPHA = %3d", alpha);

	GAMEINSTANCE.systemText.textDraw(100, 50, buf);

	GAMEINSTANCE.systemText.textDraw(100, 70, "DX_BLENDMODE_ADD");
	GAMEINSTANCE.systemText.textDraw(100, 180, "DX_BLENDMODE_MUL");
	GAMEINSTANCE.systemText.textDraw(100, 280, "DX_BLENDMODE_MULA");
	GAMEINSTANCE.systemText.textDraw(100, 370, "DX_BLENDMODE_SUB");


	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #06.");
	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Quest.");
}