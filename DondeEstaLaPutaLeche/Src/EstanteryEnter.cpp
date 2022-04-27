#include "GameFactories.h"
#include "EstanteryEnter.h"
#include "Rigibody.h"
#include "Mesh.h"
#include "Transform.h"
#include "HornoVector3.h"
#include "Entity.h"
#include "Scene.h"
#include "Event.h"
#include "InputManager.h"
#include "ElHornoBase.h"
#include "btBulletCollisionCommon.h"
#include "EntityId.h"
#include <iostream>

void El_Horno::EstanteryEnter::start()
{
	input = ElHornoBase::getInstance()->getInputManager();

}

void El_Horno::EstanteryEnter::update()
{

}

bool El_Horno::EstanteryEnter::recieveEvent(Event* ev)
{
	if (entity_->getChildCount() != 0)
		return false;

	//std::cout << ev->ty_ << "\n";
	if (ev->ty_ == EventType::CollisionStay) {

		// Coge Id de la estanteria
		Entity* estantery = static_cast<rbTriggerStay*>(ev)->other_->getParent();
		if (estantery == nullptr)
			return false;

		EntityId* estComp = estantery->getComponent<EntityId>("entityid");

		if (estComp != nullptr && estComp->getType() == Type::ESTANTERY) {

			// TODO Mostrar tecla E en la UI 

			if (input->isKeyDown(SDL_SCANCODE_E)) {

				Scene* scene = estantery->getScene();
				Transform* playerTr = entity_->getComponent<Transform>("transform");

				// Crear entidad producto
				Entity* product = scene->addEntity("product", scene->getName(), entity_);

				/*product->addComponent<Transform>("transform", HornoVector3(playerTr->getHornoPosition().x_ + 4, playerTr->getHornoPosition().y_, playerTr->getHornoPosition().z_),
					HornoVector3(0, 0, 0), HornoVector3(0.25, 0.25, 0.25));*/
				product->addComponent<Transform>("transform", HornoVector3(-10, 0, 0),
					HornoVector3(-90, 0, 0), HornoVector3(1, 1, 1));

				product->addComponent<Mesh>("mesh", estComp->getId());
				product->addComponent<RigidBody>("rigidbody", 2.0f, true, true, 0);
				product->addComponent<EntityId>("entityid", estComp->getId(), Type::PRODUCT);

				product->start();

				return true;
			}
		}
	}
	return false;
}
