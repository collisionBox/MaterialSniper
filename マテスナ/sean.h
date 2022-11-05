#pragma once

class Scene
{
public:
	~Scene();
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
private:
	void Draw();
	int Update();
	class SceneBase* nowScene;
};
#define GAMEINSTANCE Scene::GetInstance()
