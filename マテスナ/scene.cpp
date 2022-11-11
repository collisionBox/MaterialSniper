#include "environment.h"
#include "scene.h"
#if 1


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

int Scene::Update(float& gameTime, float& deltaTime)
{
	if (!nowScene)
	{
		return 0;
	}

	SceneBase* tmpScene;
	tmpScene = nowScene->Update(gameTime, deltaTime);
	if (tmpScene != nowScene)
	{
		delete nowScene;
		nowScene = tmpScene;
		return true;
	}
	return false;
}
#endif // 0
