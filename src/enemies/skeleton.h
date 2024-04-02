#ifndef RAYLIB_GAME_SRC_ENEMIES_SKELETON_H_
#define RAYLIB_GAME_SRC_ENEMIES_SKELETON_H_
#include "../terrain/collision_body.h"
#include "animation.h"
#include "../player.h"
#include "colors.h"
#include "config.h"
#include <vector>
#include "enemy.h"

extern bool showCollisionBoxes;

class Skeleton : public CollisionBody, public Enemy {
 private:
  bool deathAnimationPlayed;
  bool attacking;
  bool dealDamage;
  bool hit;
  bool staggered;
  bool facingRight;
  bool sameYPosAsPlayer;
  int delay;
  vector<CollisionBody> *terrainCollisionBodies;

  Rectangle weaponHitbox;
  int health;
  float currentY;
  float currentX;
  Player *player;
  void HandleCombat();

 public:
  Animation idleAnimation;
  Animation attackAnimation;
  Animation hitAnimation;
  Animation walkAnimation;
  Animation deathAnimation;
  bool droppedLoot{false};
 
  Reactor<int> reactor;
  Reactor<Vector2>* deathReactor;
  Skeleton(Vector2 pos, Rectangle collisionRect, Player *player, vector<CollisionBody> *terrainCollisionBodies, Reactor<Vector2> *reactor);
  void Draw();
  [[nodiscard]] int GetHealth() const;
  [[nodiscard]] bool IsDead() const;
  void Attack();
  void Damage(int damage) override;
};

#endif
