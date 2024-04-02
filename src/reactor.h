#ifndef RAYLIB_GAME_SRC_REACTOR_H_
#define RAYLIB_GAME_SRC_REACTOR_H_
#include "event.h"
#include <map>

template <typename T>
class Reactor {
 private:
  std::map<EventType, Event<T>> events;
  
 public:
  void RegisterEvent(EventType type);
  void DispatchEvent(EventType type, T data);
  void AddEventListener(EventType type, std::function<void(T)> callback);
  void Clear();
};

template <typename T>
void Reactor<T>::RegisterEvent(EventType type) {
  events.insert(std::make_pair(type, Event<T>(type)));
}

template<typename T>
void Reactor<T>::AddEventListener(EventType type, std::function<void(T)> callback) {
  events.at(type).RegisterCallback(callback);
}

template <typename T>
void Reactor<T>::DispatchEvent(EventType type, T data) {
  for (auto callback : events.at(type).callbacks) {
	callback(data);
  }
}
template <typename T>
void Reactor<T>::Clear() {
  for(auto &[type, event] : events) {
	event.Clear();
  }
}
#endif
