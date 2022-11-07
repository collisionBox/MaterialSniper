#include "environment.h"
#include "scene.h"

Scene::~Scene()
{
}

void Scene::Draw()
{
	if (!nowScene)
	{
		return;
	}
	nowScene->Draw();
}

int Scene::Update()
{
	if (!nowScene)
	{
		return 0;
	}

	SceneBase* tmpScene;
	tmpScene = nowScene->Update();
	if (tmpScene != nowScene)
	{
		delete nowScene;
		nowScene = tmpScene;
		return true;
	}
	return false;
}
