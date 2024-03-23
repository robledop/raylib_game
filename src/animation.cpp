#ifndef ANIMATION_H
#define ANIMATION_H

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
		(float)(width * scale * 4) / static_cast<float>(numberOfFrames),
		(float)(height * scale * 4)
	};
	UpdateScale();
  }

  void SetPosition(Vector2 pos) {
	this->position = pos;
  }

  Vector2 GetPosition() const
  {
	return position;
  }

  float GetTextureHeight() const {
	return rectangle.height;
  }

  float GetTextureWidth() const {
	return abs(rectangle.width);
  }
  
  void UpdateScale() {
	texture.width = width * scale * 4;
	texture.height = height * scale * 4;

	rectangle.height = static_cast<float>(texture.height);
	rectangle.width = static_cast<float>(texture.width) / static_cast<float>(numberOfFrames);
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
	  if (frame > static_cast<float>(numberOfFrames)) {
		frame = 0;
		completed = true;
	  }
	}

	DrawTextureRec(texture, rectangle, position, WHITE);

	return completed;
  }
};

#endif