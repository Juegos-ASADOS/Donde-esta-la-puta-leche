#pragma once
#ifndef _ESTANTERY_COMPONENT_H
#define _ESTANTERY_COMPONENT_H

#include <Component.h>

namespace El_Horno {
	enum amountCart {empty,half_Empty, half_Full, full};

	class PlayerInteract : public Component
	{
	public:
		PlayerInteract();
		~PlayerInteract() {};

		void start() override;
		void update() override;

		virtual bool recieveEvent(Event* ev);

	protected:
		
		//Valores de 0 a 10
		int sizeCart;
		amountCart capacity;

		InputManager* input;

	};
}
#endif 

