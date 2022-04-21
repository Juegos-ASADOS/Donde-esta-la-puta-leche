#pragma once
#ifndef _ESTANTERY_COMPONENT_H
#define _ESTANTERY_COMPONENT_H

#include <Component.h>

//UNIFICAR Y CREAR UN SOLO PLAYER INTERACT PARA ESTANTERIAS Y CARRITO
namespace El_Horno {
	enum amountCart {empty,half_Empty, half_Full, full};
	class FoodCartComponent : public Component
	{
	public:
		FoodCartComponent();

		void start() override;
		void update() override;

		virtual bool recieveEvent(Event* ev);

	protected:
		
		//Valores de 0 a 10
		int foodStored;
		amountCart capacity;

		InputManager* input;

	};
}
#endif 

