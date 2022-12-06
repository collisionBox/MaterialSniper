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
	WaitTimer(30);
	return this;

}

void Over::Draw()
{
	DrawFormatString(100, 100, white, "%d", target.GetPoint());
}

