#include "questions.h"

// �X�e�[�W����
char stageName[][32] = {

	"QUESTION # 01",
	"QUESTION # 02",
	"QUESTION # 03",
	"QUESTION # 04",
	"QUESTION # 05",
	"QUESTION # 06",
	"QUESTION # 07",
	"QUESTION # 08",
	"QUESTION # 09",
	"QUESTION # 10",
	"QUESTION # 11-14",
	"QUESTION # 15",
	"QUESTION # 16",
	"QUESTION # 17",
	"QUESTION # 18",
	"QUESTION # 19",
	"QUESTION # 20-21",
	"QUESTION # 22-23",
	"QUESTION # 24",
	"QUESTION # 25-27",
	"QUESTION # 28",
	"QUESTION # 29",
	"QUESTION # 30",

};

int QuestSelector::stageIncrement(int stageNum)
{

	// �X�e�[�W�Z���N�g���͈͓��̎�
	if (stageNum > 0 && stageNum < mStageNumMax)
	{
		return stageNum + 1;
	}

	//�Ō�̃X�e�[�W�܂ŗ����Ƃ�
	return 1;
}

int QuestSelector::stageDecrement(int stageNum)
{
	//�ŏ��̃X�e�[�W�ɗ�����
	if (stageNum == 1)
	{
		return mStageNumMax;
	}

	//����ȊO�̂Ƃ�
	return stageNum - 1;
}

//�X�e�[�W�i���o�[���X�e�[�W�𐶐����Ă��̃|�C���^��Ԃ�
Sequence* QuestSelector::stageCreator(int stageNum)
{
	if (stageNum < 0)
	{
		return NULL;
	}

	//�X�e�[�W�ɉ����āA���̃V�[�P���X�𐶐�����
	switch (stageNum)
	{
	case 1:
		return new Quest01Seq;
	case 2:
		return new Quest02Seq;
	case 3:
		return new Quest03Seq;
	case 4:
		return new Quest04Seq;
	case 5:
		return new Quest05Seq;
	case 6:
		return new Quest06Seq;
	case 7:
		return new Quest07Seq;
	case 8:
		return new Quest08Seq;
	case 9:
		return new Quest09Seq;
	case 10:
		return new Quest10Seq;
	case 11:
		return new Quest11_14Seq;
	case 12:
		return new Quest15Seq;
	case 13:
		return new Quest16Seq;
	case 14:
		return new Quest17Seq;
	case 15:
		return new Quest18Seq;
	case 16:
		return new Quest19Seq;
	case 17:
		return new Quest20_21Seq;
	case 18:
		return new Quest22_23Seq;
	case 19:
		return new Quest24Seq;
	case 20:
		return new Quest26Seq;
	case 21:
		return new Quest27Seq;
	case 22:
		return new Quest28Seq;
	case 23:
		return new Quest30Seq;


	default:
		break;
	}

	return NULL;
}

QuestSelector::QuestSelector()
{
	// �摜�ǂݍ���
	mImgHandle = LoadGraph("image/block0.bmp");
	LoadDivGraph("image/chara.png", 16, 4, 4, 64, 64, mCharaImgHandle);

	// ���j���[�֘A
	mStageNumMax        = sizeof(stageName) / sizeof(char[32]);
	mStageNumInParagrah = mStageNumMax / 2; //�P�i���ɓ���s��
	mStageNo            = 1;

	// �V�[�P���X�ڍs�֘A
	mbChangeSeqNow   = false;
	mChangeTimeCount = 0;

	//�X�N���[������֘A
	mBgXOffset = 0;
	mBgYOffset = 0;
	mBgVx = 0;
	mBgVy = 0;
	mScrollSpeed = 2;
	
	int tmp;
	GetGraphSize(mImgHandle, &mBlockSize, &tmp);

	//�A�j���[�V�����J�E���^�֘A
	mStartUpAnimCount = 0.0f;

	mpMenuStartPos = new Point2D[mStageNumMax];
	mpMenuEndPos = new Point2D[mStageNumMax];
	mpMenuNowPos = new Point2D[mStageNumMax];
	mpMenuAnimTime = new float[mStageNumMax];

	//��ʊO�J�n�ʒu���W
	const float startPosLeft  = -400.0f;              // �J�n�ʒu��x���W
	const float startPosRight = 900.0f;               // �J�n�ʒu�Ex���W
	const float endPosLeft    = 120.0f;               // ���i��x�ʒu
	const float endPosRight   = endPosLeft + 320.0f;  // �E�i��x�ʒu

	const float timeDelay = 0.05f;                    // 1�s���Ƃ̎��ԍ�
	const float columnBase = 140.0f;                  // 1�ԏ�̍s�̃x�[�X���C��
	const float columnHeightInc = 30.0f;              // ���s���̎��ԍ���		
	const float yOfs = (-columnHeightInc * mStageNumInParagrah);

	//�����J�n�E�I���ʒu
	for (int i = 0; i < mStageNumMax; i++)
	{

		//i�����̒i���Ȃ�I�t�Z�b�g�l�ύX���ĕ\�������̒i���ɂ���
		if (i < mStageNumInParagrah)
		{
			mpMenuStartPos[i] = Point2D( startPosRight, columnBase + columnHeightInc * i );
			mpMenuEndPos[i]   = Point2D( endPosLeft   , columnBase + columnHeightInc * i );
			mpMenuAnimTime[i] = -i * timeDelay;
		}
		else
		{
			mpMenuStartPos[i] = Point2D( startPosLeft, columnBase + columnHeightInc * i + yOfs);
			mpMenuEndPos[i]   = Point2D( endPosRight , columnBase + columnHeightInc * i + yOfs);
			mpMenuAnimTime[i] = -(i - mStageNumInParagrah ) * timeDelay;
		}
	}

	//�X�N���[���o�b�t�@�쐬
	mScreenBuffer = MakeScreen( 800, 600, FALSE );
	mReduceScreen = MakeScreen( 800 / 2, 600 / 2, FALSE);
	mBlurScreenBuffer = MakeScreen(800 / 2, 600 / 2, FALSE);

}

QuestSelector::~QuestSelector()
{

	delete[] mpMenuAnimTime;
	delete[] mpMenuStartPos;
	delete[] mpMenuNowPos;
	delete[] mpMenuEndPos;

	if (mImgHandle != -1)
	{
		DeleteGraph(mImgHandle);
	}
	for (int i = 0; i < 16; i++)
	{
		if (mCharaImgHandle[i] != -1)
		{
			DeleteGraph(mCharaImgHandle[i]);
		}
	}

}
Sequence* QuestSelector::move()
{
	// �A�j���[�V�����J�E���g
	if (mStartUpAnimCount < 1.0f)
	{
		mStartUpAnimCount += 0.01f;

	}
	
	if( mStartUpAnimCount > 1.0f)
	{
		mStartUpAnimCount = 1.0f;
	}

	//���ꂼ�ꕶ���̃A�j���J�E���g�A�b�v
	for (int i = 0; i < mStageNumMax; i++)
	{
		mpMenuAnimTime[i] += 0.01f;

		if (mpMenuAnimTime[i] > 1.0f)
		{
			mpMenuAnimTime[i] = 1.0f;
		}
	}

	// �C�[�W���O����
	for (int i = 0; i < mStageNumMax; i++)
	{
		float time = mpMenuAnimTime[i];
		if (time < 0.0f)
		{
			time = 0.0f;
		}
		mpMenuNowPos[i] = easeInExponential(mpMenuStartPos[i], mpMenuEndPos[i], time);
	}
	
	//�w�i�X�N���[���A�j���[�V����
	// �X�N���[�����x
	mBgVx = +mScrollSpeed;
	mBgVy = -mScrollSpeed;

	// ���x�ɉ����Ĉړ�
	mBgXOffset += mBgVx;
	mBgYOffset += mBgVy;

	// ����I�t�Z�b�g���W���Z�o ���㏑���n�߂���ɉ�ʊO����ɂȂ�悤��
	// mBlockSize���}�C�i�X���Ă���
	mBgXOffset = (mBgXOffset % mBlockSize) - mBlockSize;
	mBgYOffset = (mBgYOffset % mBlockSize) - mBlockSize;


	//�L�[����
	if (INPUT_INSTANCE.getInput(KEY_INPUT_UP) == KEY_STATE_PUSHDOWN)
	{
		mStageNo = stageDecrement(mStageNo);
	}

	if (INPUT_INSTANCE.getInput(KEY_INPUT_DOWN) == KEY_STATE_PUSHDOWN)
	{
		mStageNo = stageIncrement(mStageNo);
	}

	//�G���^�[�L�[�őI�����ꂽ�炻�̃X�e�[�W�֔��
	if (INPUT_INSTANCE.getInput(KEY_INPUT_RETURN) == KEY_STATE_PUSHDOWN)
	{
		mbChangeSeqNow = true;
	}

	// �V�[�P���X�ڍs������
	if (mbChangeSeqNow)
	{
		mChangeTimeCount++;
	}

	//�������o�߂�����V�[�P���X�ڍs
	if (mChangeTimeCount > mMaxTime)
	{
		Sequence* pStage;
		pStage = stageCreator(mStageNo);

		if (pStage != NULL)
			return pStage;
	}

	// ���s�V�[�P���X���s
	return this;
}


void QuestSelector::draw()
{
	//�w�i1pass��
	SetDrawScreen( mScreenBuffer );
	ClearDrawScreen();
	//�X�N���[����ʕ`��@�����ʊO����E����ʊO�܂ŕ`��
	// ��ʍ��������擾�i���[�v�I�[�����j
	int screenHeight = GAMEINSTANCE.getScreenHeight();
	int screenWidth = GAMEINSTANCE.getScreenWidth();

	// y���W : ���ʊO����A����ʊO�ɂȂ�܂Ń��[�v
	for (int i = 0; mBgYOffset + i * mBlockSize < screenHeight; i++)
	{
		// x���W : ����ʊO����E��ʊO�ɂȂ�܂Ń��[�v
		for (int j = 0; mBgXOffset + j * mBlockSize < screenWidth; j++)
		{

			DrawGraph(mBgXOffset + j * mBlockSize,
				mBgYOffset + i * mBlockSize,
				mImgHandle, true);
		}
	}

	//�w�i2nd pass
	// �k�����ڂ����o�b�t�@�]��
	GraphFilterBlt( mScreenBuffer, mReduceScreen, DX_GRAPH_FILTER_DOWN_SCALE, 2);
	GraphFilterBlt( mReduceScreen, mBlurScreenBuffer, DX_GRAPH_FILTER_GAUSS, 2, 200);

	// �ڂ������X�N���[���o�b�t�@�Ƀt�B���^�Ȃ��œ]��
	SetDrawScreen( mScreenBuffer );
	DrawExtendGraph( 0, 0, 800, 600, mBlurScreenBuffer, FALSE );

	//�o�b�N�o�b�t�@�ʏ�`�� 
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();

	// y���W : ���ʊO����A����ʊO�ɂȂ�܂Ń��[�v
	for (int i = 0; mBgYOffset + i * mBlockSize < screenHeight; i++)
	{
		// x���W : ����ʊO����E��ʊO�ɂȂ�܂Ń��[�v
		for (int j = 0; mBgXOffset + j * mBlockSize < screenWidth; j++)
		{

			DrawGraph(mBgXOffset + j * mBlockSize,
				mBgYOffset + i * mBlockSize,
				mImgHandle, true);
		}
	}

	//�������E�B���h�E����
	float yAnimOffset;
	yAnimOffset = easeInOutExponential(-800.0f, 0.0f, mStartUpAnimCount);

	// �ڂ������n�`��
	DrawRectGraph(60, 60 + (int)yAnimOffset,
		          60, 60 + (int)yAnimOffset,
		          screenWidth - 120, 540 + (int)yAnimOffset - 60,
		          mScreenBuffer, FALSE, FALSE);

	// �w�i����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 32);
	// �����������d�˂ĕ`��
	DrawBox(60, 60 + (int)yAnimOffset, screenWidth - 60, 540 + (int)yAnimOffset, 0xff000033, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 32);

	// �X�e�[�W�����`��
	for(int i = 0; i < mStageNumMax; i++)
	{
		//�I���X�e�[�W�̂ݕ����F�ς���
		if (mStageNo - 1 == i)
		{
			GAMEINSTANCE.systemText.setFontColor(255, 0, 0);
		}
		else
		{
			//��I�����̕����\��
			GAMEINSTANCE.systemText.setFontColor(255, 255, 255);

			// �X�e�[�W���̕`��
			GAMEINSTANCE.systemText.textDraw( (int)mpMenuNowPos[i].x,
										      (int)mpMenuNowPos[i].y,
				                                   stageName[i]);
			continue;
		}

		// �I����̓_�ŏ���
		if (!mbChangeSeqNow || (mChangeTimeCount / 5) % 2 == 0 )
		{
			GAMEINSTANCE.systemText.textDraw((int)mpMenuNowPos[i].x,
				                             (int)mpMenuNowPos[i].y,
				                                  stageName[i]);
		}
	}
	blinkingString(100, 80 + (int)yAnimOffset, "-  Q U E S T I O N   S E L E C T  -");

	GAMEINSTANCE.systemText.textDraw(10, 570, "Change to [UP / DOWN] KEY : Select [ENTER] KEY!");


}