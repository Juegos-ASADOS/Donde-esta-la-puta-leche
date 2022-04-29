#include <iostream>
#include <StartScene.h>
#include <Windows.h>
#include <GameFactories.h>
#include <SceneManager.h>
#include <GameComponentPusher.h>

extern "C"
{

	_declspec(dllexport) void addGameFactories() {
		El_Horno::Game::addFactories();
	}

	_declspec(dllexport) El_Horno::Scene* loadStartScene() {
		El_Horno::StartScene* start = new El_Horno::StartScene();
		El_Horno::SceneManager::getInstance()->setScene(start);
		El_Horno::GameComponentPusher::pushGameComponents();
		start->init("prueba");
		return start;
	}
}