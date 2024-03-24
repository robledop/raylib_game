#include "animation.h"

Animation::Animation(const char *texturePath, int numberOfFrames, float updateTime) {
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

void Animation::SetPosition(Vector2 pos) {
  this->position = pos;
}

Vector2 Animation::GetPosition() const {
  return position;
}

float Animation::GetTextureHeight() const {
  return rectangle.height;
}

float Animation::GetTextureWidth() const {
  return abs(rectangle.width);
}

void Animation::UpdateScale() {
  texture.width = width * scale * 4;
  texture.height = height * scale * 4;

  rectangle.height = static_cast<float>(texture.height);
  rectangle.width = static_cast<float>(texture.width) / static_cast<float>(numberOfFrames);
}

bool Animation::Animate(Vector2 pos, bool facingRight) {
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
