#include "event.h"
void Event::RegisterCallback(std::function<void(int)> callback) {
  callbacks.push_back(callback);
}
