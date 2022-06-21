#include <ScenesPusher.h>
#include <SceneManager.h>
#include <Scene.h>

using namespace El_Horno;
void Donde_Esta_La_Puta_Leche::ScenePusher::pushScenes()
{
	SceneManager::getInstance()->allScenes.emplace("prueba", SceneManager::getInstance()->addScene);
	SceneManager::getInstance()->allScenes.emplace("theEnd2", SceneManager::getInstance()->addScene);
	SceneManager::getInstance()->allScenes.emplace("ayuda", SceneManager::getInstance()->addScene);
	SceneManager::getInstance()->allScenes.emplace("start", SceneManager::getInstance()->addScene);
	SceneManager::getInstance()->allScenes.emplace("inicio", SceneManager::getInstance()->addScene);
}
