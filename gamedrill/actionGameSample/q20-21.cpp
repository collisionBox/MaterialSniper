#include "questions.h"

Quest20_21Seq::Quest20_21Seq()
{
	mImgHandle = LoadGraph("image/fontG.png");
}

Quest20_21Seq::~Quest20_21Seq()
{
	if (mImgHandle != -1)
	{
		DeleteGraph(mImgHandle);
	}
}
Sequence* Quest20_21Seq::move()
{
	// スペースキーが押されたら次のクエストのシーケンスを作成してシーケンスチェンジ
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest22_23Seq;
	}

	// 現行シーケンス続行
	return this;
}


void Quest20_21Seq::draw()
{
	static int t = 0;
	t++;
	if (t > 255)
		t = 0;

	ClearDrawScreen();

	GAMEINSTANCE.systemText.textDraw(200, 60, "FONT.BMP DATA");
	DrawGraph(200, 100, mImgHandle, true);

	GAMEINSTANCE.systemText.setFontColor(255 - t, t, 127 + t / 2);
	GAMEINSTANCE.systemText.textDrawMessage(180, 320, "CHAR TEXT DATA TO BMP FONT\n& CHANGE COLOR\n\nABCDEFGHIJKLMNOPQRSTUVWXYZ\nabcdefghijklmnopqrstuvwxyz\n!\"#$%'()*+,-./:;<=>?^_{}~\\", t);
	GAMEINSTANCE.systemText.setFontColor(255, 255, 255);

	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #20-21.");
	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Question.");

}