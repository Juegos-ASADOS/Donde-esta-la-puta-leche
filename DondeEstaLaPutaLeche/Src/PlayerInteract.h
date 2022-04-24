#pragma once
#ifndef _PLAYER_INTERACT_H
#define _PLAYER_INTERACT_H

#include <Component.h>

namespace El_Horno {
	class EntityId;	
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
		void dropItem();

		bool llevaCarrito;

		InputManager* input;

	};
}
#endif 

