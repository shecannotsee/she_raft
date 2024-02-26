//
// Created by shecannotsee on 24-2-26.
//

#ifndef FOLLOW_H
#define FOLLOW_H
#include "state.h"

namespace she_raft::server {

class follow {
 public:
  follow() = default;

  void vote_for();

 private:
  state s_;
};

}  // namespace she_raft::server

#endif  // FOLLOW_H
