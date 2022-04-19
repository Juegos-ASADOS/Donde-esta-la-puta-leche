#pragma once
#ifndef _ESTANTERY_COMPONENT_H
#define _ESTANTERY_COMPONENT_H

#include <Component.h>


namespace El_Horno {
	class RigidBody;
	enum amount {empty,half_Empty, half_Full, full};
	class FoodCartComponent : public Component
	{
	public:
		FoodCartComponent();

		void start() override;
		void update() override;

		virtual bool recieveEvent(Event* ev);

	protected:
		//RigidBody* rb_;
		
		//Valores de 0 a 10
		int foodStored;
		amount capacity;

		InputManager* input;

	};
}
#endif 

