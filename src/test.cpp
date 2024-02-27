//
// Created by shecannotsee on 24-2-26.
//
#include "test.h"

#include "time/time.h"

void she_raft::test::random_test() {
  for (int i = 0; i < 10; i++) {
    std::cout << she_raft::generate_random_number<int, 150, 300>() << " ";
  }
  std::cout << std::endl;
}

void she_raft::test::time_test() {
  time lalala;
  lalala.start(1000);
  for (int i = 0; i < 10; ++i) {
    std::cout << i+1 << ":";
    if (lalala.get_result() == true) {
      std::cout << "Timing complated!\n";
    } else {
      std::cout << "Timing not complated!\n";
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }
  std::cout << "other get\n";
  lalala.start(1000);
  std::this_thread::sleep_for(std::chrono::milliseconds(1500));

  if (lalala.get_result() == true) {
    std::cout << "Timing complated!\n";
  } else {
    std::cout << "Timing not complated!\n";
  }
}
