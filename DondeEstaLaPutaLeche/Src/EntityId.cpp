#include "EntityId.h"
#include "Event.h"
#include "PlayerInteract.h"
#include "Entity.h"

void El_Horno::EntityId::setParameters(std::vector<std::pair<std::string, std::string>> parameters)
{
	for (int i = 0; i < parameters.size(); i++) {
		if (parameters[i].first == "type") {
			type_ = (Type)stoi(parameters[i].second);
		}
		else if (parameters[i].first == "productType") {
			productType_ = (ProductType)stoi(parameters[i].second);
		}
		else if (parameters[i].first == "id") {
			id_ = parameters[i].second;
		}
	}
}

bool El_Horno::EntityId::recieveEvent(Event* ev)
{
	//Procesa los eventos de entrada/salida en �l, y actualiza la entidad trigger de PlayerInteract en caso de que sea el jugador
	if (ev->ty_ == EventType::TriggerEnter || ev->ty_ == EventType::TriggerExit) {
		PlayerInteract* pI = static_cast<rbTriggerStay*>(ev)->other_->getComponent<PlayerInteract>("playerinteract");
		if (pI != nullptr) {
			pI->setEstantery(entity_, ev->ty_ == EventType::TriggerEnter);
			pI->setPuddleExit(ev->ty_ == EventType::TriggerExit ? entity_ : nullptr);
			std::cout << "Ha entado/salido " << ev->ty_ << "\n";
			return true;
		}
		return false;
	}
}
