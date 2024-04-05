#ifndef RAYLIB_GAME_SRC_ENEMIES_BOSS_H_
#define RAYLIB_GAME_SRC_ENEMIES_BOSS_H_

#include "enemy.h"
#include "player.h"
#include "terrain/collision_body.h"
#include <memory>

using namespace std;

class Boss : public CollisionBody, public Enemy {
  Animation idleAnimation;
  Animation runAnimation;
  Animation attack1Animation;
  Animation attack2Animation;
  Animation attack3Animation;
  Animation attackFromAirAnimation;
  Animation hurtAnimation;
  Animation healthAnimation;
  Animation prayAnimation;
  Animation deathAnimation;
  Animation jumpAnimation;
  bool animationCompleted{};
  int random{};
 public:
  Boss(raylib::Vector2 pos,
	   raylib::Rectangle collisionRect,
	   const unique_ptr<Player> &player,
	   unique_ptr<vector<unique_ptr<CollisionBody>>> &terrainCollisionBodies,
	   const unique_ptr<Reactor<raylib::Vector2>> &reactor);
  void Draw();
  [[nodiscard]] int GetHealth() const;
  [[nodiscard]] bool IsDead() const;
  void Attack();
  void Damage(int damage) override;

 private:
  const unique_ptr<Player> &player;
  unique_ptr<vector<unique_ptr<CollisionBody>>> &terrainCollisionBodies;
  const unique_ptr<Reactor<raylib::Vector2>> &reactor;
};

#endif 
