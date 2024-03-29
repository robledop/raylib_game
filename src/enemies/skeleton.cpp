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
  DrawRectangleRec(this->collisionRect, CYAN);
  DrawRectangleRec(weaponHitbox, SEAGREEN);
#endif

  if (hit) {
	position.y = currentY - abs(idleAnimation.GetTextureHeight() - hitAnimation.GetTextureHeight());
	position.x = currentX - abs(idleAnimation.GetTextureWidth() - hitAnimation.GetTextureWidth());
	bool completed = hitAnimation.Animate(position, facingRight);
	hit = !completed;
  } else if (abs(player->position.x - currentX) < 400) {
	Attack();
  } else {
	position.y = currentY;
	position.x = currentX;
	idleAnimation.Animate(position, facingRight);
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
  }
}

void Skeleton::Attack() {
  attackAnimation.Animate(position, facingRight);

  if (attackAnimation.frame >= attackAnimation.numberOfFrames - 1) {
	dealDamage = true;
	frame = 0;
  } else if (attackAnimation.frame > 6.f) {
	if (dealDamage) {
	  dealDamage = false;
	  player->onBeingHit(1, weaponHitbox);
	}
  }
}
