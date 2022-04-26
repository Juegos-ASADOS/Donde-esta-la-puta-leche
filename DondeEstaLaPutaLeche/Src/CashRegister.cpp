#include <GameFactories.h>
#include <CashRegister.h>
#include <PlayerInteract.h>

#include "Entity.h"
#include "Event.h"
#include <iostream>


El_Horno::CashRegister::CashRegister()
{
}

//Comunica al jugador si está dentro o fuera del trigger
bool El_Horno::CashRegister::inCashRegister(Event* ev, bool enter)
{
	// Coge la entidad del jugador
	Entity* player = static_cast<rbTriggerStay*>(ev)->other_->getParent();
	if (player == nullptr)
		return false;

	//Si es el jugador y no un objeto tirado cualquiera...
	if (player->hasComponent("playerinteract")) {

		//Le comunico que está dentro del trigger
		player->getComponent<PlayerInteract>("playerinteract")->imInCartRegister(enter);

		return true;
	}
	return false;
}

bool El_Horno::CashRegister::recieveEvent(Event* ev)
{
	//Al entrar al trigger
	if (ev->ty_ == EventType::TriggerEnter) {
		return inCashRegister(ev, true);
	}
	//Al salir del trigger
	else if (ev->ty_ == EventType::TriggerExit) {
		return inCashRegister(ev, false);
	}
	return false;
}
