#ifndef RAYLIB_GAME_SRC_PLAYER_H_
#define RAYLIB_GAME_SRC_PLAYER_H_

#include "raylib.h"
#include "animation.h"

extern float scale;

enum Direction {
  LEFT,
  RIGHT,
  STOP
};

class Player {
 private:
  bool jumping{};

  Animation idleAnimation{
	  "../assets/player/_Idle.png",
	  10,
	  1.0f / 12.0f
  };
  Animation runningAnimation{
	  "../assets/player/_Run.png",
	  10,
	  1.0f / 12.0f
  };
  Animation attackAnimation{
	  "../assets/player/_Attack.png",
	  4,
	  1.0f / 12.0f
  };
  Animation jumpAnimation{
	  "../assets/player/_Jump.png",
	  3,
	  1.0f / 12.0f
  };
  Animation fallAnimation{
	  "../assets/player/_Fall.png",
	  3,
	  1.0f / 12.0f
  };

 public:
  bool isDead{false};
  bool blocked{false};
  bool leftBlocked{};
  bool rightBlocked{};
  bool falling{};
  float upwardsVelocity{};
  Rectangle hitbox{};
  bool onGround{true};
  bool attacking{};
  Vector2 position{};
  Direction direction = STOP;
  Direction lastDirection = RIGHT;

  void SetOnGround(bool on_ground);
  void SetXPosition(float x);
  void draw();
  [[nodiscard]] float GetTextureHeight() const;
  [[nodiscard]] float GetHeight() const;
  [[nodiscard]] float GetTextureWidth() const;
  [[nodiscard]] float GetWidth() const;
  void SetPosition(Vector2 pos);
};

#endif 
