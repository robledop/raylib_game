#include "raylib.h"
#include "config.h"
#include "player.h"

void Player::SetOnGround(bool on_ground) {
  this->onGround = on_ground;
}

void Player::SetXPosition(float x) {
  if (lastDirection == RIGHT && rightBlocked) {
	this->position.x = x - GetTextureWidth() / 2.5f - hitbox.width;
  } else if (lastDirection == LEFT && leftBlocked) {
	this->position.x = x - (GetTextureWidth() / 2.1f) + 24 * 3;
  }
}

void Player::draw() {
  if (isDead) {
	return;
  }

  if (position.y > maxY) {
	isDead = true;
  }

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

  const float deltaTime{GetFrameTime()};
  if (direction == LEFT && !attacking && !leftBlocked) {
	this->position.x -= RUN_SPEED;
  } else if (direction == RIGHT && !attacking && !rightBlocked) {
	this->position.x += RUN_SPEED;
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

  const bool facingRight = lastDirection == RIGHT;

  if (attacking) {
	if (attackAnimation.Animate(position, facingRight)) {
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

[[nodiscard]] float Player::GetTextureHeight() const {
  return this->runningAnimation.GetTextureHeight();
}

[[nodiscard]] float Player::GetHeight() const {
  return (this->runningAnimation.GetTextureHeight() / 2);
}

[[nodiscard]] float Player::GetTextureWidth() const {
  return abs(this->runningAnimation.GetTextureWidth());
}

[[nodiscard]] float Player::GetWidth() const {
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

void Player::SetPosition(Vector2 pos) {
  this->position = pos;
}
