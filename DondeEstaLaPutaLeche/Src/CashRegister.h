#pragma once
#ifndef _CASH_REGISTER_H
#define _CASH_REGISTER_H

#include <Component.h>

//AHORA MISMO NO SIRVE DE NADA DE NADA AAAA TODO
namespace El_Horno {

	//Gestiona los eventos al llevar la comida a la madre
	class CashRegister : public Component
	{
	public:
		CashRegister();
		bool inCashRegister(Event* ev,bool enter);

		virtual bool recieveEvent(Event* ev);
	};
}
#endif 

