#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for MinMax,
 * your policy class should have get_move method
 */
class MinMax{
public:
    static Move get_move(State *state, int depth);
    static int minmax(State *state, int depth, bool chooseMax);
    static int min(int x, int y);
    static int max(int x, int y);
};
