#include "shop.h"

Shop::Shop(Vector2 pos) {
  position = {pos.x, pos.y - animation.GetTextureHeight() + 24 * 3 * scale};
}

void Shop::Draw() {
  animation.Animate(position, true);
}