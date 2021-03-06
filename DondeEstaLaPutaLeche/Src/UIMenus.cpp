#include "UIMenus.h"

#include <Scene.h>
#include <LuaManager.h>
#include <SceneManager.h>
#include <Transform.h>
#include <Entity.h>
#include <ElHornoBase.h>
#include "GameManager.h"
#include "CameraComponent.h"


#include "InputManager.h"
#include "AudioManager.h"
#include <iostream>

using namespace El_Horno;

bool click() {
	return true;
}

Donde_Esta_La_Puta_Leche::UIMenus::UIMenus()
{
}


void Donde_Esta_La_Puta_Leche::UIMenus::init() {
	UIManager::getInstance()->defineScheme("GWEN");
	UIManager::getInstance()->defineScheme("DondeTaLeche");
	UIManager::getInstance()->defineScheme("TaharezLook");
	UIManager::getInstance()->defineScheme("Generic");

	UIManager::getInstance()->setMouseCursor("TaharezLook/MouseArrow");
	UIManager::getInstance()->showMouseCursor();
	//UIManager::getInstance()->createButton("TaharezLook", "Button", "start");
	UIManager::getInstance()->addLayout("MenuPrincipal"); //Nombre del layout, y nombre interno cualquiera(que no se repita)
	UIManager::getInstance()->addLayout("MenuPrincipal_Opciones"); //Nombre del layout, y nombre interno cualquiera(que no se repita)
	UIManager::getInstance()->addLayout("Pausa"); //Nombre del layout, y nombre interno cualquiera(que no se repita)
	UIManager::getInstance()->addLayout("Pausa_Opciones"); //Nombre del layout, y nombre interno cualquiera(que no se repita)
	UIManager::getInstance()->addLayout("Nivel_Ingame"); //Nombre del layout, y nombre interno cualquiera(que no se repita)
	UIManager::getInstance()->addLayout("Creditos"); //Nombre del layout, y nombre interno cualquiera(que no se repita)
	UIManager::getInstance()->addLayout("Victoria"); //Nombre del layout, y nombre interno cualquiera(que no se repita)
	UIManager::getInstance()->addLayout("Derrota"); //Nombre del layout, y nombre interno cualquiera(que no se repita)


	//añadir la funcionalidad a los botones

	//menu principal
	auto helperFunction = std::bind(&UIMenus::play_button, this, std::placeholders::_1);
	UIManager::getInstance()->subscribeLayoutChildEvent("MenuPrincipal", "Menu/Boton", helperFunction);
	helperFunction = std::bind(&UIMenus::opciones_button, this, std::placeholders::_1);
	UIManager::getInstance()->subscribeLayoutChildEvent("MenuPrincipal", "Menu/Boton2", helperFunction);
	helperFunction = std::bind(&UIMenus::creditos_button, this, std::placeholders::_1);
	UIManager::getInstance()->subscribeLayoutChildEvent("MenuPrincipal", "Menu/Boton3", helperFunction);
	helperFunction = std::bind(&UIMenus::salir_button, this, std::placeholders::_1);
	UIManager::getInstance()->subscribeLayoutChildEvent("MenuPrincipal", "Menu/Boton4", helperFunction);

	//menu opciones desde principal

	helperFunction = std::bind(&UIMenus::restaMusica, this, std::placeholders::_1);
	UIManager::getInstance()->subscribeLayoutChildEvent("MenuPrincipal_Opciones", "Menu/RestaMusica", helperFunction);
	helperFunction = std::bind(&UIMenus::sumaMusica, this, std::placeholders::_1);
	UIManager::getInstance()->subscribeLayoutChildEvent("MenuPrincipal_Opciones", "Menu/SumaMusica", helperFunction);
	helperFunction = std::bind(&UIMenus::restaEfectos, this, std::placeholders::_1);
	UIManager::getInstance()->subscribeLayoutChildEvent("MenuPrincipal_Opciones", "Menu/RestaEfectos", helperFunction);
	helperFunction = std::bind(&UIMenus::sumaEfectos, this, std::placeholders::_1);
	UIManager::getInstance()->subscribeLayoutChildEvent("MenuPrincipal_Opciones", "Menu/SumaEfectos", helperFunction);
	helperFunction = std::bind(&UIMenus::vuelveOpcionesMenu, this, std::placeholders::_1);
	UIManager::getInstance()->subscribeLayoutChildEvent("MenuPrincipal_Opciones", "Menu/BotonVolver", helperFunction);

	helperFunction = std::bind(&UIMenus::resUp, this, std::placeholders::_1);
	UIManager::getInstance()->subscribeLayoutChildEvent("MenuPrincipal_Opciones", "Menu/FlechaDer", helperFunction);
	helperFunction = std::bind(&UIMenus::resDown, this, std::placeholders::_1);
	UIManager::getInstance()->subscribeLayoutChildEvent("MenuPrincipal_Opciones", "Menu/FlechaIz", helperFunction);

	//menu opciones desde la pausa

	helperFunction = std::bind(&UIMenus::restaMusica, this, std::placeholders::_1);
	UIManager::getInstance()->subscribeLayoutChildEvent("Pausa_Opciones", "Menu/RestaMusica", helperFunction);
	helperFunction = std::bind(&UIMenus::sumaMusica, this, std::placeholders::_1);
	UIManager::getInstance()->subscribeLayoutChildEvent("Pausa_Opciones", "Menu/SumaMusica", helperFunction);
	helperFunction = std::bind(&UIMenus::restaEfectos, this, std::placeholders::_1);
	UIManager::getInstance()->subscribeLayoutChildEvent("Pausa_Opciones", "Menu/RestaEfectos", helperFunction);
	helperFunction = std::bind(&UIMenus::sumaEfectos, this, std::placeholders::_1);
	UIManager::getInstance()->subscribeLayoutChildEvent("Pausa_Opciones", "Menu/SumaEfectos", helperFunction);
	helperFunction = std::bind(&UIMenus::vuelveOpcionesPausa, this, std::placeholders::_1);
	UIManager::getInstance()->subscribeLayoutChildEvent("Pausa_Opciones", "Menu/BotonVolver", helperFunction);
	helperFunction = std::bind(&UIMenus::resUp, this, std::placeholders::_1);
	UIManager::getInstance()->subscribeLayoutChildEvent("Pausa_Opciones", "Menu/FlechaDer", helperFunction);
	helperFunction = std::bind(&UIMenus::resDown, this, std::placeholders::_1);
	UIManager::getInstance()->subscribeLayoutChildEvent("Pausa_Opciones", "Menu/FlechaIz", helperFunction);

	//Pausa


	helperFunction = std::bind(&UIMenus::reanudarButton, this, std::placeholders::_1);
	UIManager::getInstance()->subscribeLayoutChildEvent("Pausa", "Menu/BotonReanudar", helperFunction);
	helperFunction = std::bind(&UIMenus::opcionesPausaButton, this, std::placeholders::_1);
	UIManager::getInstance()->subscribeLayoutChildEvent("Pausa", "Menu/BotonOpciones", helperFunction);
	helperFunction = std::bind(&UIMenus::salirPausaButton, this, std::placeholders::_1);
	UIManager::getInstance()->subscribeLayoutChildEvent("Pausa", "Menu/BotonSalir", helperFunction);

	//Creditos

	helperFunction = std::bind(&UIMenus::volverCreditosButton, this, std::placeholders::_1);
	UIManager::getInstance()->subscribeLayoutChildEvent("Creditos", "Boton_Volver", helperFunction);

	//victoria

	helperFunction = std::bind(&UIMenus::volverVictoriaButton, this, std::placeholders::_1);
	UIManager::getInstance()->subscribeLayoutChildEvent("Victoria", "Boton_Volver", helperFunction);

	//derrota

	helperFunction = std::bind(&UIMenus::volverDerrotaButton, this, std::placeholders::_1);
	UIManager::getInstance()->subscribeLayoutChildEvent("Derrota", "Boton_Volver", helperFunction);

	show("Nivel_Ingame");
	show("MenuPrincipal");
}


void Donde_Esta_La_Puta_Leche::UIMenus::start()
{

}

//botones que deberian ir en LUA

//menu principal
bool Donde_Esta_La_Puta_Leche::UIMenus::play_button(const CEGUI::EventArgs& e) {
	hide("MenuPrincipal");
	UIManager::getInstance()->hideMouseCursor();
	this->setActive(false);

	AudioManager::getInstance()->stopMusic();
	AudioManager::getInstance()->playSound("Musica/Nivel.mp3", HornoVectorToFmod(HornoVector3(0, 100, 450)), 3.0f, true);

	std::string a = "theEnd2";
	LuaManager::getInstance()->pushString(a, "scene");
	LuaManager::getInstance()->callLuaFunction("loadNextScene");


	return true;
}

bool Donde_Esta_La_Puta_Leche::UIMenus::opciones_button(const CEGUI::EventArgs& e) {

	UIManager::getInstance()->showMouseCursor();
	hide("MenuPrincipal");
	show("MenuPrincipal_Opciones");
	return true;
}

bool Donde_Esta_La_Puta_Leche::UIMenus::creditos_button(const CEGUI::EventArgs& e) {
	UIManager::getInstance()->showMouseCursor();
	hide("MenuPrincipal");
	show("Creditos");
	return true;
}

//LuaManager::getInstance()->callLuaFunction("setPause");   PARA PAUSAR
//LuaManager::getInstance()->callLuaFunction("setExit");    PARA SALIR
//Exit 
bool Donde_Esta_La_Puta_Leche::UIMenus::salir_button(const CEGUI::EventArgs& e) {
	//pues decirle a todo el cacharro que se salga no tiene mas

	ElHornoBase::getInstance()->setExit();
	//hide("MenuPrincipal");
	return true;

}

//menu opciones, para los dos salvo que sea el del opciones pausa
bool Donde_Esta_La_Puta_Leche::UIMenus::restaMusica(const CEGUI::EventArgs& e) {
	LuaManager::getInstance()->callLuaFunction("setMusicDown");
	return true;
}

bool Donde_Esta_La_Puta_Leche::UIMenus::sumaMusica(const CEGUI::EventArgs& e) {
	LuaManager::getInstance()->callLuaFunction("setMusicUp");
	return true;
}

bool Donde_Esta_La_Puta_Leche::UIMenus::restaEfectos(const CEGUI::EventArgs& e) {
	LuaManager::getInstance()->callLuaFunction("setFxDown");
	AudioManager::getInstance()->playSound("SFX/CogerObjeto.mp3", HornoVectorToFmod(HornoVector3(0, 100, 450)));
	return true;
}

bool Donde_Esta_La_Puta_Leche::UIMenus::sumaEfectos(const CEGUI::EventArgs& e) {
	LuaManager::getInstance()->callLuaFunction("setFxUp");
	AudioManager::getInstance()->playSound("SFX/CogerObjeto.mp3", HornoVectorToFmod(HornoVector3(0, 100, 450)));
	return true;
}

//pausa (ElHornoBase)
bool Donde_Esta_La_Puta_Leche::UIMenus::vuelveOpcionesMenu(const CEGUI::EventArgs& e) {
	hide("MenuPrincipal_Opciones");
	show("MenuPrincipal");
	return true;
}

bool Donde_Esta_La_Puta_Leche::UIMenus::vuelveOpcionesPausa(const CEGUI::EventArgs& e) {
	hide("Pausa_Opciones");
	show("Pausa");
	return true;
}

//menu de pausa

bool Donde_Esta_La_Puta_Leche::UIMenus::reanudarButton(const CEGUI::EventArgs& e) {
	UIManager::getInstance()->hideMouseCursor();
	GameManager::getInstance()->togglePaused();
	hide("Pausa");
	//devolver el flow del juego
	return true;
}

bool Donde_Esta_La_Puta_Leche::UIMenus::opcionesPausaButton(const CEGUI::EventArgs& e) {
	hide("Pausa");
	show("Pausa_Opciones");
	return true;
}

bool Donde_Esta_La_Puta_Leche::UIMenus::salirPausaButton(const CEGUI::EventArgs& e) {
	//te devuelve al menu principal
	GameManager::getInstance()->togglePaused();

	AudioManager::getInstance()->StopAllChannels();

	//UIManager::getInstance()->hideMouseCursor();
	hide("Pausa");
	show("MenuPrincipal");
	AudioManager::getInstance()->stopMusic();
	AudioManager::getInstance()->playSound("Musica/Menu.mp3", HornoVectorToFmod(HornoVector3(0, 100, 450)), 3.0f, true);


	std::string a = "inicio";
	LuaManager::getInstance()->pushString(a, "scene");
	LuaManager::getInstance()->callLuaFunction("loadNextScene");


	return true;
}

bool Donde_Esta_La_Puta_Leche::UIMenus::volverCreditosButton(const CEGUI::EventArgs& e) {
	hide("Creditos");
	show("MenuPrincipal");
	return true;
}

bool Donde_Esta_La_Puta_Leche::UIMenus::volverVictoriaButton(const CEGUI::EventArgs& e) {
	//UIManager::getInstance()->showMouseCursor();
	hide("Victoria");
	show("MenuPrincipal");
	ElHornoBase::getInstance()->pause();
	AudioManager::getInstance()->stopMusic();
	AudioManager::getInstance()->playSound("Musica/Menu.mp3", HornoVectorToFmod(HornoVector3(0, 100, 450)), 3.0f, true);

	std::string a = "inicio";
	LuaManager::getInstance()->pushString(a, "scene");
	LuaManager::getInstance()->callLuaFunction("loadNextScene");

	return true;
}

bool Donde_Esta_La_Puta_Leche::UIMenus::volverDerrotaButton(const CEGUI::EventArgs& e) {
	//UIManager::getInstance()->showMouseCursor();
	hide("Derrota");
	show("MenuPrincipal");
	ElHornoBase::getInstance()->pause();
	AudioManager::getInstance()->stopMusic();
	AudioManager::getInstance()->playSound("Musica/Menu.mp3", HornoVectorToFmod(HornoVector3(0, 100, 450)), 3.0f, true);

	std::string a = "inicio";
	LuaManager::getInstance()->pushString(a, "scene");
	LuaManager::getInstance()->callLuaFunction("loadNextScene");

	return true;
}

bool Donde_Esta_La_Puta_Leche::UIMenus::resUp(const CEGUI::EventArgs& e) {

	LuaManager::getInstance()->callLuaFunction("setResolutionUp");

	return true;
}
bool Donde_Esta_La_Puta_Leche::UIMenus::resDown(const CEGUI::EventArgs& e) {

	LuaManager::getInstance()->callLuaFunction("setResolutionDown");

	return true;
}

void Donde_Esta_La_Puta_Leche::UIMenus::show(std::string m)
{
	bool vis = true;
	LuaManager::getInstance()->pushString(m, "button");
	LuaManager::getInstance()->pushBool(vis, "vis");
	LuaManager::getInstance()->callLuaFunction("setLayoutVisibility");
}
void Donde_Esta_La_Puta_Leche::UIMenus::hide(std::string m)
{
	bool vis = false;
	LuaManager::getInstance()->pushString(m, "button");
	LuaManager::getInstance()->pushBool(vis, "vis");
	LuaManager::getInstance()->callLuaFunction("setLayoutVisibility");
}