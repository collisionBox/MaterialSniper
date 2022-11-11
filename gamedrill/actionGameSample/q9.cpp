#include "questions.h"

Quest09Seq::Quest09Seq()
{
	//�����O�o�b�t�@�̃C���f�b�N�X
	mNowIndex = 0;
	mPrevIndex = m_maxBuf - 1;

	mNowEnterKeyState = 0;
	mPrevEneterKeyState = 0;

	//�����O�o�b�t�@������
	for (int i = 0; i < m_maxBuf; i++)
	{
		mKeyLogRingBuffer[i] = KEY_OFF;
	}
}


Quest09Seq::~Quest09Seq()
{


}
Sequence* Quest09Seq::move()
{
	// �X�y�[�X�L�[�������ꂽ�玟�̃N�G�X�g�̃V�[�P���X���쐬���ăV�[�P���X�`�F���W
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest10Seq;
	}

	// �����O�o�b�t�@�̎Q�Ƃ���i�߂�
	mNowIndex++;
	mPrevIndex++;

	// ���݂̃����O�o�b�t�@�C���f�b�N�X�������܂ōs������擪�߂�
	if (mNowIndex == m_maxBuf)
		mNowIndex = 0;

	// �ЂƂO�̃����O�o�b�t�@�C���f�b�N�X�������ɂɍs������擪�߂�
	if (mPrevIndex == m_maxBuf)
		mPrevIndex = 0;


	// �G���^�[�L�[�̌��݂̏�ԂƂЂƂO�̃t���[���̏�Ԃ�ۑ�
	mPrevEneterKeyState = mNowEnterKeyState;
	mNowEnterKeyState = CheckHitKey(KEY_INPUT_RETURN);

	//�L�[��������Ă��郍�O���쐬

	// �L�[���I�t���
	if (mPrevEneterKeyState == 0 && mNowEnterKeyState == 0)
	{
		mKeyLogRingBuffer[mNowIndex] = KEY_OFF;
	}

	// �����ꂽ
	if (mPrevEneterKeyState == 1 && mNowEnterKeyState == 0)
	{
		mKeyLogRingBuffer[mNowIndex] = KEY_PULLUP;
	}

	// �������ꂽ
	if (mPrevEneterKeyState == 0 && mNowEnterKeyState == 1)
	{
		mKeyLogRingBuffer[mNowIndex] = KEY_PUSH_DOWN;
	}

	//�����Ɖ�����Ă���
	if (mPrevEneterKeyState == 1 && mNowEnterKeyState == 1)
	{
		mKeyLogRingBuffer[mNowIndex] = KEY_PRESSED;
	}

	// ���s�V�[�P���X���s
	return this;
}


void Quest09Seq::draw()
{
	ClearDrawScreen();

	GAMEINSTANCE.systemText.textDraw(100, 30, "PUSH ENTER KEY!");

	//���O�S�\��
	char buf[256];
	for (int i = 0; i < m_maxBuf; i++)
	{
		KEY_STATE state = indexToKeyState(i);
		if (state == KEY_OFF)
		{
			GAMEINSTANCE.systemText.setFontColor(64, 64, 64);
			sprintf(buf, "%2d prevFrame : [ KEY_OFF ]", i);
		}

		if (state == KEY_PUSH_DOWN)
		{
			GAMEINSTANCE.systemText.setFontColor(255, 0, 0);
			sprintf(buf, "%2d prevFrame : [ KEY_PUSH_DOWN ]---->", i);
		}

		if (state == KEY_PRESSED)
		{
			GAMEINSTANCE.systemText.setFontColor(255, 255, 0);
			sprintf(buf, "%2d prevFrame : [ KEY_PRESSED ]      |", i);
		}

		if (state == KEY_PULLUP)
		{
			GAMEINSTANCE.systemText.setFontColor(0, 255, 0);
 			sprintf(buf, "%2d prevFrame : [ KEY_PULLUP ]<------", i);
		}

		GAMEINSTANCE.systemText.textDraw(150, 80 + i * 30, buf);
	}

	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #09.");
	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Question.");

}

//�C���f�b�N�X�l���L�[�̏�ԕϐ���Ԃ�
KEY_STATE Quest09Seq::indexToKeyState(int index)
{
	// ���݂̃C���f�b�N�X�l����index���O�̒l�B
	index = (m_maxBuf + mNowIndex - index) % m_maxBuf ;
	return mKeyLogRingBuffer[index];
}