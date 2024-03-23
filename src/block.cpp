#ifndef BLOCK
#define BLOCK

#include "raylib.h"
extern float scale;

class Block {
 protected:
  const Texture2D *texture;
  bool blocking;

 public:
  Rectangle sourceRect;
  Vector2 position{};
  Block(Vector2 pos, const Texture2D *tex, bool blocking = true) {
	this->position = pos;
	this->texture = tex;
	this->blocking = blocking;
  }

  bool CheckTopCollision(Rectangle hitbox, float playerSpeed) const {
	if (!blocking) return false;
	return (hitbox.x < (position.x + (sourceRect.width * 3 * scale)) && hitbox.x + hitbox.width > position.x)
		&& hitbox.y + hitbox.height <= position.y + playerSpeed * GetFrameTime()
		&& hitbox.y + hitbox.height >= position.y - 10 - playerSpeed * GetFrameTime();
  }

  bool CheckSideCollision(Rectangle hitbox, float playerSpeed) const {
	if (!blocking) return false;
	return hitbox.y < position.y + (sourceRect.height * 3 * scale) && hitbox.y + hitbox.height > position.y
		&& ((hitbox.x + hitbox.width <= position.x + 10 + playerSpeed * GetFrameTime()
			&& hitbox.x + hitbox.width >= position.x - 10 - playerSpeed * GetFrameTime())
			|| (hitbox.x >= position.x + (sourceRect.width * 3 * scale) - 10 - playerSpeed * GetFrameTime()
				&& hitbox.x <= position.x + (sourceRect.width * 3 * scale) + 10 + playerSpeed * GetFrameTime()));
  }

  void Draw() {
	DrawTexturePro(*texture,
				   sourceRect,
				   {position.x, position.y, 24 * 3 * scale, 24 * 3 * scale},
				   {0, 0},
				   0,
				   WHITE);
  }

#ifdef GUIDES
  DrawRectangle(position.x, position.y, 10, 10, RED);
#endif
};
#endif