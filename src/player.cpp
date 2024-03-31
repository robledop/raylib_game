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

void Player::Attack() {
  if (attackAnimation.Animate(position, facingRight)) {
	attacking = false;
  }

  if (attackAnimation.frame >= attackAnimation.numberOfFrames - 1) {
	dealDamage = true;
  } else if (attackAnimation.frame >= 2.f) {
	if (dealDamage) {
	  reactor.DispatchEvent(ATTACK, 10);
	  dealDamage = false;
	}
  }
}

void Player::Draw() {
  if (isDead && !deathAnimationPlayed) {
	deathAnimationPlayed = deathAnimation.Animate(position, lastDirection == RIGHT);
	return;
  } else if (isDead) {
	auto rect = deathAnimation.GetSourceRec();
	rect.x = rect.x + abs(rect.width) * (deathAnimation.numberOfFrames - 1);
	DrawTexturePro(deathAnimation.GetTexture(),
				   rect,
				   {position.x, position.y, abs(rect.width) * deathAnimation.scale, rect.height * deathAnimation.scale},
				   {0, 0},
				   0,
				   WHITE);
	return;
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

  if (lastDirection == RIGHT) {
	weaponHitbox.x = hitbox.x + hitbox.width;
	weaponHitbox.y = hitbox.y;
	weaponHitbox.width = 170;
	weaponHitbox.height = hitbox.height;
  } else {
	weaponHitbox.x = hitbox.x - 170;
	weaponHitbox.y = hitbox.y;
	weaponHitbox.width = 170;
	weaponHitbox.height = hitbox.height;
  }

  if (showCollisionBoxes) {
	DrawRectangleLinesEx(hitbox, 1, RED);
	DrawRectangleLinesEx(weaponHitbox, 1, BLUE);
  }

#ifdef GUIDES
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

  facingRight = lastDirection == RIGHT;

  if (attacking) {
	Attack();
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
void Player::Damage(int damage) {
  health -= damage;
  if (health <= 0) {
	isDead = true;
  }
}

Player::Player() {
  reactor.RegisterEvent(ATTACK);
  reactor.RegisterEvent(TAKE_DAMAGE);
}

void Player::Init() {
  this->onBeingHit = [this](int damage, Rectangle enemyWeaponHitbox) {
	if (CheckCollisionRecs(this->hitbox, enemyWeaponHitbox)) {
	  Damage(damage);
	  TraceLog(LOG_INFO, "Player health: %d", health);
	}
  };
}
