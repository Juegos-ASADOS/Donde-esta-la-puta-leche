#include "SecondScene.h"

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
#include <HornoVector3.h>
#include <FactoryCreator.h>
#include <PlayerController.h>
#include <PlayerInteract.h>
#include <EntityId.h>
#include <Patrol.h>
#include <vector>
#include <LuaManager.h>
#include <SceneManager.h>
#include <GameManager.h>
#include <UIMenus.h>

using namespace El_Horno;

void Donde_Esta_La_Puta_Leche::SecondScene::init(std::string name)
{
	name_ = name;
	LuaManager::getInstance()->loadScene();
}
