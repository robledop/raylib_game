#include <valarray>
#include "raylib.h"
#include "config.h"

using namespace std;

enum Direction {
  LEFT,
  RIGHT,
  STOP
};

class Player {
 private:
  bool attacking{};
  bool jumping{};
  bool falling{};
  float velocity{};
  Texture2D playerRunningTexture{};
  Rectangle playerRunningRec{};
  Texture2D playerIdleTexture{};
  Rectangle playerIdleRec{};
  Texture2D playerAttack1Texture{};
  Rectangle playerAttack1Rec{};
  Texture2D playerJumpTexture{};
  Rectangle playerJumpRec{};
  Texture2D playerFallTexture{};
  Rectangle playerFallRec{};

  const float updateTime{1.0f / 12.0f};
  float runningTime{};
  float frame{};

  bool AnimateTexture(Texture2D texture, Rectangle *rec, Vector2 pos, int numberOfFrames, bool facingRight = true) {
	float deltaTime{GetFrameTime()};
	runningTime += deltaTime;
	bool completed{false};

	rec->width = facingRight ? abs(rec->width) : -abs(rec->width);
	if (runningTime >= updateTime) {
	  runningTime = 0.0f;
	  rec->x = frame * abs(rec->width);
	  frame++;
	  if (frame > (float)numberOfFrames) {
		frame = 0;
		completed = true;
	  }
	}

	DrawTextureRec(texture, *rec, pos, WHITE);
	return completed;
  }

 public:
  Vector2 position{};
  Direction direction = STOP;
  Direction lastDirection = RIGHT;

  Player() {
	playerIdleTexture = LoadTexture(ASSETS_PATH"_Idle.png");
	playerIdleTexture.height *= 3;
	playerIdleTexture.width *= 3;
	playerRunningTexture = LoadTexture(ASSETS_PATH"_Run.png");
	playerRunningTexture.height *= 3;
	playerRunningTexture.width *= 3;
	playerAttack1Texture = LoadTexture(ASSETS_PATH"_Attack.png");
	playerAttack1Texture.height *= 3;
	playerAttack1Texture.width *= 3;
	playerJumpTexture = LoadTexture(ASSETS_PATH"_Jump.png");
	playerJumpTexture.height *= 3;
	playerJumpTexture.width *= 3;
	playerFallTexture = LoadTexture(ASSETS_PATH"_Fall.png");
	playerFallTexture.height *= 3;
	playerFallTexture.width *= 3;

	playerIdleRec = {
		0.0f,
		0.0f,
		(float)playerIdleTexture.width / 10.0f,
		(float)playerIdleTexture.height
	};

	playerRunningRec = {
		0.0f,
		0.0f,
		(float)playerRunningTexture.width / 10.0f,
		(float)playerRunningTexture.height
	};

	playerAttack1Rec = {
		0.0f,
		0.0f,
		(float)playerAttack1Texture.width / 4.0f,
		(float)playerAttack1Texture.height
	};

	playerJumpRec = {
		0.0f,
		0.0f,
		(float)playerJumpTexture.width / 3.0f,
		(float)playerJumpTexture.height
	};

	playerFallRec = {
		0.0f,
		0.0f,
		(float)playerFallTexture.width / 3.0f,
		(float)playerFallTexture.height
	};

	position = {
		(float)SCREEN_WIDTH / 2.0f - playerRunningRec.width / 2.0f,
		GROUND_LEVEL - playerRunningRec.height
	};
  }

  void draw() {
	float deltaTime{GetFrameTime()};
	if (direction == LEFT && !attacking) {
	  this->position.x -= 6;
	} else if (direction == RIGHT && !attacking) {
	  this->position.x += 6;
	}

	// add gravity to the object
	if (position.y >= GROUND_LEVEL - playerIdleRec.height) {
	  // on the ground
	  velocity = 0;
	  position.y = GROUND_LEVEL - playerIdleRec.height;
	  jumping = false;
	} else {
	  // falling
	  // GRAVITY is in pixels per second squared
	  velocity += GRAVITY * deltaTime * deltaTime;
	}

	if (IsKeyDown(KEY_SPACE) && !jumping) {
	  // jumping
	  jumping = true;
	  // JUMP_FORCE is in pixels per second
	  velocity += JUMP_FORCE * deltaTime;
	} else if (IsKeyDown(KEY_N) && !attacking) {
	  frame = 0;
	  attacking = true;
	}

	position.y += velocity;

	bool facingRight = lastDirection == RIGHT;

	if (attacking) {
	  bool completed = AnimateTexture(playerAttack1Texture, &playerAttack1Rec, position, 4, facingRight);
	  if (completed) {
		attacking = false;
	  }
	} else if (jumping && velocity < 0) {
	  AnimateTexture(playerJumpTexture, &playerJumpRec, position, 3, facingRight);
	} else if (velocity > 0) {
	  AnimateTexture(playerFallTexture, &playerFallRec, position, 3, facingRight);
	} else if (direction == RIGHT || direction == LEFT) {
	  AnimateTexture(playerRunningTexture, &playerRunningRec, position, 10, facingRight);
	} else {
	  AnimateTexture(playerIdleTexture, &playerIdleRec, position, 10, facingRight);
	}
  }

  [[nodiscard]] float GetHeight() const {
	return playerIdleRec.height;
  }
};