#pragma once
#ifndef _PLAYER_INTERACT_H
#define _PLAYER_INTERACT_H

#include <Component.h>

namespace El_Horno {
	class EntityId;	
	class InputManager;
	class PlayerInteract : public Component
	{
	public:
		PlayerInteract();
		~PlayerInteract() {};

		void start() override;
		void update() override;
		//Metodo para hallar el ID del objeto que tengo en la mano
		std::string buscoIdHijo();
		void deleteAliment();
		void imInCartRegister(bool imIn);
		inline void setEstantery(Entity* e) { triggerStay_ = e; };

	protected:
		
		bool processCollisionStay();
		bool manageCart(Entity* entity);
		bool manageCashRegister();
		bool manageEstantery(EntityId* idEntity);
		void dropItem();

		void changeCartSize(Entity* entity);

		bool carryingCart_;
		bool inCashRegister_;

		InputManager* input_;

		//Variables de triggers
		Entity* triggerStay_;
	};
}
#endif 

