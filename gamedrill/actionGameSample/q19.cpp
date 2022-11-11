#include "questions.h"

Quest19Seq::Quest19Seq()
{
	mImgHandle = LoadGraph("image/block1.bmp");

	// �u���b�N�L����
	mx = 100;
	my = 100;
	mVx = 4;
	mVy = 4;

	// �����蔻��]�[��
	mZoneX = 300;
	mZoneY = 150;
	mZoneW = 300;
	mZoneH = 400;

	mZoneAnim = 128;
	mZoneAnimInc = 1;

	mNowHit = false;

}

Quest19Seq::~Quest19Seq()
{
	if (mImgHandle != -1)
	{
		DeleteGraph(mImgHandle);
	}
}
Sequence* Quest19Seq::move()
{
	// �X�y�[�X�L�[�������ꂽ�玟�̃N�G�X�g�̃V�[�P���X���쐬���ăV�[�P���X�`�F���W
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest20_21Seq;
	}

	const int blockSize = 64;
	mx += mVx;
	my += mVy;

	//�ǂɓ���������ړ������𔽓]������
	if (mx <= 0)
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
		my = GAMEINSTANCE.getScreenHeight() - blockSize;
		mVy *= -1;
	}

	//�����蔻��]�[���A�j���[�V����
	const int zoneMax = 128;
	const int zoneMin = 64;

	//zoneAnim����������
	mZoneAnim += mZoneAnimInc;

	//���E�l�������Ă���^�����Ă��Ȃ����H
	if (mZoneAnim < zoneMin)
	{
		mZoneAnimInc *= -1;
		mZoneAnim = zoneMin;
	}

	if (mZoneAnim > zoneMax)
	{
		mZoneAnimInc *= -1;
		mZoneAnim = zoneMax;
	}

	//�����蔻��`�F�b�N
	mNowHit = hitCheck(mx, my,             //�u���b�N����
		                mx + 64, my + 64,   //�u���b�N�E��
		                mZoneX, mZoneY,   //�]�[������
	                    mZoneX + mZoneW,  //�]�[���E��
		                mZoneY + mZoneH);

	// ���s�V�[�P���X���s
	return this;
}

void Quest19Seq::draw()
{
	ClearDrawScreen();

	//�u���b�N�`��
	DrawGraph(mx, my, mImgHandle, true);

	//�]�[���`��
	SetDrawBlendMode(DX_BLENDMODE_ADD, mZoneAnim);
	DrawBox(mZoneX, mZoneY,
		    mZoneX + mZoneW, mZoneY + mZoneH,
		    0xFF9900, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, mZoneAnim);

	if (mNowHit)
	{
		GAMEINSTANCE.systemText.textDraw(400, 300, "H I T  !!");
	}

	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #19.");
	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Question.");

}

//�����蔻��`�F�b�N�������Ă�����true�Ԃ�
bool Quest19Seq::hitCheck(int leftx1, int topy1, int rightx1, int bottomy1, int leftx2, int topy2, int rightx2, int bottomy2)
{
	return (leftx1 <= rightx2 && leftx2 <= rightx1 && topy1 <= bottomy2 && topy2 <= bottomy1);
}
