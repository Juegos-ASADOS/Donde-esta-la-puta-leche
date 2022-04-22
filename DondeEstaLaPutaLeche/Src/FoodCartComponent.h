#pragma once
#ifndef _FOODCART_COMPONENT_H
#define _FOODCART_COMPONENT_H

#include <Component.h>
#include <map>

//Componente propio del carrito que gestiona las cosas que tenga en la lista


namespace El_Horno {

	class FoodCartComponent : public Component
	{
	public:
		FoodCartComponent();

		void start() override;
		void update() override;

		bool puedoMeterlo(std::string comida);

	protected:

		//TODO DEBE SER ESTE COMPONENTE EL QUE GESTIONE CUANDO COÑO CAMBIAR LA IMAGEN DEL CARRITO. QUITAR DEL PLAYER INTERACT
		int foodStored;
		int allFoodStored;

		//NO SE DONDE NI COMO CARGAR LA LISTA PERO OKAY
		std::map<std::string, int> infoList;

		std::map<std::string, int> actualList;
	};
}
#endif 

