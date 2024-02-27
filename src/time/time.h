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

enum class timer_state : unsigned char {
  idle,
  timing,
  timing_completed,
};

class time {
 public:
  time() = default;

  template <typename integer_type = int>
  void start(integer_type milliseconds) {
    std::thread timer([&,milliseconds]() {
      timer_state_ = timer_state::timing;
      printf("zzz:%d\n", milliseconds);
      std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
      complete_    = true;
      timer_state_ = timer_state::timing_completed;
      printf("timing over\n");
    });
    timer.detach();
  }

  bool get_result() {
    if (complete_)
      printf("complete == true ");
    else
      printf("complete == false ");
    if (timer_state_ == timer_state::timing)
      printf("timer_state_ == timer_state::timing ");
    else if (timer_state_ == timer_state::timing_completed)
      printf("timer_state_ == timer_state::timing_completed ");
    else
      printf("timer_state_ == timer_state::idle ");
    printf("");
    if (complete_ == true && timer_state_ == timer_state::timing_completed) {
      timer_state_ = timer_state::idle;
      complete_    = false;
      return true;
    } else {
      return false;
    }
  }

 private:
  std::atomic<bool> complete_{false};
  std::atomic<timer_state> timer_state_{timer_state::idle};
};

}  // namespace she_raft

#endif  // TIME_H
