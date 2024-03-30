#ifndef RAYLIB_TEST_SRC_CONFIG_H_
#define RAYLIB_TEST_SRC_CONFIG_H_
#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))
#define SCREEN_WIDTH    (1920)
#define SCREEN_HEIGHT    (1080)

#define WINDOW_TITLE "Raylib game"
#define GRAVITY  (1500)
#define JUMP_FORCE  (-800)
#define BG_SCALE (6.7f)
#define RUN_SPEED (7)


//#define minX  (800.0f)
//#define minY  (0.0f)
//#define maxX  (12800.0f)
//#define maxY  (3000.0f)

//#define ASSETS_PATH "~/source/raylib_game/assets"

//#define LOG

//#define BG_LOG	
//#define GUIDES

#define SHOW_COLLISION_BOXES

#define FPS

#endif //RAYLIB_TEST_SRC_CONFIG_H_