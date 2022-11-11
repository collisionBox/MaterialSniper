#include <math.h>
#include "questions.h"

// �Q�[�W��`�悷��
// x,y �Q�[�W�`�捶����W�@width, height �Q�[�W��,����, �Q�[�W�ő�l, �Q�[�W�l, �Q�[�W���J���[
void drawMeter(int x, int y, int width, int height, int max, int val , int color)
{
	int meterlen;
	int left   = x - 2 ;
	int right  = x + width + 2;
	int top    = y - 2;
	int bottom = y + height + 2;

	meterlen = (int)((float)width * ((float)val / (float)max));


	//�̗̓Q�[�W�w�i����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox( left, top, right, bottom, 0xFF880000, TRUE);

	//�̗̓Q�[�W����
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawBox(x, y, x + meterlen, y + height, color, TRUE);
	
	//�̗̓Q�[�W�̘g��`��
	
	//�㉺����
	DrawLine(left, top, right, top, 0xFFFFFFFF);
	DrawLine(left, bottom, right, bottom, 0xFFFFFFFF);

	//���E�c��
	DrawLine(left, top, left , bottom, 0xFFFFFFFF);
	DrawLine(right,top, right, bottom, 0xFFFFFFFF);

}


Quest15Seq::Quest15Seq()
{
	mVal = 0;
	mValInc = 5;

	mImgHandle = LoadGraph("image/block0.bmp");
}


Quest15Seq::~Quest15Seq()
{
	if (mImgHandle != -1)
	{
		DeleteGraph(mImgHandle);
	}
}
Sequence* Quest15Seq::move()
{
	// �X�y�[�X�L�[�������ꂽ�玟�̃N�G�X�g�̃V�[�P���X���쐬���ăV�[�P���X�`�F���W
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest16Seq;
	}

	//val����
	mVal += mValInc;

	//val������A�����𒴂������̏���
	if (mVal > mMaxval)
	{
		mVal = mMaxval;
		mValInc *= -1;
	}

	if (mVal < 0)
	{
		mVal = 0;
		mValInc *= -1;
	}

	// ���s�V�[�P���X���s
	return this;
}


void Quest15Seq::draw()
{
	ClearDrawScreen();

	//�w�i�`��
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			DrawGraph(i * 64, j * 64, mImgHandle, FALSE);
		}
	}

	//���[�^�[�`��
	drawMeter(100, 100, 600, 32, 150, mVal, 0xFFFFFF00);

	drawMeter(100, 200, 300, 16, 150, mVal, 0xFF00AA00);

	// �Q�[�W�̌��݂̒l�ƍő�l��\��
	char buf[64];
	sprintf(buf, "METER VALUE : [ %3d / %3d ]", mVal, mMaxval);
	GAMEINSTANCE.systemText.textDraw(100, 70, buf);

	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #15.");
	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Question.");

}