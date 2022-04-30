#include "Patrol.h"

#include "Entity.h"
#include "Transform.h"
#include "Rigibody.h"
#include "AnimatorController.h"
#include "ElHornoBase.h"

#include <iostream>

El_Horno::Patrol::Patrol(float tspeed, const std::vector<PatrolPos>& pos)
{
	for (auto p : pos) {
		positions_.push(p);
	}

	speed_ = tspeed;
}

El_Horno::Patrol::Patrol()
{
}

void El_Horno::Patrol::setParameters(std::vector<std::pair<std::string, std::string>> parameters)
{
	//ADAPTAR A PATROLPOS
	/*for (int i = 0; i < parameters.size(); i++) {
		if (parameters[i].first == "speed") {
			speed_ = stof(parameters[i].second);
		}
		else {
			positions_.push(OgreVectorToHorno(StringToVector(parameters[i].second)));
		}
	}*/
}

void El_Horno::Patrol::start()
{
	rb_ = entity_->getComponent<RigidBody>("rigidbody");
	tr_ = entity_->getComponent<Transform>("transform");
	anim_ = entity_->getComponent<AnimatorController>("animatorController");
}

void El_Horno::Patrol::update()
{
	if (!positions_.empty()) {

		if (isWaiting())
			return;

		PatrolPos pos = positions_.front();
		if (isClose()) {
			//Nueva posicion
			positions_.pop();
			positions_.push(pos);
			pos = positions_.front();

			//Reset de tiempo
			timer = 0;
		}

		HornoVector3 dir =	pos.pos - tr_->getHornoGlobalPosition();

		dir.y_ = 0; // Irrelevante

		rb_->setLinearVelocity(dir.normalized() * speed_);

		//Animacion
		if (anim_)
		{
			if (rb_->getHornoLinearVelocity().magnitude() > 1)
			{
				if (!walking_)
				{
					anim_->setAnimBool("Idle", "npc_walk", true);
					walking_ = true;
				}
			}
			else if (walking_)
			{
				anim_->setAnimBool("npc_walk", "Idle", true);
				walking_ = false;
			}
		}
	}
}

void El_Horno::Patrol::setSpeed(float s)
{
	speed_ = s;
}

void El_Horno::Patrol::addPosition(const PatrolPos& pos)
{
	positions_.push(pos);
}

void El_Horno::Patrol::addPosition(const HornoVector3& pos, float time)
{
	positions_.push({ pos, time });
}

void El_Horno::Patrol::addPosition(float x, float z, float time)
{
	positions_.push({ {x, 0, z}, time });
}

bool El_Horno::Patrol::isClose()
{
	HornoVector3 diff = tr_->getHornoGlobalPosition() - positions_.front().pos;
	float magnitude = diff.magnitude();

	return magnitude <= minRange_;
}

bool El_Horno::Patrol::isWaiting()
{
	if (timer < positions_.front().wait_time) {
		timer += ElHornoBase::getInstance()->getDeltaTime();
		return true;
	}
	return false;
}
