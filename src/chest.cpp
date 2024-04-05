#include "chest.h"

Chest::Chest(raylib::Vector2 position, raylib::Rectangle collisionRect) : CollisionBody{position, collisionRect} {

}

void Chest::Draw() {
  animation.DrawFirstFrame(position);
}
