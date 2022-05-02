#include "GameFactories.h"
#include "PlayerController.h"
#include "Rigibody.h"
#include "Transform.h"
#include "Entity.h"
#include "InputManager.h"
#include "ElHornoBase.h"
#include "AnimatorController.h"
#include "iostream"
#include <cmath>

void El_Horno::PlayerController::setParameters(std::vector<std::pair<std::string, std::string>> parameters)
{
	for (int i = 0; i < parameters.size(); i++) {
		if (parameters[i].first == "speed") {
			speed_ = stof(parameters[i].second);
		}
		else if (parameters[i].first == "maxForce") {
			maxForce_ = stoi(parameters[i].second);
		}
	}
}

void El_Horno::PlayerController::start()
{
	//rb_ = entity_->getComponent<RigidBody>("rigidbody");
	//rb_->setAngularFactor(0.0f);
	//rb_->setSleepingThresholds(0, 0);
	////rb_->setFriction(150);
	////rb_->setDamping(0.7f, 0);
	//rb_->setScale(HornoVector3(0.5, 0.7, 0.5));
	input_ = ElHornoBase::getInstance()->getInputManager();
	anim_ = entity_->getComponent<AnimatorController>("animatorController");
	walking_ = false;
	offset_ = 60;
}

void El_Horno::PlayerController::update()
{
	if (rb_ == nullptr) {
		rb_ = entity_->getComponent<RigidBody>("rigidbody");
		rb_->setAngularFactor(0.0f);
		rb_->setSleepingThresholds(0, 0);
		//rb_->setFriction(150);
		//rb_->setDamping(0.7f, 0);
		rb_->setScale(HornoVector3(0.5, 0.7, 0.5));
	}

	if (input_->isKeyDown(SDL_SCANCODE_A) || input_->isKeyDown(SDL_SCANCODE_S) || input_->isKeyDown(SDL_SCANCODE_D) || input_->isKeyDown(SDL_SCANCODE_W)) {

		if(rb_->getDamping() != 0.7f && !sliding_)
			rb_->setDamping(0.7f, 0);


		// Animacion	
		if (!walking_)
		{
			anim_->setAnimBool("Idle", "walk", true);
			walking_ = true;
		}
	}
	else {
		if (rb_->getDamping() != 0.999f && !sliding_)
			rb_->setDamping(0.999f, 0);

		if (walking_) {
			anim_->setAnimBool("walk", "Idle", true);
			walking_ = false;
		}
	}

	float x = -speed_ * input_->isKeyDown(SDL_SCANCODE_A) + speed_ * input_->isKeyDown(SDL_SCANCODE_D);
	float z = -speed_ * input_->isKeyDown(SDL_SCANCODE_S) + speed_ * input_->isKeyDown(SDL_SCANCODE_W);
	if (maxForce_ > rb_->getHornoLinearVelocity().magnitude())
		rb_->applyForce(HornoVector3(x, 0, -z));

	//TODO Aplicar la rotacion
	if (x != 0 || z != 0) {
		//entity_->getComponent<Transform>("transform")->rotateY(atan(x/z)- entity_->getComponent<Transform>("transform")->getRotation().y);
		entity_->getComponent<Transform>("transform")->lookAt(HornoVector3(-x, entity_->getComponent<Transform>("transform")->getPosition().y, z));
	}
}
