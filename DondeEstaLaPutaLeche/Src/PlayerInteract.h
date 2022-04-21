#pragma once
#ifndef _PLAYER_INTERACT_H
#define _PLAYER_INTERACT_H

#include <Component.h>

namespace El_Horno {
	class EntityId;

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
		
		bool processCollisionStay(Event* ev);
		bool manageCart(Event* ev);
		bool manageEstantery(Entity* entity, EntityId* idEntity);
		//void dropItem();
		//Valores de 0 a 10
		int sizeCart;
		amountCart capacity;

		InputManager* input;

	};
}
#endif 

