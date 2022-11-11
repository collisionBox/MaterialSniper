#include "questions.h"

Quest05Seq::Quest05Seq()
{
	mImgHandle1 = LoadGraph("image/block0.bmp");
	mImgHandle2 = LoadGraph("image/block1.bmp");
}


Quest05Seq::~Quest05Seq()
{
	if (mImgHandle1 != -1)
	{
		DeleteGraph(mImgHandle1);
	}

	if (mImgHandle2 != -1)
	{
		DeleteGraph(mImgHandle2);
	}

}

Sequence* Quest05Seq::move()
{
	// スペースキーが押されたら次のクエストのシーケンスを作成してシーケンスチェンジ
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest06Seq;
	}

	// 現行シーケンス続行
	return this;
}


void Quest05Seq::draw()
{
	static int alpha = 0;
	const int maxcolor = 255;

	const int blockSize = 64;
	const int maxWidthIndex = GAMEINSTANCE.getScreenWidth() / blockSize + 1;
	const int maxHeightIndex = GAMEINSTANCE.getScreenHeight() / blockSize + 1;

	//透明度アニメーション
	alpha++;
	if (alpha > maxcolor)
	{
		alpha = 0;
	}


	ClearDrawScreen();


	int i, j;

	// 背景を書く


	for (i = 0; i < maxHeightIndex; i++)
	{
		for (j = 0; j < maxWidthIndex; j++)
		{
			DrawGraph(j * blockSize, i* blockSize, mImgHandle1, false);
		}
	}

	//半透明物体を描く
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	DrawGraph(100, 100, mImgHandle2, true);

	//半透明描画モードを通常モードへ戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #05.");
	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Quest.");

}