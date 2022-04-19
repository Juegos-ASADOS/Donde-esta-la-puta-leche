#include "GameFactories.h"
#include "Entity.h"
#include "ElHornoBase.h"
#include "FoodCartComponent.h"
#include "Event.h"
#include "InputManager.h"
#include <EntityId.h>

El_Horno::FoodCartComponent::FoodCartComponent() : foodStored(0)
{
}

void El_Horno::FoodCartComponent::start()
{

}

void El_Horno::FoodCartComponent::update()
{

}

bool El_Horno::FoodCartComponent::recieveEvent(Event* ev)
{

	if (ev->ty_ == EventType::CollisionStay) {

		// Coge Id del carrito
		Entity* cart = static_cast<rbTriggerStay*>(ev)->other_->getParent();
		if (cart == nullptr)
			return false;

		EntityId* estComp = cart->getComponent<EntityId>("entityid");

		//TODO SI TIENE ALGUN OBJETO EN LA MANO...

		//Y es el carrito de la compra...
		if (estComp != nullptr && estComp->isCart()) {


			//Si pulsas la tecla E...
			if (input->isKeyDown(SDL_SCANCODE_E)) {

				//TODO ELIMINAMOS EL OBJETO QUE TENGA EN LA MANO

				//TODO COMPROBAR SI EL OBJETO QUE QUIERO METER SE PUEDE METER O LO TIRO AL SUELO
				//Mientras no esté hecho siempre se añade y ale
				foodStored++;

				//TODO SWITCH
				switch (foodStored)
				{
				case 10:
					capacity = full;
					//PROGRAMAR EL CAMBIO DE CARRITO
					break;
				case 7:
					capacity = half_Full;
					//PROGRAMAR EL CAMBIO DE CARRITO
					break;
				case 3:
					capacity = half_Empty;
					//PROGRAMAR EL CAMBIO DE CARRITO
					break;
				case 0:
					capacity = empty;
					//PROGRAMAR EL CAMBIO DE CARRITO
					break;
				default:
					break;
				}

				//Meter algun return false en la comprobacion en caso de que no se pueda meter supongo
				//O igual no pq tb ocurre un evento de tirar el objeto al suelo no c no soi 100tifiko
				return true;
			}
		}
	}
	return false;
}
