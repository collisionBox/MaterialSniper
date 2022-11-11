#include "underConstruction.h"
#include "questions.h"

UnderConstructionSeq::UnderConstructionSeq()
{
	mImgHandle = LoadGraph("image/block0.bmp");
}


UnderConstructionSeq::~UnderConstructionSeq()
{
	if (mImgHandle != -1)
	{
		DeleteGraph(mImgHandle);
	}

}
Sequence* UnderConstructionSeq::move()
{
	// スペースキーが押されたら次のクエストのシーケンスを作成してシーケンスチェンジ
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new QuestSelector;
	}

	return this;
}


void UnderConstructionSeq::draw()
{
	ClearDrawScreen();

	int i, j;

	const int blockSize = 64;
	const int maxWidthIndex = GAMEINSTANCE.getScreenWidth() / blockSize + 1;
	const int maxHeightIndex = GAMEINSTANCE.getScreenHeight() / blockSize + 1;

	for (i = 0; i < maxHeightIndex; i++)
	{
		for (j = 0; j < maxWidthIndex; j++)
		{
			DrawGraph(j * blockSize, i* blockSize, mImgHandle, false);
		}
	}

	GAMEINSTANCE.systemText.textDraw(100, 300, "THIS QUESTION IS UNDER CONSTRUCTION.\n\n Please wait until it is completed.");

	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION ---");
	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key");
}
