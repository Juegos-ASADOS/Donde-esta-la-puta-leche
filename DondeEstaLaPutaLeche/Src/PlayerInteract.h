#pragma once
#ifndef _PLAYER_INTERACT_H
#define _PLAYER_INTERACT_H

#include <Component.h>
#include <string>

namespace El_Horno {
	class EntityId;	
	class InputManager;
	class AnimatorController;
	class Timer;
	enum ProductType;

	class PlayerInteract : public Component
	{
	public:
		PlayerInteract();
		~PlayerInteract();

		void start() override;
		void update() override;
		//Metodo para hallar el ID del objeto que tengo en la mano
		std::string getHandObjectId();
		void deleteAliment();
		void imInCartRegister(bool imIn);
		inline void setEstantery(Entity* e) { triggerStay_ = e; };

	protected:
		
		void processCollisionStay();

		void manageCart(Entity* entity);
		void manageCashRegister();
		void manageMeatTicket();
		void manageWheighingMachine();
		void manageFishCleaner();
		void manageMeatStation();
		void manageEstantery(EntityId* idEntity);

		//void createProduct(std::string id, ProductType pType);
		void createProduct(std::string id, ProductType pType);
		void dropItem();

		void changeCartSize(Entity* entity);

		Entity* handObject_;
		bool carryingCart_,
			inCashRegister_,
			ticketTimerRunning_,
			ticketExpirationTimerRunning_,
			fishTimerRunning_,
			meatObtainable_,
			fishObtainable_,
			productLocked_;

		InputManager* input_;
		AnimatorController* anim_;

		//Variables de triggers
		Entity* triggerStay_;

		Timer* meatTimer_,
			* ticketExpirationTimer_,
			* fishTimer_;
		float maxTicketTime_,
			  maxFishTime_;
	};
}
#endif 

