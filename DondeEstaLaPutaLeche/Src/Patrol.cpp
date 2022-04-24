#include "Patrol.h"

#include "Entity.h"
#include "Transform.h"
#include "Rigibody.h"
#include "btBulletCollisionCommon.h"
#include <iostream>

El_Horno::Patrol::Patrol(float tspeed, const std::vector<HornoVector3>& pos)
{
	for (auto p : pos) {
		positions.push(p);
	}

	speed = tspeed;
}

void El_Horno::Patrol::start()
{
	rb = entity_->getComponent<RigidBody>("rigidbody");
	tr = entity_->getComponent<Transform>("transform");
}

void El_Horno::Patrol::update()
{
	if (!positions.empty()) {
		auto pos = positions.front();
		if (isClose()) {
			positions.pop();
			positions.push(pos);
			pos = positions.front();
		}

		auto dir = HornoVectorToBullet(pos) - HornoVectorToBullet(tr->getHornoGlobalPosition());

		rb->setLinearVelocity(dir.normalized() * speed);
	}
}

void El_Horno::Patrol::setSpeed(float s)
{
	speed = s;
}

void El_Horno::Patrol::addPosition(const HornoVector3& pos)
{
	positions.push(pos);
}

bool El_Horno::Patrol::isClose()
{
	auto diff = HornoVectorToBullet(tr->getHornoGlobalPosition()) - HornoVectorToBullet(positions.front());
	double magnitude = diff.length();

	return magnitude <= minRange;
}
