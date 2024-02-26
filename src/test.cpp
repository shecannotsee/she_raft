//
// Created by shecannotsee on 24-2-26.
//
#include "test.h"

#include "time/time.h"

void she_raft::test::time_test() {
  for (int i = 0; i < 10; i++) {
    std::cout << she_raft::generate_random_number<int, 150, 300>() << " ";
  }
}