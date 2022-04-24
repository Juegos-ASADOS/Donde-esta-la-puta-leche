#include <GameFactories.h>
#include <CashRegister.h>
#include <PlayerInteract.h>

#include "Entity.h"
#include "Event.h"
#include <iostream>


void El_Horno::CashRegister::start()
{

}

void El_Horno::CashRegister::update()
{

}

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
	if (ev->ty_ == EventType::TriggerEnter) {
		return inCashRegister(ev, true);
	}
	else if (ev->ty_ == EventType::TriggerExit) {
		return inCashRegister(ev, false);
	}
	return false;
}
