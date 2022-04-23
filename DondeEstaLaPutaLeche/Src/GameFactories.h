#pragma once
#ifndef _GAME_FACTORIES_H
#define _GAME_FACTORIES_H

#include "ElHornoBase.h"
#include "FactoryCreator.h"

namespace El_Horno {
	namespace Game {
		inline void addFactories() {
			FactoryCreator* creator = ElHornoBase::getInstance()->getFactoryCreator();

			creator->addFactory("playercontroller");
			creator->addFactory("estanteryenter");
			creator->addFactory("entityid");
			creator->addFactory("pushbutton");
			creator->addFactory("patrol");
		}
	}
}

#endif 
