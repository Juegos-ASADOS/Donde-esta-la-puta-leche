#include "StartScene.h"

#include <OgreVector.h>
#include <Entity.h>
#include <Transform.h>
#include <LightComponent.h>
#include <CameraComponent.h>
#include <AudioComponent.h>
#include <AudioListenerComponent.h>
#include <ParticleSystem.h>
//#include <UIPushButton.h>
#include <Rigibody.h>
#include <Mesh.h>
#include <AnimatorController.h>
#include <SinbadAnimTest.h>
#include <iostream>
#include <HornoVector3.h>
#include <FactoryCreator.h>
#include <PlayerController.h>
#include <PlayerInteract.h>
#include <EntityId.h>
#include <HornoVector3.h>
#include <EstanteryEnter.h>
#include <Patrol.h>
#include <vector>
#include <LuaManager.h>
#include <SceneManager.h>

namespace El_Horno {
	void StartScene::init(std::string name)
	{
		name_ = name;
		testScene();
	}

	void StartScene::testScene()
	{
		Entity* light = addEntity("light", "prueba");
		light->addComponent<Transform>("transform", HornoVector3(0, 200, 0), HornoVector3(0, 0, 0), HornoVector3(0, 0, 0));
		light->addComponent<LightComponent>("light", 0, HornoVector3(0, 0, 0));

		Entity* a = addEntity("camera", "prueba");
		HornoVector3 p = { 10,10,10 };
		a->addComponent<Transform>("transform", HornoVector3(0, 0, 0), HornoVector3(0, 0, 0), HornoVector3(0, 0, 0));
		a->addComponent<CameraComponent>("camera", HornoVector3(0, 100, 450), HornoVector3(0, 0, 0), HornoVector3(0, 0.3, 0.5), 1, 5, 10000);
		a->addComponent<AudioListenerComponent>("audioListener");

		Entity* b = addEntity("player", "prueba");
		b->addComponent<Transform>("transform", HornoVector3(-50, 40, 0), HornoVector3(0, 0, 0), p);
		b->addComponent<Mesh>("mesh", "Sinbad");
		b->addComponent<RigidBody>("rigidbody", 2.0f, false, false, 0);
		/*b->addComponent<AnimatorController>("animatorController");
		b->addComponent<SinbadAnimTest>("sinbadAnimTest");*/
		b->addComponent<AudioComponent>("audioComponent");
		b->addComponent<PlayerController>("playercontroller", 300.0f);
		//b->addComponent<EstanteryEnter>("estanteryenter");

		Entity* playerChild = addEntity("playerTrigger", "prueba", b);
		playerChild->addComponent<Transform>("transform", HornoVector3(0, 0, 0), HornoVector3(0, 0, 0), HornoVector3(5, 5, 5));
		playerChild->addComponent<RigidBody>("rigidbody", 2.0f, true, true, 0);
		playerChild->addComponent<PlayerInteract>("playerinteract");

		b = addEntity("object", "prueba");
		b->addComponent<Transform>("transform", HornoVector3(0, -15, 0), HornoVector3(0, 0, 0), HornoVector3(15, 0.1, 15));
		b->addComponent<Mesh>("mesh", "cube");
		b->addComponent<RigidBody>("rigidbody", 0.0f, false, false, 0);

		//b = addEntity("esmoque", "prueba");
		//b->addComponent<Transform>("transform", HornoVector3(250, 10, 0), HornoVector3(0, 0, 0), p);
		//b->addComponent<ParticleSystem>("particleSystem", "smoke", "Smoke", 10, true);

		b = addEntity("estantery", "prueba");
		b->addComponent<Transform>("transform", HornoVector3(50, 10, 0), HornoVector3(0, 0, 0), HornoVector3(0.5, 1, 0.25));
		b->addComponent<Mesh>("mesh", "cube");
		b->addComponent<RigidBody>("rigidbody", 0.0f, false, false, 0);
		b->addComponent<EntityId>("entityid", "Agua", true);

		Entity* stanChild = addEntity("estanteryTrigger", "prueba", b);
		stanChild->addComponent<Transform>("transform", HornoVector3(-50, 0, 0), HornoVector3(0, 0, 0), HornoVector3(5, 5, 5));
		stanChild->addComponent<RigidBody>("rigidbody", 0.0f, true, false, 0);
		
		std::vector<HornoVector3> patata; 

		patata.push_back(HornoVector3(-150, 10, 0));
		patata.push_back(HornoVector3(-250, 10, 0));
		patata.push_back(HornoVector3(-250, 10, -100));
		patata.push_back(HornoVector3(-150, 10, -100));

		b = addEntity("moneco", "prueba");
		b->addComponent<Transform>("transform", HornoVector3(-150, 10, 0), HornoVector3(0, 0, 0), HornoVector3(0.5, 0.5, 0.5));
		b->addComponent<Mesh>("mesh", "penguin");
		b->addComponent<RigidBody>("rigidbody", 3.0f, false, false, 0);
		b->addComponent<Patrol>("patrol", 50, patata);

		LuaManager::getInstance()->loadScene();
		
		//b = addEntity("button1", "prueba");
		//b->addComponent<Transform>("transform", HornoVector3(0,0,0), HornoVector3(0, 0, 0), HornoVector3(0, 0, 0));
		//b->addComponent<UIPushButton>("pushbutton", "TaharezLook", 0.05f, 0.05f, 0.2f, 0.1f, "push1");

		std::cout << "ESCENA CARGADA\n";
	}
}