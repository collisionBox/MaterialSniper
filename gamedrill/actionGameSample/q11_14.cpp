#include "questions.h"

Quest11_14Seq::Quest11_14Seq()
{
	mScore     = 0;   // スコア
	mAimScore  = 0;   // 目標スコア
	mCountdown = 10;  // カウントダウン
	mCountup   = 0;   // カウントアップ
	mMin       = 0;   // 分

	mTime = mNowTime = GetNowCount();
}


Quest11_14Seq::~Quest11_14Seq()
{
}
Sequence* Quest11_14Seq::move()
{
	// スペースキーが押されたら次のクエストのシーケンスを作成してシーケンスチェンジ
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest15Seq;
	}

	//１秒(1000ミリ秒以上)経過したか？
	mNowTime = GetNowCount();
	if (mNowTime - mTime > 1000)
	{
		//タイマーを一秒増やす
		mCountup++;

		//タイマーを1秒減らす
		mCountdown--;

		//1分経った時の処理
		if (mCountup % 60 == 0)
		{
			mCountup = 0;
			mMin++;
		}

		//カウントダウン0以下になったら0に戻す。
		if (mCountdown < 0)
			mCountdown = 0;

		//5秒おきにスコア100点プラス
		if (mCountup % 5 == 0)
		{
			mAimScore += 100;
		}

		//計測基準を現在にセット
		mTime = mNowTime;
	}

	//1秒以下～小数点第二位までの秒数を算出
	mMiliSec = (mNowTime - mTime) / 10;

	//スコアを目標スコアに足していく処理
	if (mAimScore != mScore)
		mScore += 2;

	// 現行シーケンス続行
	return this;
}


void Quest11_14Seq::draw()
{
	ClearDrawScreen();

	char buf[256];

	//スコア表示
	sprintf(buf, "SCORE : %5d", mScore );
	GAMEINSTANCE.systemText.textDraw(200, 200, buf);

	//カウントダウンタイマー
	sprintf(buf, "COUNT DOWN TIMER : [ %2d ]", mCountdown );
	if (mCountdown == 0)
	{
		GAMEINSTANCE.systemText.setFontColor(255, 0, 0);
	}
	GAMEINSTANCE.systemText.textDraw(200, 250, buf);

	//カウントアップタイマー
	GAMEINSTANCE.systemText.setFontColor(255, 255, 255);
	sprintf(buf, "TIME : [ %02d' %02d\" %02d ]", mMin, mCountup,mMiliSec);
	GAMEINSTANCE.systemText.textDraw(200, 300, buf);

	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #11,12,13,14.");
	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Question.");

}