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

		auto dir = HornoVectorToBullet(pos) - HornoVectorToBullet(tr->getHornoPosition());

		rb->setLinearVelocity(dir.normalized() * speed);

		std::cout << "GOING TO " << pos.x_ << " " << pos.y_ << " " << pos.z_ << "\n";
		std::cout << "FROM " << tr->getHornoPosition().x_ << " " << tr->getHornoPosition().y_ << " " << tr->getHornoPosition().z_ << "\n";

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
	auto diff = HornoVectorToBullet(tr->getHornoPosition()) - HornoVectorToBullet(positions.front());
	double magnitude = diff.length();

	return magnitude <= minRange;
}
