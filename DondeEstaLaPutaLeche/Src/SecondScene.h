#pragma once
#ifndef _SECOND_SCENE_H
#define _SECOND_SCENE_H

#include <Scene.h>

namespace El_Horno {
	class SecondScene : public Scene
	{
	public:
		//StartScene() : Scene() {};
		virtual void init(std::string name) override;
		void testScene();
	};
}

#endif 

