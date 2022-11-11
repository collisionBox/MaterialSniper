#include "questions.h"

Quest02Seq::Quest02Seq()
{
	mImgHandle[0] = LoadGraph("image/block0.bmp");
	mImgHandle[1] = LoadGraph("image/block1.bmp");
}


Quest02Seq::~Quest02Seq()
{
	if (mImgHandle[0] != -1)
	{
		DeleteGraph(mImgHandle[0]);
	}

	if (mImgHandle[1] != -1)
	{
		DeleteGraph(mImgHandle[1]);
	}
}
Sequence* Quest02Seq::move()
{
	// スペースキーが押されたら次のクエストのシーケンスを作成してシーケンスチェンジ
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest03Seq;
	}

	return this;
}


void Quest02Seq::draw()
{
	ClearDrawScreen();

	int i, j;

	const int blockSize = 64;
	const int maxWidthIndex  = GAMEINSTANCE.getScreenWidth() / blockSize + 1;
	const int maxHeightIndex = GAMEINSTANCE.getScreenHeight() / blockSize + 1;

	for (i = 0; i < maxHeightIndex; i++)
	{
		for (j = 0; j < maxWidthIndex; j++)
		{
			DrawGraph(j * blockSize, i* blockSize, mImgHandle[(i + j) % 2], false);
		}
	}

	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #02.");
	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Quest.");
}
