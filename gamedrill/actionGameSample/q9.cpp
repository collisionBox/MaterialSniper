#include "questions.h"

Quest09Seq::Quest09Seq()
{
	//リングバッファのインデックス
	mNowIndex = 0;
	mPrevIndex = m_maxBuf - 1;

	mNowEnterKeyState = 0;
	mPrevEneterKeyState = 0;

	//リングバッファ初期化
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
	// スペースキーが押されたら次のクエストのシーケンスを作成してシーケンスチェンジ
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest10Seq;
	}

	// リングバッファの参照を一つ進める
	mNowIndex++;
	mPrevIndex++;

	// 現在のリングバッファインデックスが末尾まで行ったら先頭戻す
	if (mNowIndex == m_maxBuf)
		mNowIndex = 0;

	// ひとつ前のリングバッファインデックスが末尾にに行ったら先頭戻す
	if (mPrevIndex == m_maxBuf)
		mPrevIndex = 0;


	// エンターキーの現在の状態とひとつ前のフレームの状態を保存
	mPrevEneterKeyState = mNowEnterKeyState;
	mNowEnterKeyState = CheckHitKey(KEY_INPUT_RETURN);

	//キーが押されているログを作成

	// キーがオフ状態
	if (mPrevEneterKeyState == 0 && mNowEnterKeyState == 0)
	{
		mKeyLogRingBuffer[mNowIndex] = KEY_OFF;
	}

	// 今離れた
	if (mPrevEneterKeyState == 1 && mNowEnterKeyState == 0)
	{
		mKeyLogRingBuffer[mNowIndex] = KEY_PULLUP;
	}

	// 今押された
	if (mPrevEneterKeyState == 0 && mNowEnterKeyState == 1)
	{
		mKeyLogRingBuffer[mNowIndex] = KEY_PUSH_DOWN;
	}

	//ずっと押されている
	if (mPrevEneterKeyState == 1 && mNowEnterKeyState == 1)
	{
		mKeyLogRingBuffer[mNowIndex] = KEY_PRESSED;
	}

	// 現行シーケンス続行
	return this;
}


void Quest09Seq::draw()
{
	ClearDrawScreen();

	GAMEINSTANCE.systemText.textDraw(100, 30, "PUSH ENTER KEY!");

	//ログ全表示
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

//インデックス値よりキーの状態変数を返す
KEY_STATE Quest09Seq::indexToKeyState(int index)
{
	// 現在のインデックス値からindex分前の値。
	index = (m_maxBuf + mNowIndex - index) % m_maxBuf ;
	return mKeyLogRingBuffer[index];
}