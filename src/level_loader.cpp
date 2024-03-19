#include <string>
#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include "raylib.h"
#include "ground_grass.cpp"

using namespace std;

extern float scale;
extern int groundLevel;

class LevelLoader {
  vector<string> level;
  vector<GroundGrass> ground;
 public:
  LevelLoader(const string &filename) {
	ifstream file(filename);
	string line;
	while (getline(file, line)) {
	  level.push_back(line);
	}
	
	LoadLevel();
  }

  void LoadLevel() {
	for (int i = 0; i < level.size(); i++) {
	  string line = level[i];
	  for (int j = 0; j < line.size(); j++) {
		char c = line[j];
		if (c == '#') {
		  auto g = GroundGrass(j * 24 * 3, i * 24 * 3);
		  ground.push_back(g);
		}
	  }
	}
  }

  void DrawLevel() {
	for (auto &g : ground) {
	  g.Draw();
	}
  }
  
  bool CheckCollision(int px, int py, int pw, int ph) {
	for (auto &g : ground) {
	  if (g.CheckCollision(px, py, pw, ph)) {
		groundLevel = g.y;
		return true;
	  }
	}
	groundLevel = 2000;
	return false;
  }
  
};