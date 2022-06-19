#pragma once
#ifndef _PLAYER_MOVEMENT_H
#define _PLAYER_MOVEMENT_H

#include <Component.h>


namespace El_Horno {
	class RigidBody;
	class Transform;
	class InputManager;
	class AnimatorController;
	namespace Donde_Esta_La_Puta_Leche {

		enum PLayerState { PLAYER_DEFAULT, PLAYER_CART, PLAYER_PRODUCT };

		class PlayerController : public Component
		{
		public:
			PlayerController(float s) : speed_(s), maxForce_(100) {};
			PlayerController() {};

			void setParameters(std::vector<std::pair<std::string, std::string>> parameters) override;
			void start() override;
			void update() override;
			inline void setSpeed(float s) { speed_ = s; };
			inline void setSliding(bool sl) { sliding_ = sl; };
			void setPlayerState(PLayerState s);

		protected:
			float speed_;
			RigidBody* rb_;
			Transform* tb_;
			InputManager* input_;
			int maxForce_,
				offset_;
			El_Horno::AnimatorController* anim_;
			bool walking_;
			bool sliding_ = false;
			PLayerState pState_;
		};
	}
}
#endif 

