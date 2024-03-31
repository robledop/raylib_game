#include "event.h"
void Event::RegisterCallback(std::function<void(int)> callback) {
  callbacks.push_back(callback);
}

void Event::Clear() {
  callbacks.clear();
}
