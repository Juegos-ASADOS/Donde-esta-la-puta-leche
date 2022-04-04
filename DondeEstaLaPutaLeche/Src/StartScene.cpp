#include "StartScene.h"
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

namespace El_Horno {
	void StartScene::init()
	{
		Entity* light = addEntity("light", "prueba");
		light->addComponent<Transform>("transform", HornoVector3(0, 200, 0), HornoVector3(0, 0, 0), HornoVector3(0, 0, 0));
		light->addComponent<LightComponent>("light", 0, HornoVector3(0, 0, 0));

		Entity* a = addEntity("camera", "prueba");
		El_Horno::HornoVector3 p = { 10,10,10 };
		a->addComponent<Transform>("transform", El_Horno::HornoVector3(0, 0, 0), El_Horno::HornoVector3(0, 0, 0), El_Horno::HornoVector3(0, 0, 0));
		a->addComponent<CameraComponent>("camera", El_Horno::HornoVector3(0, 100, 450), El_Horno::HornoVector3(0, 0, 0), El_Horno::HornoVector3(0, 0.3, 0.5), 1, 5, 10000);
		a->addComponent<AudioListenerComponent>("audioListener");

		Entity* b = addEntity("object", "prueba");
		b->addComponent<Transform>("transform", El_Horno::HornoVector3(0, 150, 0), El_Horno::HornoVector3(0, 0, 0), p);
		b->addComponent<Mesh>("mesh", "Sinbad");
		b->addComponent<RigidBody>("rigidbody", 2.0f, false, false, 0);
		b->addComponent<AnimatorController>("animatorController");
		b->addComponent<SinbadAnimTest>("sinbadAnimTest");
		b->addComponent<AudioComponent>("audioComponent");

		b = addEntity("object2", "prueba");
		b->addComponent<Transform>("transform", El_Horno::HornoVector3(0, -15, 0), El_Horno::HornoVector3(0, 0, 0), El_Horno::HornoVector3(5, 0.1, 5));
		b->addComponent<Mesh>("mesh", "cube");
		b->addComponent<RigidBody>("rigidbody", 0.0f, false, false, 0);

		b = addEntity("esmoque", "prueba");
		b->addComponent<Transform>("transform", El_Horno::HornoVector3(250, 10, 0), El_Horno::HornoVector3(0, 0, 0), p);
		b->addComponent<ParticleSystem>("particleSystem", "smoke", "Smoke", 10, true);
		std::cout << "ESCENA CARGADA\n";
	}
}