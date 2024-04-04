#include "animation.h"

Animation::Animation(const char *texturePath, int numberOfFrames, float updateTime, float scale, int rows, int firstRow, int lastRow) :
	numberOfFrames{numberOfFrames},
	updateTime{updateTime},
	scale{scale},
	rows{rows},
	firstRow{firstRow},
	lastRow{lastRow} {
  this->texture = LoadTexture(texturePath);
  rectangle = {
	  0.0f,
	  0.0f,
	  static_cast<float>(texture.width) / static_cast<float>(numberOfFrames),
	  static_cast<float>(texture.height) / static_cast<float>(rows)
  };
  currentRow = firstRow;
  
  texturePath = texturePath;
}

void Animation::SetPosition(Vector2 pos) {
  this->position = pos;
}

Vector2 Animation::GetPosition() const {
  return position;
}

float Animation::GetTextureHeight() const {
  return rectangle.height * scale;
}

float Animation::GetTextureWidth() const {
  return abs(rectangle.width * scale);
}

void Animation::Reset() {
  frame = 0;
  runningTime = 0.0f;
}

void Animation::DrawFirstFrame(Vector2 pos) {
  position = pos;
  Rectangle rect = {
	  0.0f,
	  0.0f,
	  abs(rectangle.width),
	  rectangle.height
  };
  DrawTexturePro(texture,
				 rect,
				 {position.x, position.y, abs(rectangle.width * scale), rectangle.height * scale},
				 {0, 0},
				 0,
				 WHITE);
}

void Animation::DrawLastFrame(Vector2 pos) {
  position = pos;
  Rectangle rect = rectangle;

  rect.x = abs(rectangle.width) * (numberOfFrames - 1);
  DrawTexturePro(texture,
				 rect,
				 {position.x, position.y, abs(rectangle.width * scale), rectangle.height * scale},
				 {0, 0},
				 0,
				 WHITE);
}

bool Animation::Animate(Vector2 pos, bool facingRight) {
  position = pos;
  bool completed{false};
  runningTime += GetFrameTime();

  rectangle.width = facingRight ? abs(rectangle.width) : -abs(rectangle.width);
  if (runningTime >= updateTime) {
	runningTime = 0.0f;
	if (rectangle.x + abs(rectangle.width) >= texture.width) {
	  if (currentRow >= lastRow) {
		currentRow = firstRow;
	  } else {
		currentRow++;
	  }
	}
	rectangle.x = frame * abs(rectangle.width);
	rectangle.y = currentRow * abs(rectangle.height);
	frame++;
	if (frame >= static_cast<float>(numberOfFrames) && currentRow == firstRow) {
	  frame = 0;
	  completed = true;
	}
  }

  DrawTexturePro(texture,
				 rectangle,
				 {position.x, position.y, abs(rectangle.width * scale), rectangle.height * scale},
				 {0, 0},
				 0,
				 WHITE);

  return completed;
}

Texture2D Animation::GetTexture() const {
  return texture;
}

Rectangle Animation::GetSourceRec() const {
  return rectangle;
}

Animation::~Animation() {
  UnloadTexture(texture);
}
