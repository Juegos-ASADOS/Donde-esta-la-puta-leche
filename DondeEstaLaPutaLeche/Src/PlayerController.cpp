#include "GameFactories.h"
#include "PlayerController.h"
#include "Rigibody.h"
#include "Entity.h"
#include "InputManager.h"
#include "ElHornoBase.h"
#include "btBulletCollisionCommon.h"
#include "iostream"

void El_Horno::PlayerController::start()
{
	rb_ = entity_->getComponent<RigidBody>("rigidbody");
	rb_->setAngularFactor(0.0f);
	rb_->setSleepingThresholds(0, 0);
	rb_->setFriction(50);
	input_ = ElHornoBase::getInstance()->getInputManager();
}

void El_Horno::PlayerController::update()
{
	float x = -speed_ * input_->isKeyDown(SDL_SCANCODE_A) + speed_ * input_->isKeyDown(SDL_SCANCODE_D);
	float z = -speed_ * input_->isKeyDown(SDL_SCANCODE_S) + speed_ * input_->isKeyDown(SDL_SCANCODE_W);

	auto force = btVector3(x, 0, -z);

	if(maxForce_ > rb_->getLinearVelocity().length())
		rb_->applyForce(force);

	//TODO Aplicar la rotacion
	
	//std::cout << rb_->getLinearVelocity().length() << "\n" << rb_->getLinearVelocity().x() << " " << rb_->getLinearVelocity().y() << " " << rb_->getLinearVelocity().z() <<"\n";
}
