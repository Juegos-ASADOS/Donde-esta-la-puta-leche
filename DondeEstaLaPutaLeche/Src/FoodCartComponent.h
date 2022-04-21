#pragma once
#ifndef _ESTANTERY_COMPONENT_H
#define _ESTANTERY_COMPONENT_H

#include <Component.h>
#include <map>
//Componente propio del carrito que gestiona las cosas que tenga en la lista

using namespace std;

namespace El_Horno {

	enum foodType {Tomatico, platanito, pescao, carne};
	class FoodCartComponent : public Component
	{
	public:
		FoodCartComponent();

		void start() override;
		void update() override;

		bool puedoMeterlo(foodType comida);


	protected:

		//TODO DEBE SER ESTE COMPONENTE EL QUE GESTIONE CUANDO COÑO CAMBIAR LA IMAGEN DEL CARRITO. QUITAR DEL PLAYER INTERACT
		int foodStored;

		//NO SE DONDE NI COMO CARGAR LA LISTA PERO OKAY
		map<foodType, int> infoList;

		map<foodType, int> actualList;
		

	};
}
#endif 

