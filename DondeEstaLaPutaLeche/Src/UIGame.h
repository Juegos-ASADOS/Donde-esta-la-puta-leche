#pragma once
#ifndef _UI_GAME_H
#define _UI_GAME_H

#include <Component.h>

#include "UIManager.h"

namespace El_Horno {
	class UIGame : public Component
	{
	public:
		UIGame();

		void start() override;
		void update() override;

	private:

		void show(std::string menu);
		void hide(std::string menu);
		void setList();

		Entity* menu = nullptr;
	};
}
#endif _UI_GAME_H

