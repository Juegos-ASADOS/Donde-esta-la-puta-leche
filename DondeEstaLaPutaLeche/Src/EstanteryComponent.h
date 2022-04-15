#pragma once
#ifndef _ESTANTERY_COMPONENT_H
#define _ESTANTERY_COMPONENT_H

#include <Component.h>


namespace El_Horno {
	class RigidBody;
	enum estanteryType {TOMATES, COCACOLA};

	class EstanteryComponent : public Component
	{
	public:
		EstanteryComponent(estanteryType id) : id_(id) {};

		void start() override;
		//void update() override;

		inline const estanteryType getId() { return id_; };
	protected:
		//RigidBody* rb_;
		estanteryType id_;
	};
}
#endif 

