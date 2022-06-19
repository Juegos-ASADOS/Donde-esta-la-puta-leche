#pragma once
#ifndef _GAME_FACTORIES_H
#define _GAME_FACTORIES_H

#include "ElHornoBase.h"
#include "FactoryCreator.h"

namespace El_Horno {
	namespace Donde_Esta_La_Puta_Leche {
		inline void addFactories() {
			FactoryCreator* creator = ElHornoBase::getInstance()->getFactoryCreator();

			creator->addFactory("playercontroller");
			creator->addFactory("playerinteract");
			creator->addFactory("gamemanager");
			creator->addFactory("entityid");
			creator->addFactory("pushbutton");
			creator->addFactory("patrol");
			creator->addFactory("uimenus");
		}
	}
}

#endif 
