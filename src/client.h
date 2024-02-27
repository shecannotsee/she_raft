//
// Created by shecannotsee on 24-2-27.
//

#ifndef CLIENT_H
#define CLIENT_H
#include <memory>

#include "server/external_interface.h"

namespace she_raft {

template <typename value_type>
class client {
 public:
  client()  = default;
  ~client() = default;

 private:
  std::unique_ptr<value_type> temp = nullptr;

 public:
  bool pass_to_server(value_type value) {
    if (external_interface::set<value_type>(value)) {
      return true;
    } else {
      temp = value;
      return false;
    }
  }
};

}  // namespace she_raft

#endif  // CLIENT_H
