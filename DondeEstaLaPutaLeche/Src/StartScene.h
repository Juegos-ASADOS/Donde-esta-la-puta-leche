#pragma once
#ifndef _START_SCENE_H
#define _START_SCENE_H

#include <GameScene.h>

namespace El_Horno {
	class StartScene : public GameScene
	{
	public:
		//StartScene() : Scene() {};
		virtual void init() override;
		void testScene();
	};
}

#endif 

