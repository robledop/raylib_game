#ifndef RAYLIB_GAME_SRC_EVENT_H_
#define RAYLIB_GAME_SRC_EVENT_H_
#include <string>
#include <vector>
#include <functional>

enum EventType{
  ATTACK,
  TAKE_DAMAGE
};

class Event {
 private:
  EventType type;
 public:
  std::vector<std::function<void(int)>> callbacks;
  Event(EventType type) : type{type} {};
  void RegisterCallback(std::function<void(int)> callback);
  void Clear();
};

#endif
