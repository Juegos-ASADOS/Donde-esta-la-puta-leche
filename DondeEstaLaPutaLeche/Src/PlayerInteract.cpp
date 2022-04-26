
//TODO REVISAR SI PONER "" O <>
#include "GameFactories.h"
#include "Entity.h"
#include "ElHornoBase.h"
#include "PlayerInteract.h"
#include "PlayerController.h"
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
#include <Rigibody.h>
#include <AnimatorController.h>
#include <iostream>

El_Horno::PlayerInteract::PlayerInteract() : carryingCart_(true), triggerStay_(nullptr)
{
}

void El_Horno::PlayerInteract::start()
{
	//Cogemos el input manager
	input_ = ElHornoBase::getInstance()->getInputManager();
}

void El_Horno::PlayerInteract::update()
{
	//Si pulsas la tecla R...
	if (input_->isKeyDown(SDL_SCANCODE_R)) {
		dropItem();
	}
	processCollisionStay();
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

//Eliminamos de la mano el objeto que tenga para a�adirlo al carrito
void El_Horno::PlayerInteract::deleteAliment()
{
	auto it = entity_->getChildren().begin();

	//Avanza hasta encontrar al objeto
	while (it != entity_->getChildren().end() && (*it)->getComponent<EntityId>("entityId") != nullptr) {
		it++;
	}

	//Le digo al manager que me elimine la instancia si no apunta al final de la lista
	if (it == entity_->getChildren().end())
		return;

	SceneManager::getInstance()->getCurrentScene()->deleteEntity((*it)->getName());
}

bool El_Horno::PlayerInteract::processCollisionStay()
{
	// Coge Id de la entidad

	if (triggerStay_ != nullptr) {
		EntityId* idEntity = triggerStay_->getComponent<EntityId>("entityid");

		//Y es el carrito de la compra...
		if (idEntity->isCart()) {
			return manageCart(triggerStay_->getParent());
		}
		//Si es la estanteria...
		else if (idEntity->isEstantery()) {
			return manageEstantery(idEntity);
		}
		//Si estoy en la caja...
		else if (idEntity->isCashRegister())
			return manageCashRegister();
	}
	return false;
}

bool El_Horno::PlayerInteract::manageCart(Entity* entity)
{
	//Si pulsas la tecla E...
	if (input_->isKeyDown(SDL_SCANCODE_E)) {

		//Si estoy moviendome con el carrito
		if (carryingCart_) 
		{
			//Dejo el carrito suelto
			entity->setParent(nullptr);
			auto rb = entity_->getParent()->getComponent<RigidBody>("rigidbody");
			rb->setDamping(1.0f, 1.0f);
			auto pc = entity_->getParent()->getComponent<PlayerController>("playercontroller");
			pc->setSpeed(300);
			carryingCart_ = false;


			return true;
		}
		else {
			//Si no tiene nada en la mano (A parte del trigger) y no tienes carrito...
			if (entity_->getChildCount() == 1) {

				//Hago hijo al carrito para que se mueva junto con el player
				entity->setParent(entity_);

				//Habr� que ajustar esto para posicionar al carro justo agarrado de la mano del player
				auto rb = entity_->getParent()->getComponent<RigidBody>("rigidbody");
				rb->setDamping(0.5f, 0.5f);
				auto pc = entity_->getParent()->getComponent<PlayerController>("playercontroller");
				pc->setSpeed(450);
				carryingCart_ = true;

				return true;
			}
			//Si lo que quiero es meter un objeto...
			else {

				//Busco el id del objeto
				std::string idName = buscoIdHijo();

				//TODO CAMBIAR TODO ESTO
				//Si esta dentro de la lista...
				//if (GameManager::getInstance()->checkObject(idName)) {
				//	//No necesito a�adirlo a la lista pq el metodo de antes del GM ya lo hace

				//	//Elimino el objeto que tenga en la mano
				//	deleteAliment();

				//	//Y cambio el carrito d tama�o
				//	changeCartSize(entity);

				//	return true;
				//}
				////Si te has equivocado...
				//else {
				//	//La penalizacion est� hecha en el GM		

				//	//TODO reproducir algun sonido de que te has equivocado y por eso tiramos al suelo el objeto

				//	//Elimino el objeto que tenga en la mano
				//	deleteAliment();
				//	return true;
				//}
			}
		}
	}
	return false;
}

bool El_Horno::PlayerInteract::manageCashRegister()
{
	//Si pulsas la tecla E...
	if (input_->isKeyDown(SDL_SCANCODE_E)) {

		//Si tengo el carrito agarrado...
		if (carryingCart_) {

			//Cambio el mesh si he soltado muchos objetos

			//Busco el id del objeto
			std::string idName = "";
			//Recorro el vector hasta encontrar uno que tenga el componente entityId
			auto it = entity_->getChildren().begin();
			bool idFound = false;

			//Voy buscando el carrito en mis hijos
			while (!(*it)->hasComponent("foodcartcomponent")) {
				it++;
			}

			//Llamo a un metodo que vacia el carrito y resta los objetos que tenga que entregar


			//Si esta dentro de la lista...
			if (GameManager::getInstance()->checkObject(idName)) {
				//No necesito a�adirlo a la lista pq el metodo de antes del GM ya lo hace

				//Y cambiamos el tama�o del carrito
				changeCartSize(*it);

				return true;
			}
			//Si te has equivocado...
			else {

				//TODO Reproducir algun sonido en plan nono cari�o que este objeto no est� en la lista mi ciela 
				return true;
			}
			return true;
		}
		//Si solo llevo un objeto en la mano...
		else {
			//Le digo al GM que elimine el objeto de la lista (si se puede)


			//Y destruyo el elemento que est� agarrando
			deleteAliment();

			//TODO No se si hay que sumar algun tipo de puntuacion rara o que
		}
	}

	return false;
}

bool El_Horno::PlayerInteract::manageEstantery(EntityId* idEntity)
{
	//Oscar: No se por que cogias la escena de otra entidad y no de esta�?
	//Si tiene alimento en la mano...
	if (entity_->getChildCount() != 1)
		//No ocurre nada
		return false;

	// TODO Mostrar tecla E en la UI 

	if (input_->isKeyDown(SDL_SCANCODE_E)) {

		Scene* scene = entity_->getScene();
		Transform* playerTr = entity_->getComponent<Transform>("transform");

		// Crear entidad producto
		Entity* product = scene->addEntity("product", scene->getName(), entity_);

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
	auto it = entity_->getChildren().begin();
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
			//TODO Igual queremos meter algo tipo que en vez de que solo caiga tambi�n lo impulses hacia una direccion random o algo no se
		}
		it++;
	}
}

//Cambia el mesh del carrito en funcion del porcentaje que tenga
void El_Horno::PlayerInteract::changeCartSize(Entity* entity)
{
	//Cambio el mesh por un carrito que pese m�s
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
}

void El_Horno::PlayerInteract::imInCartRegister(bool imIn)
{
	inCashRegister_ = imIn;
}
