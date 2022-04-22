
//TODO REVISAR SI PONER "" O <>
#include "GameFactories.h"
#include "Entity.h"
#include "ElHornoBase.h"
#include "PlayerInteract.h"
#include "Event.h"
#include "InputManager.h"
#include <EntityId.h>
#include <Transform.h>
#include <Scene.h>
#include <Mesh.h>
#include <Rigibody.h>
#include <FoodCartComponent.h>
#include <GameManager.h>

El_Horno::PlayerInteract::PlayerInteract() : sizeCart(0), capacity(empty)
{
}

void El_Horno::PlayerInteract::start()
{
	//Cogemos el input manager
	input = ElHornoBase::getInstance()->getInputManager();
}

void El_Horno::PlayerInteract::update()
{
	//TODO SI PULSAS LA R TIRAS EL PUTO OBJETO AL SUELO Y A MAMARLA
	if (input->isKeyDown(SDL_SCANCODE_R)) {

		std::string idName = buscoIdHijo();

		//Si tengo algún objeto cualquiera en la mano
		if (idName != "") {
	
			//Lo tiro al puto suelo
			//TODO

		}

	}
}

std::string El_Horno::PlayerInteract::buscoIdHijo()
{
	std::string idName = "";
	//Recorro el vector hasta encontrar uno que tenga el componente entityId
	auto it = entity_->getChildren().begin();
	bool idFound = false;

	while (it != entity_->getChildren().end() && !idFound) {

		//Cogemos el posible id
		auto id = (*it)->getComponent<EntityId>("entityId");
		//
		if (id != nullptr) {
			idName = id->getId();
			idFound = true;
		}
		it++;
	}

	return idName;
}

bool El_Horno::PlayerInteract::recieveEvent(Event* ev)
{
	//Comprobamos colisiones
	if (ev->ty_ == EventType::TriggerStay) {
		return processCollisionStay(ev);
	}

	return false;
}

bool El_Horno::PlayerInteract::processCollisionStay(Event* ev)
{
	// Coge Id de la entidad
	Entity* entity = static_cast<rbTriggerStay*>(ev)->other_->getParent();

	if (entity == nullptr)
		return false;

	EntityId* idEntity = entity->getComponent<EntityId>("entityid");

	//TODO SI TIENE ALGUN OBJETO EN LA MANO...

	if (idEntity != nullptr) {

		//Y es el carrito de la compra...
		if (idEntity->isCart()) {
			return manageCart(ev, entity);
		}
		//Si es la estanteria...
		else if (idEntity->isEstantery()) {
			return manageEstantery(entity, idEntity);
		}
	}
	return false;
}

bool El_Horno::PlayerInteract::manageCart(Event* ev, Entity* entity)
{
	//Si pulsas la tecla E...
	if (input->isKeyDown(SDL_SCANCODE_E)) {

		//Si no tiene nada en la mano (A parte del trigger)...
		//TODO TENDRA QUE SER ==1 PQ EL TRIGGER YA ES UN HIJO
		if (entity_->getChildCount() == 0) {
			//Me agarro al puto carrito



			return true;
		}
		else {

			std::string idName = buscoIdHijo();

			

			//Si esta dentro de la lista...
			if (!GameManager::getInstance()->checkObject(idName)) {
				//No necesito añadirlo a la lista pq el metodo de antes del GM ya lo hace

				//Elimino el objeto que tenga en la mano
				//TODO

				return true;
			}
			//Si te has equivocado...
			else {
				//La penalizacion está hecha en el GM

				//Elimino el objeto que tenga en la mano
				//TODO

				return true;
			}
		}
	}
	return false;
}

bool El_Horno::PlayerInteract::manageEstantery(Entity* entity, EntityId* idEntity)
{
	//Si no tiene alimentos que coger...
	if (entity_->getChildCount() != 0)
		//No ocurre nada
		return false;

	// TODO Mostrar tecla E en la UI 

	if (input->isKeyDown(SDL_SCANCODE_E)) {

		Scene* scene = entity->getScene();
		Transform* playerTr = entity_->getComponent<Transform>("transform");

		// Crear entidad producto
		Entity* product = scene->addEntity("product", scene->getName(), entity_);

		/*product->addComponent<Transform>("transform", HornoVector3(playerTr->getHornoPosition().x_ + 4, playerTr->getHornoPosition().y_, playerTr->getHornoPosition().z_),
			HornoVector3(0, 0, 0), HornoVector3(0.25, 0.25, 0.25));*/
		product->addComponent<Transform>("transform", HornoVector3(-10, 10, 0),
			HornoVector3(-90, 0, 0), HornoVector3(25, 25, 25));

		product->addComponent<Mesh>("mesh", idEntity->getId());
		product->addComponent<RigidBody>("rigidbody", 2.0f, true, true, 0);
		product->addComponent<EntityId>("entityid", idEntity->getId());

		product->start();

		return true;
	}
}
