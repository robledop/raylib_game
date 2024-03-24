#include "raylib.h"
#include "block.cpp"

extern float scale;

class GroundGrassLeftCorner : public Block {
  bool adjacent = false;
 public:
  GroundGrassLeftCorner(Vector2 pos, const Texture2D* tex, bool adjacent = false) : Block(pos, tex) {
	if (adjacent){
	  sourceRect =  {2, 0, 22, 24};
	}else{
	  sourceRect =  {0, 0, 24, 24};
	}
  }
};