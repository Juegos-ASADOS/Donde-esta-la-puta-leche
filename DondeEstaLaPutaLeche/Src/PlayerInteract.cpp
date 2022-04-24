
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
#include <SceneManager.h>
#include <iostream>

El_Horno::PlayerInteract::PlayerInteract() : llevaCarrito(true)
{
}

void El_Horno::PlayerInteract::start()
{
	//Cogemos el input manager
	input = ElHornoBase::getInstance()->getInputManager();
}

void El_Horno::PlayerInteract::update()
{
	//Si pulsas la tecla R...
	if (input->isKeyDown(SDL_SCANCODE_R)) {
		dropItem();
	}
}

std::string El_Horno::PlayerInteract::buscoIdHijo()
{
	std::string idName = "";
	//Recorro el vector hasta encontrar uno que tenga el componente entityId
	auto it = entity_->getParent()->getChildren().begin();
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

//Eliminamos de la mano el objeto que tenga para añadirlo al carrito
void El_Horno::PlayerInteract::eliminoAlimento()
{
	auto it = entity_->getParent()->getChildren().begin();

	//Avanza hasta encontrar al objeto
	while (it != entity_->getParent()->getChildren().end() && (*it)->getComponent<EntityId>("entityId") != nullptr) {
		it++;
	}

	//Le digo al manager que me elimine la instancia si no apunta al final de la lista
	if (it != entity_->getParent()->getChildren().end())
		return;
	SceneManager::getInstance()->getCurrentScene()->deleteEntity((*it)->getName());
}

bool El_Horno::PlayerInteract::recieveEvent(Event* ev)
{
	//Comprobamos colisiones
	if (ev->ty_ == EventType::TriggerStay && static_cast<rbTriggerStay*>(ev)->other_->getComponent<RigidBody>("rigidbody")->isTrigger()) {
		std::cout << "Recivo tu mierda\n";
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

		//Si estoy moviendome con el carrito
		if (llevaCarrito) {
			//Dejo el carrito suelto
			entity->setParent(nullptr);
			llevaCarrito = false;

			return true;
		}
		else {
			//Si no tiene nada en la mano (A parte del trigger) y no tienes carrito...
			if (entity_->getParent()->getChildCount() == 1) {

				//Hago hijo al carrito para que se mueva junto con el player
				entity->setParent(entity_->getParent());

				//Habrá que ajustar esto para posicionar al carro justo agarrado de la mano del player

				llevaCarrito = true;

				return true;
			}
			//Si lo que quiero es meter un objeto...
			else {

				//Busco el id del objeto
				std::string idName = buscoIdHijo();

				//Si esta dentro de la lista...
				if (GameManager::getInstance()->checkObject(idName)) {
					//No necesito añadirlo a la lista pq el metodo de antes del GM ya lo hace

					//Elimino el objeto que tenga en la mano
					eliminoAlimento();

					//Cambio el mesh por un carrito que pese más
					auto porcentaje = GameManager::getInstance()->getProductCompletionPercentaje();
					if (porcentaje == 100) {
						//Cambia a lleno

						//Eliminamos el mesh
						entity->removeComponent("mesh");
						//Y metemos el nuevo
						entity->addComponent<Mesh>("mesh", "FullCart");
						entity->getComponent<Mesh>("mesh")->start();
					}
					else if (porcentaje >= 50) {
						//Cambia a medio lleno
						//Eliminamos el mesh
						entity->removeComponent("mesh");
						//Y metemos el nuevo
						entity->addComponent<Mesh>("mesh", "HalfFullCart");
						entity->getComponent<Mesh>("mesh")->start();

					}
					else if (porcentaje > 0) {
						//Cambia a medio vacio
						//Eliminamos el mesh
						entity->removeComponent("mesh");
						//Y metemos el nuevo
						entity->addComponent<Mesh>("mesh", "HalfEmptyCart");
						entity->getComponent<Mesh>("mesh")->start();

					}

					return true;
				}
				//Si te has equivocado...
				//Si te has equivocado...
				else {
					//La penalizacion está hecha en el GM				
					//Elimino el objeto que tenga en la mano
					eliminoAlimento();
					return true;
				}
			}
		}
	}
	return false;
}

bool El_Horno::PlayerInteract::manageEstantery(Entity* entity, EntityId* idEntity)
{
	//Si tiene alimento en la mano...
	if (entity_->getParent()->getChildCount() != 1)
		//No ocurre nada
		return false;

	// TODO Mostrar tecla E en la UI 

	if (input->isKeyDown(SDL_SCANCODE_E)) {

		Scene* scene = entity->getScene();
		Transform* playerTr = entity_->getParent()->getComponent<Transform>("transform");

		// Crear entidad producto
		Entity* product = scene->addEntity("product", scene->getName(), entity_->getParent());

		product->addComponent<Transform>("transform", HornoVector3(-10, 10, 0),
			HornoVector3(-90, 0, 0), HornoVector3(25, 25, 25));

		product->addComponent<Mesh>("mesh", idEntity->getId());
		product->addComponent<RigidBody>("rigidbody", 2.0f, true, true, 0);
		product->addComponent<EntityId>("entityid", idEntity->getId());

		product->start();

		return true;
	}
}

void El_Horno::PlayerInteract::dropItem()
{
	//Recorro el vector hasta encontrar uno que tenga el componente entityId
	auto it = entity_->getParent()->getChildren().begin();
	bool idFound = false;

	while (it != entity_->getChildren().end() && !idFound) {

		//Cogemos el posible id
		auto id = (*it)->getComponent<EntityId>("entityId");

		//Si tiene objeto en la mano...
		if (id != nullptr) {
			idFound = true;

			//Y lo tiro
			//Con esto la gravedad deberia de aplicarse y se deberia de caer al suelo no?
			(*it)->setParent(nullptr);
		}
		it++;
	}
}
