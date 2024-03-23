#include "raylib.h"
#include "raymath.h"
#include "config.h"
#include "player.cpp"
#include "level_loader.cpp"

class Game {
 private:
  Player player{};
  LevelLoader loader{ASSETS_PATH"levels/level1.txt"};
  Texture2D background1 = LoadTexture(ASSETS_PATH"background_layer_1.png");
  Texture2D background2 = LoadTexture(ASSETS_PATH"background_layer_2.png");
  Texture2D background3 = LoadTexture(ASSETS_PATH"background_layer_3.png");
  Camera2D camera{};
  float bg1X{};
  float bg2X{};
  float bg3X{};

 public:
  Game() {
	camera.zoom = 1.0f;
	player.position.y = 685;

	camera.offset = {
		static_cast<float>(GetScreenWidth()) / 2.0f - (player.GetTextureWidth() / 2),
		static_cast<float>(GetScreenHeight()) / 2.0f - player.GetTextureHeight() / 2
	};
  }
  void Draw() {
	camera.target = {player.position.x, GetScreenHeight() - GetScreenHeight() * 0.65f};

	if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) {
	  player.direction = RIGHT;
	  player.lastDirection = RIGHT;
	} else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) {
	  player.direction = LEFT;
	  player.lastDirection = LEFT;
	} else { player.direction = STOP; }

	if (player.direction == RIGHT && !player.attacking && !player.blocked && !player.isDead) {
	  bg1X -= 1;
	  bg2X -= 2;
	  bg3X -= 3;

	  if (bg1X <= -background1.width * scale * BG_SCALE) bg1X = 0;
	  if (bg2X <= -background2.width * scale * BG_SCALE) bg2X = 0;
	  if (bg3X <= -background3.width * scale * BG_SCALE) bg3X = 0;
	}

	if (player.direction == LEFT && !player.attacking && !player.blocked && !player.isDead) {
	  bg1X += 1;
	  bg2X += 2;
	  bg3X += 3;

	  if (bg1X >= 0) bg1X = -background1.width * scale * BG_SCALE;
	  if (bg2X >= 0) bg2X = -background2.width * scale * BG_SCALE;
	  if (bg3X >= 0) bg3X = -background3.width * scale * BG_SCALE;
	}

	Vector2 bg1Pos{bg1X, 0};
	Vector2 bg1Pos_2{bg1X + background1.width * scale * BG_SCALE, 0};
	Vector2 bg2Pos{bg2X, 0};
	Vector2 bg2Pos_2{bg2X + background2.width * scale * BG_SCALE, 0};

	Vector2 bg3Pos{bg3X, 0};
	Vector2 bg3Pos_2{bg3X + background3.width * scale * BG_SCALE, 0};

	DrawTextureEx(background1, bg1Pos, 0.0f, scale * BG_SCALE, WHITE);
	DrawTextureEx(background1, bg1Pos_2, 0.0f, scale * BG_SCALE, WHITE);
	DrawTextureEx(background2, bg2Pos, 0.0f, scale * BG_SCALE, WHITE);
	DrawTextureEx(background2, bg2Pos_2, 0.0f, scale * BG_SCALE, WHITE);
	DrawTextureEx(background3, bg3Pos, 0.0f, scale * BG_SCALE, WHITE);
	DrawTextureEx(background3, bg3Pos_2, 0.0f, scale * BG_SCALE, WHITE);

	BeginMode2D(camera);
	{
	  loader.DrawLevel();
	  player.draw();

	  float collision = loader.CheckCollision(player.hitbox, player.upwardsVelocity);
	  if (collision == 0) {
		player.SetOnGround(false);
	  } else {
		player.SetOnGround(true);
		player.position.y = collision - player.GetTextureHeight();
		player.upwardsVelocity = 0;
		player.falling = false;
	  }

	  float sideCollision = loader.CheckSideCollision(player.hitbox, RUN_SPEED + player.upwardsVelocity / 2.0f);
	  if (sideCollision > 0) {
		player.blocked = true;
		if (sideCollision > player.hitbox.x) {
		  player.rightBlocked = true;
		  player.leftBlocked = false;
		} else if (sideCollision < player.hitbox.x + player.GetWidth()) {
		  player.leftBlocked = true;
		  player.rightBlocked = false;
		}
		player.SetXPosition(sideCollision);
	  } else {
		player.blocked = false;
		player.leftBlocked = false;
		player.rightBlocked = false;
	  }

	}
	EndMode2D();
	
	if (player.isDead) {
	  DrawText("You died!", GetScreenWidth() / 2 - MeasureText("You died!", 50) / 2, GetScreenHeight() / 2, 50, RED);
	}
  }
};