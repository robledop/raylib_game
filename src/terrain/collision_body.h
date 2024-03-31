#ifndef RAYLIB_GAME_SRC_TERRAIN_H_
#define RAYLIB_GAME_SRC_TERRAIN_H_

#include "raylib.h"
#include <tuple>

extern float scale;

class CollisionBody {
 protected:
  bool blocking;
  Rectangle collisionRect;
  Vector2 position;

 public:
  CollisionBody(Vector2 position, Rectangle collisionRect, bool blocking = true);
  std::tuple<bool, float> CheckTopCollision(Rectangle hitbox, float playerSpeed) const;
  std::tuple<bool, float>  CheckSideCollision(Rectangle hitbox, float playerSpeed) const;
  bool CheckBottomCollision(Rectangle hitbox, float playerSpeed) const;
  Rectangle GetHitbox() const;
};

#endif 
