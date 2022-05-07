#pragma once
#ifndef _PATROL_H
#define _PATROL_H

#include <Component.h>
#include <queue>
#include "HornoVector3.h"

namespace El_Horno {
	class Transform;
	class RigidBody;
	class AnimatorController;

	struct PatrolPos {
		HornoVector3 pos;
		float wait_time;
	};

	class Patrol : public Component
	{
	public:
		Patrol(float tspeed, int type, const std::vector<PatrolPos>& pos = std::vector<PatrolPos>());
		Patrol();

		void setParameters(std::vector<std::pair<std::string, std::string>> parameters) override;
		void start() override;
		void update() override;

		void setSpeed(float s);
		void setRange(float r) { minRange_ = r; };
		void addPosition(const PatrolPos& pos);
		void addPosition(const HornoVector3& pos, float time);
		void addPosition(float x, float z, float time);
	private:
		bool isClose();
		bool isWaiting();

		Transform* tr_;
		RigidBody* rb_;
		AnimatorController* anim_;
		std::queue<PatrolPos> positions_;

		float speed_ = 1.0f;
		float minRange_ = 5.0f;

		double timer = 0.0;

		bool walking_ = false,
			sleepThresh_;

		int type_ = 0;
		std::string idleName;
		std::string walkName;
	};
}
#endif 

