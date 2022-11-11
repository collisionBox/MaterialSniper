#include "questions.h"

Quest16Seq::Quest16Seq()
{
	mImgHandle = LoadGraph("image/block1.bmp");

	mx = 100;
	my = 100;

	mVx = 8;
	mVy = 8;
	
}

Quest16Seq::~Quest16Seq()
{
	if (mImgHandle != -1)
	{
		DeleteGraph(mImgHandle);
	}
}
Sequence* Quest16Seq::move()
{
	// �X�y�[�X�L�[�������ꂽ�玟�̃N�G�X�g�̃V�[�P���X���쐬���ăV�[�P���X�`�F���W
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest17Seq;
	}

	const int blockSize = 64;

	mx += mVx;
	my += mVy;

	//�ǂɓ���������ړ������𔽓]������
	if (mx <= 0 )
	{
		mx = 0;
		mVx *= -1;
	}
	if (mx > GAMEINSTANCE.getScreenWidth() - blockSize)
	{
		mx = GAMEINSTANCE.getScreenWidth() - blockSize;
		mVx *= -1;
	}

	if (my < 0)
	{
		my = 0;
		mVy *= -1;
	}

	if (my > GAMEINSTANCE.getScreenHeight() - blockSize)
	{
		my = GAMEINSTANCE.getScreenHeight()- blockSize;
		mVy *= -1;
	}



	// ���s�V�[�P���X���s
	return this;
}

void Quest16Seq::draw()
{
	ClearDrawScreen();

	DrawGraph(mx, my, mImgHandle, true);

	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #16.");
	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Question.");

}