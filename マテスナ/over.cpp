#include "over.h"

Over::Over()
{
}

Over::~Over()
{
}

SceneBase* Over::Update(float& gameTime, float& deltaTime)
{
	WaitTimer(30);

	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		WaitTimer(30);
		return new Title;
	}
	if (CheckHitKey(KEY_INPUT_TAB))
	{
		WaitTimer(30);
		return new Game;
	}
	WaitTimer(30);
	return this;

}

void Over::Draw()
{
	DrawFormatString(100, 100, white, "%d", target.GetPoint());
	DrawFormatString(100, 300, white, "title:space\nretry:tab");
}

