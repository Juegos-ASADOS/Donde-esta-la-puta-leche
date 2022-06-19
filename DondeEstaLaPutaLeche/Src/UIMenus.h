#pragma once
#ifndef _UI_MENUS_H
#define _UI_MENUS_H

#include <Component.h>

#include "UIManager.h"

namespace El_Horno {
    namespace Donde_Esta_La_Puta_Leche {
        class UIMenus : public Component
        {
        public:
            UIMenus();


            void start() override;
            void update() override {};
            void init();

            //botones de los menus que deberian de ir por LUA
            bool play_button(const CEGUI::EventArgs& e);
            bool opciones_button(const CEGUI::EventArgs& e);
            bool creditos_button(const CEGUI::EventArgs& e);
            bool salir_button(const CEGUI::EventArgs& e);
            bool restaMusica(const CEGUI::EventArgs& e);
            bool sumaMusica(const CEGUI::EventArgs& e);
            bool restaEfectos(const CEGUI::EventArgs& e);
            bool sumaEfectos(const CEGUI::EventArgs& e);
            bool restaResolucion(const CEGUI::EventArgs& e);
            bool sumaResolucion(const CEGUI::EventArgs& e);
            bool vuelveOpcionesMenu(const CEGUI::EventArgs& e);
            bool vuelveOpcionesPausa(const CEGUI::EventArgs& e);
            bool reanudarButton(const CEGUI::EventArgs& e);
            bool opcionesPausaButton(const CEGUI::EventArgs& e);

            bool salirPausaButton(const CEGUI::EventArgs& e);
            bool volverCreditosButton(const CEGUI::EventArgs& e);
            bool volverVictoriaButton(const CEGUI::EventArgs& e);
            bool volverDerrotaButton(const CEGUI::EventArgs& e);
            bool resUp(const CEGUI::EventArgs& e);
            bool resDown(const CEGUI::EventArgs& e);

        private:

            void show(std::string menu);
            void hide(std::string menu);

            Entity* menu = nullptr;
        };
    }
}
#endif _UI_MENUS_H