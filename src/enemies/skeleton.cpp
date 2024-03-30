#include "skeleton.h"

Skeleton::Skeleton(Vector2 pos, Rectangle collRect, Player *p) : CollisionBody{pos, collRect, true},
																 player{p} {
  currentY = pos.y;
  currentX = pos.x;
}

void Skeleton::Draw() {
  if (IsDead()) {
	return;
  }

  facingRight = player->position.x + idleAnimation.GetTextureWidth() > currentX;
  collisionRect = {currentX, currentY, idleAnimation.GetTextureWidth(), idleAnimation.GetTextureHeight()};
  position.y = currentY - abs(idleAnimation.GetTextureHeight() - attackAnimation.GetTextureHeight());

  if (facingRight) {
	position.x = currentX;
	weaponHitbox = {collisionRect.x + idleAnimation.GetTextureWidth(), collisionRect.y, 90, collisionRect.height};
  } else {
	position.x = currentX - abs(idleAnimation.GetTextureWidth() - attackAnimation.GetTextureWidth());
	weaponHitbox = {collisionRect.x - 90, collisionRect.y, 90, collisionRect.height};
  }

#ifdef SHOW_COLLISION_BOXES
  DrawRectangleLinesEx(this->collisionRect, 2, CYAN);
  DrawRectangleLinesEx(weaponHitbox, 2, SEAGREEN);
#endif

  if (hit) {
	attackAnimation.Reset();
	delay = 0;

	position.y = currentY - abs(idleAnimation.GetTextureHeight() - hitAnimation.GetTextureHeight());
	if (facingRight) {
	  position.x = currentX - abs(idleAnimation.GetTextureWidth() - hitAnimation.GetTextureWidth());
	} else {
	  position.x = currentX - abs(idleAnimation.GetTextureWidth() - hitAnimation.GetTextureWidth() + 30);
	}
	bool completed = hitAnimation.Animate(position, facingRight);
	hit = !completed;
  }
  else if (abs(player->position.x - currentX) < 800 && abs(player->position.x - currentX) > 300) {
	if (player->position.x < currentX) {
	  currentX -= 1;
	} else {
	  currentX += 1;
	}
	position.y = currentY;
	position.x = currentX;
	walkAnimation.Animate(position, facingRight);
  } else if (abs(player->position.x - currentX) <= 300 && delay++ >= 60) {
	// Wait a second before attacking.
	// The attack animation is 18 frames long, and it runs 1/12 of 60 frames (5 times per second).
	if (delay > 60 + attackAnimation.numberOfFrames * 5) {
	  delay = 0;
	}

	Attack();
  } else {
	position.y = currentY;
	position.x = currentX;
	idleAnimation.Animate(position, facingRight);
	attackAnimation.Reset();
  }

  // Draw health bar at the top of the skeleton
  DrawRectangle(static_cast<int>(currentX) + 10, static_cast<int>(currentY) - 10, health, 10, RED);
}

void Skeleton::Init() {
  this->player->reactor.AddEventListener(ATTACK, [this](int data) {
	Damage(data);
  });
}

Rectangle Skeleton::GetHitbox() const {
  return collisionRect;
}

int Skeleton::GetHealth() const {
  return health;
}

bool Skeleton::IsDead() const {
  return health <= 0;
}

void Skeleton::Damage(int damage) {
  if (CheckCollisionRecs(player->weaponHitbox, collisionRect)) {
	hit = true;
	health -= damage;
	hitAnimation.Reset();
  }
}

void Skeleton::Attack() {
  attackAnimation.Animate(position, facingRight);

  if (attackAnimation.frame >= attackAnimation.numberOfFrames - 1) {
	dealDamage = true;
  } else if (attackAnimation.frame > 6.f) {
	if (dealDamage) {
	  dealDamage = false;
	  player->onBeingHit(1, weaponHitbox);
	}
  }
}

