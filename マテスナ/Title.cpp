#include "Title.h"


Title::Title()
{
	titleFontHandle = CreateFontToHandle(NULL, 400, 4);
}
Title::~Title()
{
}

SceneBase* Title::Update(float& gameTime, float& deltaTime)
{

	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		return new Game;
	}
	return this;
}

void Title::Draw()
{
	DrawFormatStringFToHandle(0, 0, white, titleFontHandle, "TITLE");
}
