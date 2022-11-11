#include "questions.h"

Quest18Seq::Quest18Seq()
{
	//背景画像取得
	mImgBG = LoadGraph("image/block1.bmp");

	//キャラアニメ画像
	LoadDivGraph("image/chara.png", 16, 4, 4, 64, 64, mImgPlayer);

	//地面の高さ
	mGroundY = 512;

	//アニメーション配列初期化
	//待機モーション
	mPStartAnimNum[CHARA_STATE_WAIT] = 0;
	mPEndAnimNum[CHARA_STATE_WAIT] = 3;

	//走りモーション
	mPStartAnimNum[CHARA_STATE_RUN] = 4;
	mPEndAnimNum[CHARA_STATE_RUN] = 7;

	//ジャンプ中モーション
	mPStartAnimNum[CHARA_STATE_JUMP] = 14;
	mPEndAnimNum[CHARA_STATE_JUMP] = 15;

	//地面に立っている
	mPStartAnimNum[CHARA_STATE_ON_GROUND] = 0;
	mPEndAnimNum[CHARA_STATE_ON_GROUND] = 0;

	//キャラ初期化
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
	//アニメーション用カウンタ
	static int anim = 0;
	anim++;
	const int interval = 8; //次のアニメに進むためのインターバル
	static int animCounter = 0;

	//インターバル分進んだら一つ進める
	if (anim % interval == 0)
	{
		animCounter++;
	}

	int animNum; //そのモーションのアニメ枚数
	const int charaSpeed = 3;

	// 待機中なら
	if (mPState == CHARA_STATE_WAIT || mPState == CHARA_STATE_ON_GROUND)
	{

		//左右キー押されたか？
		if (INPUT_INSTANCE.getInput(KEY_INPUT_RIGHT) != KEY_STATE_OFF)
		{
			mPVx = charaSpeed;
			mPState = CHARA_STATE_RUN;
			mRightFlg = true;
		}
		//左右キー押されたか？
		if (INPUT_INSTANCE.getInput(KEY_INPUT_LEFT) != KEY_STATE_OFF)
		{
			mPVx = -charaSpeed;
			mPState = CHARA_STATE_RUN;
			mRightFlg = false;
		}

		//ウエイトモーションのアニメ枚数取得
		animNum = mPEndAnimNum[CHARA_STATE_WAIT] - mPStartAnimNum[CHARA_STATE_WAIT];
		//ウエイトモーション
		mPAnimNum = mPStartAnimNum[CHARA_STATE_WAIT] + animCounter % animNum;

	}

	// キャラ移動中
	if (mPState == CHARA_STATE_RUN)
	{
		//移動中にキー離されたか？
		if (INPUT_INSTANCE.getInput(KEY_INPUT_RIGHT) == KEY_STATE_OFF &&
			INPUT_INSTANCE.getInput(KEY_INPUT_LEFT) == KEY_STATE_OFF)
		{
			//ウエイトモードに
			mPState = CHARA_STATE_WAIT;
			mPVx = 0;
		}
		else 
		{
			//移動アニメ処理
			animNum = mPEndAnimNum[CHARA_STATE_RUN] - mPStartAnimNum[CHARA_STATE_RUN];
			mPAnimNum = mPStartAnimNum[CHARA_STATE_RUN] + animCounter % animNum;
		}
	}

	// ジャンプ
	if (mPState == CHARA_STATE_RUN || mPState == CHARA_STATE_WAIT)
	{
		if (INPUT_INSTANCE.getInput(KEY_INPUT_Z) == KEY_PUSH_DOWN)
		{
			mPState = CHARA_STATE_JUMP;
			mPVy = -mPJumpPow;
		}
	}

	// ジャンプ中処理
	if (mPState == CHARA_STATE_JUMP)
	{
		//ジャンプ移動中
		mPVy += 1; // GRAVITY;
		if (mPVy > 0)
			mPAnimNum = mPEndAnimNum[CHARA_STATE_JUMP];
		else
			mPAnimNum = mPStartAnimNum[CHARA_STATE_JUMP];
	}

	// 位置を更新
	mPx += mPVx;
	mPy += mPVy;

	//キャラ座標横方向補正
	if (mPx < 0)
	{
		mPx = 0;
	}
	if (mPx > GAMEINSTANCE.getScreenWidth() - 64)
	{
		mPx = GAMEINSTANCE.getScreenWidth() - 64;
	}

	//地面と接触したか？
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

	// スペースキーが押されたら次のクエストのシーケンスを作成してシーケンスチェンジ
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest19Seq;
	}

	// 現行シーケンス続行
	return this;
}


void Quest18Seq::draw()
{
	ClearDrawScreen();

	int screenWidth = GAMEINSTANCE.getScreenWidth();
	int screenHeight = GAMEINSTANCE.getScreenHeight();

	//背景描画
	for (int i = 0; i * 64 + mGroundY < screenHeight; i++)
	{
		for (int j = 0; j * 64 < screenWidth; j++)
		{
			DrawGraph(j * 64, mGroundY + i * 64, mImgBG, FALSE);
		}
	}

	//DrawRotaGraph2は表示位置 画像半分サイズずれるのでその対策
	int ofs = 32;
	DrawRotaGraph2(mPx + ofs, mPy + ofs, ofs, ofs, 1.0, 0.0, mImgPlayer[mPAnimNum], TRUE , mRightFlg);

	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #018.");
	GAMEINSTANCE.systemText.textDraw(200, 120, "[ARROW KEY] -- MOVE.\n[Z] KEY     -- JUMP.");

	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Question.");

}