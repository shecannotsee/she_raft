//
// Created by shecannotsee on 24-2-26.
//

#ifndef CANDIDATE_H
#define CANDIDATE_H
#include <atomic>

namespace she_raft::server {

enum class candidate_state : unsigned char {
  becoming_leader,
  calculalating_votes,
  becoming_follow,
};

class candidate {
 public:
  candidate() = default;

  auto get_state() const -> candidate_state {
    return state_;
  }

  template <typename integer_type = int>
  void check_the_number_of_votes(integer_type total_votes) {
    int has_votes = has_votes_;
    if (has_votes + has_votes > total_votes) {
      state_ = candidate_state::becoming_leader;
    }
  }

  template <typename integer_type = int>
  void leadership_has_been_produced() {
    state_ = candidate_state::becoming_follow;
  }

 private:
  candidate_state state_{candidate_state::calculalating_votes};
  std::atomic<int> has_votes_{0};
};

}  // namespace she_raft::server

#endif  // CANDIDATE_H
