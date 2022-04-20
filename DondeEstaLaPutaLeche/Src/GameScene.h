#pragma once
#ifndef _GAME_SCENE_H
#define _GAME_SCENE_H

#include <Scene.h>
class lua_State;

namespace El_Horno {
	class HornoVector3;

	class GameScene : public Scene
	{
	public:
		virtual void init() override;
	protected:
		//HornoVector3 pos, HornoVector3 rot, HornoVector3 scale, std::string mesh,
		//float mass, int collisionShape, float speed)
		static void createPlayer(lua_State* L);
		//HornoVector3 pos, HornoVector3 rot, HornoVector3 scale, int lightType, HornoVector3 dirLight
		static void createLight(lua_State* L);
		//HornoVector3 pos, HornoVector3 rot, HornoVector3 scale, HornoVector3 camPos,
		//HornoVector3 lookAt, HornoVector3 color, float alpha, int nearDist, int farDist
		static void createCamera(lua_State* L);
		//HornoVector3 pos, HornoVector3 rot, HornoVector3 scale, std::string mesh,
		//float mass, bool isTrigger, bool isKinematic, int collisionShape
		static void createObject(lua_State* L);
		//HornoVector3 pos, HornoVector3 rot, HornoVector3 scale, std::string mesh,
		//int collisionShape, std::string id, HornoVector3 triggerPos, HornoVector3 triggerRot,
		//HornoVector3 triggerScale, int triggerCollisionShape
		static void createEstantery(lua_State* L);
	};
}

#endif 

