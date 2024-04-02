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
  float fallSpeed{0};
  float sidewaysSpeed{0};
  float bounciness{1.75f};
  bool bouncing{false};
  CollisionBody(Vector2 position, Rectangle collisionRect, bool blocking = true);
  std::tuple<bool, float> CheckTopCollision(Rectangle hitbox, float playerSpeed) const;
  std::tuple<bool, float>  CheckSideCollision(Rectangle hitbox, float playerSpeed) const;
  bool CheckBottomCollision(Rectangle hitbox, float playerSpeed) const;
  Rectangle GetHitbox() const;
  void SetPosition(Vector2 position);
  Vector2 GetPosition();
  void Update();
};

#endif 
