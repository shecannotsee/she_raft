//
// Created by shecannotsee on 24-2-26.
//

#ifndef GROUP_H
#define GROUP_H
#include <variant>

#include "candidate.h"
#include "follow.h"
#include "leader.h"
#include "data.h"

namespace she_raft {

class service {
 public:
  service() = default;

 private:
  server::data data_{};
  std::variant<server::follow, server::candidate, server::leader> server_type_{server::follow()};
};

class group {
 public:
 private:
};

template <typename integer_type = int, integer_type number_of_servers>
static void start() {
  while (1) {
    break;
  }
}

}  // namespace she_raft

#endif  // GROUP_H
