#ifndef RAYLIB_GAME_SRC_ENEMIES_BOSS_H_
#define RAYLIB_GAME_SRC_ENEMIES_BOSS_H_

#include "enemy.h"
#include "player.h"
#include "terrain/collision_body.h"

class Boss : public CollisionBody, public Enemy{
  Animation idleAnimation;
 public:
  Boss(Vector2 pos, Rectangle collisionRect, Player *player, vector<CollisionBody> *terrainCollisionBodies, Reactor<Vector2> *reactor);
  void Draw();
  [[nodiscard]] int GetHealth() const;
  [[nodiscard]] bool IsDead() const;
  void Attack();
  void Damage(int damage) override;

 private:
  Player *player;
  vector<CollisionBody> *terrainCollisionBodies;
  Reactor<Vector2> *reactor;
};

#endif 
