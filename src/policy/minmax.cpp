#include <cstdlib>

#include "../state/state.hpp"
#include "./minmax.hpp"


/**
 * @brief get a legal action using Minmax
 *
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move
 */
Move MinMax::get_move(State *state, int depth){
    if(!state->legal_actions.size())
        state->get_legal_actions();

    auto actions = state->legal_actions;
    int max_score = -(state->inf);
    Move next_move = Move(Point(-1, -1), Point(-1, -1));
    for(Move action: actions){
        State *next_state = state->next_state(action);
        int score = minmax(next_state, depth, false);
        if(score > max_score) {
            next_move = action;
            max_score = score;
        }
    }
    return next_move;
}

int MinMax::minmax(State *state, int depth, bool chooseMax) {
    if(state->game_state == WIN)
        return state->inf;
    else if(depth == 0)
        return state->evaluate();
    if(!state->legal_actions.size())
        state->get_legal_actions();
    if(!state->legal_actions.size())
        return state->evaluate();
    auto actions = state->legal_actions;
    if(!chooseMax){
        int min_score = state->inf;
        for(Move action : actions)
            min_score = min(min_score, minmax(state->next_state(action), depth - 1, true));
        return min_score;
    }
    else{
        int max_score = -(state->inf);
        for(Move action : actions)
            max_score = max(max_score, minmax(state->next_state(action), depth - 1, false));
        return max_score;
    }
}

int MinMax::min(int x, int y){
    return x < y ? x : y;
};

int MinMax::max(int x, int y){
    return x > y ? x : y;
};
