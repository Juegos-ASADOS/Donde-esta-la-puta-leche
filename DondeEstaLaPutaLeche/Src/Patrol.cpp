#include "Patrol.h"

#include "Entity.h"
#include "Transform.h"
#include "Rigibody.h"
#include "AnimatorController.h"
#include "btBulletCollisionCommon.h"
#include <iostream>

El_Horno::Patrol::Patrol(float tspeed, const std::vector<HornoVector3>& pos)
{
	for (auto p : pos) {
		positions_.push(p);
	}

	speed_ = tspeed;
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
		auto pos = positions_.front();
		if (isClose()) {
			positions_.pop();
			positions_.push(pos);
			pos = positions_.front();
		}

		auto dir = HornoVectorToBullet(pos) - HornoVectorToBullet(tr_->getHornoGlobalPosition());

		rb_->setLinearVelocity(dir.normalized() * speed_);

		//Animacion
		if (anim_)
		{
			if (rb_->getLinearVelocity().length() > 1)
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

void El_Horno::Patrol::addPosition(const HornoVector3& pos)
{
	positions_.push(pos);
}

bool El_Horno::Patrol::isClose()
{
	auto diff = HornoVectorToBullet(tr_->getHornoGlobalPosition()) - HornoVectorToBullet(positions_.front());
	double magnitude = diff.length();

	return magnitude <= minRange_;
}
