#pragma once
#ifndef _ENTITY_ID_H
#define _ENTITY_ID_H

#include <Component.h>

namespace El_Horno {
	class RigidBody;
	namespace Donde_Esta_La_Puta_Leche {
		enum Type { PRODUCT, ESTANTERY, CART, CASHREGISTER, MEATTICKET, MEATSTATION, FISHCLEANER, WHEIGHINGMACHINE, PUDDLE };
		enum ProductType { NONE, DEFAULT, FRUIT, FISH };

		class EntityId : public Component
		{
		public:
			EntityId(Type type, ProductType prodType = ProductType::NONE, std::string id = "") : id_(id), type_(type), productType_(prodType) {};
			EntityId() {};

			void setParameters(std::vector<std::pair<std::string, std::string>> parameters) override;
			inline const std::string getId() { return id_; };
			inline const Type getType() { return type_; };
			inline const ProductType getProdType() { return productType_; };

			virtual bool recieveEvent(Event* ev);
		protected:
			std::string id_;
			Type type_;
			ProductType productType_;
		};
	}
}
#endif 

