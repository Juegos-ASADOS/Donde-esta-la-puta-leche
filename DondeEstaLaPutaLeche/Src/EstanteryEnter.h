#pragma once
#ifndef _ESTANTERY_ENTER_H
#define _ESTANTERY_ENTER_H

#include <Component.h>

namespace El_Horno {
	class RigidBody;
	class InputManager;

	class EstanteryEnter : public Component
	{
	public:
		EstanteryEnter() {};

		void start() override;
		void update() override;

		virtual bool recieveEvent(Event* ev);
	protected:
		InputManager* input;
	};
}
#endif 

