#include "skeleton.h"
void Skeleton::Draw() {
  static bool completed{false};
  if (abs(player.position.x - currentX) < 400) {
	position.y = currentY - abs(idleAnimation.GetTextureHeight() - attackAnimation.GetTextureHeight());
	position.x = currentX - abs(idleAnimation.GetTextureWidth() - attackAnimation.GetTextureWidth());
	completed = attackAnimation.Animate(position, false);
  } else if (completed) {
	position.y = currentY;
	position.x = currentX;
	idleAnimation.Animate(position, false);
  } else {
	position.y = currentY - abs(idleAnimation.GetTextureHeight() - attackAnimation.GetTextureHeight());
	position.x = currentX - abs(idleAnimation.GetTextureWidth() - attackAnimation.GetTextureWidth());
	completed = attackAnimation.Animate(position, false);
  }
}
Skeleton::Skeleton(Vector2 pos, Rectangle collisionRect, Player &player) : CollisionBody{pos, collisionRect, true},
																		   player{player} {
  currentY = pos.y;
  currentX = pos.x;
}
