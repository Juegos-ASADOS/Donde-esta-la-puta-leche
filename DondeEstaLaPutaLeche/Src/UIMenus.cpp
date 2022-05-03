#include "UIMenus.h"

#include <Scene.h>
#include <SceneManager.h>
#include <UILayout.h>
#include <Transform.h>
#include <Entity.h>

#include "InputManager.h"
#include <iostream>

namespace El_Horno {

	bool click(const CEGUI::EventArgs& e) {
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
		menu->addComponent<UILayout>("uilayout");
		menu->awake();
		menu->start();
	}

	void UIMenus::update()
	{
		if (InputManager::getInstance()->getKeyDown(SDL_SCANCODE_M)) {
			show();
		}
		else if (InputManager::getInstance()->getKeyDown(SDL_SCANCODE_N)) {
			hide();
		}
	}

	void UIMenus::hide()
	{
		menu->getComponent<UILayout>("uilayout")->setLayoutVisibility("MenuPrincipal", false);
	}

	void UIMenus::show()
	{
		menu->getComponent<UILayout>("uilayout")->loadScheme("DondeTaLeche");
		menu->getComponent<UILayout>("uilayout")->loadScheme("GWEN");
		menu->getComponent<UILayout>("uilayout")->addLayout("MenuPrincipal", "menuPrincipal");
		menu->getComponent<UILayout>("uilayout")->setLayoutVisibility("MenuPrincipal", true);
		//menu->getComponent<UILayout>("uilayout")->subscribeChildEvent("MenuPrincipal/Fondo", click);
	}

}