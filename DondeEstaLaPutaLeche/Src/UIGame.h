#pragma once
#ifndef _UI_GAME_H
#define _UI_GAME_H

#include <Component.h>

#include "UIManager.h"

namespace El_Horno {
	namespace Donde_Esta_La_Puta_Leche {
		class UIGame : public Component
		{
		public:
			UIGame();

			void start() override;
			void update() override;

			void setTicketIntro();
			void setTicketTurno();
			void setTicketLimite();
			void hideTicket();
			void setList();

		private:

			void show(std::string menu);
			void hide(std::string menu);

			Entity* menu = nullptr;
		};
	}
}
#endif _UI_GAME_H

