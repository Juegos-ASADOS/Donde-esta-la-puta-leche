#include <GameComponentPusher.h>
#include <ComponentPusher.h>
#include <SceneManager.h>
#include "Patrol.h"
#include "EntityId.h"
#include "EstanteryEnter.h"
#include "FoodCartComponent.h"
#include "PlayerController.h"
#include "PlayerInteract.h"
#include "CashRegister.h"
#include "GameManager.h"

void El_Horno::GameComponentPusher::pushComponents()
{
	SceneManager::getInstance()->possibleComponents.emplace("patrol", &SceneManager::getInstance()->createComponent<Patrol>);
	SceneManager::getInstance()->possibleComponents.emplace("entityid", &SceneManager::getInstance()->createComponent<EntityId>);
	SceneManager::getInstance()->possibleComponents.emplace("estanteryenter", &SceneManager::getInstance()->createComponent<EstanteryEnter>);
	SceneManager::getInstance()->possibleComponents.emplace("foodcart", &SceneManager::getInstance()->createComponent<FoodCartComponent>);
	SceneManager::getInstance()->possibleComponents.emplace("playercontroller", &SceneManager::getInstance()->createComponent<PlayerController>);
	SceneManager::getInstance()->possibleComponents.emplace("playerinteract", &SceneManager::getInstance()->createComponent<PlayerInteract>);
	SceneManager::getInstance()->possibleComponents.emplace("cashregister", &SceneManager::getInstance()->createComponent<CashRegister>);
	SceneManager::getInstance()->possibleComponents.emplace("gamemanager", &SceneManager::getInstance()->createComponent<GameManager>);
	ComponentPusher::pushComponents();
}
