#include <ScenesPusher.h>
#include <SceneManager.h>
#include <SecondScene.h>
#include <StartScene.h>

void El_Horno::ScenePusher::pushScenes()
{
	SceneManager::getInstance()->allScenes.emplace("prueba", SceneManager::getInstance()->addScene<SecondScene>);
	SceneManager::getInstance()->allScenes.emplace("start", SceneManager::getInstance()->addScene<StartScene>);
}
