#include "GameFactories.h"
#include "GameManager.h"
#include "Rigibody.h"
#include "Entity.h"
#include "Timer.h"
#include "ElHornoBase.h"
#include "btBulletCollisionCommon.h"

using namespace El_Horno;

GameManager* GameManager::instance_ = 0;

GameManager* GameManager::getInstance()
{
	if (instance_ == 0)
		return nullptr;

	return instance_;
}

bool GameManager::setupInstance()
{
	if (instance_ == 0) {
		instance_ = new GameManager();
		return true;
	}
	return false;
}

void GameManager::erase()
{
	delete instance_;
}

void El_Horno::GameManager::start()
{
	gameState_ = GameState::MAINMENU;
	listComplete_ = false;
}

void El_Horno::GameManager::update()
{
	if (gameState_ == GameState::RUNNING && gameTimer_->getTime() >= maxTime_) {
		//Game over
	}
}

// Establece los parametros iniciales de scene
void El_Horno::GameManager::setLevel(float maxTime, std::map<std::string, int> list)
{
	maxTime_ = maxTime;
	list_ = list;

	gameTimer_->resetTimer();
}

// Busca la id en la lista, si está, resta uno a second. Si no está
// o está a 0 devuelve false
bool El_Horno::GameManager::checkObject(std::string objectId)
{
	auto it = list_.find(objectId);
	if (it != list_.end() && it->second > 0) {
		//Lo puedo meter
		it->second -= 1;
		return true;
	}
	return false;
}

// Activa o desactiva la pausa y el gameTimer
// en consecuencia (IGUAL HAY QUE CAMBIAR ESTO
// A QUE UTILICE EL DELTATIME)
void El_Horno::GameManager::togglePaused()
{
	if (gameState_ == GameState::RUNNING) {
		gameState_ = GameState::PAUSED;

		maxTime_ -= gameTimer_->getTime();
	}
	else if (gameState_ == GameState::PAUSED) {
		gameState_ = GameState::RUNNING;

		gameTimer_->resetTimer();
	}
}
