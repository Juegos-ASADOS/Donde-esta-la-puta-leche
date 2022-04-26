#include "GameFactories.h"
#include "PlayerController.h"
#include "Rigibody.h"
#include "Entity.h"
#include "InputManager.h"
#include "ElHornoBase.h"
#include "btBulletCollisionCommon.h"
#include "AnimatorController.h"
#include "iostream"

void El_Horno::PlayerController::start()
{
	rb_ = entity_->getComponent<RigidBody>("rigidbody");
	rb_->setAngularFactor(0.0f);
	rb_->setSleepingThresholds(0, 0);
	rb_->setFriction(50);
	rb_->setScale(HornoVector3(0.5, 0.7, 0.5));
	input_ = ElHornoBase::getInstance()->getInputManager();
	anim_ = entity_->getComponent<AnimatorController>("animatorController");
	walking_ = false;

}

void El_Horno::PlayerController::update()
{
	float x = -speed_ * input_->isKeyDown(SDL_SCANCODE_A) + speed_ * input_->isKeyDown(SDL_SCANCODE_D);
	float z = -speed_ * input_->isKeyDown(SDL_SCANCODE_S) + speed_ * input_->isKeyDown(SDL_SCANCODE_W);

	auto force = btVector3(x, 0, -z);

	if(maxForce_ > rb_->getLinearVelocity().length())
		rb_->applyForce(force);

	// Animacion
	if (rb_->getLinearVelocity().length() > 1)
	{
		if (!walking_)
		{
			anim_->setAnimBool("Idle", "walk", true);
			walking_ = true;
		}
	}
	else if(walking_)
	{
		anim_->setAnimBool("walk", "Idle", true);
		walking_ = false;
	}

	//TODO Aplicar la rotacion
	
	//std::cout << rb_->getLinearVelocity().length() << "\n" << rb_->getLinearVelocity().x() << " " << rb_->getLinearVelocity().y() << " " << rb_->getLinearVelocity().z() <<"\n";
}
