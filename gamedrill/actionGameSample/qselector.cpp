#include "questions.h"

// ステージ名称
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

	// ステージセレクトが範囲内の時
	if (stageNum > 0 && stageNum < mStageNumMax)
	{
		return stageNum + 1;
	}

	//最後のステージまで来たとき
	return 1;
}

int QuestSelector::stageDecrement(int stageNum)
{
	//最初のステージに来た時
	if (stageNum == 1)
	{
		return mStageNumMax;
	}

	//それ以外のとき
	return stageNum - 1;
}

//ステージナンバーよりステージを生成してそのポインタを返す
Sequence* QuestSelector::stageCreator(int stageNum)
{
	if (stageNum < 0)
	{
		return NULL;
	}

	//ステージに応じて、そのシーケンスを生成する
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
	// 画像読み込み
	mImgHandle = LoadGraph("image/block0.bmp");
	LoadDivGraph("image/chara.png", 16, 4, 4, 64, 64, mCharaImgHandle);

	// メニュー関連
	mStageNumMax        = sizeof(stageName) / sizeof(char[32]);
	mStageNumInParagrah = mStageNumMax / 2; //１段落に入る行数
	mStageNo            = 1;

	// シーケンス移行関連
	mbChangeSeqNow   = false;
	mChangeTimeCount = 0;

	//スクロール制御関連
	mBgXOffset = 0;
	mBgYOffset = 0;
	mBgVx = 0;
	mBgVy = 0;
	mScrollSpeed = 2;
	
	int tmp;
	GetGraphSize(mImgHandle, &mBlockSize, &tmp);

	//アニメーションカウンタ関連
	mStartUpAnimCount = 0.0f;

	mpMenuStartPos = new Point2D[mStageNumMax];
	mpMenuEndPos = new Point2D[mStageNumMax];
	mpMenuNowPos = new Point2D[mStageNumMax];
	mpMenuAnimTime = new float[mStageNumMax];

	//画面外開始位置座標
	const float startPosLeft  = -400.0f;              // 開始位置左x座標
	const float startPosRight = 900.0f;               // 開始位置右x座標
	const float endPosLeft    = 120.0f;               // 左段落x位置
	const float endPosRight   = endPosLeft + 320.0f;  // 右段落x位置

	const float timeDelay = 0.05f;                    // 1行ごとの時間差
	const float columnBase = 140.0f;                  // 1番上の行のベースライン
	const float columnHeightInc = 30.0f;              // 改行毎の字間高さ		
	const float yOfs = (-columnHeightInc * mStageNumInParagrah);

	//文字開始・終了位置
	for (int i = 0; i < mStageNumMax; i++)
	{

		//iが次の段落ならオフセット値変更して表示を次の段落にする
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

	//スクリーンバッファ作成
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
	// アニメーションカウント
	if (mStartUpAnimCount < 1.0f)
	{
		mStartUpAnimCount += 0.01f;

	}
	
	if( mStartUpAnimCount > 1.0f)
	{
		mStartUpAnimCount = 1.0f;
	}

	//それぞれ文字のアニメカウントアップ
	for (int i = 0; i < mStageNumMax; i++)
	{
		mpMenuAnimTime[i] += 0.01f;

		if (mpMenuAnimTime[i] > 1.0f)
		{
			mpMenuAnimTime[i] = 1.0f;
		}
	}

	// イージング処理
	for (int i = 0; i < mStageNumMax; i++)
	{
		float time = mpMenuAnimTime[i];
		if (time < 0.0f)
		{
			time = 0.0f;
		}
		mpMenuNowPos[i] = easeInExponential(mpMenuStartPos[i], mpMenuEndPos[i], time);
	}
	
	//背景スクロールアニメーション
	// スクロール速度
	mBgVx = +mScrollSpeed;
	mBgVy = -mScrollSpeed;

	// 速度に応じて移動
	mBgXOffset += mBgVx;
	mBgYOffset += mBgVy;

	// 左上オフセット座標を算出 左上書き始めが常に画面外からになるように
	// mBlockSize分マイナスしている
	mBgXOffset = (mBgXOffset % mBlockSize) - mBlockSize;
	mBgYOffset = (mBgYOffset % mBlockSize) - mBlockSize;


	//キー操作
	if (INPUT_INSTANCE.getInput(KEY_INPUT_UP) == KEY_STATE_PUSHDOWN)
	{
		mStageNo = stageDecrement(mStageNo);
	}

	if (INPUT_INSTANCE.getInput(KEY_INPUT_DOWN) == KEY_STATE_PUSHDOWN)
	{
		mStageNo = stageIncrement(mStageNo);
	}

	//エンターキーで選択されたらそのステージへ飛ぶ
	if (INPUT_INSTANCE.getInput(KEY_INPUT_RETURN) == KEY_STATE_PUSHDOWN)
	{
		mbChangeSeqNow = true;
	}

	// シーケンス移行中処理
	if (mbChangeSeqNow)
	{
		mChangeTimeCount++;
	}

	//時刻が経過したらシーケンス移行
	if (mChangeTimeCount > mMaxTime)
	{
		Sequence* pStage;
		pStage = stageCreator(mStageNo);

		if (pStage != NULL)
			return pStage;
	}

	// 現行シーケンス続行
	return this;
}


void QuestSelector::draw()
{
	//背景1pass目
	SetDrawScreen( mScreenBuffer );
	ClearDrawScreen();
	//スクロール画面描画　左上画面外から右下画面外まで描画
	// 画面高さ幅を取得（ループ終端条件）
	int screenHeight = GAMEINSTANCE.getScreenHeight();
	int screenWidth = GAMEINSTANCE.getScreenWidth();

	// y座標 : 上画面外から、下画面外になるまでループ
	for (int i = 0; mBgYOffset + i * mBlockSize < screenHeight; i++)
	{
		// x座標 : 左画面外から右画面外になるまでループ
		for (int j = 0; mBgXOffset + j * mBlockSize < screenWidth; j++)
		{

			DrawGraph(mBgXOffset + j * mBlockSize,
				mBgYOffset + i * mBlockSize,
				mImgHandle, true);
		}
	}

	//背景2nd pass
	// 縮小→ぼかしバッファ転送
	GraphFilterBlt( mScreenBuffer, mReduceScreen, DX_GRAPH_FILTER_DOWN_SCALE, 2);
	GraphFilterBlt( mReduceScreen, mBlurScreenBuffer, DX_GRAPH_FILTER_GAUSS, 2, 200);

	// ぼかし→スクリーンバッファにフィルタなしで転送
	SetDrawScreen( mScreenBuffer );
	DrawExtendGraph( 0, 0, 800, 600, mBlurScreenBuffer, FALSE );

	//バックバッファ通常描画 
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();

	// y座標 : 上画面外から、下画面外になるまでループ
	for (int i = 0; mBgYOffset + i * mBlockSize < screenHeight; i++)
	{
		// x座標 : 左画面外から右画面外になるまでループ
		for (int j = 0; mBgXOffset + j * mBlockSize < screenWidth; j++)
		{

			DrawGraph(mBgXOffset + j * mBlockSize,
				mBgYOffset + i * mBlockSize,
				mImgHandle, true);
		}
	}

	//半透明ウィンドウ処理
	float yAnimOffset;
	yAnimOffset = easeInOutExponential(-800.0f, 0.0f, mStartUpAnimCount);

	// ぼかし下地描画
	DrawRectGraph(60, 60 + (int)yAnimOffset,
		          60, 60 + (int)yAnimOffset,
		          screenWidth - 120, 540 + (int)yAnimOffset - 60,
		          mScreenBuffer, FALSE, FALSE);

	// 背景処理
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 32);
	// 半透明黒を重ねて描画
	DrawBox(60, 60 + (int)yAnimOffset, screenWidth - 60, 540 + (int)yAnimOffset, 0xff000033, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 32);

	// ステージ文字描画
	for(int i = 0; i < mStageNumMax; i++)
	{
		//選択ステージのみ文字色変える
		if (mStageNo - 1 == i)
		{
			GAMEINSTANCE.systemText.setFontColor(255, 0, 0);
		}
		else
		{
			//非選択時の文字表示
			GAMEINSTANCE.systemText.setFontColor(255, 255, 255);

			// ステージ名称描画
			GAMEINSTANCE.systemText.textDraw( (int)mpMenuNowPos[i].x,
										      (int)mpMenuNowPos[i].y,
				                                   stageName[i]);
			continue;
		}

		// 選択後の点滅処理
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