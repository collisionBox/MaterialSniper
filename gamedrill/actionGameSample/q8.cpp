#include "q8.h"
#include "questions.h"
#include <math.h>


int fadeinc = 1;

Quest08Seq::Quest08Seq()
{
	mImgHandle = LoadGraph("image/block1.bmp");
	fade = 0;
}


Quest08Seq::~Quest08Seq()
{
	if (mImgHandle != -1)
	{
		DeleteGraph(mImgHandle);
	}
}
Sequence* Quest08Seq::move()
{
	// �X�y�[�X�L�[�������ꂽ�玟�̃N�G�X�g�̃V�[�P���X���쐬���ăV�[�P���X�`�F���W
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest09Seq;
	}

	//��ʃt�F�[�h�C�����A�E�g�����`�F�b�N
	if (fade > 255 && fadeinc > 0)
	{
		fadeinc *= -1;
	}
	if (fade < 0 && fadeinc < 0)
	{
		fadeinc *= -1;
	}		
	fade += fadeinc;

	// ���s�V�[�P���X���s
	return this;
}


void Quest08Seq::draw()
{
	char buf[256];
	static float angle = 0.0f;
	angle += 0.05f;

	static float exanim = 0.0f;
	exanim += 0.01f;



	ClearDrawScreen();
	DrawRotaGraph2(200, 100, 0, 0, 1.0, angle, mImgHandle, false, false);
	DrawRotaGraph2(200, 300, 32, 32, 1.0, angle, mImgHandle, false, false);
	DrawRotaGraph2(200, 500, 32, 32, 2.0f * sinf(exanim), angle, mImgHandle, false, false);


	// �������\��
	sprintf(buf, "DrawRotaGraph center(0, 0) ExtRate = 1.0 \n angle = %3.2f", angle);
	GAMEINSTANCE.systemText.textDraw(10, 30, buf);

	sprintf(buf, "DrawRotaGraph center(32, 32) ExtRate = 1.0 \n angle = %3.2f", angle);
	GAMEINSTANCE.systemText.textDraw(10, 200, buf);

	sprintf(buf, "DrawRotaGraph ExtRate = %+3.2f angle = %3.2f", 2.0f * sinf(exanim), angle);
	GAMEINSTANCE.systemText.textDraw(10, 400, buf);

	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #08.");

	//��ʑS�̃t�F�[�h�p��`�������`��
	//���������̂�`��(�������j
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade);
	DrawBox(0, 0, GAMEINSTANCE.getScreenWidth(), GAMEINSTANCE.getScreenHeight(), 0xffffffff, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, fade);


	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Quest.");
}