#include "raylib.h"
#include "config.h"
#include "animation.cpp"

using namespace std;
extern int groundLevel;
extern float scale;

enum Direction {
  LEFT,
  RIGHT,
  STOP
};

class Player {
 private:
  bool jumping{};
  bool falling{};
  float upwardsVelocity{};

  Animation idleAnimation{
	  ASSETS_PATH"_Idle.png",
	  10,
	  1.0f / 12.0f
  };
  Animation runningAnimation{
	  ASSETS_PATH"_Run.png",
	  10,
	  1.0f / 12.0f
  };
  Animation attackAnimation{
	  ASSETS_PATH"_Attack.png",
	  4,
	  1.0f / 12.0f
  };
  Animation jumpAnimation{
	  ASSETS_PATH"_Jump.png",
	  3,
	  1.0f / 12.0f
  };
  Animation fallAnimation{
	  ASSETS_PATH"_Fall.png",
	  3,
	  1.0f / 12.0f
  };

 public:
  bool onGround{};
  bool attacking{};
  Vector2 position{};
  Direction direction = STOP;
  Direction lastDirection = RIGHT;

  Player() {
	position = {0, 1000};
  }
  
  void draw() {
	float deltaTime{GetFrameTime()};
	if (direction == LEFT && !attacking) {
	  this->position.x -= 6;
	} else if (direction == RIGHT && !attacking) {
	  this->position.x += 6;
	}

	// add gravity to the object
//	if (position.y >= groundLevel - idleAnimation.GetHeight()) {
	if (onGround) {
	  // on the ground
	  upwardsVelocity = 0;
//	  position.y = groundLevel - idleAnimation.GetHeight();
	  jumping = false;
	} else {
	  // falling
	  // GRAVITY is in pixels per second squared
	  upwardsVelocity += GRAVITY * deltaTime * deltaTime;
	}

	if ((IsKeyPressed(KEY_SPACE) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)) && !jumping) {
	  // jumping
	  jumping = true;
	  // JUMP_FORCE is in pixels per second
	  upwardsVelocity += JUMP_FORCE * deltaTime;
	} else if ((IsKeyPressed(KEY_N) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) && !attacking) {
	  attacking = true;
	}

	position.y += upwardsVelocity;

	bool facingRight = lastDirection == RIGHT;

	if (attacking) {
	  bool completed = attackAnimation.Animate(position, facingRight);
	  if (completed) {
		attacking = false;
	  }
	} else if (jumping && upwardsVelocity < 0) {
	  jumpAnimation.Animate(position, facingRight);
	} else if (upwardsVelocity > 0) {
	  fallAnimation.Animate(position, facingRight);
	} else if (direction == RIGHT || direction == LEFT) {
	  runningAnimation.Animate(position, facingRight);
	} else {
	  idleAnimation.Animate(position, facingRight);
	}
  }

  [[nodiscard]] float GetHeight() const {
	return this->runningAnimation.GetHeight();
  }

  [[nodiscard]] float GetWidth() const {
	return abs(this->runningAnimation.GetWidth());
  }

  void SetPosition(Vector2 pos) {
	this->position = pos;
  }
  
};