#include "shop.h"

void Shop::Draw() {
  animation.Animate(position, true);
}
Shop::Shop(Vector2 pos, Rectangle collisionRect) : CollisionBody(pos, collisionRect, false) {

}
Rectangle Shop::GetHitbox() const {
  return Rectangle();
}
