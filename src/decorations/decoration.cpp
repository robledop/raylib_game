#include "decoration.h"

Decoration::Decoration(raylib::Vector2 pos, const raylib::Texture *tex) {
  this->texture = tex;
  this->position = pos;
  this->rec = {
	  .x= 0,
	  .y = 0,
	  .width = static_cast<float>(texture->width),
	  .height = static_cast<float>(texture->height)
  };
}

Decoration::Decoration(raylib::Vector2 pos, const raylib::Texture *tex, raylib::Rectangle rec) {
  this->texture = tex;
  this->position = pos;
  this->rec = rec;
}

void Decoration::Draw() const {
  texture->Draw(
	  rec,
	  {position.x, position.y, rec.width * scale * 3, rec.height * scale * 3},
	  {0, 0}, 0, WHITE);
}
