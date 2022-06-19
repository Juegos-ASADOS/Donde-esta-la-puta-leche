#include "GameFactories.h"
#include "PlayerController.h"
#include "Rigibody.h"
#include "Transform.h"
#include "Entity.h"
#include "InputManager.h"
#include "ElHornoBase.h"
#include "AnimatorController.h"
#include <cmath>
using namespace El_Horno;

void Donde_Esta_La_Puta_Leche::PlayerController::setParameters(std::vector<std::pair<std::string, std::string>> parameters)
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

void Donde_Esta_La_Puta_Leche::PlayerController::start()
{
	input_ = ElHornoBase::getInstance()->getInputManager();
	anim_ = entity_->getComponent<AnimatorController>("animatorcontroller");
	walking_ = false;
	offset_ = 60;
	pState_ = PLAYER_CART;
	tb_ = entity_->getComponent<Transform>("transform");
}

void Donde_Esta_La_Puta_Leche::PlayerController::update()
{
	if (rb_ == nullptr) {
		rb_ = entity_->getComponent<RigidBody>("rigidbody");
		rb_->setSleepingThresholds(0, 0);
	}

	bool left = (input_->getAxis(SDL_CONTROLLER_AXIS_LEFTX) < 0.0f || input_->isKeyDown(SDL_SCANCODE_A));
	bool right = (input_->getAxis(SDL_CONTROLLER_AXIS_LEFTX) > 0.0f || input_->isKeyDown(SDL_SCANCODE_D));
	bool up = (input_->getAxis(SDL_CONTROLLER_AXIS_LEFTY) < 0.0f || input_->isKeyDown(SDL_SCANCODE_W));
	bool down = (input_->getAxis(SDL_CONTROLLER_AXIS_LEFTY) > 0.0f || input_->isKeyDown(SDL_SCANCODE_S));
	float x = -speed_ * left + speed_ * right;
	float z = -speed_ * down + speed_ * up;
	if (maxForce_ > rb_->getHornoLinearVelocity().magnitude())
		rb_->applyForce(HornoVector3(x, 0, -z));

	if (left || right || up || down) {

		if(rb_->getDamping() != 0.7f && !sliding_)
			rb_->setDamping(0.7f, 0);


		// Animacion idle->andar
		if (!walking_)
		{
			switch (pState_)
			{
			case PLAYER_DEFAULT:
				anim_->setAnimBool("Idle", "walk", true);
				break;
			case PLAYER_CART:
				anim_->setAnimBool("Idle_with_cart", "walk_with_cart", true);
				break;
			case PLAYER_PRODUCT:
				anim_->setAnimBool("Idle_with_product", "walk_with_product", true);
				break;
			default:
				break;
			}

			walking_ = true;
		}

		tb_->lookAt(HornoVector3(-x + tb_->getPosition().x, tb_->getPosition().y, z + tb_->getPosition().z));
	}
	else {
		if (rb_->getDamping() != 0.999f && !sliding_)
			rb_->setDamping(0.999f, 0);

		// Animacion andar->idle
		if (walking_) 
		{
			switch (pState_)
			{
			case PLAYER_DEFAULT:
				anim_->setAnimBool("walk", "Idle", true);
				break;
			case PLAYER_CART:
				anim_->setAnimBool("walk_with_cart", "Idle_with_cart", true);
				break;
			case PLAYER_PRODUCT:
				anim_->setAnimBool("walk_with_product", "Idle_with_product", true);
				break;
			default:
				break;
			}

			walking_ = false;
		}
	}
}

void Donde_Esta_La_Puta_Leche::PlayerController::setPlayerState(PLayerState s)
{
	pState_ = s;
	walking_ = false;
}
