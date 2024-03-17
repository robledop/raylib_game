#include "raylib.h"
#include "config.h"

enum Direction {
  LEFT,
  RIGHT,
  STOP
};

class Player {
 private:
  Image playerRunning{};
  Texture2D playerRunningAnim{};
  Image playerIdle{};
  Texture2D playerIdleAnim{};
  Image playerAttack1{};
  Texture2D playerAttack1Anim{};
  unsigned int nextFrameDataOffset;
  int currentAnimFrame;
  int frameDelay;
  int frameCounter;
  int animFrames;

 public:
  int x;
  int y;
  Direction direction = STOP;

  Player() {
	x = 100;
	y = GROUND_LEVEL;

	nextFrameDataOffset = 0;  // Current byte offset to next frame in image.data

	currentAnimFrame = 0;       // Current animation frame to load and draw
	frameDelay = 8;             // Frame delay to switch between animation frames
	frameCounter = 0;           // General frames counter
	animFrames = 0;

	// Load all GIF animation frames into a single Image
	// NOTE: GIF data is always loaded as RGBA (32bit) by default
	// NOTE: Frames are just appended one after another in image.data memory
	playerIdle = LoadImageAnim(ASSETS_PATH"__Idle.gif", &animFrames);
	playerRunning = LoadImageAnim(ASSETS_PATH"__Run.gif", &animFrames);
	playerAttack1 = LoadImageAnim(ASSETS_PATH"__Attack.gif", &animFrames);

	// Load texture from image
	// NOTE: We will update this texture when required with next frame data
	// WARNING: It's not recommended to use this technique for sprites animation,
	// use spritesheets instead, like illustrated in textures_sprite_anim example
	playerIdleAnim = LoadTextureFromImage(playerIdle);
	playerRunningAnim = LoadTextureFromImage(playerRunning);
	playerAttack1Anim = LoadTextureFromImage(playerAttack1);
  }

  void draw() {
	if (direction == LEFT) {
	  this->x -= 6;
	} else if (direction == RIGHT) {
	  this->x += 6;
	}

	frameCounter++;
	if (frameCounter >= frameDelay) {
	  // Move to next frame
	  // NOTE: If final frame is reached we return to first frame
	  currentAnimFrame++;
	  if (currentAnimFrame >= animFrames) currentAnimFrame = 0;

	  // Get memory offset position for next frame data in image.data
	  nextFrameDataOffset = playerIdle.width * playerIdle.height * 4 * currentAnimFrame;

	  // Update GPU texture data with next frame image data
	  // WARNING: Data size (frame size) and pixel format must match already created texture
	  UpdateTexture(playerIdleAnim, ((unsigned char *)playerIdle.data) + nextFrameDataOffset);
	  UpdateTexture(playerRunningAnim, ((unsigned char *)playerRunning.data) + nextFrameDataOffset);
	  UpdateTexture(playerAttack1Anim, ((unsigned char *)playerAttack1.data) + nextFrameDataOffset);

	  frameCounter = 0;
	}

	if (IsKeyDown(KEY_SPACE)) {
	  
	  TraceLog(TraceLogLevel::LOG_INFO, "Player attack");
	  
	  DrawTexturePro(playerAttack1Anim,
					 {
						 0,
						 0,
						 static_cast<float>(direction == RIGHT ? playerAttack1.width : -playerAttack1.width),
						 static_cast<float>(playerAttack1.height)
					 },
					 {
						 static_cast<float>(this->x - playerAttack1.width * 1.5),
						 static_cast<float>(this->y - playerAttack1.height * 3.75),
						 static_cast<float>(playerAttack1.width * 3),
						 static_cast<float>(playerAttack1.height * 3)
					 },
					 {0, 0},
					 0,
					 WHITE);
	} else if (direction == LEFT || direction == RIGHT) {
	  DrawTexturePro(playerRunningAnim,
					 {
						 0,
						 0,
						 static_cast<float>(direction == RIGHT ? playerRunning.width : -playerRunning.width),
						 static_cast<float>(playerIdle.height)
					 },
					 {
						 static_cast<float>(this->x - playerRunning.width * 1.5),
						 static_cast<float>(this->y - playerRunning.height * 3.75),
						 static_cast<float>(playerRunning.width * 3),
						 static_cast<float>(playerRunning.height * 3)
					 },
					 {0, 0},
					 0,
					 WHITE);

	} else {
	  DrawTexturePro(playerIdleAnim,
					 {
						 0,
						 0,
						 static_cast<float>(playerIdle.width),
						 static_cast<float>(playerIdle.height)
					 },
					 {
						 static_cast<float>(this->x - playerIdle.width * 1.5),
						 static_cast<float>(this->y - playerIdle.height * 3.75),
						 static_cast<float>(playerIdle.width * 3),
						 static_cast<float>(playerIdle.height * 3)
					 },
					 {0, 0},
					 0,
					 WHITE);
	}
  }
};