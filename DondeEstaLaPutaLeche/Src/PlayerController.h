#pragma once
#ifndef _PLAYER_MOVEMENT_H
#define _PLAYER_MOVEMENT_H

#include <Component.h>


namespace El_Horno {
	class RigidBody;
	class InputManager;
	class AnimatorController;
	
	class PlayerController : public Component
	{
	public:
		PlayerController(float s) : speed_(s), maxForce_(200) {};
		PlayerController() {};

		void setParameters(std::vector<std::pair<std::string, std::string>> parameters) override;
		void start() override;
		void update() override;
		inline void setSpeed(float s) { speed_ = s; };
		inline void setSliding(bool sl) { sliding_ = sl; };
	protected:
		float speed_;
		RigidBody* rb_;
		InputManager* input_;
		int maxForce_,
			offset_;
		AnimatorController* anim_;
		bool walking_;
		bool sliding_ = false;
	};
}
#endif 

