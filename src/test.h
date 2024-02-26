//
// Created by shecannotsee on 24-2-26.
//

#ifndef TEST_H
#define TEST_H

#include <iostream>

namespace she_raft::test {

void time_test();

static void run_test() {
  time_test();
  std::cout << std::endl;
}

}  // namespace she_raft::test

#endif  // TEST_H
