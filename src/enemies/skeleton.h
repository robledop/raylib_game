#ifndef RAYLIB_GAME_SRC_ENEMIES_SKELETON_H_
#define RAYLIB_GAME_SRC_ENEMIES_SKELETON_H_
#include "../terrain/collision_body.h"
#include "animation.h"
#include "../player.h"
#include "colors.h"
#include "config.h"
#include <vector>

class Skeleton : public CollisionBody {
 private:
  bool dealDamage{true};
  bool hit;
  bool facingRight{true};
  bool sameYPosAsPlayer{false};
  int delay{};
  vector<CollisionBody>* terrainCollisionBodies;
  
  Rectangle weaponHitbox{};
  int health{100};
  float currentY{};
  float currentX{};
  Player *player;
  Animation idleAnimation{
	  "assets/enemies/skeleton/Skeleton Idle.png",
	  11,
	  1.0f / 12.0f,
	  5.f
  };

  Animation attackAnimation{
	  "assets/enemies/skeleton/Skeleton Attack.png",
	  18,
	  1.0f / 12.0f,
	  5.f
  };
  
  Animation hitAnimation{
	  "assets/enemies/skeleton/Skeleton Hit.png",
	  8,
	  1.0f / 12.0f,
	  5.f
  };

  Animation walkAnimation{
	  "assets/enemies/skeleton/Skeleton Walk.png",
	  13,
	  1.0f / 12.0f,
	  5.f
  };
 public:
  Reactor reactor{};
  Skeleton(Vector2 pos, Rectangle collisionRect, Player *player, vector<CollisionBody>* terrainCollisionBodies);
  void Draw();
  [[nodiscard]] Rectangle GetHitbox() const;
  void Damage(int damage);
  [[nodiscard]] int GetHealth() const;
  [[nodiscard]] bool IsDead() const;
  void Attack();
  void Init();
};

#endif
