#ifndef RAYLIB_GAME_SRC_REACTOR_H_
#define RAYLIB_GAME_SRC_REACTOR_H_
#include "event.h"
#include <map>

class Reactor {
 private:
  std::map<EventType, Event> events;
  
 public:
  void RegisterEvent(EventType type);
  void DispatchEvent(EventType type, int data);
  void AddEventListener(EventType type, std::function<void(int)> callback);
  void Clear();
};

#endif
