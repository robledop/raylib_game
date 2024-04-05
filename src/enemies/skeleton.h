#ifndef RAYLIB_GAME_SRC_ENEMIES_SKELETON_H_
#define RAYLIB_GAME_SRC_ENEMIES_SKELETON_H_
#include "../terrain/collision_body.h"
#include "animation.h"
#include "../player.h"
#include "colors.h"
#include "config.h"
#include <vector>
#include "enemy.h"
#include <memory>

using namespace std;

extern bool showCollisionBoxes;

class Skeleton : public CollisionBody, public Enemy {
 private:
  
//  Skeleton(raylib::Vector2 pos,
//		   raylib::Rectangle collisionRect,
//		   const unique_ptr<Player> &player,
//		   const unique_ptr<vector<unique_ptr<CollisionBody>>> &terrainCollisionBodies,
//		   const unique_ptr<Reactor<raylib::Vector2>> &reactor);
  bool deathAnimationPlayed;
  bool attacking;
  bool dealDamage;
  bool hit;
  bool staggered;
  bool facingRight;
  bool sameYPosAsPlayer;
  int delay;
  const unique_ptr<vector<unique_ptr<CollisionBody>>> &terrainCollisionBodies;

  Rectangle weaponHitbox;
  int health;
  float currentY;
  float currentX;
  const unique_ptr<Player> &player;
  void HandleCombat();

 public:
  Skeleton(raylib::Vector2 pos,
		   raylib::Rectangle collisionRect,
		   const unique_ptr<Player> &player,
		   const unique_ptr<vector<unique_ptr<CollisionBody>>> &terrainCollisionBodies,
		   const unique_ptr<Reactor<raylib::Vector2>> &reactor,
		   const shared_ptr<raylib::Texture2D> idleTexture,
		   const shared_ptr<raylib::Texture2D> attackTexture,
		   const shared_ptr<raylib::Texture2D> hitTexture,
		   const shared_ptr<raylib::Texture2D> walkTexture,
		   const shared_ptr<raylib::Texture2D> deathTexture);
  Animation idleAnimation;
  Animation attackAnimation;
  Animation hitAnimation;
  Animation walkAnimation;
  Animation deathAnimation;
  bool droppedLoot{false};

  Reactor<int> reactor;
  const unique_ptr<Reactor<raylib::Vector2>> &deathReactor;
  void Draw();
  [[nodiscard]] int GetHealth() const;
  [[nodiscard]] bool IsDead() const;
  void Attack();
  void Damage(int damage) override;
};

#endif
