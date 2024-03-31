#ifndef RAYLIB_GAME_SRC_ENEMIES_SKELETON_H_
#define RAYLIB_GAME_SRC_ENEMIES_SKELETON_H_
#include "../terrain/collision_body.h"
#include "animation.h"
#include "../player.h"
#include "colors.h"
#include "config.h"
#include <vector>

extern bool showCollisionBoxes;

class Skeleton : public CollisionBody {
 private:
  bool dealDamage;
  bool hit;
  bool facingRight;
  bool sameYPosAsPlayer;
  int delay;
  vector<CollisionBody> *terrainCollisionBodies;

  Rectangle weaponHitbox;
  int health;
  float currentY;
  float currentX;
  Player *player;

 public:
  Animation idleAnimation;
  Animation attackAnimation;
  Animation hitAnimation;
  Animation walkAnimation;
 
  Reactor reactor;
  Skeleton(Vector2 pos, Rectangle collisionRect, Player *player, vector<CollisionBody> *terrainCollisionBodies);
  void Draw();
  [[nodiscard]] Rectangle GetHitbox() const;
  void Damage(int damage);
  [[nodiscard]] int GetHealth() const;
  [[nodiscard]] bool IsDead() const;
  void Attack();
};

#endif
