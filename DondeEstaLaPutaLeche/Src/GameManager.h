#pragma once
#ifndef _GAME_MANAGER_H
#define _GAME_MANAGER_H

#include <Component.h>
#include <map>

namespace El_Horno {
	class RigidBody;
	class Timer;
	class InputManager;
	enum GameState { RUNNING, PAUSED, MAINMENU, STARTSTATE };

	class GameManager : public Component
	{
	public:
		GameManager();
		~GameManager();

		static GameManager* getInstance();
		static bool setupInstance();
		static void erase();


		void setParameters(std::vector<std::pair<std::string, std::string>> parameters) override;
		void start() override;
		void update() override;

		void setLevel(float maxTime, std::map<std::string, int> list, int proctNum);

		bool checkObject(std::string objectId);
		void togglePaused();
		void checkEnd();
		inline const bool hasWon() { return win_; };
		inline const int getWrongProductNumber() { return wrongProducts_; };
		const float getProductCompletionPercentaje();
		inline const std::map<std::string, int> getList() { return list_; };

		//Se llama cuando vas a darle la compra a la madre
		void paidFoodMum();

		//Metodos para modificar la UI ingame
		void setTicketIntro();
		void setTicketTurno();
		void setTicketLimite();
		void hideTicket();
		void setList();
		void checkProductUI(std::string productId, int i);
		void showTutorial(std::string name);
		void hideTutorial();

	protected:
		static GameManager* instance_;
		std::map<std::string, int> list_;

		GameState gameState_;
		Entity* interfaz_;

		// Time
		Timer* gameTimer_ = nullptr;
		float maxTime_,
			objectiveTime_;

		int productNum_,
			maxProducts_,
			minWrongProducts_,
			wrongProducts_,
			endingEggs_;

		//Por si vas a la madre y das los alimentos que tengas en el carrito sin que esten todos
		int paidFood;

		bool win_;
		InputManager* input_;


		std::string actualTuto_ = "";
	};
}
#endif 

