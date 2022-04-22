#pragma once
#ifndef _ENTITY_ID_H
#define _ENTITY_ID_H

#include <Component.h>

namespace El_Horno {
	class RigidBody;

	class EntityId : public Component
	{
	public:
		EntityId(std::string id, bool est = false, bool isCart = false) : id_(id), isEstantery_(est), isCart_(isCart) {};

		//void start() override;

		inline const std::string getId() { return id_; };
		inline const bool isEstantery() { return isEstantery_; };
		inline const bool isCart() { return isCart_; }
	protected:
		std::string id_;
		bool isEstantery_;
		bool isCart_;
	};
}
#endif 

