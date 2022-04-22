#pragma once
#ifndef _GAME_MANAGER_H
#define _GAME_MANAGER_H

#include <Component.h>
#include <map>


namespace El_Horno {
	class RigidBody;
	class Timer;
	enum GameState {RUNNING, PAUSED, MAINMENU, STARTSTATE};

	class GameManager : public Component
	{
	public:
		GameManager() {};
		~GameManager() {};

		static GameManager* getInstance();
		static bool setupInstance();
		static void erase();


		void start() override;
		void update() override;

		void setLevel(float maxTime, std::map<std::string, int> list, int proctNum);
		
		bool checkObject(std::string objectId);
		void togglePaused();
		inline const bool hasWon() { return win_; };
		inline const int getWrongProductNumber() { return wrongProducts_; };
	protected:
		static GameManager* instance_;
		std::map<std::string, int> list_;

		GameState gameState_;

		// Time
		Timer* gameTimer_;
		float maxTime_;

		int productNum_,
			wrongProducts_;

		bool win_;
	};
}
#endif 

