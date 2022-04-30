
//TODO REVISAR SI PONER "" O <>
#include "GameFactories.h"
#include "Entity.h"
#include "ElHornoBase.h"
#include "PlayerInteract.h"
#include "PlayerController.h"
#include "Event.h"
#include "InputManager.h"
#include <EntityId.h>
#include <HornoVector3.h>
#include <Transform.h>
#include <Scene.h>
#include <Mesh.h>
#include <Rigibody.h>
#include <FoodCartComponent.h>
#include <GameManager.h>
#include <SceneManager.h>
#include <Rigibody.h>
#include <AnimatorController.h>
#include <Timer.h>
#include <iostream>

El_Horno::PlayerInteract::PlayerInteract() : carryingCart_(false), triggerStay_(nullptr), handObject_(nullptr), fishTimer_(nullptr),
ticketTimerRunning_(false), fishTimerRunning_(false), productLocked_(false), meatTimer_(nullptr), maxTicketTime_(7), maxFishTime_(7),
meatObtainable_(false), fishObtainable_(false), ticketExpirationTimer_(nullptr), ticketExpirationTimerRunning_(false)
{
}

El_Horno::PlayerInteract::~PlayerInteract()
{
	delete fishTimer_; fishTimer_ = nullptr;
	delete meatTimer_; meatTimer_ = nullptr;
	delete ticketExpirationTimer_; ticketExpirationTimer_ = nullptr;
}

void El_Horno::PlayerInteract::start()
{
	//Cogemos el input manager
	input_ = ElHornoBase::getInstance()->getInputManager();
	meatTimer_ = new Timer();
	fishTimer_ = new Timer();
	ticketExpirationTimer_ = new Timer();
}

void El_Horno::PlayerInteract::update()
{
	//Si pulsas la tecla R...
	if (input_->isKeyDown(SDL_SCANCODE_R)) {
		dropItem();
	}

	// Se puede obtener la carne
	if (ticketTimerRunning_ && meatTimer_->getTime() >= maxTicketTime_) {
		cout << "timer carne terminao\n";
		ticketTimerRunning_ = false;
		ticketExpirationTimerRunning_ = true;
		ticketExpirationTimer_->resetTimer();
		meatObtainable_ = true;
	}

	// Se deja de poder obtener la carne
	if (ticketExpirationTimerRunning_ && ticketExpirationTimer_->getTime() >= maxTicketTime_) {
		cout << "timer ticket expirao\n";
		ticketExpirationTimerRunning_ = false;
		meatObtainable_ = false;
	}

	// Se puede obtener el pescado
	if (fishTimerRunning_ && fishTimer_->getTime() >= maxFishTime_) {
		fishObtainable_ = true;
		cout << "timer pescao terminao\n";
		fishTimerRunning_ = false;
	}

	processCollisionStay();
}

std::string El_Horno::PlayerInteract::getHandObjectId()
{
	return handObject_->getComponent<EntityId>("entityid")->getId();
}

//Eliminamos de la mano el objeto que tenga para a�adirlo al carrito
void El_Horno::PlayerInteract::deleteAliment()
{
	std::string id = handObject_->getComponent<EntityId>("entityid")->getId();
	entity_->getComponent<Mesh>("mesh")->detachObject(handObject_);
	SceneManager::getInstance()->getCurrentScene()->deleteEntity(handObject_->getName());
	handObject_ = nullptr;

	//Transform del jugador
	Transform* tr = entity_->getComponent<Transform>("transform");

	if (!carryingCart_) {
		Entity* ob = entity_->getScene()->addEntity("productShot", entity_->getScene()->getName());
		ob->addComponent<Transform>("transform", OgreVectorToHorno(tr->getPosition()) /*+ HornoVector3(10, 0, 0)*/,
			HornoVector3(-90, 0, 0), HornoVector3(15, 15, 15));

		ob->addComponent<Mesh>("mesh", id);
		ob->addComponent<RigidBody>("rigidbody", 2.0f, false, false, 0);

		ob->start();

		//Lanza el objeto
		ob->getComponent<RigidBody>("rigidbody")->applyForce(HornoVector3(100, 0, 0));
	}
}

void El_Horno::PlayerInteract::processCollisionStay()
{
	// Coge Id de la entidad

	if (triggerStay_ != nullptr) {
		EntityId* idEntity = triggerStay_->getComponent<EntityId>("entityid");

		Type t = idEntity->getType();

		switch (t)
		{
		case El_Horno::PRODUCT:
			break;
		case El_Horno::ESTANTERY:
			manageEstantery(idEntity);
			break;
		case El_Horno::CART:
			manageCart(triggerStay_->getParent());
			break;
		case El_Horno::CASHREGISTER:
			manageCashRegister();
			break;
		case El_Horno::MEATTICKET:
			manageMeatTicket();
			break;
		case El_Horno::WHEIGHINGMACHINE:
			manageWheighingMachine();
			break;
		case El_Horno::FISHCLEANER:
			manageFishCleaner();
			break;
		case El_Horno::MEATSTATION:
			manageMeatStation();
			break;
		default:
			break;
		}
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
			/*entity->setParent(nullptr);
			auto rb = entity_->getComponent<RigidBody>("rigidbody");
			rb->setDamping(1.0f, 1.0f);
			auto pc = entity_->getComponent<PlayerController>("playercontroller");
			pc->setSpeed(300);
			carryingCart_ = false;
			std::cout << "Soltar carrito\n";*/
		}
		else {
			//Si no tiene nada en la mano...
			if (handObject_ == nullptr) {

				//Hago hijo al carrito para que se mueva junto con el player. Carrito kinematico
				entity->getComponent<RigidBody>("rigidbody")->setKinematic(true);
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
			else if (!productLocked_) {
				//Busco el id del objeto
				std::string idName = getHandObjectId();

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
			else {
				//TODO Feedback (audio o UI) para indicar que hay que pesar/limpiar producto antes de poder meterlo al carro
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

void El_Horno::PlayerInteract::manageMeatTicket()
{
	// TODO Mostrar tecla E en la UI
	if (input_->isKeyDown(SDL_SCANCODE_E)) {
		cout << "carne\n";
		meatTimer_->resetTimer();
		ticketTimerRunning_ = true;
	}
}

void El_Horno::PlayerInteract::manageWheighingMachine()
{
	if (productLocked_ && handObject_ != nullptr && handObject_->getComponent<EntityId>("entityid")->getProdType() == ProductType::FRUIT) {
		cout << "fruta fuera\n";
		// TODO Mostrar tecla E en la UI

		if (input_->isKeyDown(SDL_SCANCODE_E)) {
			productLocked_ = false;
			cout << "fruta dentro\n";
			//TODO Poner feedback de que el producto ha sido pesado
		}
	}
}

void El_Horno::PlayerInteract::manageFishCleaner()
{
	if (handObject_ != nullptr && handObject_->getComponent<EntityId>("entityid")->getProdType() == ProductType::FISH) {
		// TODO Mostrar tecla E en la UI 
		cout << "pescado fuera\n";
		// Si se presiona la E se inicia el timer de limpieza de pescado
		if (input_->isKeyDown(SDL_SCANCODE_E)) {
			productLocked_ = false;
			fishTimerRunning_ = true;
			fishTimer_->resetTimer();
			deleteAliment();
			cout << "pescado dentro\n";
		}
	}
	else if (fishObtainable_ && handObject_ == nullptr) {
		// TODO Mostrar tecla E en la UI 
		// Si el pescado esta limpio
		if (input_->isKeyDown(SDL_SCANCODE_E)) {
			cout << "pescado en mano\n";
			createProduct("Agua", ProductType::DEFAULT);
			fishObtainable_ = false;
		}
	}
}

void El_Horno::PlayerInteract::manageMeatStation()
{
	if (meatObtainable_ && handObject_ == nullptr) {
		cout << "Se puede obtener carne\n";
		// TODO Mostrar tecla E en la UI 
		if (input_->isKeyDown(SDL_SCANCODE_E)) {
			cout << "Se obtuvo carne\n";
		
			// ESTO SERA "carne" CUANDO TENGAMOS EL MESH
			createProduct("Agua", ProductType::DEFAULT);
			meatObtainable_ = false;
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
		// Crear entidad producto
		createProduct(idEntity->getId(), idEntity->getProdType());
	}
}

void El_Horno::PlayerInteract::createProduct(std::string id, ProductType pType)
{
	Scene* scene = entity_->getScene();
	Transform* playerTr = entity_->getComponent<Transform>("transform");

	handObject_ = scene->addEntity("product", scene->getName());
	handObject_->addComponent<Transform>("transform", HornoVector3(0, 0, 0),
		HornoVector3(-90, 0, 0), HornoVector3(25, 25, 25), true);

	handObject_->addComponent<Mesh>("mesh", id);
	handObject_->addComponent<EntityId>("entityid", Type::PRODUCT, pType, id);

	handObject_->start();

	entity_->getComponent<Mesh>("mesh")->attachObject("Mano.R", handObject_);

	// Se bloquea la posibilidad de meterlo al carrito hasta que se tomen las acciones pertinentes
	if (pType == ProductType::FISH || pType == ProductType::FRUIT)
		productLocked_ = true;
}

void El_Horno::PlayerInteract::dropItem()
{
	if (handObject_ != nullptr) {
		deleteAliment();
		productLocked_ = false;
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
