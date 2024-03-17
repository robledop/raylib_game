#include <complex>
#include "raylib.h"
using namespace std;

class Animation {
  Texture2D texture;
  Rectangle rectangle;
  Vector2 position;
  float updateTime;
  float runningTime{};
  float frame{};
  int numberOfFrames;
  float scale;

 public:
  Animation(const char *texturePath, int numberOfFrames, float updateTime, float scale) {
	this->texture = LoadTexture(texturePath);
	this->numberOfFrames = numberOfFrames;
	this->updateTime = updateTime;
	this->texture.height *= scale;
	this->texture.width *= scale;
	this->scale = scale;
	rectangle = {
		0.0f,
		0.0f,
		(float)texture.width / (float)numberOfFrames,
		(float)texture.height
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

  bool Animate(Vector2 pos, bool facingRight = true) {
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
	DrawTextureRec(texture, rectangle, position, WHITE);
	return completed;
  }
};