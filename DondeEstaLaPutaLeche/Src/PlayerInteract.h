#pragma once
#ifndef _PLAYER_INTERACT_H
#define _PLAYER_INTERACT_H

#include <Component.h>
#include <string>
#include <vector>

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
		void deleteAliment(bool ceaseExistence);
		void imInCartRegister(bool imIn);
		void setEstantery(Entity* e, bool enter);
		inline void setPuddleExit(Entity* e) { triggerExit_ = e; };

	protected:
		
		void processCollisionStay();
		void processCollisionExit();
		Entity* processTriggerPriority();
		void manageCart(Entity* entity);
		void manageCashRegister();
		void manageMeatTicket();
		void manageWheighingMachine();
		void manageFishCleaner();
		void manageMeatStation();
		void manageEstantery(EntityId* idEntity);
		void managePuddle();

		//void createProduct(std::string id, ProductType pType);
		void createProduct(std::string id, ProductType pType);
		void dropItem();

		void changeCartSize(Entity* entity);

		void instanciateCart();

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
		std::vector<Entity*> triggeredEntities_;
		Entity* triggerStay_,
			  * triggerExit_;	//Salida del charco

		Timer* meatTimer_,
			* ticketExpirationTimer_,
			* fishTimer_;
		float maxTicketTime_,
			  maxFishTime_;

	};
}
#endif 

