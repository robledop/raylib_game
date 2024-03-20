#include <complex>
#include "raylib.h"
using namespace std;
extern float scale;

class Animation {
  Texture2D texture;
  Rectangle rectangle;
  Vector2 position;
  float updateTime;
  float runningTime{};
  float frame{};
  int numberOfFrames;
  int width;
  int height;

 public:
  Animation(const char *texturePath, int numberOfFrames, float updateTime) {
	this->texture = LoadTexture(texturePath);
	width = texture.width;
	height = texture.height;

	this->numberOfFrames = numberOfFrames;
	this->updateTime = updateTime;
	rectangle = {
		0.0f,
		0.0f,
		(float)(width * scale * 4) / (float)numberOfFrames,
		(float)(height * scale * 4)
	};
  }

  void SetPosition(Vector2 pos) {
	this->position = pos;
  }

  Vector2 GetPosition() {
	return position;
  }

  float GetHeight() const {
	return rectangle.height;
  }

  float GetWidth() const {
	return rectangle.width;
  }
  
  void UpdateScale() {
	texture.width = width * scale * 4;
	texture.height = height * scale * 4;

	rectangle.height = (float)texture.height;
	rectangle.width = (float)texture.width / (float)numberOfFrames;
  }

  bool Animate(Vector2 pos, bool facingRight = true) {
	UpdateScale();
	position = pos;
	bool completed{false};
	float deltaTime{GetFrameTime()};
	runningTime += deltaTime;

	rectangle.width = facingRight ? abs(rectangle.width) : -abs(rectangle.width);
	if (runningTime >= updateTime) {
	  runningTime = 0.0f;
	  rectangle.x = frame * abs(rectangle.width);
	  frame++;
	  if (frame > (float)numberOfFrames) {
		frame = 0;
		completed = true;
	  }
	}

//	if (facingRight){
//	  DrawRectangle(position.x, position.y, rectangle.width, rectangle.height, RED);
//	}else{
//	  DrawRectangle(position.x, position.y, -rectangle.width, rectangle.height, RED);
//	}
	DrawTextureRec(texture, rectangle, position, WHITE);
	DrawRectangle(position.x + abs(rectangle.width) / 2, position.y + rectangle.height, 10, 10, BLUE);

	return completed;
  }
};