#include "GameFactories.h"
#include "Entity.h"
#include "ElHornoBase.h"
#include "FoodCartComponent.h"
#include <EntityId.h>

El_Horno::FoodCartComponent::FoodCartComponent()
{

}

void El_Horno::FoodCartComponent::start()
{

}

void El_Horno::FoodCartComponent::update()
{

}

bool El_Horno::FoodCartComponent::puedoMeterlo(std::string comida)
{
	//Buscamos el alimento...
	auto aux = infoList.find(comida);

	//Si ha llegado al final...
	if (aux == infoList.end())
		//Es porque ni si quiera hay que comprarlo
		return false;
	//Si ha parado para buscarlo...
	else {

		//Si los alimentos que tengo son menores a los que necesito...
		if (actualList.at(aux->first) < aux->second) {



			//Le sumamos el alimento
			actualList.find(comida)->second++;


			//TODO VAINAS DEL FOODSTORED

			foodStored++;


			//Y se guarda
			return true;
		}
		//Si ya he cogido el numero maximo de ese alimento...
		else
			//No puedo meter más
			return false;
	}

}
