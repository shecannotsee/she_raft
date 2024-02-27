//
// Created by shecannotsee on 24-2-26.
//

#ifndef BASE_SERVER_H
#define BASE_SERVER_H

#include <atomic>

namespace she_raft::server {

enum class vote : unsigned char {
  _0,
  _1,
};

struct data {
  std::atomic<vote> num{vote::_1};
  std::atomic<int> term{0};  // version
};

}  // namespace she_raft::server

#endif  // BASE_SERVER_H
