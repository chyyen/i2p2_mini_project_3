#include <cstdlib>
#include <utility>
#include <stdio.h>

#include "../state/state.hpp"
#include "./alphabeta.hpp"


/**
 * @brief get a legal action using Minmax
 *
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move
 */
Move ALPHABETA::get_move(State *state, int depth){
    if(!state->legal_actions.size())
        state->get_legal_actions();

    auto actions = state->legal_actions;
    int max_score = -(state->inf);
    int alpha = -(state->inf), beta = state->inf;
    Move next_move = Move(Point(-1, -1), Point(-1, -1));
    for(Move action: actions){
        State *next_state = state->next_state(action);
        int score = alpha_beta(next_state, depth, alpha, beta, false, state->player);
        if(score > max_score) {
            next_move = action;
            max_score = score;
        }
        alpha = max(alpha, score);
        if(alpha > beta)
            break;
    }
    return next_move;
}

std::pair<int, Move> ALPHABETA::get_move2(State *state, int depth){
    if(!state->legal_actions.size())
        state->get_legal_actions();

    auto actions = state->legal_actions;
    int max_score = -(state->inf);
    int alpha = -(state->inf), beta = state->inf;
    Move next_move = Move(Point(-1, -1), Point(-1, -1));
    for(Move action: actions){
        State *next_state = state->next_state(action);
        int score = alpha_beta(next_state, depth, alpha, beta, false, state->player);
        if(score > max_score) {
            next_move = action;
            max_score = score;
        }
        alpha = max(alpha, score);
        if(alpha > beta)
            break;
    }
    return std::make_pair((int)actions.size(), next_move);
}

int ALPHABETA::alpha_beta(State *state, int depth, int alpha, int beta, bool chooseMax, int root_player) {
    /* base case */
    if (state->game_state == WIN) {
        if (state->player == root_player)
            return state->inf;
        else
            return -(state->inf);
    }
    else if (depth == 0){
        if(state->player == root_player)
            return state->evaluate();
        else
            return -(state->evaluate());
    }
    state->get_legal_actions();
    /* */
    auto actions = state->legal_actions;
    if(!chooseMax){
        int min_score = state->inf;
        for(Move action : actions) {
            int cur = alpha_beta(state->next_state(action), depth - 1, alpha, beta, true, root_player);
            min_score = min(min_score, cur);
            beta = min(beta, cur);
            if(beta <= alpha)
                break;
        }
        return min_score;
    }
    else{
        int max_score = -(state->inf);
        for(Move action : actions) {
            int cur = alpha_beta(state->next_state(action), depth - 1, alpha, beta, false, root_player);
            max_score = max(max_score, cur);
            alpha = max(alpha, cur);
            if(alpha >= beta)
                break;
        }
        return max_score;
    }
}

int ALPHABETA::min(int x, int y){
    return x < y ? x : y;
};

int ALPHABETA::max(int x, int y){
    return x > y ? x : y;
};
