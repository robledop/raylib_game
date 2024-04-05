#ifndef RAYLIB_GAME_SRC_TERRAIN_H_
#define RAYLIB_GAME_SRC_TERRAIN_H_

#include <tuple>
#include "raylib-cpp.hpp"

extern float scale;

class CollisionBody {
 protected:
  bool blocking;
  raylib::Rectangle collisionRect;
  raylib::Vector2 position;

 public:
  float fallSpeed{0};
  float sidewaysSpeed{0};
  float bounciness{1.75f};
  bool bouncing{false};
  CollisionBody(raylib::Vector2 position, raylib::Rectangle collisionRect, bool blocking = true);
  std::tuple<bool, float> CheckTopCollision(raylib::Rectangle hitbox, float playerSpeed) const;
  std::tuple<bool, float> CheckSideCollision(raylib::Rectangle hitbox, float playerSpeed) const;
  bool CheckBottomCollision(raylib::Rectangle hitbox, float playerSpeed) const;
  raylib::Rectangle GetHitbox() const;
  void SetPosition(raylib::Vector2 position);
  raylib::Vector2 GetPosition();
  void Update();
};

#endif 
