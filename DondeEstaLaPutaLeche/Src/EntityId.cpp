#include "EntityId.h"
#include "Event.h"
#include "PlayerInteract.h"
#include "Entity.h"
#include <iostream>

//void El_Horno::EntityId::setParameters(std::vector<std::pair<std::string, std::string>> parameters)
//{
//	for (int i = 0; i < parameters.size(); i++) {
//		if (parameters[i].first == "id") {
//			id_ = parameters[i].second;
//		}
//		else if (parameters[i].first == "isEstantery") {
//			isEstantery_ = stoi(parameters[i].second);
//		}
//		else if (parameters[i].first == "isCart") {
//			isCart_ = stoi(parameters[i].second);
//		}
//		else if (parameters[i].first == "isCashRegister") {
//			isCashRegister_ = stoi(parameters[i].second);
//		}
//	}
//}

bool El_Horno::EntityId::recieveEvent(Event* ev)
{
	//Procesa los eventos de entrada/salida en él, y actualiza la entidad trigger de PlayerInteract en caso de que sea el jugador
	if (ev->ty_ == EventType::TriggerEnter || ev->ty_ == EventType::TriggerExit) {
		PlayerInteract* pI = static_cast<rbTriggerStay*>(ev)->other_->getComponent<PlayerInteract>("playerinteract");
		if (pI != nullptr) {
			pI->setEstantery(ev->ty_ == EventType::TriggerEnter ? entity_ : nullptr);
			pI->setPuddleExit(ev->ty_ == EventType::TriggerExit ? entity_ : nullptr);
			std::cout << "Ha entado/salido " << ev->ty_ << "\n";
			return true;
		}
		return false;
	}
}
