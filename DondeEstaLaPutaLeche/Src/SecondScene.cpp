#include "SecondScene.h"

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
#include <iostream>
#include <HornoVector3.h>
#include <FactoryCreator.h>
#include <PlayerController.h>
#include <PlayerInteract.h>
#include <EntityId.h>
#include <HornoVector3.h>
#include <Patrol.h>
#include <vector>
#include <LuaManager.h>
#include <SceneManager.h>
#include <GameManager.h>
#include "UIMenus.h"

namespace El_Horno {
	void SecondScene::init(std::string name)
	{
		name_ = name;
		//testScene();
		LuaManager::getInstance()->loadScene();
	}

	void SecondScene::testScene()
	{
		// GameManager
		Entity* a = addEntity("gamemanager", "prueba");
		a->addComponent<Transform>("transform", HornoVector3(0, 0, 0), HornoVector3(0, 0, 0), HornoVector3(0, 0, 0));
		a->addComponent<GameManager>("gamemanager");

		// Light
		a = addEntity("light", "prueba");
		a->addComponent<Transform>("transform", HornoVector3(0, 200, 200), HornoVector3(0, 0, 0), HornoVector3(0, 0, 0));
		a->addComponent<LightComponent>("light", 1, HornoVector3(0, 0, 0));

		// Camera
		Entity* cam = addEntity("camera", "prueba");
		HornoVector3 p = { 10,10,10 };
		cam->addComponent<Transform>("transform", HornoVector3(0, 0, 0), HornoVector3(0, 0, 0), HornoVector3(0, 0, 0));
		cam->addComponent<CameraComponent>("camera", HornoVector3(0, 100, 450), HornoVector3(0, 0, 0), HornoVector3(0, 0.3, 0.5), 1, 5, 10000);
		cam->addComponent<AudioListenerComponent>("audioListener");

		// Player
		a = addEntity("player", "prueba");
		a->addComponent<Transform>("transform", HornoVector3(-50, 15, 0), HornoVector3(0, 0, 0), p);
		cam->getComponent<CameraComponent>("camera")->setFollow(a->getComponent<Transform>("transform"), 0.2f, HornoVector3(50, 60, 450));
		a->addComponent<Mesh>("mesh", "pipo");
		a->addComponent<RigidBody>("rigidbody", 2.0f, false, false, 0);
		a->addComponent<AudioComponent>("audioComponent");
		a->addComponent<PlayerController>("playercontroller", 1500.0f);
		a->addComponent<PlayerInteract>("playerinteract");

		////Carro hijo del player
		Entity* ba = addEntity("cart", "prueba", a);
		ba->addComponent<Transform>("transform", HornoVector3(0, 0, 2.5), HornoVector3(0, 0, 0), HornoVector3(0.02, 0.02, 0.02));
		ba->addComponent<Mesh>("mesh", "cube");
		ba->addComponent<RigidBody>("rigidbody", 2.0f, true, true, 0);

		//Trigger del carrito
		Entity* trig = addEntity("cartTrigger", "prueba", ba);
		trig->addComponent<Transform>("transform", HornoVector3(0, 0, 0), HornoVector3(0, 0, 0), HornoVector3(3.5, 3, 3.5));
		trig->addComponent<RigidBody>("rigidbody", 1.0f, true, true, 0);
		trig->addComponent<EntityId>("entityid", Type::CART);

		//Creacion maquina de estados animator
		std::vector<std::pair<std::string, std::string>> animVector;
		animVector.push_back(std::pair<std::string, std::string>("Idle_with_cart", "walk_with_cart"));
		animVector.push_back(std::pair<std::string, std::string>("walk_with_cart", "Idle_with_cart"));
		animVector.push_back(std::pair<std::string, std::string>("Idle", "walk"));
		animVector.push_back(std::pair<std::string, std::string>("walk", "Idle"));
		animVector.push_back(std::pair<std::string, std::string>("Idle_with_product", "walk_with_product"));
		animVector.push_back(std::pair<std::string, std::string>("walk_with_product", "Idle_with_product"));
		animVector.push_back(std::pair<std::string, std::string>("AnyState", "Idle"));
		animVector.push_back(std::pair<std::string, std::string>("AnyState", "Idle_with_product"));
		animVector.push_back(std::pair<std::string, std::string>("AnyState", "Idle_with_cart"));
		a->addComponent<AnimatorController>("animatorController", animVector);

		//b->addComponent<EstanteryEnter>("estanteryenter");
		/*Entity* playerChild = addEntity("playerTrigger", "prueba", b);
		playerChild->addComponent<Transform>("transform", HornoVector3(0, 0, 0), HornoVector3(0, 0, 0), HornoVector3(5, 5, 5));
		playerChild->addComponent<RigidBody>("rigidbody", 2.0f, true, false, 0);*/

		a = addEntity("object", "prueba");
		a->addComponent<Transform>("transform", HornoVector3(0, -15, 0), HornoVector3(0, 0, 0), HornoVector3(15, 0.1, 15));
		a->addComponent<Mesh>("mesh", "cube");
		a->addComponent<RigidBody>("rigidbody", 0.0f, false, false, 0);

		//b = addEntity("esmoque", "prueba");
		//b->addComponent<Transform>("transform", HornoVector3(250, 10, 0), HornoVector3(0, 0, 0), p);
		//b->addComponent<ParticleSystem>("particleSystem", "smoke", "Smoke", 10, true);

		// Estanteria pescado
		a = addEntity("festantery", "prueba");
		a->addComponent<Transform>("transform", HornoVector3(0, 10, 450), HornoVector3(0, 0, 0), HornoVector3(0.5, 1, 0.25));
		a->addComponent<Mesh>("mesh", "cube");
		a->addComponent<RigidBody>("rigidbody", 0.0f, false, false, 0);

		Entity* trigger = addEntity("festanteryTrigger", "prueba", a);
		trigger->addComponent<Transform>("transform", HornoVector3(0, 0, 0), HornoVector3(0, 0, 0), HornoVector3(5, 5, 5));
		trigger->addComponent<RigidBody>("rigidbody", 0.0f, true, false, 0);
		trigger->addComponent<EntityId>("entityid", Type::ESTANTERY, ProductType::FISH, "Agua");

		// Estanteria normal
		a = addEntity("mestantery", "prueba");
		a->addComponent<Transform>("transform", HornoVector3(150, 10, 450), HornoVector3(0, 0, 0), HornoVector3(0.5, 1, 0.25));
		a->addComponent<Mesh>("mesh", "cube");
		a->addComponent<RigidBody>("rigidbody", 0.0f, false, false, 0);

		trigger = addEntity("mestanteryTrigger", "prueba", a);
		trigger->addComponent<Transform>("transform", HornoVector3(0, 0, 0), HornoVector3(0, 0, 0), HornoVector3(5, 5, 5));
		trigger->addComponent<RigidBody>("rigidbody", 0.0f, true, false, 0);
		trigger->addComponent<EntityId>("entityid", Type::ESTANTERY, ProductType::DEFAULT, "Agua");

		// Estanteria fruta
		a = addEntity("frestantery", "prueba");
		a->addComponent<Transform>("transform", HornoVector3(-150, 10, 450), HornoVector3(0, 0, 0), HornoVector3(0.5, 1, 0.25));
		a->addComponent<Mesh>("mesh", "cube");
		a->addComponent<RigidBody>("rigidbody", 0.0f, false, false, 0);

		trigger = addEntity("frestanteryTrigger", "prueba", a);
		trigger->addComponent<Transform>("transform", HornoVector3(0, 0, 0), HornoVector3(0, 0, 0), HornoVector3(5, 5, 5));
		trigger->addComponent<RigidBody>("rigidbody", 0.0f, true, false, 0);
		trigger->addComponent<EntityId>("entityid", Type::ESTANTERY, ProductType::FRUIT, "Agua");

		std::vector<PatrolPos> patata;

		patata.push_back({ HornoVector3(-150, 10, 0), 1 });
		patata.push_back({ HornoVector3(-250, 10, 0), 1 });
		patata.push_back({ HornoVector3(-250, 10, -100), 1 });
		patata.push_back({ HornoVector3(-150, 10, -100), 1 });

		// NPC
		a = addEntity("moneco", "prueba");
		a->addComponent<Transform>("transform", HornoVector3(-150, 10, 0), HornoVector3(0, 0, 0), HornoVector3(0.5, 0.5, 0.5));
		a->addComponent<Mesh>("mesh", "penguin");
		a->addComponent<RigidBody>("rigidbody", 3.0f, false, false, 0);
		a->addComponent<Patrol>("patrol", 50, patata);

		/*a = addEntity("menu", "prueba");
		a->addComponent<Transform>("transform", HornoVector3(0, 0, 0), HornoVector3(0, 0, 0), HornoVector3(1, 1, 1));
		a->addComponent<UIMenus>("uimenus");*/
		/*std::vector<std::pair<std::string, std::string>> animVectorNpc;
		animVectorNpc.push_back(std::pair<std::string, std::string>("Idle", "npc_walk"));
		animVectorNpc.push_back(std::pair<std::string, std::string>("npc_walk", "Idle"));
		animVectorNpc.push_back(std::pair<std::string, std::string>("AnyState", "Idle"));
		b->addComponent<AnimatorController>("animatorController", animVectorNpc);*/

		//b = addEntity("button1", "prueba");
		//b->addComponent<Transform>("transform", HornoVector3(0,0,0), HornoVector3(0, 0, 0), HornoVector3(0, 0, 0));
		//b->addComponent<UIPushButton>("pushbutton", "TaharezLook", 0.05f, 0.05f, 0.2f, 0.1f, "push1");

		// Caja Registradora
		a = addEntity("cashRegister", "prueba");
		a->addComponent<Transform>("transform", HornoVector3(0, 15, -300), HornoVector3(0, 0, 0), HornoVector3(0.5, 1.5, 0.25));
		a->addComponent<Mesh>("mesh", "cube");
		a->addComponent<RigidBody>("rigidbody", 0.0f, false, false, 0);

		// Trigger de la caja
		trigger = addEntity("cashTrigger", "prueba", a);
		trigger->addComponent<Transform>("transform", HornoVector3(0, 0, 0), HornoVector3(0, 0, 0), HornoVector3(5, 5, 5));
		trigger->addComponent<RigidBody>("rigidbody", 0.0f, true, false, 0);
		trigger->addComponent<EntityId>("entityid", Type::CASHREGISTER);

		//// Carrito
		//a = addEntity("cartInstance", "prueba");
		//a->addComponent<Transform>("transform", HornoVector3(-100, 10, -300), HornoVector3(0, 0, 0), HornoVector3(0.2, 0.2, 0.2));
		//a->addComponent<Mesh>("mesh", "cube");
		//a->addComponent<RigidBody>("rigidbody", 200.0f, false, false, 0);

		//// Trigger del carrito
		//trigger = addEntity("cartTriggerInstance", "prueba", a);
		//trigger->addComponent<Transform>("transform", HornoVector3(0, 0, 0), HornoVector3(0, 0, 0), HornoVector3(3.5, 3, 3.5));
		//trigger->addComponent<RigidBody>("rigidbody", 0.0f, true, true, 0);
		//trigger->addComponent<EntityId>("entityid", Type::CART);

		// Estacion de tickets
		a = addEntity("meatticket", "prueba");
		a->addComponent<Transform>("transform", HornoVector3(150, 10, 300), HornoVector3(0, 0, 0), HornoVector3(0.5, 1, 0.25));
		a->addComponent<Mesh>("mesh", "cube");
		a->addComponent<RigidBody>("rigidbody", 0.0f, false, false, 0);

		trigger = addEntity("ticketTrigger", "prueba", a);
		trigger->addComponent<Transform>("transform", HornoVector3(00, 0, 0), HornoVector3(0, 0, 0), HornoVector3(5, 5, 5));
		trigger->addComponent<RigidBody>("rigidbody", 0.0f, true, false, 0);
		trigger->addComponent<EntityId>("entityid", Type::MEATTICKET);

		// Pescado
		a = addEntity("fishcleaner", "prueba");
		a->addComponent<Transform>("transform", HornoVector3(0, 10, 300), HornoVector3(0, 0, 0), HornoVector3(0.5, 1, 0.25));
		a->addComponent<Mesh>("mesh", "cube");
		a->addComponent<RigidBody>("rigidbody", 0.0f, false, false, 0);

		trigger = addEntity("fishTrigger", "prueba", a);
		trigger->addComponent<Transform>("transform", HornoVector3(00, 0, 0), HornoVector3(0, 0, 0), HornoVector3(5, 5, 5));
		trigger->addComponent<RigidBody>("rigidbody", 0.0f, true, false, 0);
		trigger->addComponent<EntityId>("entityid", Type::FISHCLEANER);

		// Bascula
		a = addEntity("weighingmachine", "prueba");
		a->addComponent<Transform>("transform", HornoVector3(-150, 10, 300), HornoVector3(0, 0, 0), HornoVector3(0.5, 1, 0.25));
		a->addComponent<Mesh>("mesh", "cube");
		a->addComponent<RigidBody>("rigidbody", 0.0f, false, false, 0);

		trigger = addEntity("weighingTrigger", "prueba", a);
		trigger->addComponent<Transform>("transform", HornoVector3(00, 0, 0), HornoVector3(0, 0, 0), HornoVector3(5, 5, 5));
		trigger->addComponent<RigidBody>("rigidbody", 0.0f, true, false, 0);
		trigger->addComponent<EntityId>("entityid", Type::WHEIGHINGMACHINE);

		// Estaci�n de recogida de carne
		a = addEntity("meatstation", "prueba");
		a->addComponent<Transform>("transform", HornoVector3(250, 10, 300), HornoVector3(0, 0, 0), HornoVector3(0.5, 1, 0.25));
		a->addComponent<Mesh>("mesh", "cube");
		a->addComponent<RigidBody>("rigidbody", 0.0f, false, false, 0);

		trigger = addEntity("stationTrigger", "prueba", a);
		trigger->addComponent<Transform>("transform", HornoVector3(0, 0, 0), HornoVector3(0, 0, 0), HornoVector3(5, 5, 5));
		trigger->addComponent<RigidBody>("rigidbody", 0.0f, true, false, 0);
		trigger->addComponent<EntityId>("entityid", Type::MEATSTATION);

		//charco
		a = addEntity("puddle", "prueba");
		a->addComponent<Transform>("transform", HornoVector3(300, 10, 20), HornoVector3(0, 0, 0), HornoVector3(5, 5, 5));
		a->addComponent<RigidBody>("rigidbody", 0.0f, true, false, 0);
		a->addComponent<EntityId>("entityid", Type::PUDDLE);

		//LuaManager::getInstance()->loadScene();

		std::cout << "ESCENA CARGADA\n";
	}
}