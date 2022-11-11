#include "questions.h"

Quest18Seq::Quest18Seq()
{
	//�w�i�摜�擾
	mImgBG = LoadGraph("image/block1.bmp");

	//�L�����A�j���摜
	LoadDivGraph("image/chara.png", 16, 4, 4, 64, 64, mImgPlayer);

	//�n�ʂ̍���
	mGroundY = 512;

	//�A�j���[�V�����z�񏉊���
	//�ҋ@���[�V����
	mPStartAnimNum[CHARA_STATE_WAIT] = 0;
	mPEndAnimNum[CHARA_STATE_WAIT] = 3;

	//���胂�[�V����
	mPStartAnimNum[CHARA_STATE_RUN] = 4;
	mPEndAnimNum[CHARA_STATE_RUN] = 7;

	//�W�����v�����[�V����
	mPStartAnimNum[CHARA_STATE_JUMP] = 14;
	mPEndAnimNum[CHARA_STATE_JUMP] = 15;

	//�n�ʂɗ����Ă���
	mPStartAnimNum[CHARA_STATE_ON_GROUND] = 0;
	mPEndAnimNum[CHARA_STATE_ON_GROUND] = 0;

	//�L����������
	mPx       = GAMEINSTANCE.getScreenWidth() / 2 - 64;
	mPy       = mGroundY - 64   ;
	mPVx      = 0                ;
	mPVy      = 0                ;
	mPHeight  = 64               ;
	mPJumpPow = 25               ;
	mPAnimNum = 0                ;
	mPState   = CHARA_STATE_WAIT ;
	mRightFlg = true             ;

}


Quest18Seq::~Quest18Seq()
{
	if (mImgBG != -1)
	{
		DeleteGraph(mImgBG);
	}
}
Sequence* Quest18Seq::move()
{
	//�A�j���[�V�����p�J�E���^
	static int anim = 0;
	anim++;
	const int interval = 8; //���̃A�j���ɐi�ނ��߂̃C���^�[�o��
	static int animCounter = 0;

	//�C���^�[�o�����i�񂾂��i�߂�
	if (anim % interval == 0)
	{
		animCounter++;
	}

	int animNum; //���̃��[�V�����̃A�j������
	const int charaSpeed = 3;

	// �ҋ@���Ȃ�
	if (mPState == CHARA_STATE_WAIT || mPState == CHARA_STATE_ON_GROUND)
	{

		//���E�L�[�����ꂽ���H
		if (INPUT_INSTANCE.getInput(KEY_INPUT_RIGHT) != KEY_STATE_OFF)
		{
			mPVx = charaSpeed;
			mPState = CHARA_STATE_RUN;
			mRightFlg = true;
		}
		//���E�L�[�����ꂽ���H
		if (INPUT_INSTANCE.getInput(KEY_INPUT_LEFT) != KEY_STATE_OFF)
		{
			mPVx = -charaSpeed;
			mPState = CHARA_STATE_RUN;
			mRightFlg = false;
		}

		//�E�G�C�g���[�V�����̃A�j�������擾
		animNum = mPEndAnimNum[CHARA_STATE_WAIT] - mPStartAnimNum[CHARA_STATE_WAIT];
		//�E�G�C�g���[�V����
		mPAnimNum = mPStartAnimNum[CHARA_STATE_WAIT] + animCounter % animNum;

	}

	// �L�����ړ���
	if (mPState == CHARA_STATE_RUN)
	{
		//�ړ����ɃL�[�����ꂽ���H
		if (INPUT_INSTANCE.getInput(KEY_INPUT_RIGHT) == KEY_STATE_OFF &&
			INPUT_INSTANCE.getInput(KEY_INPUT_LEFT) == KEY_STATE_OFF)
		{
			//�E�G�C�g���[�h��
			mPState = CHARA_STATE_WAIT;
			mPVx = 0;
		}
		else 
		{
			//�ړ��A�j������
			animNum = mPEndAnimNum[CHARA_STATE_RUN] - mPStartAnimNum[CHARA_STATE_RUN];
			mPAnimNum = mPStartAnimNum[CHARA_STATE_RUN] + animCounter % animNum;
		}
	}

	// �W�����v
	if (mPState == CHARA_STATE_RUN || mPState == CHARA_STATE_WAIT)
	{
		if (INPUT_INSTANCE.getInput(KEY_INPUT_Z) == KEY_PUSH_DOWN)
		{
			mPState = CHARA_STATE_JUMP;
			mPVy = -mPJumpPow;
		}
	}

	// �W�����v������
	if (mPState == CHARA_STATE_JUMP)
	{
		//�W�����v�ړ���
		mPVy += 1; // GRAVITY;
		if (mPVy > 0)
			mPAnimNum = mPEndAnimNum[CHARA_STATE_JUMP];
		else
			mPAnimNum = mPStartAnimNum[CHARA_STATE_JUMP];
	}

	// �ʒu���X�V
	mPx += mPVx;
	mPy += mPVy;

	//�L�������W�������␳
	if (mPx < 0)
	{
		mPx = 0;
	}
	if (mPx > GAMEINSTANCE.getScreenWidth() - 64)
	{
		mPx = GAMEINSTANCE.getScreenWidth() - 64;
	}

	//�n�ʂƐڐG�������H
	if (mPState == CHARA_STATE_JUMP)
	{
		if (mPy + mPHeight > mGroundY)
		{
			mPy = mGroundY - mPHeight;
			mPVy = 0;
			mPState = CHARA_STATE_WAIT;
			mPAnimNum = mPStartAnimNum[CHARA_STATE_WAIT];
		}
	}

	// �X�y�[�X�L�[�������ꂽ�玟�̃N�G�X�g�̃V�[�P���X���쐬���ăV�[�P���X�`�F���W
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest19Seq;
	}

	// ���s�V�[�P���X���s
	return this;
}


void Quest18Seq::draw()
{
	ClearDrawScreen();

	int screenWidth = GAMEINSTANCE.getScreenWidth();
	int screenHeight = GAMEINSTANCE.getScreenHeight();

	//�w�i�`��
	for (int i = 0; i * 64 + mGroundY < screenHeight; i++)
	{
		for (int j = 0; j * 64 < screenWidth; j++)
		{
			DrawGraph(j * 64, mGroundY + i * 64, mImgBG, FALSE);
		}
	}

	//DrawRotaGraph2�͕\���ʒu �摜�����T�C�Y�����̂ł��̑΍�
	int ofs = 32;
	DrawRotaGraph2(mPx + ofs, mPy + ofs, ofs, ofs, 1.0, 0.0, mImgPlayer[mPAnimNum], TRUE , mRightFlg);

	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #018.");
	GAMEINSTANCE.systemText.textDraw(200, 120, "[ARROW KEY] -- MOVE.\n[Z] KEY     -- JUMP.");

	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Question.");

}