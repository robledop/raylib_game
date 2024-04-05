#include "shop.h"

void Shop::Draw() {
  animation.Animate(position, true);
}

Shop::Shop(raylib::Vector2 position, raylib::Rectangle collisionRect) : CollisionBody(position, collisionRect, false) {

}
