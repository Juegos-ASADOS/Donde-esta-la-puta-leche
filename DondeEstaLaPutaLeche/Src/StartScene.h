#pragma once
#ifndef _START_SCENE_H
#define _START_SCENE_H

#include <Scene.h>

namespace El_Horno {
	class StartScene : public Scene
	{
	public:
		//StartScene() : Scene() {};
		virtual void init(std::string name) override;
		void testScene();
		void menuPrincipal();
	};
}

#endif 

