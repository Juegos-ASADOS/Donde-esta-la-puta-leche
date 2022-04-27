
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

El_Horno::PlayerInteract::PlayerInteract() : carryingCart_(false), triggerStay_(nullptr), handObject_(nullptr)
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
	return handObject_->getComponent<EntityId>("entityid")->getId();
}

//Eliminamos de la mano el objeto que tenga para a�adirlo al carrito
void El_Horno::PlayerInteract::deleteAliment()
{
	SceneManager::getInstance()->getCurrentScene()->deleteEntity(handObject_->getName());
}

void El_Horno::PlayerInteract::processCollisionStay()
{
	// Coge Id de la entidad

	if (triggerStay_ != nullptr) {
		EntityId* idEntity = triggerStay_->getComponent<EntityId>("entityid");

		//Y es el carrito de la compra...
		if (idEntity->isCart()) {
			manageCart(triggerStay_->getParent());
		}
		//Si es la estanteria...
		else if (idEntity->isEstantery()) {
			manageEstantery(idEntity);
		}
		//Si estoy en la caja...
		else if (idEntity->isCashRegister())
			manageCashRegister();
	}
}

void El_Horno::PlayerInteract::manageCart(Entity* entity)
{
	//Si pulsas la tecla E...
	if (input_->isKeyDown(SDL_SCANCODE_E)) {

		//Si estoy moviendome con el carrito
		if (carryingCart_)
		{
			//Dejo el carrito suelto
			entity->setParent(nullptr);
			auto rb = entity_->getComponent<RigidBody>("rigidbody");
			rb->setDamping(1.0f, 1.0f);
			auto pc = entity_->getComponent<PlayerController>("playercontroller");
			pc->setSpeed(300);
			carryingCart_ = false;
			std::cout << "Soltar carrito\n";
		}
		else {
			//Si no tiene nada en la mano...
			if (handObject_ == nullptr) {

				//Hago hijo al carrito para que se mueva junto con el player
				entity->setParent(entity_);

				//Habr� que ajustar esto para posicionar al carro justo agarrado de la mano del player
				auto rb = entity_->getComponent<RigidBody>("rigidbody");
				rb->setDamping(0.5f, 0.5f);
				auto pc = entity_->getComponent<PlayerController>("playercontroller");
				pc->setSpeed(450);
				carryingCart_ = true;
				std::cout << "Coger carrito\n";
			}
			//Si lo que quiero es meter un objeto...
			else {
				//Busco el id del objeto
				std::string idName = buscoIdHijo();

				//Si esta dentro de la lista...
				if (GameManager::getInstance()->checkObject(idName)) {
					//Y cambio el carrito d tama�o
					changeCartSize(entity);
					std::cout << "Objeto correcto\n";
				}
				//Si te has equivocado...
				else {
					//TODO reproducir algun sonido de que te has equivocado y por eso tiramos al suelo el objeto
					std::cout << "Objeto equivocado\n";
				}
				//TODO añadir uno al FoodCartComponent
				deleteAliment();
			}
		}
	}
}

void El_Horno::PlayerInteract::manageCashRegister()
{
	//Si pulsas la tecla E...
	if (input_->isKeyDown(SDL_SCANCODE_E)) {

		//Si tengo el carrito agarrado...
		if (carryingCart_) {
			//Busco el id del objeto
			std::string idName = "";
			//Recorro el vector hasta encontrar uno que tenga el componente entityId
			auto it = entity_->getChildren().begin();
			bool idFound = false;

			//Voy buscando el carrito en mis hijos
			while (!(*it)->hasComponent("foodcartcomponent")) {
				it++;
			}

			//Con esto hace luego la proporcion de lo que tiene en el carrito correctamente
			GameManager::getInstance()->paidFoodMum();

			//Llamo a un metodo que vacia el carrito y resta los objetos que tenga que entregar
			changeCartSize(*it);

			GameManager::getInstance()->checkEnd();			
		}
	}
}

void El_Horno::PlayerInteract::manageEstantery(EntityId* idEntity)
{
	//Oscar: No se por que cogias la escena de otra entidad y no de esta�?
	//Si tiene alimento en la mano o el carro...
	if (handObject_ != nullptr || entity_->getChildCount() != 0)
		//No ocurre nada
		return;

	// TODO Mostrar tecla E en la UI 
	if (input_->isKeyDown(SDL_SCANCODE_E)) {
		Scene* scene = entity_->getScene();
		Transform* playerTr = entity_->getComponent<Transform>("transform");

		// Crear entidad producto
		handObject_ = scene->addEntity("product", scene->getName());
		handObject_->addComponent<Transform>("transform", HornoVector3(-10, 10, 0),
			HornoVector3(-90, 0, 0), HornoVector3(25, 25, 25), true);

		handObject_->addComponent<Mesh>("mesh", idEntity->getId());
		handObject_->addComponent<EntityId>("entityid", idEntity->getId());

		handObject_->start();

		entity_->getComponent<Mesh>("mesh")->attachObject("Mano.R", handObject_);
	}
}

void El_Horno::PlayerInteract::dropItem()
{
	//Recorro el vector hasta encontrar uno que tenga el componente entityId
	vector<Entity*> it = entity_->getChildren();
	bool idFound = false;
	int i = 0;
	while (i < it.size() && !idFound) {

		//Cogemos el posible id
		EntityId* id = it[i]->getComponent<EntityId>("entityid");
		//Si tiene objeto en la mano...
		if (id != nullptr) {
			idFound = true;

			//Y lo tiro
			//Con esto la gravedad deberia de aplicarse y se deberia de caer al suelo no?
			it[i]->setParent(nullptr);
			//TODO Igual queremos meter algo tipo que en vez de que solo caiga tambi�n lo impulses hacia una direccion random o algo no se
		}
		i++;
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
