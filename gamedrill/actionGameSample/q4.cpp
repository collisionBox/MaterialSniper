#include "questions.h"

Quest04Seq::Quest04Seq()
{
	// �摜�ǂݍ���
	//    ������ �� �t�@�C����, ������, ����������, �c��������, ��pixel�T�C�Y, �cpixel�T�C�Y, �C���[�WID�i�[�p�z��̐擪�A�h���X
	LoadDivGraph("image/chara.png",16, 4, 4, 64, 64, mImgHandle );

	mAnimCounter = 0;
	mMaxAnimnum = 16;
	mInterval = 10;
}

Quest04Seq::~Quest04Seq()
{
	for (int i = 0; i < 16; i++)
	{
		if (mImgHandle[i] != -1)
		{
			DeleteGraph(mImgHandle[i]);
		}
	}
}
Sequence* Quest04Seq::move()
{
	static int frame = 0;
	frame++;

	// �t���[����m_inerval�Őݒ肳��Ă���t���[������
	if (frame % mInterval == 0)
	{
		//�A�j���[�V����1���i�߂�
		mAnimCounter++;
		
		//�A�j���[�V������������������߂�
		if (mAnimCounter >= mMaxAnimnum)
		{
			mAnimCounter = 0;
		}
	}

	// �X�y�[�X�L�[�������ꂽ�玟�̃N�G�X�g�̃V�[�P���X���쐬���ăV�[�P���X�`�F���W
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest05Seq;
	}

	// ���s�V�[�P���X���s
	return this;
}


void Quest04Seq::draw()
{
	ClearDrawScreen();

	DrawGraph(300, 300, mImgHandle[mAnimCounter], true);

	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #04.");
	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Quest.");
}