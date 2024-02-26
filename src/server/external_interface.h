//
// Created by shecannotsee on 24-2-26.
//

#ifndef EXTERNAL_INTERFACE_H
#define EXTERNAL_INTERFACE_H

namespace she_raft::external_interface {

template <typename value_type>
static value_type get() {
}

template <typename value_type>
static bool set(value_type value) {
  return true;
}

}  // namespace she_raft::external_interface

#endif  // EXTERNAL_INTERFACE_H
