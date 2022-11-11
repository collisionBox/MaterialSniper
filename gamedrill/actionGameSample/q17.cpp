#include "questions.h"


//�X�N���[���p�^�[��
int scrX[] = {  0, -1,  0, +1, +1, +1, -1, -1 };
int scrY[] = { +1,  0, -1,  0, +1, -1, -1, +1 };

//�X�N���[���p�^�[���̍ő吔
const int scrMaxPattern = sizeof(scrX) / sizeof(int);

Quest17Seq::Quest17Seq()
{
	mImgBlock[0] = LoadGraph("image/block0.bmp");
	mImgBlock[1] = LoadGraph("image/block1.bmp");


	// �`��J�n�I�t�Z�b�g�ʒu
	mBgXOffset = 0;
	mBgYOffset = 0;

	mNowScrDirPattern = 0;

	//�ړ���
	mBgVx = scrX[mNowScrDirPattern];
	mBgVy = scrY[mNowScrDirPattern];

	//�u���b�N�T�C�Y�擾�i�����`�ł��邱�Ƃ�O��B�c���T�C�Y�Ⴄ�Ƃ��͕ϐ��p�ӂ���j
	int tmp;
	GetGraphSize(mImgBlock[0], &mBlockSize, &tmp);

}


Quest17Seq::~Quest17Seq()
{
	for (int i = 0; i < 2; i++)
	{
		if (mImgBlock[i] != -1)
		{
			DeleteGraph(mImgBlock[i]);
		}
	}
}
Sequence* Quest17Seq::move()
{
	// �X�y�[�X�L�[�������ꂽ�玟�̃N�G�X�g�̃V�[�P���X���쐬���ăV�[�P���X�`�F���W
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest18Seq;
	}

	if (INPUT_INSTANCE.getInput(KEY_INPUT_RETURN) == KEY_STATE_PUSHDOWN)
	{
		mNowScrDirPattern = (mNowScrDirPattern + 1) % scrMaxPattern;
	}

	static int scrollSpeed = 8;

	// �X�N���[�����x
	mBgVx = scrX[mNowScrDirPattern] * scrollSpeed;
	mBgVy = scrY[mNowScrDirPattern] * scrollSpeed;

	// ���x�ɉ����Ĉړ�
	mBgXOffset += mBgVx;
	mBgYOffset += mBgVy;

	// ����I�t�Z�b�g���W���Z�o ���㏑���n�߂���ɉ�ʊO����ɂȂ�悤��
	// mBlockSize���}�C�i�X���Ă���

	mBgXOffset = (mBgXOffset % mBlockSize) - mBlockSize;
	mBgYOffset = (mBgYOffset % mBlockSize) - mBlockSize;

	// ���s�V�[�P���X���s
	return this;
}


void Quest17Seq::draw()
{
	ClearDrawScreen();

	//�X�N���[����ʕ`��@�����ʊO����E����ʊO�܂ŕ`��

	// ��ʍ��������擾�i���[�v�I�[�����j
	int screenHeight = GAMEINSTANCE.getScreenHeight();
	int screenWidth  = GAMEINSTANCE.getScreenWidth();


	// y���W : ���ʊO����A����ʊO�ɂȂ�܂Ń��[�v
	for (int i = 0; mBgYOffset + i * mBlockSize < screenHeight ; i++)
	{
		// x���W : ����ʊO����E��ʊO�ɂȂ�܂Ń��[�v
		for (int j = 0; mBgXOffset + j * mBlockSize < screenWidth ; j++)
		{

			DrawGraph( mBgXOffset + j * mBlockSize, 
				       mBgYOffset + i * mBlockSize,
				       mImgBlock[ 0 ], true);
		}
	}
	GAMEINSTANCE.systemText.textDraw(60, 300, "HIT RETURN KEY TO CHANGE SCROLL DIR.");
	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #17.");
	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Question.");

}