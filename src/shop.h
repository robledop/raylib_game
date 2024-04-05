#ifndef RAYLIB_GAME_SRC_SHOP_H_
#define RAYLIB_GAME_SRC_SHOP_H_

#include "raylib-cpp.hpp"
#include "animation.h"
#include "terrain/collision_body.h"

extern float scale;

class Shop : public CollisionBody {
 private:
  Animation animation{
	  "assets/shops/shop_anim.png",
	  6,
	  1.0f / 12.0f
  };

 public:
  Shop(raylib::Vector2 position, raylib::Rectangle collisionRect); 

  void Draw();
};

#endif 
