#include "collision_body.h"

CollisionBody::CollisionBody(Vector2 pos,
                             Rectangle collisionRect,
                             bool blocking)
    : blocking{blocking}, collisionRect{collisionRect}, position{pos} {}

std::tuple<bool, float> CollisionBody::CheckTopCollision(
    Rectangle hitbox,
    float playerSpeed) const {
  if (!blocking)
    return std::make_tuple(false, 0);
  return std::make_tuple((hitbox.x < (position.x + collisionRect.width) &&
                          (hitbox.x + hitbox.width) > position.x) &&
                             hitbox.y + hitbox.height <=
                                 position.y + playerSpeed * GetFrameTime() &&
                             hitbox.y + hitbox.height >=
                                 position.y - 10 - playerSpeed * GetFrameTime(),
                         position.y);
}

std::tuple<bool, float> CollisionBody::CheckSideCollision(
    Rectangle hitbox,
    float playerSpeed) const {
  if (!blocking)
    return std::make_tuple(false, 0);
  return std::make_tuple(
      hitbox.y < position.y + (collisionRect.height) &&
          hitbox.y + hitbox.height > position.y &&
          ((hitbox.x + hitbox.width <=
                position.x + 10 + playerSpeed * GetFrameTime() &&
            hitbox.x + hitbox.width >=
                position.x - 10 - playerSpeed * GetFrameTime()) ||
           (hitbox.x >= position.x + (collisionRect.width) - 10 -
                            playerSpeed * GetFrameTime() &&
            hitbox.x <= position.x + (collisionRect.width) + 10 +
                            playerSpeed * GetFrameTime())),
      position.x);
}

bool CollisionBody::CheckBottomCollision(Rectangle hitbox,
                                         float playerSpeed) const {
  if (!blocking)
    return false;
  return (hitbox.x < (position.x + (collisionRect.width * 3 * scale)) &&
          hitbox.x + hitbox.width > position.x) &&
         hitbox.y >= position.y + (collisionRect.height * 3 * scale) -
                         playerSpeed * GetFrameTime() &&
         hitbox.y <= position.y + (collisionRect.height * 3 * scale) + 10 +
                         playerSpeed * GetFrameTime();
}
Rectangle CollisionBody::GetCollisionRect() const {
  return collisionRect;
}
