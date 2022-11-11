#include "questions.h"

Quest05Seq::Quest05Seq()
{
	mImgHandle1 = LoadGraph("image/block0.bmp");
	mImgHandle2 = LoadGraph("image/block1.bmp");
}


Quest05Seq::~Quest05Seq()
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

Sequence* Quest05Seq::move()
{
	// �X�y�[�X�L�[�������ꂽ�玟�̃N�G�X�g�̃V�[�P���X���쐬���ăV�[�P���X�`�F���W
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest06Seq;
	}

	// ���s�V�[�P���X���s
	return this;
}


void Quest05Seq::draw()
{
	static int alpha = 0;
	const int maxcolor = 255;

	const int blockSize = 64;
	const int maxWidthIndex = GAMEINSTANCE.getScreenWidth() / blockSize + 1;
	const int maxHeightIndex = GAMEINSTANCE.getScreenHeight() / blockSize + 1;

	//�����x�A�j���[�V����
	alpha++;
	if (alpha > maxcolor)
	{
		alpha = 0;
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

	//���������̂�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	DrawGraph(100, 100, mImgHandle2, true);

	//�������`�惂�[�h��ʏ탂�[�h�֖߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #05.");
	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Quest.");

}