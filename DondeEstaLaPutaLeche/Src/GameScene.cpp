#include "GameScene.h"
#include <OgreVector.h>
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
#include <SinbadAnimTest.h>
#include <iostream>
#include <HornoVector3.h>
#include <FactoryCreator.h>
#include <PlayerController.h>
#include <EntityId.h>
#include <EstanteryEnter.h>
#include <LuaManager.h>

namespace El_Horno {

	void GameScene::init()
	{
	}

	void GameScene::createPlayer(lua_State* L)
	{
		//LuaRef n = LuaManager::getInstance()->getFromLua("scene");


	}

	void GameScene::createLight(lua_State* L)
	{
		int n = LuaManager::getInstance()->luaGetTop(L);
	}

	void GameScene::createCamera(lua_State* L)
	{
		int n = LuaManager::getInstance()->luaGetTop(L);
	}

	void GameScene::createObject(lua_State* L)
	{
		int n = LuaManager::getInstance()->luaGetTop(L);
	}

	void GameScene::createEstantery(lua_State* L)
	{
		int n = LuaManager::getInstance()->luaGetTop(L);
	}

	//void GameScene::createPlayer(HornoVector3 pos, HornoVector3 rot, HornoVector3 scale, std::string mesh,
	//	float mass, int collisionShape, float speed)
	//{
	//	Entity* b = addEntity("player", name_);
	//	b->addComponent<Transform>("transform", pos, rot, scale);
	//	b->addComponent<Mesh>("mesh", mesh);
	//	b->addComponent<RigidBody>("rigidbody", mass, false, false, collisionShape);
	//	/*b->addComponent<AnimatorController>("animatorController");
	//	b->addComponent<SinbadAnimTest>("sinbadAnimTest");*/
	//	b->addComponent<AudioComponent>("audioComponent");
	//	b->addComponent<PlayerController>("playercontroller", speed);
	//	b->addComponent<EstanteryEnter>("estanteryenter");
	//}

	//void GameScene::createLight(HornoVector3 pos, HornoVector3 rot, HornoVector3 scale, int lightType, HornoVector3 dirLight)
	//{
	//	Entity* light = addEntity("light", name_);
	//	light->addComponent<Transform>("transform", pos, rot, scale);
	//	light->addComponent<LightComponent>("light", lightType, dirLight);
	//}

	//// transform pos y camara pos - aclaracion
	//// a->addComponent<Transform>("transform", HornoVector3(0, 0, 0), HornoVector3(0, 0, 0), HornoVector3(0, 0, 0));
	//// a->addComponent<CameraComponent>("camera", HornoVector3(0, 100, 450), HornoVector3(0, 0, 0), HornoVector3(0, 0.3, 0.5), 1, 5, 10000);
	//void GameScene::createCamera(HornoVector3 pos, HornoVector3 rot, HornoVector3 scale, HornoVector3 camPos, 
	//	HornoVector3 lookAt, HornoVector3 color, float alpha, int nearDist, int farDist)
	//{
	//	Entity* a = addEntity("camera", name_);
	//	a->addComponent<Transform>("transform", pos, rot, scale);
	//	a->addComponent<CameraComponent>("camera", camPos, lookAt, color, alpha, nearDist, farDist);
	//	a->addComponent<AudioListenerComponent>("audioListener");
	//}

	//void GameScene::createObject(HornoVector3 pos, HornoVector3 rot, HornoVector3 scale, std::string mesh,
	//	float mass, bool isTrigger, bool isKinematic, int collisionShape)
	//{
	//	Entity* b = addEntity("object", name_);
	//	b->addComponent<Transform>("transform", pos, rot, scale);
	//	b->addComponent<Mesh>("mesh", mesh);
	//	b->addComponent<RigidBody>("rigidbody", mass, isTrigger, isKinematic, collisionShape);
	//}

	//void GameScene::createEstantery(HornoVector3 pos, HornoVector3 rot, HornoVector3 scale, std::string mesh,
	//	int collisionShape, std::string id, HornoVector3 triggerPos, HornoVector3 triggerRot, 
	//	HornoVector3 triggerScale, int triggerCollisionShape)
	//{
	//	Entity* b = addEntity("estantery", name_);
	//	b->addComponent<Transform>("transform", pos, rot, scale);
	//	b->addComponent<Mesh>("mesh", mesh);
	//	b->addComponent<RigidBody>("rigidbody", 0.0f, false, false, collisionShape);
	//	b->addComponent<EntityId>("entityid", id, true);

	//	Entity* stanChild = addEntity("estanteryTrigger", name_, b);
	//	stanChild->addComponent<Transform>("transform", triggerPos, triggerRot, triggerScale);
	//	stanChild->addComponent<RigidBody>("rigidbody", 0.0f, true, false, triggerCollisionShape);
	//}
}