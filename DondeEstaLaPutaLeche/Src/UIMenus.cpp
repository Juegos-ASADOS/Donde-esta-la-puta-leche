#include "UIMenus.h"

#include <Scene.h>
#include <SceneManager.h>
#include <UILayout.h>
#include <Transform.h>
#include <Entity.h>

#include "InputManager.h"
#include <iostream>

namespace El_Horno {

	bool click() {
		std::cout << "CLICK GE EGCGI CKUCJ\n";
		return true;
	}

	UIMenus::UIMenus()
	{
	}

	void UIMenus::start()
	{
		menu = SceneManager::getInstance()->getCurrentScene()->addEntity("menuprincipal", "prueba");
		menu->addComponent<Transform>("transform", HornoVector3(0, 0, 0), HornoVector3(0, 0, 0), HornoVector3(1, 1, 1));
		menu->addComponent<UILayout>("uilayout", "MenuPrincipal_Opciones", "first");
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
		menu->getComponent<UILayout>("uilayout")->removeLayout();
	}

	void UIMenus::show()
	{
		menu->getComponent<UILayout>("uilayout")->loadScheme("GWEN");
		menu->getComponent<UILayout>("uilayout")->loadScheme("DondeTaLeche");
		menu->getComponent<UILayout>("uilayout")->loadScheme("TaharezLook");
		menu->getComponent<UILayout>("uilayout")->loadScheme("Generic");
		//menu->getComponent<UILayout>("uilayout")->createButton("TaharezLook", "Button", "start");
		menu->getComponent<UILayout>("uilayout")->loadLayout();
		menu->getComponent<UILayout>("uilayout")->subscribeChildEvent("Menu/BotonVolver", click);
	}

}