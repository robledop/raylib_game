#include "shop.h"

void Shop::Draw() {
  animation.Animate(position, true);
}

Shop::Shop(Vector2 position, Rectangle collisionRect) : CollisionBody(position, collisionRect, false) {

}
