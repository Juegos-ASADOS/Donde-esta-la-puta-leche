#include <GameComponentPusher.h>
#include <ComponentPusher.h>
#include <SceneManager.h>

#include "Transform.h"
#include "Mesh.h"
#include "AnimatorController.h"
#include "AudioComponent.h"
#include "AudioListenerComponent.h"
#include "CameraComponent.h"
#include "LightComponent.h"
#include "ParticleSystem.h"
#include "Rigibody.h"

#include "Patrol.h"
#include "EntityId.h"
#include "EstanteryEnter.h"
#include "FoodCartComponent.h"
#include "PlayerController.h"
#include "PlayerInteract.h"
#include "CashRegister.h"
#include "GameManager.h"

void El_Horno::GameComponentPusher::pushGameComponents()
{
	SceneManager::getInstance()->possibleComponents.emplace("transform", &SceneManager::getInstance()->createComponent<Transform>);
	SceneManager::getInstance()->possibleComponents.emplace("mesh", &SceneManager::getInstance()->createComponent<Mesh>);
	SceneManager::getInstance()->possibleComponents.emplace("animatorcontroller", &SceneManager::getInstance()->createComponent<AnimatorController>);
	SceneManager::getInstance()->possibleComponents.emplace("audiocomponent", &SceneManager::getInstance()->createComponent<AudioComponent>);
	SceneManager::getInstance()->possibleComponents.emplace("audiolistener", &SceneManager::getInstance()->createComponent<AudioListenerComponent>);
	SceneManager::getInstance()->possibleComponents.emplace("camera", &SceneManager::getInstance()->createComponent<CameraComponent>);
	SceneManager::getInstance()->possibleComponents.emplace("light", &SceneManager::getInstance()->createComponent<LightComponent>);
	SceneManager::getInstance()->possibleComponents.emplace("particlesystem", &SceneManager::getInstance()->createComponent<ParticleSystem>);
	SceneManager::getInstance()->possibleComponents.emplace("rigidbody", &SceneManager::getInstance()->createComponent<RigidBody>);
	//SceneManager::getInstance()->possibleComponents.emplace("uipushbutton", &SceneManager::getInstance()->createComponent<UIPushButton>);

	SceneManager::getInstance()->possibleComponents.emplace("patrol", &SceneManager::getInstance()->createComponent<Patrol>);
	SceneManager::getInstance()->possibleComponents.emplace("entityid", &SceneManager::getInstance()->createComponent<EntityId>);
	SceneManager::getInstance()->possibleComponents.emplace("estanteryenter", &SceneManager::getInstance()->createComponent<EstanteryEnter>);
	SceneManager::getInstance()->possibleComponents.emplace("foodcart", &SceneManager::getInstance()->createComponent<FoodCartComponent>);
	SceneManager::getInstance()->possibleComponents.emplace("playercontroller", &SceneManager::getInstance()->createComponent<PlayerController>);
	SceneManager::getInstance()->possibleComponents.emplace("playerinteract", &SceneManager::getInstance()->createComponent<PlayerInteract>);
	SceneManager::getInstance()->possibleComponents.emplace("cashregister", &SceneManager::getInstance()->createComponent<CashRegister>);
	SceneManager::getInstance()->possibleComponents.emplace("gamemanager", &SceneManager::getInstance()->createComponent<GameManager>);
	//ComponentPusher::pushComponents();
}
