#ifndef RAYLIB_GAME_SRC_CHEST_H_
#define RAYLIB_GAME_SRC_CHEST_H_

#include "animation.h"
#include "terrain/collision_body.h"

class Chest : public CollisionBody{
 private:
  Animation animation{
	  "assets/village/Chest Animation 1.png",
	  7,
	  1.0f / 12.0f,
	  3.f
  };

 public:
  Chest(raylib::Vector2 position, raylib::Rectangle collisionRect);
  void Draw();

};

#endif
