#include "GameFactories.h"
#include "GameManager.h"
#include "InputManager.h"
#include "LuaManager.h"
#include "UIManager.h"
#include "SecondScene.h"
#include "SceneManager.h"
#include "Rigibody.h"
#include "Entity.h"
#include "Timer.h"
#include "ElHornoBase.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace El_Horno;

GameManager* GameManager::instance_ = 0;

El_Horno::GameManager::GameManager()
{
	gameTimer_ = new Timer();
	gameState_ = GameState::MAINMENU;
}

El_Horno::GameManager::~GameManager()
{
	if (this == instance_) {
		instance_ = nullptr;
	}
	else {
		delete instance_;
	}
	
	if (gameTimer_ != nullptr)
		delete gameTimer_; gameTimer_ = nullptr;
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

void El_Horno::GameManager::setParameters(std::vector<std::pair<std::string, std::string>> parameters)
{
	for (int i = 0; i < parameters.size(); i++) {
		if (parameters[i].first == "state") {
			gameState_ = (GameState)stoi(parameters[i].second);
		}
		else if (parameters[i].first == "productNum") {
			productNum_ = stoi(parameters[i].second);
			maxProducts_ = productNum_;
		}
		else if (parameters[i].first == "maxTime") {
			maxTime_ = stoi(parameters[i].second);
		}
		else if (parameters[i].first == "list") {

			std::istringstream in(parameters[i].second);
			std::string val;
			std::vector<std::string> values;
			while (std::getline(in, val, ','))
			{ values.push_back(val); }

			for (size_t e = 0; e < values.size(); e+=2) {
				list_.emplace(std::pair<std::string, int>(values[e], stoi(values[e + 1])));
			}
		}
	}
}

void El_Horno::GameManager::start()
{
	input_ = ElHornoBase::getInstance()->getInputManager();
	setupInstance();

	wrongProducts_ = 0;
	win_ = false;

	gameTimer_->resetTimer();
}

void El_Horno::GameManager::update()
{
	//actualizar la ui del reloj
	if (gameState_ == GameState::RUNNING) {

		string var = "Nivel_Ingame";
		LuaManager::getInstance()->pushString(var, "layout");
		var = "Reloj/Texto_Reloj";
		LuaManager::getInstance()->pushString(var, "child");


		int tiempo = maxTime_ - gameTimer_->getTime();

		var = (((tiempo / 60 < 10) ? "0" : "") + to_string(tiempo / 60) + ":" + ((tiempo % 60 < 10) ? "0" : "") + to_string((tiempo % 60)));

		//std::cout << var <<"\n";

		LuaManager::getInstance()->pushString(var, "hora");

		LuaManager::getInstance()->callLuaFunction("setLayoutWidgetText");
	}


	if (gameState_ == GameState::RUNNING && gameTimer_->getTime() >= maxTime_) {
		//Game over
		endingEggs_ = 0;

		// Escena final sin puntuación
		UIManager::getInstance()->setLayoutVisibility("Derrota", true);
		gameState_ == GameState::MAINMENU;
		list_.clear();
	}
	else if (gameState_ == GameState::RUNNING && win_) {
		//Ganar
		endingEggs_ = 1;

		if (gameTimer_->getTime() <= (maxTime_/3)*2)
			endingEggs_++;
		if (wrongProducts_ <= maxProducts_ / 4)
			endingEggs_++;

		//Pasar a la escena de score teniendo en cuenta la puntuación (huevos)

		UIManager::getInstance()->setLayoutVisibility("Victoria", true);

		for (int i = 0; i < endingEggs_; i++) {
			UIManager::getInstance()->subscribeLayoutChildVisibility("Victoria", "Ovo" + to_string(i + 1), true);
		}
		gameState_ == GameState::MAINMENU;
		//win_ = false;
		list_.clear();
	}
	if (input_->isKeyDown(SDL_SCANCODE_J)) {
		//win_ = true;
		gameState_ = GameState::RUNNING;
	}
	if (input_->isKeyDown(SDL_SCANCODE_K)) {
		LuaManager::getInstance()->callLuaFunction("loadNextScene");
		return;
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

