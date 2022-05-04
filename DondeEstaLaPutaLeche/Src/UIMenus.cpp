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
		menu->getComponent<UILayout>("uilayout")->addLayout("MenuPrincipal_Opciones"); //Nombre del layout, y nombre interno cualquiera(que no se repita)
		menu->getComponent<UILayout>("uilayout")->addLayout("Pausa"); //Nombre del layout, y nombre interno cualquiera(que no se repita)
		menu->getComponent<UILayout>("uilayout")->addLayout("Pausa_Opciones"); //Nombre del layout, y nombre interno cualquiera(que no se repita)


		//añadir la funcionalidad a los botones

		//menu principal
		auto helperFunction = std::bind(&UIMenus::play_button, this, std::placeholders::_1);
		menu->getComponent<UILayout>("uilayout")->subscribeChildEvent("MenuPrincipal", "Menu/Boton", helperFunction);
		helperFunction = std::bind(&UIMenus::opciones_button, this, std::placeholders::_1);
		menu->getComponent<UILayout>("uilayout")->subscribeChildEvent("MenuPrincipal", "Menu/Boton2", helperFunction);
		helperFunction = std::bind(&UIMenus::creditos_button, this, std::placeholders::_1);
		menu->getComponent<UILayout>("uilayout")->subscribeChildEvent("MenuPrincipal", "Menu/Boton3", helperFunction);
		helperFunction = std::bind(&UIMenus::salir_button, this, std::placeholders::_1);
		menu->getComponent<UILayout>("uilayout")->subscribeChildEvent("MenuPrincipal", "Menu/Boton4", helperFunction);

		//menu opciones desde principal

		helperFunction = std::bind(&UIMenus::restaMusica, this, std::placeholders::_1);
		menu->getComponent<UILayout>("uilayout")->subscribeChildEvent("MenuPrincipal_Opciones", "Menu/RestaMusica", helperFunction);
		helperFunction = std::bind(&UIMenus::sumaMusica, this, std::placeholders::_1);
		menu->getComponent<UILayout>("uilayout")->subscribeChildEvent("MenuPrincipal_Opciones", "Menu/SumaMusica", helperFunction);
		helperFunction = std::bind(&UIMenus::restaEfectos, this, std::placeholders::_1);
		menu->getComponent<UILayout>("uilayout")->subscribeChildEvent("MenuPrincipal_Opciones", "Menu/RestaEfectos", helperFunction);
		helperFunction = std::bind(&UIMenus::sumaEfectos, this, std::placeholders::_1);
		menu->getComponent<UILayout>("uilayout")->subscribeChildEvent("MenuPrincipal_Opciones", "Menu/SumaEfectos", helperFunction);
		helperFunction = std::bind(&UIMenus::restaResolucion, this, std::placeholders::_1);
		menu->getComponent<UILayout>("uilayout")->subscribeChildEvent("MenuPrincipal_Opciones", "Menu/FlechaIz", helperFunction);
		helperFunction = std::bind(&UIMenus::sumaResolucion, this, std::placeholders::_1);
		menu->getComponent<UILayout>("uilayout")->subscribeChildEvent("MenuPrincipal_Opciones", "Menu/FlechaDer", helperFunction);
		helperFunction = std::bind(&UIMenus::vuelveOpcionesMenu, this, std::placeholders::_1);
		menu->getComponent<UILayout>("uilayout")->subscribeChildEvent("MenuPrincipal_Opciones", "Menu/BotonVolver", helperFunction);

		//menu opciones desde la pausa

		helperFunction = std::bind(&UIMenus::restaMusica, this, std::placeholders::_1);
		menu->getComponent<UILayout>("uilayout")->subscribeChildEvent("Pausa_Opciones", "Menu/RestaMusica", helperFunction);
		helperFunction = std::bind(&UIMenus::sumaMusica, this, std::placeholders::_1);
		menu->getComponent<UILayout>("uilayout")->subscribeChildEvent("Pausa_Opciones", "Menu/SumaMusica", helperFunction);
		helperFunction = std::bind(&UIMenus::restaEfectos, this, std::placeholders::_1);
		menu->getComponent<UILayout>("uilayout")->subscribeChildEvent("Pausa_Opciones", "Menu/RestaEfectos", helperFunction);
		helperFunction = std::bind(&UIMenus::sumaEfectos, this, std::placeholders::_1);
		menu->getComponent<UILayout>("uilayout")->subscribeChildEvent("Pausa_Opciones", "Menu/SumaEfectos", helperFunction);
		helperFunction = std::bind(&UIMenus::restaResolucion, this, std::placeholders::_1);
		menu->getComponent<UILayout>("uilayout")->subscribeChildEvent("Pausa_Opciones", "Menu/FlechaIz", helperFunction);
		helperFunction = std::bind(&UIMenus::sumaResolucion, this, std::placeholders::_1);
		menu->getComponent<UILayout>("uilayout")->subscribeChildEvent("Pausa_Opciones", "Menu/FlechaDer", helperFunction);
		helperFunction = std::bind(&UIMenus::vuelveOpcionesPausa, this, std::placeholders::_1);
		menu->getComponent<UILayout>("uilayout")->subscribeChildEvent("Pausa_Opciones", "Menu/BotonVolver", helperFunction);

		//Pausa

		helperFunction = std::bind(&UIMenus::reanudarButton, this, std::placeholders::_1);
		menu->getComponent<UILayout>("uilayout")->subscribeChildEvent("Pausa", "Menu/BotonReanudar", helperFunction);
		helperFunction = std::bind(&UIMenus::opcionesPausaButton, this, std::placeholders::_1);
		menu->getComponent<UILayout>("uilayout")->subscribeChildEvent("Pausa", "Menu/BotonOpciones", helperFunction);
		helperFunction = std::bind(&UIMenus::salirPausaButton, this, std::placeholders::_1);
		menu->getComponent<UILayout>("uilayout")->subscribeChildEvent("Pausa", "Menu/BotonSalir", helperFunction);

		// helperFunction = std::bind(&UIMenus::play_button, this, std::placeholders::_1);
		//menu->getComponent<UILayout>("uilayout")->subscribeChildEvent("MenuPrincipal", "Menu/Boton3", helperFunction);
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



	//botones que deberian ir en LUA

	//menu principal
	bool UIMenus::play_button(const CEGUI::EventArgs& e) {
		hide("MenuPrincipal");
		return true;
	}

	bool UIMenus::opciones_button(const CEGUI::EventArgs& e) {

		hide("MenuPrincipal");
		show("MenuPrincipal_Opciones");
		return true;
	}

	bool UIMenus::creditos_button(const CEGUI::EventArgs& e) {

		hide("MenuPrincipal");
		show("Creditos");
		return true;
	}


	bool UIMenus::salir_button(const CEGUI::EventArgs& e) {

		//pues decirle a todo el cacharro que se salga no tiene mas
		hide("MenuPrincipal");
		return true;

	}

	//menu opciones, para los dos salvo que sea el del opciones pausa
	bool UIMenus::restaMusica(const CEGUI::EventArgs& e) {

		std::cout << "resta musica\n";
		return true;
	}

	bool UIMenus::sumaMusica(const CEGUI::EventArgs& e) {

		std::cout << "suma musica\n";
		return true;
	}

	bool UIMenus::restaEfectos(const CEGUI::EventArgs& e) {

		std::cout << "resta sonido efectos\n";
		return true;
	}

	bool UIMenus::sumaEfectos(const CEGUI::EventArgs& e) {

		std::cout << "suma sonido efectos\n";
		return true;
	}

	bool UIMenus::restaResolucion(const CEGUI::EventArgs& e) {
		std::cout << "baja resolucion\n";
		return true;
	}

	bool UIMenus::sumaResolucion(const CEGUI::EventArgs& e) {

		std::cout << "sube resolucion\n";
		return true;
	}

	bool UIMenus::vuelveOpcionesMenu(const CEGUI::EventArgs& e) {
		hide("MenuPrincipal_Opciones");
		show("MenuPrincipal");
		return true;
	}

	bool UIMenus::vuelveOpcionesPausa(const CEGUI::EventArgs& e) {
		hide("Pausa_Opciones");
		show("Pausa");
		return true;
	}

	//menu de pausa

	bool UIMenus::reanudarButton(const CEGUI::EventArgs& e) {

		hide("Pausa");
		//devolver el flow del juego
		return true;
	}

	bool UIMenus::opcionesPausaButton(const CEGUI::EventArgs& e) {
		hide("Pausa");
		show("Pausa_Opciones");
		return true;
	}

	bool UIMenus::salirPausaButton(const CEGUI::EventArgs& e) {
		hide("Pausa");
		return true;
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