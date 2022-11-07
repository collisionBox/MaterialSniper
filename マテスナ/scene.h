#pragma once
#include "game.h"
#include "sceneBase.h"
//Game.h

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
private:
	void Draw();
	int Update();
	class SceneBase* nowScene;
};
#define GAMEINSTANCE Scene::GetInstance()
