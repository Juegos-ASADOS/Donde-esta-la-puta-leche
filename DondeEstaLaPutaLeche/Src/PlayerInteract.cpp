
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
			return manageCart(ev,entity);
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
	
	//Si no tiene alimentos que coger...
	
	//TODO TENDRA QUE SER ==1 PQ EL TRIGGER YA ES UN HIJO
	if (entity_->getChildCount() == 0)
		//No ocurre nada
		return false;

	//Si pulsas la tecla E...
	if (input->isKeyDown(SDL_SCANCODE_E)) {

		//Si puedo meterlo..
		if (!GameManager::getInstance()->checkObject("ay")) {
			//No necesito añadirlo a la lista pq el metodo de antes del GM ya lo hace


			//Elimino el objeto que tenga en la mano
			

			//TODO


			return true;
		}
		//No puedes meterlo
		else {

			//Lo tiro a tomar por culo



			//Igual aqui es otro return true creo
			return true;
		}

		
	}

	//TODO SI PULSAS OTRA TECLA COGES O SUELTAS EL CARRITO

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
