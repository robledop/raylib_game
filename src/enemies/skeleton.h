#ifndef RAYLIB_GAME_SRC_ENEMIES_SKELETON_H_
#define RAYLIB_GAME_SRC_ENEMIES_SKELETON_H_
#include "../terrain/collision_body.h"
#include "animation.h"
#include "../player.h"

class Skeleton : public CollisionBody {
  private:
  float currentY{};
  float currentX{};
  Player& player;
  Animation idleAnimation{
	  "assets/enemies/skeleton/Skeleton Idle.png",
	  11,
	  1.0f / 12.0f,
	 5.f 
  };
  
  Animation attackAnimation{
	  "assets/enemies/skeleton/Skeleton Attack.png",
	  18,
	  1.0f / 12.0f,
	  5.f
  };
  
  
 public:
  Skeleton(Vector2 pos, Rectangle collisionRect, Player& player);
  void Draw();
};

#endif
