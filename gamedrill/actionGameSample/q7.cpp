#include "q7.h"
#include "questions.h"
#include <math.h>

Quest07Seq::Quest07Seq()
{
	mImgHandle = LoadGraph("image/block1.bmp");
}


Quest07Seq::~Quest07Seq()
{
	if (mImgHandle != -1)
	{
		DeleteGraph(mImgHandle);
	}
}
Sequence* Quest07Seq::move()
{
	// スペースキーが押されたら次のクエストのシーケンスを作成してシーケンスチェンジ
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest08Seq;
	}

	// 現行シーケンス続行
	return this;
}


void Quest07Seq::draw()
{
	char buf[256];
	static float angle = 0.0f;
	angle += 0.05f;

	static float exanim = 0.0f;
	exanim += 0.01f;

	ClearDrawScreen();
	DrawRotaGraph2(200, 100, 0, 0, 1.0, angle, mImgHandle, false, false);
	DrawRotaGraph2(200, 300, 32, 32, 1.0, angle, mImgHandle, false, false);
	DrawRotaGraph2(200, 500, 32, 32, 2.0f * sinf(exanim), angle, mImgHandle, false, false);

	sprintf(buf, "DrawRotaGraph center(0, 0) ExtRate = 1.0 \n angle = %3.2f", angle);
	GAMEINSTANCE.systemText.textDraw(10, 30, buf);

	sprintf(buf, "DrawRotaGraph center(32, 32) ExtRate = 1.0 \n angle = %3.2f", angle);
	GAMEINSTANCE.systemText.textDraw(10, 200, buf);

	sprintf(buf, "DrawRotaGraph ExtRate = %+3.2f angle = %3.2f", 2.0f * sinf(exanim), angle);
	GAMEINSTANCE.systemText.textDraw(10, 400, buf);

	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #07.");
	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Quest.");
}