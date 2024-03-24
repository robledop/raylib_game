#ifndef RAYLIB_GAME_SRC_SHOP_H_
#define RAYLIB_GAME_SRC_SHOP_H_

#include "raylib.h"
#include "animation.h"

extern float scale;

class Shop {
 private:
  Vector2 position;
  Animation animation{
	  ASSETS_PATH"decorations/shop_anim.png",
	  6,
	  1.0f / 12.0f
  };

 public:
  Shop(Vector2 pos);
  void Draw(); 
};

#endif 
