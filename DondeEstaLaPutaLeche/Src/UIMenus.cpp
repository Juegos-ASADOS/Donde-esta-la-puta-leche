#include "UIMenus.h"

#include <Scene.h>
#include <LuaManager.h>
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
		menu = entity_->getScene()->addEntity("menudeprueba", entity_->getScene()->getName());
		menu->addComponent<Transform>("transform", HornoVector3(0, 0, 0), HornoVector3(0, 0, 0), HornoVector3(1, 1, 1));
		menu->addComponent<UILayout>("uilayout");
		menu->awake();
		menu->start();
		menu->getComponent<UILayout>("uilayout")->loadScheme("GWEN");
		menu->getComponent<UILayout>("uilayout")->loadScheme("DondeTaLeche");
		menu->getComponent<UILayout>("uilayout")->loadScheme("TaharezLook");
		menu->getComponent<UILayout>("uilayout")->loadScheme("Generic");
		//menu->getComponent<UILayout>("uilayout")->createButton("TaharezLook", "Button", "start");
		menu->getComponent<UILayout>("uilayout")->addLayout("MenuPrincipal"); //Nombre del layout, y nombre interno cualquiera(que no se repita)
		menu->getComponent<UILayout>("uilayout")->addLayout("Pausa"); //Nombre del layout, y nombre interno cualquiera(que no se repita)
		menu->getComponent<UILayout>("uilayout")->addLayout("Carballo"); //Nombre del layout, y nombre interno cualquiera(que no se repita)
	}

	void UIMenus::update()
	{
		if (InputManager::getInstance()->getKeyDown(SDL_SCANCODE_M)) {
			show("MenuPrincipal");
		}
		else if (InputManager::getInstance()->getKeyDown(SDL_SCANCODE_N)) {
			hide("MenuPrincipal");
		}
		else if (InputManager::getInstance()->getKeyDown(SDL_SCANCODE_B)) {
			show("Pausa");
		}
		else if (InputManager::getInstance()->getKeyDown(SDL_SCANCODE_V)) {
			hide("Pausa");
		}
		else if (InputManager::getInstance()->getKeyDown(SDL_SCANCODE_O)) {
			show("Carballo");
		}
		else if (InputManager::getInstance()->getKeyDown(SDL_SCANCODE_P)) {
			hide("Carballo");
		}
	}
	void UIMenus::show(std::string m)
	{
		menu->getComponent<UILayout>("uilayout")->setLayoutVisibility(m, true);
	}
	void UIMenus::hide(std::string m)
	{
		menu->getComponent<UILayout>("uilayout")->setLayoutVisibility(m, false);
	}


}