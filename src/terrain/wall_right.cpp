#include "terrain.h"

extern float scale;

class WallRight : public Terrain {
  bool adjacent = false;
 public:
  WallRight(Vector2 pos, const Texture2D *tex, bool adjacent = false) : Terrain(pos, tex) {
	if (adjacent) {
	  sourceRect = {24 * 3, 24 * 2, 22, 24};
	} else {
	  sourceRect = {24 * 3, 24 * 2, 24, 24};
	}
  }
};
