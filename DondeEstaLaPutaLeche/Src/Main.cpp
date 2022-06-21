#include <Windows.h>
#include <GameFactories.h>
#include <SceneManager.h>
#include <GameComponentPusher.h>
#include <ScenesPusher.h>
#include <Scene.h>

extern "C"
{

	_declspec(dllexport) void addGameFactories() {
		El_Horno::Donde_Esta_La_Puta_Leche::addFactories();
	}

	_declspec(dllexport) El_Horno::Scene* loadStartScene() {
		El_Horno::Scene* start = new El_Horno::Scene();
		El_Horno::SceneManager::getInstance()->setScene(start);
		El_Horno::Donde_Esta_La_Puta_Leche::GameComponentPusher::pushGameComponents();
		El_Horno::Donde_Esta_La_Puta_Leche::ScenePusher::pushScenes();
		start->init("inicio");
		//start->testScene();
		return start;
	}
}