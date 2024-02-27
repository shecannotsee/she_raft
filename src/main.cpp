//
// Created by shecannotsee on 24-2-26.
//
#include <server/group.h>

#include <iostream>
#include <thread>

#include "test.h"

int main() {
  using namespace she_raft;
  std::cout << "Start unit testing\n";
  test::run_test();
  std::cout << "Unit testing completed\n";

  std::cout << "main\n" << std::endl;
  std::thread server([]() { group<int, 1>::start(); });

  std::thread client([]() {

  });

  server.join();
  client.join();

  return 0;
}
