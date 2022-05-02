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
	pState_ = El_Horno::PLAYER_CART;
	tb_ = entity_->getComponent<Transform>("transform");
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


		// Animacion idle->andar
		if (!walking_)
		{
			switch (pState_)
			{
			case El_Horno::PLAYER_DEFAULT:
				anim_->setAnimBool("Idle", "walk", true);
				break;
			case El_Horno::PLAYER_CART:
				anim_->setAnimBool("Idle_with_cart", "walk_with_cart", true);
				break;
			case El_Horno::PLAYER_PRODUCT:
				anim_->setAnimBool("Idle_with_product", "walk_with_product", true);
				break;
			default:
				break;
			}

			walking_ = true;
		}
	}
	else {
		if (rb_->getDamping() != 0.999f && !sliding_)
			rb_->setDamping(0.999f, 0);

		// Animacion andar->idle
		if (walking_) 
		{
			switch (pState_)
			{
			case El_Horno::PLAYER_DEFAULT:
				anim_->setAnimBool("walk", "Idle", true);
				break;
			case El_Horno::PLAYER_CART:
				anim_->setAnimBool("walk_with_cart", "Idle_with_cart", true);
				break;
			case El_Horno::PLAYER_PRODUCT:
				anim_->setAnimBool("walk_with_product", "Idle_with_product", true);
				break;
			default:
				break;
			}

			walking_ = false;
		}
	}

	bool left = (input_->getAxis(SDL_CONTROLLER_AXIS_LEFTX) < 0.0f || input_->isKeyDown(SDL_SCANCODE_A));
	bool right = (input_->getAxis(SDL_CONTROLLER_AXIS_LEFTX) > 0.0f || input_->isKeyDown(SDL_SCANCODE_D));
	bool up = (input_->getAxis(SDL_CONTROLLER_AXIS_LEFTY) < 0.0f || input_->isKeyDown(SDL_SCANCODE_W));
	bool down = (input_->getAxis(SDL_CONTROLLER_AXIS_LEFTY) > 0.0f || input_->isKeyDown(SDL_SCANCODE_S));
	float x = -speed_ * left + speed_ * right;
	float z = -speed_ * down + speed_ * up;
	if (maxForce_ > rb_->getHornoLinearVelocity().magnitude())
		rb_->applyForce(HornoVector3(x, 0, -z));

	//TODO Aplicar la rotacion
	if (x != 0 || z != 0) {
		tb_->lookAt(HornoVector3(-x+ tb_->getPosition().x, tb_->getPosition().y, z + tb_->getPosition().z));
	}
}

void El_Horno::PlayerController::setPlayerState(PLayerState s)
{
	pState_ = s;
	walking_ = false;
}
