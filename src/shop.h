#ifndef RAYLIB_GAME_SRC_SHOP_H_
#define RAYLIB_GAME_SRC_SHOP_H_

#include "raylib.h"
#include "animation.h"
#include "terrain/collision_body.h"

extern float scale;

class Shop : public CollisionBody {
 private:
  Animation animation{
	  ASSETS_PATH"shops/shop_anim.png",
	  6,
	  1.0f / 12.0f
  };

 public:
  Shop(Vector2 position, Rectangle collisionRect); 

  void Draw();
};

#endif 
