#include "raylib.h"
#include "terrain.h"

extern float scale;

class GroundRock : public Terrain {
 public:
  GroundRock(Vector2 pos, const Texture2D* tex) : Terrain(pos, tex) {
	sourceRect =  {24 * 7 , 0, 24, 24};
  }
};
