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
	//サウンド停止
	StopSoundMem(mSndHandle1);
	StopSoundMem(mSndHandle2);

	//サウンドメモリ解放
	if (mSndHandle1 != -1)
	{
		DeleteSoundMem(mSndHandle1);
	}
	//サウンドメモリ解放
	if (mSndHandle2 != -1)
	{
		DeleteSoundMem(mSndHandle2);
	}

}
Sequence* Quest10Seq::move()
{
	//初回音楽が再生されていなかったら再生
	if (!mbNowPlay1 && mSndHandle1 != -1)
	{
		mbNowPlay1 = true;
		PlaySoundMem(mSndHandle1, DX_PLAYTYPE_LOOP);
	}

	//エンターキーでサウンド再生
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

	// スペースキーが押されたら次のクエストのシーケンスを作成してシーケンスチェンジ
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest11_14Seq;
	}

	// 現行シーケンス続行
	return this;
}


void Quest10Seq::draw()
{
	int time, min,sec,msec;
	char buf[256];

	ClearDrawScreen();

	//再生中表示
	if (mbNowPlay1)
	{
		//再生タイムを取得
		time = GetSoundCurrentTime(mSndHandle1);

		//秒,分、ミリ秒を計算
		sec = time / 1000;
		min = sec / 60;
		sec -= min * 60;

		// ミリ秒算出(１０ミリ秒単位っぽい)
		msec = (time - sec * 1000 - min * 60000) / 10;

		sprintf(buf, "[ %02d'%02d\"%02d ] : SOUND PLAYING ( LOOP ).",min, sec, msec);
		GAMEINSTANCE.systemText.textDraw(100, 300, buf);
	}

	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #10.");

	GAMEINSTANCE.systemText.textDraw(100, 260, "PUSH ENTER KEY TO SOUND FX.");


	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Question.");

}