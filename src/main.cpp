//
// Created by shecannotsee on 24-2-26.
//
#include <server/group.h>

#include <iostream>

#include "test.h"

int main() {
  using namespace she_raft;
  std::cout << "Start unit testing\n";
  test::run_test();
  std::cout << "Unit testing completed\n";

  std::cout << "main\n" << std::endl;

  return 0;
}
