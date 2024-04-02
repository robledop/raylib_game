#ifndef RAYLIB_GAME_SRC_UTILS_WHERE_H_
#define RAYLIB_GAME_SRC_UTILS_WHERE_H_
#include <vector>
#include <functional>

template<typename T>
std::vector<T> where(const std::vector<T> &inVec, std::function<bool(const T &)> predicate) {
  std::vector<T> result;
  copy_if(inVec.begin(), inVec.end(), back_inserter(result), predicate);
  return result;
}

#endif
