#ifndef RAYLIB_GAME_SRC_PLAYER_H_
#define RAYLIB_GAME_SRC_PLAYER_H_

#include "raylib.h"
#include "animation.h"
#include "reactor.h"
#include "config.h"

extern float scale;
extern bool showCollisionBoxes;

enum Direction {
  LEFT,
  RIGHT,
  STOP
};


class Player {
 private:
  bool facingRight{true};
  bool dealDamage{true};
  bool jumping{};
  bool hit{};

  Animation idleAnimation;
  Animation runningAnimation;
  Animation attackAnimation;
  Animation jumpAnimation;
  Animation fallAnimation;
  Animation deathAnimation;
  Animation hitAnimation;

 public:
  int collectedCoins{};
  int healthPotions{};
  std::function<void(int, Rectangle)> onBeingHit;
  Reactor<int> reactor{};
  float maxHealth{100};
  float maxStamina{100};
  float health{100};
  float stamina{100};
  Rectangle weaponHitbox{};
  bool isDead{false};
  bool deathAnimationPlayed{false};
  bool blocked{false};
  bool leftBlocked{};
  bool rightBlocked{};
  bool falling{};
  float fallSpeed{};
  Rectangle hitbox{};
  bool onGround{true};
  bool attacking{};
  Vector2 position{};
  Direction direction{STOP};
  Direction lastDirection{RIGHT};

  Player();
  void SetOnGround(bool on_ground);
  void SetXPosition(float x);
  void Draw();
  [[nodiscard]] float GetTextureHeight() const;
  [[nodiscard]] float GetHeight() const;
  [[nodiscard]] float GetTextureWidth() const;
  [[nodiscard]] float GetWidth() const;
  void SetPosition(Vector2 pos);
  void Attack();
  void Damage(int damage);
};

#endif 
