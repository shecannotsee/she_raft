//
// Created by shecannotsee on 24-2-26.
//

#ifndef FOLLOW_H
#define FOLLOW_H
#include "data.h"

namespace she_raft::server {

enum class follow_state : unsigned char {
  revolution,
  following_leader,
  election,
};

class follow {
 public:
  follow() = default;

  auto get_state() const -> follow_state {
    return state_;
  }

 private:
  follow_state state_{follow_state::revolution};
};

}  // namespace she_raft::server

#endif  // FOLLOW_H
