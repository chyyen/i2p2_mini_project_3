#pragma once
#include "../state/state.hpp"
#include <utility>


/**
 * @brief Policy class for MinMax,
 * your policy class should have get_move method
 */
class ALPHABETA{
public:
    static Move get_move(State *state, int depth);
    static std::pair<int, Move> get_move2(State *state, int depth);
    static int alpha_beta(State *state, int depth, int alpha, int beta, bool chooseMax, int root_player);
    static int min(int x, int y);
    static int max(int x, int y);
};
