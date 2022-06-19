#include "StartScene.h"

#include <Entity.h>
#include <Transform.h>
#include <LightComponent.h>
#include <CameraComponent.h>
#include <AudioComponent.h>
#include <AudioListenerComponent.h>
#include <ParticleSystem.h>
#include <Rigibody.h>
#include <Mesh.h>
#include <AnimatorController.h>
#include <FactoryCreator.h>
#include <PlayerController.h>
#include <PlayerInteract.h>
#include <EntityId.h>
#include <HornoVector3.h>
#include <Patrol.h>
#include <vector>
#include <LuaManager.h>
#include <SceneManager.h>
#include <AudioManager.h>
#include <GameManager.h>
#include "UIMenus.h"
#include "UIGame.h"

using namespace El_Horno;

void Donde_Esta_La_Puta_Leche::StartScene::init(std::string name)
{
	name_ = name;
	LuaManager::getInstance()->loadScene();
	AudioManager::getInstance()->stopMusic();
	AudioManager::getInstance()->playSound("Musica/Menu.mp3", HornoVectorToFmod(HornoVector3(0, 100, 0)), 50.0f, true);
}