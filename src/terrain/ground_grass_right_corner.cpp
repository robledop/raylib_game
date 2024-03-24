#include "block.cpp"

extern float scale;

class GroundGrassRightCorner : public Block {
  bool adjacent = false;
 public:
  GroundGrassRightCorner(Vector2 pos,const Texture2D *tex, bool adjacent = false) : Block(pos, tex) {
	if (adjacent){
	  sourceRect = {(24 * 3) - 2, 0, 22, 24};
	}else{
	  sourceRect = {24 * 3, 0, 24, 24};
	}
  }
};