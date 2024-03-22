#include "raylib.h"
#include "config.h"
#include "animation.cpp"

using namespace std;
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

  void SetOnGround(bool on_ground) {
	this->onGround = on_ground;
  }

  void SetXPosition(float x) {
	if (lastDirection == RIGHT && rightBlocked) {
	  this->position.x = x - GetTextureWidth() / 2.5f - hitbox.width;
	} else if (lastDirection == LEFT && leftBlocked) {
	  this->position.x = x - (GetTextureWidth() / 2.1f) + 24 * 3;
	}
  }

  void draw() {
	float hitboxX;
	if (lastDirection == RIGHT) {
	  hitboxX = position.x + GetTextureWidth() / 2.5f;
	} else {
	  hitboxX = position.x + GetTextureWidth() / 2.1f;
	}
	hitbox = {
		hitboxX,
		position.y + GetTextureHeight() / 2,
		GetWidth(),
		GetHeight()
	};
	
#ifdef GUIDES
	DrawRectangleRec(hitbox, RED);
	DrawRectangle(position.x, position.y, 10, 10, GREEN);
#endif

	float deltaTime{GetFrameTime()};
	if (direction == LEFT && !attacking && !leftBlocked) {
	  this->position.x -= 6;
	} else if (direction == RIGHT && !attacking && !rightBlocked) {
	  this->position.x += 6;
	}

	// add gravity to the object
	if (onGround) {
	  // on the ground
	  upwardsVelocity = 0;
	  jumping = false;
	} else {
	  // falling
	  // GRAVITY is in pixels per second squared
	  if (upwardsVelocity < 10) {
		upwardsVelocity += GRAVITY * deltaTime * deltaTime;
	  }
	}

	if ((IsKeyPressed(KEY_SPACE) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)) && !jumping) {
	  // jumping
	  jumping = true;
	  // JUMP_FORCE is in pixels per second
	  upwardsVelocity += JUMP_FORCE * deltaTime;
	  onGround = false;
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

#ifdef GUIDES
	DrawRectangle(hitbox.x, hitbox.y, 10, 10, GREEN);
#endif
  }

  [[nodiscard]] float GetTextureHeight() const {
	return this->runningAnimation.GetTextureHeight();
  }

  [[nodiscard]] float GetHeight() const {
	return this->runningAnimation.GetTextureHeight() / 2;
  }

  [[nodiscard]] float GetTextureWidth() const {
	return abs(this->runningAnimation.GetTextureWidth());
  }

  [[nodiscard]] float GetWidth() const {
	if (direction == RIGHT || direction == LEFT) {
	  return abs(this->runningAnimation.GetTextureWidth() / 8);
	} else if (jumping) {
	  return abs(this->jumpAnimation.GetTextureWidth() / 8);
	} else if (attacking) {
	  return abs(this->attackAnimation.GetTextureWidth() / 8);
	} else {
	  return abs(this->idleAnimation.GetTextureWidth() / 8);
	}
  }

  void SetPosition(Vector2 pos) {
	this->position = pos;
  }

};