#include "chest.h"

Chest::Chest(Vector2 position, Rectangle collisionRect) : CollisionBody{position, collisionRect} {

}

void Chest::Draw() {
  animation.DrawFirstFrame(position);
}
