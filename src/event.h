#ifndef RAYLIB_GAME_SRC_EVENT_H_
#define RAYLIB_GAME_SRC_EVENT_H_
#include <string>
#include <vector>
#include <functional>

enum EventType {
  ATTACK,
  TAKE_DAMAGE,
  ENEMY_DEATH,
};

template<typename T>
class Event {
 private:
  EventType type;
 public:
  std::vector<std::function<void(T)>> callbacks;
  Event(EventType type) : type{type} {};
  void RegisterCallback(std::function<void(T)> callback);
  void Clear();
};

template<typename T>
void Event<T>::RegisterCallback(std::function<void(T)> callback) {
  callbacks.push_back(callback);
}
template<typename T>
void Event<T>::Clear() {
  callbacks.clear();
}
#endif
