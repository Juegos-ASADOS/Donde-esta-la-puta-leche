#pragma once
#ifndef _ENTITY_ID_H
#define _ENTITY_ID_H

#include <Component.h>

namespace El_Horno {
	class RigidBody;
	enum Type { PRODUCT, ESTANTERY, CART, CASHREGISTER, MEATTICKET, FISHCLEANER, WHEIGHINGMACHINE, PUDDLE };
	enum ProductType { NONE, DEFAULT, FRUIT, FISH, MEAT };

	class EntityId : public Component
	{
	public:
		EntityId(Type type, ProductType prodType = ProductType::NONE, std::string id = "") : id_(id), type_(type), productType_(prodType) {};
		EntityId() {};

		//void start() override;
		//void setParameters(std::vector<std::pair<std::string, std::string>> parameters) override;
		inline const std::string getId() { return id_; };
		inline const Type getType() { return type_; };
		inline const ProductType getProdType() { return productType_; };
		//inline const bool isEstantery() { return isEstantery_; };
		//inline const bool isCart() { return isCart_; }
		//inline const bool isCashRegister() { return isCashRegister_; }

		virtual bool recieveEvent(Event* ev);
	protected:
		std::string id_;
		Type type_;
		ProductType productType_;
		/*bool isEstantery_;
		bool isCart_;
		bool isCashRegister_;*/
	};
}
#endif 

