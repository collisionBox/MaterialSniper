#include "questions.h"

Quest04Seq::Quest04Seq()
{
	// 画像読み込み
	//    引数は ↓ ファイル名, 総枚数, 横方向枚数, 縦方向枚数, 横pixelサイズ, 縦pixelサイズ, イメージID格納用配列の先頭アドレス
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

	// フレームがm_inervalで設定されているフレーム毎に
	if (frame % mInterval == 0)
	{
		//アニメーション1枚進める
		mAnimCounter++;
		
		//アニメーションが枚数超えたら戻す
		if (mAnimCounter >= mMaxAnimnum)
		{
			mAnimCounter = 0;
		}
	}

	// スペースキーが押されたら次のクエストのシーケンスを作成してシーケンスチェンジ
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest05Seq;
	}

	// 現行シーケンス続行
	return this;
}


void Quest04Seq::draw()
{
	ClearDrawScreen();

	DrawGraph(300, 300, mImgHandle[mAnimCounter], true);

	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #04.");
	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Quest.");
}