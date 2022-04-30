#include "GameFactories.h"
#include "GameManager.h"
#include "Rigibody.h"
#include "Entity.h"
#include "Timer.h"
#include "ElHornoBase.h"
#include "btBulletCollisionCommon.h"

using namespace El_Horno;

GameManager* GameManager::instance_ = 0;

El_Horno::GameManager::GameManager()
{
	gameState_ = GameState::STARTSTATE;

	// Esto es para probar 
	list_.emplace(std::pair<string, int>("Agua", 1));
	productNum_ = 1;
	maxProducts_ = productNum_;
}

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
	setupInstance();
}

void El_Horno::GameManager::update()
{
	if (gameState_ == GameState::RUNNING && gameTimer_->getTime() >= maxTime_) {
		//Game over
		endingEggs_ = 0;

		// Escena final sin puntuación
	}
	else if (gameState_ == GameState::RUNNING && win_) {
		//Ganar
		endingEggs_ = 1;

		if (gameTimer_->getTime() <= (maxTime_/3)*2)
			endingEggs_++;
		if (wrongProducts_ <= maxProducts_ / 4)
			endingEggs_++;

		//Pasar a la escena de score teniendo en cuenta la puntuación (huevos)
	}
}

// Establece los parametros iniciales de scene
void El_Horno::GameManager::setLevel(float maxTime, std::map<std::string, int> list, int productNum)
{
	wrongProducts_ = 0;
	maxTime_ = maxTime;
	list_ = list;
	productNum_ = productNum;
	maxProducts_ = productNum;
	win_ = false;

	gameTimer_->resetTimer();

	if (gameState_ == GameState::STARTSTATE)
		gameState_ = GameState::MAINMENU;
	else if (gameState_ == GameState::MAINMENU)
		gameState_ = GameState::RUNNING;
	else if (gameState_ == GameState::RUNNING)
		gameState_ = GameState::MAINMENU;
}

// Busca la id en la lista, si está, resta uno a second. Si no está
// o está a 0 devuelve false y añade un producto erroneo
bool El_Horno::GameManager::checkObject(std::string objectId)
{
	auto it = list_.find(objectId);
	if (it != list_.end() && it->second > 0) {
		//Lo puedo meter
		it->second -= 1;
		productNum_--;
		return true;
	}
	wrongProducts_++;
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

// Comprueba si están todos los objetos en el carro
// para dar por valida la victoria
void El_Horno::GameManager::checkEnd()
{
	if (productNum_ <= 0)
		win_ = true;
}

// Comprueba el procentaje de productos en el carro para cambiar 
// la cantidad mostrada en la mesh
const float El_Horno::GameManager::getProductCompletionPercentaje()
{
	return 100 - ((productNum_ - paidFood) / maxProducts_ * 100);
}

void El_Horno::GameManager::paidFoodMum()
{
	//Todos los que hay - los que te faltan por comprar = los que has llevado a la madre
	paidFood = maxProducts_ - productNum_;
}

