#pragma once
#include "game.h"
#include "sceneBase.h"
//Game.h
#if 1

class Scene 
{
public:
	~Scene();
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
	void SetScene(SceneBase* scene) { nowScene = scene; }

	int Update(float& gameTime, float& deltaTime);
	void Draw();
	class SceneBase* nowScene;
};
#define GAMEINSTANCE Scene::GetInstance()
#endif // 0
