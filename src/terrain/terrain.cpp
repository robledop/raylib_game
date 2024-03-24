#include "terrain.h"

Terrain::Terrain(Vector2 pos, const Texture2D *tex, bool blocking) : texture{tex}, position{pos}, blocking{blocking} {}

bool Terrain::CheckTopCollision(Rectangle hitbox, float playerSpeed) const {
  if (!blocking) return false;
  return (hitbox.x < (position.x + (sourceRect.width * 3 * scale)) && hitbox.x + hitbox.width > position.x)
	  && hitbox.y + hitbox.height <= position.y + playerSpeed * GetFrameTime()
	  && hitbox.y + hitbox.height >= position.y - 10 - playerSpeed * GetFrameTime();
}

bool Terrain::CheckSideCollision(Rectangle hitbox, float playerSpeed) const {
  if (!blocking) return false;
  return hitbox.y < position.y + (sourceRect.height * 3 * scale) && hitbox.y + hitbox.height > position.y
	  && ((hitbox.x + hitbox.width <= position.x + 10 + playerSpeed * GetFrameTime()
		  && hitbox.x + hitbox.width >= position.x - 10 - playerSpeed * GetFrameTime())
		  || (hitbox.x >= position.x + (sourceRect.width * 3 * scale) - 10 - playerSpeed * GetFrameTime()
			  && hitbox.x <= position.x + (sourceRect.width * 3 * scale) + 10 + playerSpeed * GetFrameTime()));
}

void Terrain::Draw() {
  DrawTexturePro(*texture,
				 sourceRect,
				 {position.x, position.y, 24 * 3 * scale, 24 * 3 * scale},
				 {0, 0},
				 0,
				 WHITE);
}

bool Terrain::CheckBottomCollision(Rectangle hitbox, float playerSpeed) const {
  if (!blocking) return false;
  return (hitbox.x < (position.x + (sourceRect.width * 3 * scale)) && hitbox.x + hitbox.width > position.x)
	  && hitbox.y >= position.y + (sourceRect.height * 3 * scale) - playerSpeed * GetFrameTime()
	  && hitbox.y <= position.y + (sourceRect.height * 3 * scale) + 10 + playerSpeed * GetFrameTime();
}
