#include "decoration.h"

Decoration::Decoration(Vector2 pos, const Texture *tex) {
  this->texture = tex;
  this->position = pos;
  this->rec = {0, 0, (float)texture->width, (float)texture->height};
}

Decoration::Decoration(Vector2 pos, const Texture *tex, Rectangle rec) {
  this->texture = tex;
  this->position = pos;
  this->rec = rec;
}

void Decoration::Draw() {
  DrawTexturePro(*texture,
				 rec,
				 {position.x, position.y, rec.width * scale * 3, rec.height * scale * 3},
				 {0, 0},
				 0,
				 WHITE);
}