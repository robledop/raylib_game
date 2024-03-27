#include "skeleton.h"
void Skeleton::Draw() {
  if (IsDead()) {
	return;
  }

  bool facingRight = player.position.x + idleAnimation.GetTextureWidth() > currentX;
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
  } else if (abs(player.position.x - currentX) < 400) {
	Attack();
	attackAnimation.Animate(position, facingRight);
	if (CheckCollisionRecs(player.hitbox, weaponHitbox)) {
	  if (dealDamage) {
		player.Damage(1);
	  }
	}
  } else {
	position.y = currentY;
	position.x = currentX;
	idleAnimation.Animate(position, facingRight);
  }

  if (player.dealDamage && !damagedByCurrentAttack) {
	if (CheckCollisionRecs(player.weaponHitbox, collisionRect)) {
	  TraceLog(LOG_INFO, "Skeleton hit");
	  hit = true;
	  Damage();
	}
  } else if (!player.dealDamage) {
	damagedByCurrentAttack = false;
  }

  // Draw health bar at the top of the skeleton
  DrawRectangle(currentX + 10, currentY - 10, health, 10, RED);
}

Skeleton::Skeleton(Vector2
				   pos, Rectangle
				   collisionRect, Player &player) : CollisionBody{pos, collisionRect, true},
													player{player} {
  currentY = pos.y;
  currentX = pos.x;
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
void Skeleton::Damage() {
  health -= 10;
  damagedByCurrentAttack = true;
}

void Skeleton::Attack() {
  float deltaTime{GetFrameTime()};
  runningTime += deltaTime;
  float updateTime{1 / 12.f};

  if (runningTime >= updateTime) {
	runningTime = 0.0f;
	frame++;
	if (frame > 18.f) {
	  frame = 0;
	} else if (frame > 4.f) {
	  dealDamage = false;
	} else if (frame > 3.f) {
	  dealDamage = true;
	}
  }
}
