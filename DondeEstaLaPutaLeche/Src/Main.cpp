#include <iostream>
#include <StartScene.h>
#include <Windows.h>

extern "C"
{
	_declspec(dllexport) El_Horno::Scene* loadStartScene() {
		El_Horno::StartScene* start = new El_Horno::StartScene();
		start->init();
		return start;
	}
}