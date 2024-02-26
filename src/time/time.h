//
// Created by shecannotsee on 24-2-26.
//

#ifndef TIME_H
#define TIME_H

#include <atomic>
#include <chrono>
#include <functional>
#include <random>
#include <thread>

namespace she_raft {

template <typename type = int, type min, type max>
static int generate_random_number() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<type> dist(min, max);
  return dist(gen);
}

template <typename func_t = void, typename... args_t>
class time {
 public:
  time(const int milliseconds, func_t&& func, args_t&&... args)
      : duration(milliseconds), function(std::forward<func_t>(func), std::forward<args_t>(args)...), active(true) {
  }

  // 开始计时
  void start() {
    std::thread([this]() {
      std::this_thread::sleep_for(std::chrono::milliseconds(duration));
      if (active) {
        function();
      }
    }).detach();
  }

  // 停止计时
  void stop() {
    active = false;
  }

 private:
  int duration;                    // 时间间隔
  std::function<void()> function;  // 要执行的函数
  std::atomic<bool> active;        // 计时器是否激活
};

}  // namespace she_raft

#endif  // TIME_H
