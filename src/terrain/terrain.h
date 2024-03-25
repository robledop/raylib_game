#ifndef RAYLIB_GAME_SRC_TERRAIN_H_
#define RAYLIB_GAME_SRC_TERRAIN_H_

#include "raylib.h"
#include <tuple>

extern float scale;

class Terrain {
 protected:
  bool blocking;
  Rectangle rect;
  Vector2 position{};

 public:
  Terrain(Vector2 pos, Rectangle rectangle, bool blocking = true);
  std::tuple<bool, float> CheckTopCollision(Rectangle hitbox, float playerSpeed) const;
  std::tuple<bool, float>  CheckSideCollision(Rectangle hitbox, float playerSpeed) const;
  bool CheckBottomCollision(Rectangle hitbox, float playerSpeed) const;

//  void Draw();

};

#endif 
