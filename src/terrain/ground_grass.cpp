#include "raylib.h"
#include "terrain.h"

extern float scale;

class GroundGrass : public Terrain {
 public:
  GroundGrass(Vector2 pos, const Texture2D* tex) : Terrain(pos, tex) {
	sourceRect =  {24 * 2 , 0, 24, 24};
  }
};