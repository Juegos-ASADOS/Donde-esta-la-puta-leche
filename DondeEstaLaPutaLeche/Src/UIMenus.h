#pragma once
#ifndef _UI_MENUS_H
#define _UI_MENUS_H

#include <Component.h>

namespace El_Horno {
	class UIMenus : public Component
	{
	public:
		UIMenus();

		void start() override;
		void update() override;

	private:

		void hide();
		void show();

		Entity* menu;
	};
}
#endif _UI_MENUS_H

