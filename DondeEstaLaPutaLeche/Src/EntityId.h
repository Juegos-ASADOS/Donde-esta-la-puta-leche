#pragma once
#ifndef _ENTITY_ID_H
#define _ENTITY_ID_H

#include <Component.h>

namespace El_Horno {
	class RigidBody;
	enum Type { PRODUCT, ESTANTERY, CART, CASHREGISTER, MEATTICKET };

	class EntityId : public Component
	{
	public:
		EntityId(std::string id, Type type) : id_(id), type_(type) {};
		EntityId() {};

		//void start() override;
		//void setParameters(std::vector<std::pair<std::string, std::string>> parameters) override;
		inline const std::string getId() { return id_; };
		inline const Type getType() { return type_; };
		//inline const bool isEstantery() { return isEstantery_; };
		//inline const bool isCart() { return isCart_; }
		//inline const bool isCashRegister() { return isCashRegister_; }

		virtual bool recieveEvent(Event* ev);
	protected:
		std::string id_;
		Type type_;
		/*bool isEstantery_;
		bool isCart_;
		bool isCashRegister_;*/
	};
}
#endif 

