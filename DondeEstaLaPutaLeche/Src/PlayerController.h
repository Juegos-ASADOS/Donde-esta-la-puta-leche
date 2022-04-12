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
		PlayerController(float s) : speed(s) {};

		void start() override;
		void update() override;
	protected:
		float speed;
		RigidBody* rb;
		InputManager* input;
	};
}
#endif 

