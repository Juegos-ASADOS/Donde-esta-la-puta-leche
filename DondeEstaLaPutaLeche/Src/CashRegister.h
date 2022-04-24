#pragma once
#ifndef _CASH_REGISTER_H
#define _CASH_REGISTER_H

#include <Component.h>

namespace El_Horno {

	class CashRegister : public Component
	{
	public:
		CashRegister() {};

		void start() override;
		void update() override;
		bool inCashRegister(Event* ev,bool enter);

		virtual bool recieveEvent(Event* ev);
	protected:
	};
}
#endif 

