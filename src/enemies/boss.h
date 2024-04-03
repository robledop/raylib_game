#ifndef RAYLIB_GAME_SRC_ENEMIES_BOSS_H_
#define RAYLIB_GAME_SRC_ENEMIES_BOSS_H_

#include "enemy.h"
#include "player.h"
#include "terrain/collision_body.h"
#include <memory>

using namespace std;

class Boss : public CollisionBody, public Enemy {
  Animation idleAnimation;
 public:
  Boss(Vector2 pos,
	   Rectangle collisionRect,
	   const unique_ptr<Player> &player,
	   unique_ptr<vector<unique_ptr<CollisionBody>>> &terrainCollisionBodies,
	   const unique_ptr<Reactor<Vector2>> &reactor);
  void Draw();
  [[nodiscard]] int GetHealth() const;
  [[nodiscard]] bool IsDead() const;
  void Attack();
  void Damage(int damage) override;

 private:
  const unique_ptr<Player> &player;
  unique_ptr<vector<unique_ptr<CollisionBody>>> &terrainCollisionBodies;
  const unique_ptr<Reactor<Vector2>> &reactor;
};

#endif 
