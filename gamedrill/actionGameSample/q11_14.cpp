#include "questions.h"

Quest11_14Seq::Quest11_14Seq()
{
	mScore     = 0;   // �X�R�A
	mAimScore  = 0;   // �ڕW�X�R�A
	mCountdown = 10;  // �J�E���g�_�E��
	mCountup   = 0;   // �J�E���g�A�b�v
	mMin       = 0;   // ��

	mTime = mNowTime = GetNowCount();
}


Quest11_14Seq::~Quest11_14Seq()
{
}
Sequence* Quest11_14Seq::move()
{
	// �X�y�[�X�L�[�������ꂽ�玟�̃N�G�X�g�̃V�[�P���X���쐬���ăV�[�P���X�`�F���W
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest15Seq;
	}

	//�P�b(1000�~���b�ȏ�)�o�߂������H
	mNowTime = GetNowCount();
	if (mNowTime - mTime > 1000)
	{
		//�^�C�}�[����b���₷
		mCountup++;

		//�^�C�}�[��1�b���炷
		mCountdown--;

		//1���o�������̏���
		if (mCountup % 60 == 0)
		{
			mCountup = 0;
			mMin++;
		}

		//�J�E���g�_�E��0�ȉ��ɂȂ�����0�ɖ߂��B
		if (mCountdown < 0)
			mCountdown = 0;

		//5�b�����ɃX�R�A100�_�v���X
		if (mCountup % 5 == 0)
		{
			mAimScore += 100;
		}

		//�v��������݂ɃZ�b�g
		mTime = mNowTime;
	}

	//1�b�ȉ��`�����_���ʂ܂ł̕b�����Z�o
	mMiliSec = (mNowTime - mTime) / 10;

	//�X�R�A��ڕW�X�R�A�ɑ����Ă�������
	if (mAimScore != mScore)
		mScore += 2;

	// ���s�V�[�P���X���s
	return this;
}


void Quest11_14Seq::draw()
{
	ClearDrawScreen();

	char buf[256];

	//�X�R�A�\��
	sprintf(buf, "SCORE : %5d", mScore );
	GAMEINSTANCE.systemText.textDraw(200, 200, buf);

	//�J�E���g�_�E���^�C�}�[
	sprintf(buf, "COUNT DOWN TIMER : [ %2d ]", mCountdown );
	if (mCountdown == 0)
	{
		GAMEINSTANCE.systemText.setFontColor(255, 0, 0);
	}
	GAMEINSTANCE.systemText.textDraw(200, 250, buf);

	//�J�E���g�A�b�v�^�C�}�[
	GAMEINSTANCE.systemText.setFontColor(255, 255, 255);
	sprintf(buf, "TIME : [ %02d' %02d\" %02d ]", mMin, mCountup,mMiliSec);
	GAMEINSTANCE.systemText.textDraw(200, 300, buf);

	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #11,12,13,14.");
	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Question.");

}