#pragma once
#ifndef _PLAYER_MOVEMENT_H
#define _PLAYER_MOVEMENT_H

#include <Component.h>


namespace El_Horno {
	class RigidBody;
	class InputManager;
	
	class PlayerController : public Component
	{
	public:
		PlayerController(float s) : speed_(s), maxForce_(155) {};

		void start() override;
		void update() override;
		inline void setSpeed(float s) { speed_ = s; };
	protected:
		float speed_;
		RigidBody* rb_;
		InputManager* input_;
		int maxForce_;
	};
}
#endif 

