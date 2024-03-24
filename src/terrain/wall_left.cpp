#include "terrain.h"

extern float scale;

class WallLeft : public Terrain {
  bool adjacent = false;
 public:
  WallLeft(Vector2 pos, const Texture2D *tex, bool adjacent = false) : Terrain(pos, tex) {
	if (adjacent) {
	  sourceRect = {2, 24 * 1, 22, 24};
	} else {
	  sourceRect = {0, 24 * 1, 24, 24};
	}
  }
};