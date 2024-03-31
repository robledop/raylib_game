#include "reactor.h"

void Reactor::RegisterEvent(EventType type) {
  events.insert(std::make_pair(type, Event(type)));
}
void Reactor::DispatchEvent(EventType type, int data) {
  for (auto callback : events.at(type).callbacks) {
	callback(data);
  }
}
void Reactor::AddEventListener(EventType type, std::function<void(int)> callback) {
  events.at(type).RegisterCallback(callback);
}
void Reactor::Clear() {
  for(auto &[type, event] : events) {
	event.Clear();
  }
}
