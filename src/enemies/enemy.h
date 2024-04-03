#ifndef RAYLIB_GAME_SRC_ENEMIES_ENEMY_H_
#define RAYLIB_GAME_SRC_ENEMIES_ENEMY_H_

#include "player.h"
class Enemy {
 public:
  virtual void Damage(int damage) = 0;
};

#endif 
