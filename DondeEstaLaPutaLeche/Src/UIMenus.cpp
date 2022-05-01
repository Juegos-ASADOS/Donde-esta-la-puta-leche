#include "UIMenus.h"

#include <Scene.h>
#include <SceneManager.h>
#include <UILayout.h>
#include <Transform.h>
#include <Entity.h>
#include "CEGUI/EventArgs.h"

#include "InputManager.h"
#include <iostream>

namespace El_Horno {

	bool click(const CEGUI::EventArgs&) {
		std::cout << "CLICK GE EGCGI CKUCJ\n";
		return true;
	}

	UIMenus::UIMenus()
	{
	}

	void UIMenus::start()
	{
		menu = SceneManager::getInstance()->getCurrentScene()->addEntity("menu", "prueba");
		menu->addComponent<Transform>("transform", HornoVector3(0, 0, 0), HornoVector3(0, 0, 0), HornoVector3(1, 1, 1));
		menu->addComponent<UILayout>("uilayout", "TaharezLookOverview", "first");
		menu->awake();
		menu->start();
		menu->getComponent<UILayout>("uilayout")->subscribeChildEvent("clikao", click);
	}

	void UIMenus::update()
	{
		if (InputManager::getInstance()->isKeyDown(SDL_SCANCODE_M)) {
			show();
		}
		else if (InputManager::getInstance()->isKeyDown(SDL_SCANCODE_N)) {
			hide();
		}
	}

	void UIMenus::hide()
	{
		menu->getComponent<UILayout>("uilayout")->removeLayout();
	}

	void UIMenus::show()
	{
		menu->getComponent<UILayout>("uilayout")->loadScheme("TaharezLook");
		menu->getComponent<UILayout>("uilayout")->loadScheme("Generic");
		menu->getComponent<UILayout>("uilayout")->loadLayout();
	}

}