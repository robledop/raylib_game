#include "terrain.h"

class GroundDark : public Terrain {
 public:
  GroundDark(Vector2 pos, const Texture2D* tex, bool blocking = true) : Terrain(pos, tex, blocking) {
	sourceRect =  {24 * 1, 24 * 1, 24, 24};
  }
};