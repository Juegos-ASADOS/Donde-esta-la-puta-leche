#include "EntityId.h"
#include "Event.h"
#include "PlayerInteract.h"
#include "Entity.h"
#include <iostream>

bool El_Horno::EntityId::recieveEvent(Event* ev)
{
	//Procesa los eventos de entrada/salida en él, y actualiza la entidad trigger de PlayerInteract en caso de que sea el jugador
	if (ev->ty_ == EventType::TriggerEnter || ev->ty_ == EventType::TriggerExit) {
		PlayerInteract* pI = static_cast<rbTriggerStay*>(ev)->other_->getComponent<PlayerInteract>("playerinteract");
		if (pI != nullptr) {
			pI->setEstantery(ev->ty_ == EventType::TriggerEnter ? entity_ : nullptr);
			std::cout << "Ha entado/salido " << ev->ty_ << "\n";
			return true;
		}
		return false;
	}
}
