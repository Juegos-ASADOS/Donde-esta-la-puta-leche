#pragma once
#ifndef _PATROL_H
#define _PATROL_H

#include <Component.h>
#include <queue>
#include "HornoVector3.h"

namespace El_Horno {
	class Transform;
	class RigidBody;

	class Patrol : public Component
	{
	public:
		Patrol(float tspeed, const std::vector<HornoVector3>& pos = std::vector<HornoVector3>());

		void start() override;
		void update() override;

		void setSpeed(float s);
		void setRange(float r) { minRange = r; };
		void addPosition(const HornoVector3& pos);
	private:
		bool isClose();

		Transform* tr;
		RigidBody* rb;
		std::queue<HornoVector3> positions;

		float speed = 1.0f;
		float minRange = 5.0f;
	};
}
#endif 

