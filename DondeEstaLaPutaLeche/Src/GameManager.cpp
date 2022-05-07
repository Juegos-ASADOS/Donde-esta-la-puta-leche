#include "GameFactories.h"
#include "GameManager.h"
#include "InputManager.h"
#include "LuaManager.h"
#include "UIManager.h"
#include "SecondScene.h"
#include "SceneManager.h"
#include "AudioManager.h"
#include "Rigibody.h"
#include "Transform.h"
#include "Entity.h"
#include "Timer.h"
#include "UIMenus.h"
#include "ElHornoBase.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace El_Horno;

GameManager* GameManager::instance_ = 0;

El_Horno::GameManager::GameManager()
{
	LuaManager::getInstance()->readLuaScript("prefabs");
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
		instance_ = SceneManager::getInstance()->getCurrentScene()->getEntity("gamemanager")->getComponent<GameManager>("gamemanager");
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

			tutorialShown_ = 3;
		}
		else if (parameters[i].first == "productNum") {
			productNum_ = stoi(parameters[i].second);
			maxProducts_ = productNum_;

			wrongProducts_ = 0;
			win_ = false;
		}
		else if (parameters[i].first == "maxTime") {
			maxTime_ = stoi(parameters[i].second);
		}
		else if (parameters[i].first == "list") {

			list_.clear();

			std::istringstream in(parameters[i].second);
			std::string val;
			std::vector<std::string> values;
			while (std::getline(in, val, ','))
			{
				values.push_back(val);
			}

			for (size_t e = 0; e < values.size(); e += 2) {
				list_.emplace(std::pair<std::string, int>(values[e], stoi(values[e + 1])));
			}

			gameTimer_->resetTimer();

			resetList();
			setList();
		}
	}
}

void El_Horno::GameManager::start()
{
	if (setupInstance()) {

		input_ = ElHornoBase::getInstance()->getInputManager();

		if (interfaz_ == nullptr) {
			interfaz_ = SceneManager::getInstance()->getCurrentScene()->addEntity("interfaz", "interfaces");
			interfaz_->addComponent<UIMenus>("uimenus");
			interfaz_->getComponent<UIMenus>("uimenus")->init();
			interfaz_->setDontDestryOnLoad(true);
		}
	}
}

void El_Horno::GameManager::update()
{
	if (gameState_ == GameState::RUNNING) {
		if (tutorialShown_ == 3) {
			showTutorial("Inico");
			tutorialShown_--;
		}
		else if (tutorialShown_ == 2 && (input_->getKeyDown(SDL_SCANCODE_E) || input_->isButtonDown(SDL_CONTROLLER_BUTTON_X))) {
			hideTutorial();
			showTutorial("Baldas");
			tutorialShown_--;
		}
		else if (tutorialShown_ == 1 && (input_->getKeyDown(SDL_SCANCODE_E) || input_->isButtonDown(SDL_CONTROLLER_BUTTON_X))) {
			hideTutorial();
			tutorialShown_--;
		}

	//actualizar la ui del reloj

		string var = "Nivel_Ingame";
		LuaManager::getInstance()->pushString(var, "layout");
		var = "Reloj/Texto_Reloj";
		LuaManager::getInstance()->pushString(var, "child");
		int tiempo = maxTime_ - gameTimer_->getTime();
		var = (((tiempo / 60 < 10) ? "0" : "") + to_string(tiempo / 60) + ":" + ((tiempo % 60 < 10) ? "0" : "") + to_string((tiempo % 60)));
		LuaManager::getInstance()->pushString(var, "hora");
		LuaManager::getInstance()->callLuaFunction("setLayoutWidgetText");


		//comprobacion del pause

		if (input_->getKeyDown(SDL_SCANCODE_ESCAPE)) 
			togglePaused();	
		//AudioManager::getInstance()->SetChannel3dPosition(AudioManager::getInstance()->getMusicChannel(), SceneManager::getInstance()->getCurrentScene()->getEntity("camera")->getComponent<Transform>("transform")->getPosition())
		/*if (tiempo == (maxTime_ / 3.0f*2))
		{
			AudioManager::getInstance()->stopMusic();
			AudioManager::getInstance()->playSound("Musica/Nivel.mp3", HornoVectorToFmod(HornoVector3(0, 100, 450)), 50.0f, true);

		}
		else if (tiempo == maxTime_ / 3.0f) {
			AudioManager::getInstance()->stopMusic();
			AudioManager::getInstance()->playSound("Musica/Nivel.mp3", HornoVectorToFmod(HornoVector3(0, 100, 450)), 50.0f, true);
		}*/
	}


	if (gameState_ == GameState::RUNNING && gameTimer_->getTime() >= maxTime_) {
		gameState_ = GameState::MAINMENU;
		ElHornoBase::getInstance()->pause();

		//Game over
		endingEggs_ = 0;

		// Escena final sin puntuaci�n
		UIManager::getInstance()->setLayoutVisibility("Derrota", true);
		UIManager::getInstance()->showMouseCursor();
	}
	else if (gameState_ == GameState::RUNNING && win_) {
		gameState_ = GameState::MAINMENU;
		ElHornoBase::getInstance()->pause();


		//Ganar
		endingEggs_ = 1;

		if (gameTimer_->getTime() <= (maxTime_ / 3) * 2)
			endingEggs_++;
		if (wrongProducts_ <= maxProducts_ / 4)
			endingEggs_++;

		//Pasar a la escena de score teniendo en cuenta la puntuaci�n (huevos)
		UIManager::getInstance()->setLayoutVisibility("Victoria", true);
		UIManager::getInstance()->showMouseCursor();
		for (int i = 0; i < endingEggs_; i++) {
			UIManager::getInstance()->subscribeLayoutChildVisibility("Victoria", "Ovo" + to_string(i + 1), true);
		}
		//win_ = false;
	}
	if (input_->isKeyDown(SDL_SCANCODE_J)) {
		win_ = true;
		gameState_ = GameState::RUNNING;
	}
	/*if (input_->isKeyDown(SDL_SCANCODE_K)) {
		LuaManager::getInstance()->callLuaFunction("loadNextScene");
		return;
	}*/
}

void El_Horno::GameManager::pauseUpdate()
{

	//capaz no queremos ahcer esto pero idk
	if (gameState_ == GameState::PAUSED) {
		if (input_->getKeyDown(SDL_SCANCODE_ESCAPE))
			togglePaused();
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

// Busca la id en la lista, si est�, resta uno a second. Si no est�
// o est� a 0 devuelve false y a�ade un producto erroneo
bool El_Horno::GameManager::checkObject(std::string objectId)
{
	auto it = list_.find(objectId);
	if (it != list_.end() && it->second > 0) {
		//Lo puedo meter
		it->second -= 1;
		productNum_--;

		// Tacha de la lista
		if (it->second <= 0) {
			checkProductUI(objectId, distance(list_.begin(), list_.find(objectId)) + 1);
		}

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
	ElHornoBase::getInstance()->pause();
	if (gameState_ == GameState::RUNNING) {

		UIManager::getInstance()->setLayoutVisibility("Pausa", true);
		gameState_ = GameState::PAUSED;
		UIManager::getInstance()->showMouseCursor();
		maxTime_ -= gameTimer_->getTime();
		AudioManager::getInstance()->pauseAllChannels();
	}
	else if (gameState_ == GameState::PAUSED || gameState_ == GameState::MAINMENU) {
		gameState_ = GameState::RUNNING;
		UIManager::getInstance()->setLayoutVisibility("Pausa", false);
		UIManager::getInstance()->setLayoutVisibility("Pausa_Opciones", false);
		gameTimer_->resetTimer();
		AudioManager::getInstance()->resumeAllChannels();
	}
}

// Comprueba si est�n todos los objetos en el carro
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
	return 100 - (((float)productNum_ - (float)paidFood) / (float)maxProducts_ * 100);
}

void El_Horno::GameManager::paidFoodMum()
{
	//Todos los que hay - los que te faltan por comprar = los que has llevado a la madre
	paidFood = maxProducts_ - productNum_;
}


// UI //
// METODOS PARA MODIFICAR LA UI
// UI //
void El_Horno::GameManager::setList()
{
	// Recorremos el mapa de la lista
	int i = 1;
	for (auto product : list_)
	{
		// Poner imagen del producto
		std::string name = "Producto_" + std::to_string(i);
		UIManager::getInstance()->setChildProperty("Nivel_Ingame", name, "Image", "DondeTaLeche/" + product.first);

		// Poner la cantidad de ese producto
		std::string cant = "Num_" + std::to_string(i);
		if (product.second > 1)
			UIManager::getInstance()->setChildProperty("Nivel_Ingame", cant, "Image", "DondeTaLeche/X" + std::to_string(product.second));
		i++;
	}

}
//Resetea todos los elementos de la lista a vacio
void El_Horno::GameManager::resetList()
{
	// Recorremos el mapa de la lista
	for (int i = 1; i < MAX_PRODUCTOS; i++)
	{
		// Poner imagen vacia
		std::string name = "Producto_" + std::to_string(i);
		UIManager::getInstance()->setChildProperty("Nivel_Ingame", name, "Image", "DondeTaLeche/Producto_Vacio");

		// Poner la imagen vacia
		std::string cant = "Num_" + std::to_string(i);
		UIManager::getInstance()->setChildProperty("Nivel_Ingame", cant, "Image", "DondeTaLeche/Producto_Vacio");

		// Poner la imagen vacia
		std::string tick = "Tick_" + std::to_string(i);
		UIManager::getInstance()->setChildProperty("Nivel_Ingame", tick, "Image", "DondeTaLeche/Producto_Vacio");
	}

}

// Sacamos el ticket de espera
void El_Horno::GameManager::setTicketIntro()
{
	UIManager::getInstance()->setChildProperty("Nivel_Ingame", "Ticket_Espera", "Visible", "true");
}

// Tu turno
void El_Horno::GameManager::setTicketTurno()
{
	UIManager::getInstance()->setChildProperty("Nivel_Ingame", "Ticket_Espera", "Visible", "false");
	UIManager::getInstance()->setChildProperty("Nivel_Ingame", "Ticket", "Visible", "true");
}

// Tu turno
void El_Horno::GameManager::setTicketLimite()
{
	UIManager::getInstance()->setChildProperty("Nivel_Ingame", "Ticket", "Visible", "false");
	UIManager::getInstance()->setChildProperty("Nivel_Ingame", "Ticket_Paso", "Visible", "true");
}

// Esconder tickets
void El_Horno::GameManager::hideTicket()
{
	UIManager::getInstance()->setChildProperty("Nivel_Ingame", "Ticket_Paso", "Visible", "false");
	UIManager::getInstance()->setChildProperty("Nivel_Ingame", "Ticket", "Visible", "false");
}

// Se llama cuando hay que poner un tick en la lista, se le pasa el nombre y la pos en el mapa
void El_Horno::GameManager::checkProductUI(std::string productId, int i)
{
	UIManager::getInstance()->setChildProperty("Nivel_Ingame", "Tick_" + std::to_string(i), "Visible", "true");
}

// Se usa para enseñar un tutorial
// strings =  Inicio, Baldas, Fruta, Pescado, Carne 
void El_Horno::GameManager::showTutorial(std::string name)
{
	UIManager::getInstance()->setChildProperty("Nivel_Ingame", "Tutorial", "Visible", "true");
	UIManager::getInstance()->setChildProperty("Nivel_Ingame", "Tutorial_" + name, "Visible", "true");
	actualTuto_ = name;
}

// Se usa para esconder el tutorial actual
void El_Horno::GameManager::hideTutorial()
{
	UIManager::getInstance()->setChildProperty("Nivel_Ingame", "Tutorial", "Visible", "false");
	UIManager::getInstance()->setChildProperty("Nivel_Ingame", "Tutorial_" + actualTuto_, "Visible", "false");
	actualTuto_ = "";
}

