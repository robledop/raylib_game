#include "terrain.h"

Terrain::Terrain(Vector2 pos, Rectangle rectangle, bool blocking) : rect{rectangle},
																	position{pos},
																	blocking{blocking} {}

std::tuple<bool, float> Terrain::CheckTopCollision(Rectangle hitbox, float playerSpeed) const {
  if (!blocking) return std::make_tuple(false, 0);
  return std::make_tuple((hitbox.x < (position.x + rect.width) && (hitbox.x + hitbox.width) > position.x)
							 && hitbox.y + hitbox.height <= position.y + playerSpeed * GetFrameTime()
							 && hitbox.y + hitbox.height >= position.y - 10 - playerSpeed * GetFrameTime(), position.y);
}

std::tuple<bool, float> Terrain::CheckSideCollision(Rectangle hitbox, float playerSpeed) const {
  if (!blocking) return std::make_tuple(false, 0);
  return std::make_tuple(hitbox.y < position.y + (rect.height) && hitbox.y + hitbox.height > position.y
							 && ((hitbox.x + hitbox.width <= position.x + 10 + playerSpeed * GetFrameTime()
								 && hitbox.x + hitbox.width >= position.x - 10 - playerSpeed * GetFrameTime())
								 || (hitbox.x
									 >= position.x + (rect.width) - 10 - playerSpeed * GetFrameTime()
									 && hitbox.x
										 <= position.x + (rect.width) + 10 + playerSpeed * GetFrameTime())),
						 position.x);
}

//void Terrain::Draw() {
//  DrawTexturePro(*texture,
//				 rect,
//				 {position.x, position.y, 24 * 3 * scale, 24 * 3 * scale},
//				 {0, 0},
//				 0,
//				 WHITE);
//}

bool Terrain::CheckBottomCollision(Rectangle hitbox, float playerSpeed) const {
  if (!blocking) return false;
  return (hitbox.x < (position.x + (rect.width * 3 * scale)) && hitbox.x + hitbox.width > position.x)
	  && hitbox.y >= position.y + (rect.height * 3 * scale) - playerSpeed * GetFrameTime()
	  && hitbox.y <= position.y + (rect.height * 3 * scale) + 10 + playerSpeed * GetFrameTime();
}
