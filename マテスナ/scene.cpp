#include "environment.h"
#include "scene.h"
#if 1


Scene::~Scene()
{
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
		return 1;
	}
	return 0;
}
#endif // 0

void Scene::Draw()
{
	if (!nowScene)
	{
		return;
	}
	nowScene->Draw();
}