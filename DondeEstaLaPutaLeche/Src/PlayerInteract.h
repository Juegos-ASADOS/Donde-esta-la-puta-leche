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
		//Metodo para hallar el ID del objeto que tengo en la mano
		std::string buscoIdHijo();
		void eliminoAlimento();

		virtual bool recieveEvent(Event* ev);

	protected:
		
		bool processCollisionStay(Event* ev);
		bool manageCart(Event* ev,Entity* entity);
		bool manageEstantery(Entity* entity, EntityId* idEntity);
		//void dropItem();
		//Valores de 0 a 10
		int sizeCart;

		bool llevaCarrito;
		amountCart capacity;

		InputManager* input;

	};
}
#endif 

