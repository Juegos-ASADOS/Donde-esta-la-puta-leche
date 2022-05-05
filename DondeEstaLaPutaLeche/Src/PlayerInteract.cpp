#include "GameFactories.h"
#include "Entity.h"
#include "ElHornoBase.h"
#include "PlayerInteract.h"
#include "PlayerController.h"
#include "Event.h"
#include "InputManager.h"
#include "UIManager.h"
#include <EntityId.h>
#include <HornoVector3.h>
#include <Transform.h>
#include <Scene.h>
#include <Mesh.h>
#include <Rigibody.h>
#include <GameManager.h>
#include <SceneManager.h>
#include <Rigibody.h>
#include <AnimatorController.h>
#include <AudioComponent.h>
#include <Timer.h>
#include <iostream>

El_Horno::PlayerInteract::PlayerInteract() : carryingCart_(true), triggerStay_(nullptr), handObject_(nullptr), fishTimer_(nullptr),
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
	anim_ = entity_->getComponent<AnimatorController>("animatorcontroller");
	anim_->setAnimBool("AnyState", "Idle_with_cart", true);
	//LuaManager::getInstance()->pushNumber(maxTicketTime_, "ticketTime");
	//LuaManager::getInstance()->readLuaScript("shop");
}

void El_Horno::PlayerInteract::update()
{
	//Si pulsas la tecla R...
	if (input_->isKeyDown(SDL_SCANCODE_R) || input_->isButtonDown(SDL_CONTROLLER_BUTTON_B)) {
		dropItem();
	}

	// Se puede obtener la carne
	if (ticketTimerRunning_ && meatTimer_->getTime() >= maxTicketTime_) {
		cout << "timer carne terminao\n";
		ticketTimerRunning_ = false;
		ticketExpirationTimerRunning_ = true;
		ticketExpirationTimer_->resetTimer();
		meatObtainable_ = true;
		//Audio
		entity_->getComponent<AudioComponent>("audiocomponent")->playSound("SFX/ComidaLista.mp3");
	}

	// Se deja de poder obtener la carne
	if (ticketExpirationTimerRunning_ && ticketExpirationTimer_->getTime() >= maxTicketTime_) {
		cout << "timer ticket expirao\n";
		ticketExpirationTimerRunning_ = false;
		meatObtainable_ = false;
		//!Audio 

	}

	// Se puede obtener el pescado
	if (fishTimerRunning_ && fishTimer_->getTime() >= maxFishTime_) {
		fishObtainable_ = true;
		cout << "timer pescao terminao\n";
		fishTimerRunning_ = false;
		//Audio
		entity_->getComponent<AudioComponent>("audiocomponent")->playSound("SFX/ComidaLista.mp3");
	}

	processCollisionStay();
	processCollisionExit();
}

std::string El_Horno::PlayerInteract::getHandObjectId()
{
	return handObject_->getComponent<EntityId>("entityid")->getId();
}

//Eliminamos de la mano el objeto que tenga para a�adirlo al carrito
void El_Horno::PlayerInteract::deleteAliment(bool ceaseExistence)
{
	std::string id = handObject_->getComponent<EntityId>("entityid")->getId();
	entity_->getComponent<Mesh>("mesh")->detachObject(handObject_);
	SceneManager::getInstance()->getCurrentScene()->deleteEntity(handObject_->getName());
	handObject_ = nullptr;

	//Transform del jugador
	Transform* tr = entity_->getComponent<Transform>("transform");

	if (!ceaseExistence && !carryingCart_) {
		Entity* ob = SceneManager::getInstance()->getCurrentScene()->addEntity("productShot", entity_->getScene()->getName());
		ob->addComponent<Transform>("transform", tr->getHornoGlobalPosition() /*+ HornoVector3(10, 0, 0)*/,
			HornoVector3(-90, 0, 0), HornoVector3(15, 15, 15));

		ob->addComponent<Mesh>("mesh", id);
		ob->addComponent<RigidBody>("rigidbody", 2.0f, false, false, 0);

		ob->awake();
		ob->start();

		//Lanza el objeto
		ob->getComponent<RigidBody>("rigidbody")->applyForce(HornoVector3(100, 0, 0));
	}
}

void El_Horno::PlayerInteract::processCollisionStay()
{
	// Coge Id de la entidad

	if (triggeredEntities_.size() > 0) {

		triggerStay_ = processTriggerPriority();

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

void El_Horno::PlayerInteract::processCollisionExit()
{
	if (triggerExit_ != nullptr) {
		EntityId* idEntity = triggerExit_->getComponent<EntityId>("entityid");

		Type t = idEntity->getType();

		switch (t)
		{
		case El_Horno::PUDDLE:
			entity_->getComponent<RigidBody>("rigidbody")->setDamping(0.7f, 0.7f);
			entity_->getComponent<PlayerController>("playercontroller")->setSliding(false);
			break;
		default:
			break;
		}
		triggerExit_ = nullptr;
		for (int i = 0; i < triggeredEntities_.size(); i++) {
			if (triggeredEntities_[i]->getComponent<EntityId>("entityid")->getType() == Type::PUDDLE) {
				triggeredEntities_.erase(triggeredEntities_.begin() + i);
				return;
			}
		}
	}
}

El_Horno::Entity* El_Horno::PlayerInteract::processTriggerPriority()
{
	float minDist = -1;
	Entity* nearestEnt = nullptr;
	bool cart = false;
	bool cashReg = false;
	int puddle = 0;

	// Buscar entre las entidades trigger
	for (int i = 0; i < triggeredEntities_.size(); i++) {
		float dist = (triggeredEntities_[i]->getComponent<Transform>("transform")->getHornoGlobalPosition()
			- entity_->getComponent<Transform>("transform")->getHornoGlobalPosition()).magnitude();

		// El carro se devuelve con prioridad
		if (!cashReg && !cart && triggeredEntities_[i]->getComponent<EntityId>("entityid")->getType() == Type::CART) {
			nearestEnt = triggeredEntities_[i];
			cart = true;
		}
		else if (triggeredEntities_[i]->getComponent<EntityId>("entityid")->getType() == Type::CASHREGISTER) {
			nearestEnt = triggeredEntities_[i];
			cashReg = true;
		}
		else if (triggeredEntities_[i]->getComponent<EntityId>("entityid")->getType() == Type::PUDDLE) {
			managePuddle();
			puddle = i;
		}
		else if (!cart && (minDist == -1 || dist < minDist)) {
			minDist = dist;
			nearestEnt = triggeredEntities_[i];
		}
	}
	if (nearestEnt == nullptr)
		nearestEnt = triggeredEntities_[puddle];
	return nearestEnt;
}

void El_Horno::PlayerInteract::manageCart(Entity* entity)
{
	//Si pulsas la tecla E...
	if (input_->getKeyDown(SDL_SCANCODE_E) || input_->isButtonDown(SDL_CONTROLLER_BUTTON_X)) {

		//Si estoy moviendome con el carrito
		if (carryingCart_)
		{
			entity_->getChild("cart")->setActive(false);

			//Dejo el carrito suelto
			instanciateCart();
			auto rb = entity_->getComponent<RigidBody>("rigidbody");
			rb->setScale(HornoVector3(0.5, 0.7, 0.5));
			rb->setDamping(1.0f, 1.0f);
			auto pc = entity_->getComponent<PlayerController>("playercontroller");
			pc->setSpeed(300);
			pc->setPlayerState(El_Horno::PLAYER_DEFAULT);
			anim_->setAnimBool("AnyState", "Idle", true);
			carryingCart_ = false;
			std::cout << "Soltar carrito\n";
		}
		else {
			//Si no tiene nada en la mano...
			if (handObject_ == nullptr) {

				//Hago hijo al carrito para que se mueva junto con el player. Carrito kinematico
				entity_->getChild("cart")->setActive(true);
				std::cout << triggerStay_->getParent()->getName() << "\n";
				SceneManager::getInstance()->getCurrentScene()->deleteEntity(triggerStay_->getParent()->getName());

				entity_->getComponent<RigidBody>("rigidbody")->setScale(HornoVector3(0.5,0.7,1.3));

				int i = 0;
				bool found = false;
				while (!found && i < triggeredEntities_.size()) {
					if (triggeredEntities_[i]->getComponent<EntityId>("entityid")->getType() == Type::CART) {
						triggeredEntities_.erase(triggeredEntities_.begin() + i);
						found = true;
					}
					i++;
				}
				triggerStay_ = nullptr;
				//Habr� que ajustar esto para posicionar al carro justo agarrado de la mano del player
				auto rb = entity_->getComponent<RigidBody>("rigidbody");
				rb->setDamping(0.5f, 0.5f);
				auto pc = entity_->getComponent<PlayerController>("playercontroller");
				pc->setSpeed(450);
				pc->setPlayerState(El_Horno::PLAYER_CART);
				anim_->setAnimBool("AnyState", "Idle_with_cart", true);
				carryingCart_ = true;
				std::cout << "Coger carrito\n";
				//Audio
				entity_->getComponent<AudioComponent>("audiocomponent")->playSound("SFX/Carrito.mp3");
			}
			//Si lo que quiero es meter un objeto...
			else if (!productLocked_) {
				cout << "intento meter objeto jijio\n";
				//Busco el id del objeto
				std::string idName = getHandObjectId();

				//Si esta dentro de la lista...
				if (GameManager::getInstance()->checkObject(idName)) {
					//Y cambio el carrito d tama�o
					changeCartSize(entity);
					std::cout << "Objeto correcto\n";
					//Audio //Meter objeto en el carro
					entity_->getComponent<AudioComponent>("audiocomponent")->playSound("SFX/SoltarObjeto.mp3");
				}
				//Si te has equivocado...
				else {
					std::cout << "Objeto equivocado\n";
					//Audio
					entity_->getComponent<AudioComponent>("audiocomponent")->playSound("SFX/MalAlimento.mp3");
				}
				//TODO añadir uno al FoodCartComponent
				deleteAliment(true);

				auto pc = entity_->getComponent<PlayerController>("playercontroller");
				pc->setPlayerState(El_Horno::PLAYER_DEFAULT);
				anim_->setAnimBool("AnyState", "Idle", true);
			}
			else {
				//TODO Feedback (audio o UI) para indicar que hay que pesar/limpiar producto antes de poder meterlo al carro
				//!Audio JBL apagar  
			}
		}
	}
}

void El_Horno::PlayerInteract::manageCashRegister()
{
	//Si pulsas la tecla E...
	if (input_->isKeyDown(SDL_SCANCODE_E) || input_->isButtonDown(SDL_CONTROLLER_BUTTON_X)) {

		//Si tengo el carrito agarrado...
		if (carryingCart_) {
			//Con esto hace luego la proporcion de lo que tiene en el carrito correctamente
			GameManager::getInstance()->paidFoodMum();

			//Llamo a un metodo que vacia el carrito y resta los objetos que tenga que entregar
			changeCartSize(entity_->getChild("cart"));

			GameManager::getInstance()->checkEnd();

			//Audiod
			entity_->getComponent<AudioComponent>("audiocomponent")->playSound("SFX/Ambiente/BeepCaja.mp3");
		}
	}
}

void El_Horno::PlayerInteract::manageMeatTicket()
{
	// TODO Mostrar tecla E en la UI
	if (input_->isKeyDown(SDL_SCANCODE_E) || input_->isButtonDown(SDL_CONTROLLER_BUTTON_X)) {
		cout << "carne\n";
		meatTimer_->resetTimer();
		ticketTimerRunning_ = true;
		cout << maxTicketTime_ << "\n";
		//Audio
		entity_->getComponent<AudioComponent>("audiocomponent")->playSound("SFX/Ticket.mp3");

		//UIManager::getInstance()->setLayoutChildVisibility()
	}
}

void El_Horno::PlayerInteract::manageWheighingMachine()
{
	if (productLocked_ && handObject_ != nullptr && handObject_->getComponent<EntityId>("entityid")->getProdType() == ProductType::FRUIT) {
		cout << "fruta fuera\n";
		// TODO Mostrar tecla E en la UI

		if (input_->isKeyDown(SDL_SCANCODE_E) || input_->isButtonDown(SDL_CONTROLLER_BUTTON_X)) {
			productLocked_ = false;
			cout << "fruta dentro\n";
			//TODO Poner feedback de que el producto ha sido pesado
			entity_->getComponent<AudioComponent>("audiocomponent")->playSound("SFX/ComidaLista.mp3");
		}
	}
}

void El_Horno::PlayerInteract::manageFishCleaner()
{
	if (handObject_ != nullptr && handObject_->getComponent<EntityId>("entityid")->getProdType() == ProductType::FISH) {
		// TODO Mostrar tecla E en la UI 
		cout << "pescado fuera\n";
		// Si se presiona la E se inicia el timer de limpieza de pescado
		if (input_->isKeyDown(SDL_SCANCODE_E) || input_->isButtonDown(SDL_CONTROLLER_BUTTON_X)) {
			productLocked_ = false;
			fishTimerRunning_ = true;
			fishTimer_->resetTimer();
			deleteAliment(true);

			auto pc = entity_->getComponent<PlayerController>("playercontroller");
			pc->setPlayerState(El_Horno::PLAYER_DEFAULT);
			anim_->setAnimBool("AnyState", "Idle", true);
			cout << "pescado dentro\n";
			//Audio
			entity_->getComponent<AudioComponent>("audiocomponent")->playSound("SFX/CortarAlimento.mp3");
		}
	}
	else if (fishObtainable_ && handObject_ == nullptr) {
		// TODO Mostrar tecla E en la UI 
		// Si el pescado esta limpio
		if (input_->isKeyDown(SDL_SCANCODE_E) || input_->isButtonDown(SDL_CONTROLLER_BUTTON_X)) {
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
		if (input_->isKeyDown(SDL_SCANCODE_E) || input_->isButtonDown(SDL_CONTROLLER_BUTTON_X)) {
			cout << "Se obtuvo carne\n";

			// ESTO SERA "carne" CUANDO TENGAMOS EL MESH
			createProduct("Agua", ProductType::DEFAULT);
			meatObtainable_ = false;
		}
	}
}

void El_Horno::PlayerInteract::manageEstantery(EntityId* idEntity)
{
	//Si tiene alimento en la mano o el carro...
	if (handObject_ != nullptr || carryingCart_)
		//No ocurre nada
		return;

	// TODO Mostrar tecla E en la UI 
	if (input_->isKeyDown(SDL_SCANCODE_E) || input_->isButtonDown(SDL_CONTROLLER_BUTTON_X)) {
		// Crear entidad producto
		createProduct(idEntity->getId(), idEntity->getProdType());
	}
}

void El_Horno::PlayerInteract::createProduct(std::string id, ProductType pType)
{
	cout << "CREO PRODUCTO UO\n";

	Scene* scene = entity_->getScene();
	Transform* playerTr = entity_->getComponent<Transform>("transform");

	handObject_ = scene->addEntity("product", scene->getName());
	handObject_->addComponent<Transform>("transform", HornoVector3(0, 0, 0),
		HornoVector3(-90, 0, 0), HornoVector3(25, 25, 25), true);

	handObject_->addComponent<Mesh>("mesh", id);
	handObject_->addComponent<EntityId>("entityid", Type::PRODUCT, pType, id);

	handObject_->awake();
	handObject_->start();

	entity_->getComponent<Mesh>("mesh")->attachObject("Producto", handObject_);

	// Se bloquea la posibilidad de meterlo al carrito hasta que se tomen las acciones pertinentes
	if (pType == ProductType::FISH || pType == ProductType::FRUIT)
		productLocked_ = true;

	auto pc = entity_->getComponent<PlayerController>("playercontroller");
	pc->setPlayerState(El_Horno::PLAYER_PRODUCT);
	anim_->setAnimBool("AnyState", "Idle_with_product", true);

	//Audio
	entity_->getComponent<AudioComponent>("audiocomponent")->playSound("SFX/CogerObjerto.mp3");
}

void El_Horno::PlayerInteract::managePuddle()
{
	entity_->getComponent<RigidBody>("rigidbody")->setDamping(0.05f, 0.05f);
	entity_->getComponent<PlayerController>("playercontroller")->setSliding(true);
}

void El_Horno::PlayerInteract::dropItem()
{
	if (handObject_ != nullptr) {
		deleteAliment(false);
		productLocked_ = false;

		auto pc = entity_->getComponent<PlayerController>("playercontroller");
		pc->setPlayerState(El_Horno::PLAYER_DEFAULT);
		anim_->setAnimBool("AnyState", "Idle", true);
		//Audio
		entity_->getComponent<AudioComponent>("audiocomponent")->playSound("SFX/SoltarObjeto.mp3");
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
		entity->addComponent<Mesh>("mesh", "cube");
		entity->getComponent<Mesh>("mesh")->awake();
		entity->getComponent<Mesh>("mesh")->start();
	}
	else if (porcentaje >= 50) {
		//Cambia a medio lleno
		//Eliminamos el mesh
		entity->removeComponent("mesh");
		//Y metemos el nuevo
		entity->addComponent<Mesh>("mesh", "cube");
		entity->getComponent<Mesh>("mesh")->awake();
		entity->getComponent<Mesh>("mesh")->start();

	}
	else if (porcentaje > 0) {
		//Cambia a medio vacio
		//Eliminamos el mesh
		entity->removeComponent("mesh");
		//Y metemos el nuevo
		entity->addComponent<Mesh>("mesh", "cube");
		entity->getComponent<Mesh>("mesh")->awake();
		entity->getComponent<Mesh>("mesh")->start();

	}
}

void El_Horno::PlayerInteract::instanciateCart()
{
	//Carro hijo del player
	Transform* tr = entity_->getChild("cart")->getComponent<Transform>("transform");
	Entity* cart = SceneManager::getInstance()->getCurrentScene()->addEntity("cartInstance", "prueba");
	cart->addComponent<Transform>("transform", OgreVectorToHorno(tr->getGlobalPosition()),
		HornoVector3(0, 0, 0), HornoVector3(0.2, 0.2, 0.2));
	cart->addComponent<Mesh>("mesh", "cube");
	cart->addComponent<RigidBody>("rigidbody", 100.0f, false, false, 0);
	cart->awake();
	cart->start();
	cart->getComponent<RigidBody>("rigidbody")->setAngularFactor(0);
	//Trigger del carrito
	Entity* trig = SceneManager::getInstance()->getCurrentScene()->addEntity("cartTriggerInstance", "prueba", cart);
	trig->addComponent<Transform>("transform", HornoVector3(0, 0, 0), HornoVector3(0, 0, 0), HornoVector3(3.5, 3, 3.5));
	trig->addComponent<RigidBody>("rigidbody", 1.0f, true, true, 0);
	trig->addComponent<EntityId>("entityid", Type::CART);
	trig->awake();
	trig->start();
}

void El_Horno::PlayerInteract::imInCartRegister(bool imIn)
{
	inCashRegister_ = imIn;
}

void El_Horno::PlayerInteract::setEstantery(Entity* e, bool enter)
{
	if (enter)
		triggeredEntities_.push_back(e);
	else {
		for (size_t i = 0; i < triggeredEntities_.size(); i++)
		{
			if (e == triggeredEntities_[i]) {
				triggeredEntities_.erase(triggeredEntities_.begin() + i);
				return;
			}
		}
	}
}
