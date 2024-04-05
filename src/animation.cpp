#include "animation.h"
Animation::Animation(const string &texturePath,
					 int numberOfFrames,
					 float updateTime,
					 float scale,
					 int rows,
					 int firstRow,
					 int lastRow) :
	Animation{
		make_shared<raylib::Texture2D>(texturePath),
		numberOfFrames,
		updateTime,
		scale,
		rows,
		firstRow,
		lastRow} {
}

Animation::Animation(const shared_ptr<raylib::Texture2D> texture,
					 int numberOfFrames,
					 float updateTime,
					 float scale,
					 int rows,
					 int firstRow,
					 int lastRow) :
	numberOfFrames{numberOfFrames},
	updateTime{updateTime},
	scale{scale},
	rows{rows},
	firstRow{firstRow},
	lastRow{lastRow},
	texture{texture} {

  rectangle = {
	  .x = 0.0f,
	  .y = 0.0f,
	  .width = static_cast<float>(texture->width) / static_cast<float>(numberOfFrames),
	  .height = static_cast<float>(texture->height) / static_cast<float>(rows)
  };
  currentRow = firstRow;
}

void Animation::SetPosition(raylib::Vector2 pos) {
  this->position = pos;
}

raylib::Vector2 Animation::GetPosition() const {
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

void Animation::DrawFirstFrame(raylib::Vector2 pos) {
  position = pos;
  raylib::Rectangle rect = {
	  0.0f,
	  0.0f,
	  abs(rectangle.width),
	  rectangle.height
  };
  texture->Draw(
	  rect,
	  {
		  position.x,
		  position.y,
		  abs(rectangle.width * scale),
		  rectangle.height * scale
	  },
	  {0, 0},
	  0,
	  WHITE);
}

void Animation::DrawLastFrame(raylib::Vector2 pos) {
  position = pos;
  raylib::Rectangle rect = rectangle;

  rect.x = abs(rectangle.width) * (numberOfFrames - 1);
  texture->Draw(
	  rect,
	  {position.x, position.y, abs(rectangle.width * scale), rectangle.height * scale},
	  {0, 0},
	  0,
	  WHITE);
}

bool Animation::Animate(raylib::Vector2 pos, bool facingRight) {
  position = pos;
  bool completed{false};
  runningTime += GetFrameTime();

  rectangle.width = facingRight ? abs(rectangle.width) : -abs(rectangle.width);
  if (runningTime >= updateTime) {
	runningTime = 0.0f;
	if (rectangle.x + abs(rectangle.width) >= texture->width) {
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

  texture->Draw(
	  rectangle,
	  {
		  position.x,
		  position.y,
		  abs(rectangle.width * scale),
		  rectangle.height * scale
	  },
	  {0, 0},
	  0,
	  WHITE);

  return completed;
}

raylib::Rectangle Animation::GetSourceRec() const {
  return rectangle;
}

//Animation::~Animation() {
////  texture->Unload();
//}
