#include "skeleton.h"
void Skeleton::Draw() {
  if (IsDead()) {
	return;
  }

#ifdef SHOW_COLLISION_BOXES
  DrawRectangleRec(this->collisionRect, CYAN);
  DrawRectangleRec(weaponHitbox, SEAGREEN);
#endif

  static bool completed{false};
  if (abs(player.position.x - currentX) < 400) {
	position.y = currentY - abs(idleAnimation.GetTextureHeight() - attackAnimation.GetTextureHeight());
	position.x = currentX - abs(idleAnimation.GetTextureWidth() - attackAnimation.GetTextureWidth());
	completed = attackAnimation.Animate(position, false);
	if (CheckCollisionRecs(player.hitbox, weaponHitbox)) {
	  player.Damage(2);
	}
  } else if (completed) {
	position.y = currentY;
	position.x = currentX;
	idleAnimation.Animate(position, false);
  } else {
	position.y = currentY - abs(idleAnimation.GetTextureHeight() - attackAnimation.GetTextureHeight());
	position.x = currentX - abs(idleAnimation.GetTextureWidth() - attackAnimation.GetTextureWidth());
	completed = attackAnimation.Animate(position, false);
  }

  if (player.dealDamage && !damagedByCurrentAttack) {
	if (CheckCollisionRecs(player.weaponHitbox, collisionRect)) {
	  TraceLog(LOG_INFO, "Skeleton hit");
	  Damage();
	}
  } else if (!player.dealDamage) {
	damagedByCurrentAttack = false;
  }

  // Draw health bar at the top of the skeleton
  DrawRectangle(currentX + 10, currentY - 10, health, 10, RED);
}

Skeleton::Skeleton(Vector2 pos, Rectangle collisionRect, Player &player) : CollisionBody{pos, collisionRect, true},
																		   player{player} {
  currentY = pos.y;
  currentX = pos.x;
  weaponHitbox = {collisionRect.x - 90, collisionRect.y, 90, collisionRect.height};
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
