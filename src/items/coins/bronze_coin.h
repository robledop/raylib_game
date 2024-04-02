#ifndef RAYLIB_GAME_SRC_ITEMS_COINS_BRONZE_COIN_H_
#define RAYLIB_GAME_SRC_ITEMS_COINS_BRONZE_COIN_H_

#include "terrain/collision_body.h"
#include "animation.h"

class BronzeCoin : public CollisionBody {
  Animation animation;

 public:
  bool isCollected{};
  BronzeCoin(const char *texturePath, Vector2 position, Rectangle drawingRect) :
	  animation{texturePath, 5, 1.0f / 12.0f, 2.f},
	  CollisionBody{position, drawingRect} {
  }
  ~BronzeCoin();
  void Draw();
};

#endif 
