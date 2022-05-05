#include "UIGame.h"

#include <Scene.h>
#include <LuaManager.h>
#include <SceneManager.h>
#include <UILayout.h>
#include <Transform.h>
#include <Entity.h>
#include <GameManager.h>

#include "InputManager.h"
#include <iostream>

namespace El_Horno {


	UIGame::UIGame()
	{
	}

	void UIGame::start()
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

		//Cargamos el Layout de la UI ingame
		menu->getComponent<UILayout>("uilayout")->addLayout("Nivel_Ingame"); //Nombre del layout, y nombre interno cualquiera(que no se repita)

		menu->getComponent<UILayout>("uilayout")->addWidgetToLayout("Nivel_Ingame", "Fruta", "GWEN/StaticImage"); //Nombre del layout, y nombre interno cualquiera(que no se repita)
		menu->getComponent<UILayout>("uilayout")->setChildProperty("Nivel_Ingame", "Fruta", "Image", "DondeTaLeche/Producto_Calabaza"); //Nombre del layout, y nombre interno cualquiera(que no se repita)
		menu->getComponent<UILayout>("uilayout")->setChildProperty("Nivel_Ingame", "Fruta", "Position", "{{0,429},{0,362}}"); //Nombre del layout, y nombre interno cualquiera(que no se repita)
		menu->getComponent<UILayout>("uilayout")->setChildProperty("Nivel_Ingame", "Fruta", "Size", "{{1,-1776},{1,-948}}"); //Nombre del layout, y nombre interno cualquiera(que no se repita)
		menu->getComponent<UILayout>("uilayout")->setChildProperty("Nivel_Ingame", "Fruta", "Area", "{{0,863},{0,434},{1,-837},{1,-448}}"); //Nombre del layout, y nombre interno cualquiera(que no se repita)
		//menu->getComponent<UILayout>("uilayout")->setChildProperty("Nivel_Ingame", "Fruta", "MaxSize", "{{1,0},{1,0}}"); //Nombre del layout, y nombre interno cualquiera(que no se repita)
		//menu->getComponent<UILayout>("uilayout")->setChildProperty("Nivel_Ingame", "Fruta", "MinSize", "{{0,0},{0,0}}"); //Nombre del layout, y nombre interno cualquiera(que no se repita)
		//menu->getComponent<UILayout>("uilayout")->setChildProperty("Nivel_Ingame", "Fruta", "VerticalAlignment", "Top"); //Nombre del layout, y nombre interno cualquiera(que no se repita)
		//menu->getComponent<UILayout>("uilayout")->setChildProperty("Nivel_Ingame", "Fruta", "HorizontalAlignment", "Left"); //Nombre del layout, y nombre interno cualquiera(que no se repita)
		//menu->getComponent<UILayout>("uilayout")->setChildProperty("Nivel_Ingame", "Fruta", "AspectRatio", "1"); //Nombre del layout, y nombre interno cualquiera(que no se repita)


		//setList();
		show("Nivel_Ingame");


		// helperFunction = std::bind(&UIMenus::play_button, this, std::placeholders::_1);
		//menu->getComponent<UILayout>("uilayout")->subscribeChildEvent("MenuPrincipal", "Menu/Boton3", helperFunction);
	}

	void UIGame::update()
	{
		setList();

	}



	void UIGame::show(std::string m)
	{
		menu->getComponent<UILayout>("uilayout")->setLayoutVisibility(m, true);
	}
	void UIGame::hide(std::string m)
	{
		menu->getComponent<UILayout>("uilayout")->setLayoutVisibility(m, false);
	}

	void UIGame::setList()
	{
		//// Guardamos la lista
		//std::map<std::string, int> list = GameManager::getInstance()->getList();
		//std::cout << GameManager::getInstance()->getList().at("Producto_Tomate");
		// Recorremos el mapa de la lista
		int i = 0;
		for (auto product : GameManager::getInstance()->getList())
		{
			std::cout << "carnallo";
			// Poner imagen del producto
			menu->getComponent<UILayout>("uilayout")->setChildProperty("Nivel_Ingame", "Producto_" + i, "Image", "DondeTaLeche/" + product.first);
			cout << product.first;

			// Poner la cantidad de ese producto
			if (product.second > 0)
				menu->getComponent<UILayout>("uilayout")->setChildProperty("Nivel_Ingame", "Num_" + i, "Image", "DondeTaLeche/X" + product.second);
			i++;
		}

	}


}