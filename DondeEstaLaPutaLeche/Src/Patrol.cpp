#include "Patrol.h"

#include "Entity.h"
#include "Transform.h"
#include "Rigibody.h"
#include "AnimatorController.h"
#include "ElHornoBase.h"
#include <sstream>

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
	for (int i = 0; i < parameters.size(); i++) {
		if (parameters[i].first == "speed") {
			speed_ = stof(parameters[i].second);
		}
		else {
			std::istringstream in(parameters[i].second);
			std::string val;
			std::vector<float> values;

			while (getline(in, val, ',')) {
				values.push_back(std::stod(val));
			}

			int i = 0;
			while (values.size() >= i + 4) {
				positions_.push({ HornoVector3( values[i], values[i+1], values[i+2]), values[i+3] });
				i += 4;
			}
		}
	}
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
			//Reset de tiempo
			timer = pos.wait_time;
			//Nueva posicion
			positions_.pop();
			positions_.push(pos);
			pos = positions_.front();

			rb_->setLinearVelocity({0,0,0});
			return;
		}

		HornoVector3 dir =	pos.pos - tr_->getHornoGlobalPosition();

		dir.y_ = 0; // Irrelevante

		rb_->setLinearVelocity(dir.normalized() * speed_);

		tr_->lookAt(HornoVector3(-dir.x_ + tr_->getPosition().x, tr_->getPosition().y, -dir.z_ + tr_->getPosition().z));

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
	diff.y_ = 0;
	float magnitude = diff.magnitude();

	return magnitude <= minRange_;
}

bool El_Horno::Patrol::isWaiting()
{
	if (timer > 0) {
		timer -= ElHornoBase::getInstance()->getDeltaTime();
		return true;
	}
	return false;
}
