#include "questions.h"


Quest10Seq::Quest10Seq()
{
	mSndHandle1 = LoadSoundMem("data/06 NSF-771-06_pops.wav");
	mbNowPlay1 = false;

	mSndHandle2 = LoadSoundMem("data/09 touch sound1.wav");
	mbNowPlay2 = false;
}


Quest10Seq::~Quest10Seq()
{
	//�T�E���h��~
	StopSoundMem(mSndHandle1);
	StopSoundMem(mSndHandle2);

	//�T�E���h���������
	if (mSndHandle1 != -1)
	{
		DeleteSoundMem(mSndHandle1);
	}
	//�T�E���h���������
	if (mSndHandle2 != -1)
	{
		DeleteSoundMem(mSndHandle2);
	}

}
Sequence* Quest10Seq::move()
{
	//���񉹊y���Đ�����Ă��Ȃ�������Đ�
	if (!mbNowPlay1 && mSndHandle1 != -1)
	{
		mbNowPlay1 = true;
		PlaySoundMem(mSndHandle1, DX_PLAYTYPE_LOOP);
	}

	//�G���^�[�L�[�ŃT�E���h�Đ�
	if (INPUT_INSTANCE.getInput(KEY_INPUT_RETURN) == KEY_STATE_PUSHDOWN && !mbNowPlay2)
	{
		mbNowPlay2 = true;
		PlaySoundMem(mSndHandle2, DX_PLAYTYPE_BACK);
	}

	if (mbNowPlay2)
	{
		if (!CheckSoundMem(mSndHandle2))
		{
			mbNowPlay2 = false;
		}
	}

	// �X�y�[�X�L�[�������ꂽ�玟�̃N�G�X�g�̃V�[�P���X���쐬���ăV�[�P���X�`�F���W
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest11_14Seq;
	}

	// ���s�V�[�P���X���s
	return this;
}


void Quest10Seq::draw()
{
	int time, min,sec,msec;
	char buf[256];

	ClearDrawScreen();

	//�Đ����\��
	if (mbNowPlay1)
	{
		//�Đ��^�C�����擾
		time = GetSoundCurrentTime(mSndHandle1);

		//�b,���A�~���b���v�Z
		sec = time / 1000;
		min = sec / 60;
		sec -= min * 60;

		// �~���b�Z�o(�P�O�~���b�P�ʂ��ۂ�)
		msec = (time - sec * 1000 - min * 60000) / 10;

		sprintf(buf, "[ %02d'%02d\"%02d ] : SOUND PLAYING ( LOOP ).",min, sec, msec);
		GAMEINSTANCE.systemText.textDraw(100, 300, buf);
	}

	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #10.");

	GAMEINSTANCE.systemText.textDraw(100, 260, "PUSH ENTER KEY TO SOUND FX.");


	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Question.");

}