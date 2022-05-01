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
#include "UILayout.h"

#include "Patrol.h"
#include "EntityId.h"
#include "FoodCartComponent.h"
#include "PlayerController.h"
#include "PlayerInteract.h"
#include "CashRegister.h"
#include "GameManager.h"
#include "UIMenus.h"

void El_Horno::GameComponentPusher::pushGameComponents()
{
	SceneManager::getInstance()->possibleComponents.emplace("transform", &SceneManager::getInstance()->createComponent<Transform>);
	SceneManager::getInstance()->possibleComponents.emplace("mesh", &SceneManager::getInstance()->createComponent<Mesh>);
	SceneManager::getInstance()->possibleComponents.emplace("animatorController", &SceneManager::getInstance()->createComponent<AnimatorController>);
	SceneManager::getInstance()->possibleComponents.emplace("audioComponent", &SceneManager::getInstance()->createComponent<AudioComponent>);
	SceneManager::getInstance()->possibleComponents.emplace("audioListener", &SceneManager::getInstance()->createComponent<AudioListenerComponent>);
	SceneManager::getInstance()->possibleComponents.emplace("camera", &SceneManager::getInstance()->createComponent<CameraComponent>);
	SceneManager::getInstance()->possibleComponents.emplace("light", &SceneManager::getInstance()->createComponent<LightComponent>);
	SceneManager::getInstance()->possibleComponents.emplace("particleSystem", &SceneManager::getInstance()->createComponent<ParticleSystem>);
	SceneManager::getInstance()->possibleComponents.emplace("rigidbody", &SceneManager::getInstance()->createComponent<RigidBody>);
	SceneManager::getInstance()->possibleComponents.emplace("uilayout", &SceneManager::getInstance()->createComponent<UILayout>);

	SceneManager::getInstance()->possibleComponents.emplace("patrol", &SceneManager::getInstance()->createComponent<Patrol>);
	SceneManager::getInstance()->possibleComponents.emplace("entityId", &SceneManager::getInstance()->createComponent<EntityId>);
	SceneManager::getInstance()->possibleComponents.emplace("foodCart", &SceneManager::getInstance()->createComponent<FoodCartComponent>);
	SceneManager::getInstance()->possibleComponents.emplace("playerController", &SceneManager::getInstance()->createComponent<PlayerController>);
	SceneManager::getInstance()->possibleComponents.emplace("playerInteract", &SceneManager::getInstance()->createComponent<PlayerInteract>);
	SceneManager::getInstance()->possibleComponents.emplace("cashRegister", &SceneManager::getInstance()->createComponent<CashRegister>);
	SceneManager::getInstance()->possibleComponents.emplace("gamemanager", &SceneManager::getInstance()->createComponent<GameManager>);
	SceneManager::getInstance()->possibleComponents.emplace("uimenus", &SceneManager::getInstance()->createComponent<UIMenus>);
	//ComponentPusher::pushComponents();
}
