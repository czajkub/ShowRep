#ifndef GAME_H
#define GAME_H

#include "state.h"

class Game
{
    std::vector<State> turn_;
    InitialState initialState_;

    bool init_ = false;

public:
    /**
     * @brief Load game state from lines of log
     * @param QStringList consisting of separate lines of the log
     */
    void init(QStringList &lines);
    /**
     * @brief insert turn into turn_ vector
     * @param current state
     */
    void addTurn(const State &turn) { turn_.push_back(turn); }
    /**
     * @return size of turn_ vector
     */
    int turns() const { return turn_.size(); }

    bool initialised() const { return init_; }

    const std::vector<State> &game() const { return turn_; }


    /**
     * collect nicknames from the last state, go backwards in the turn_ vector
     * and set the correct nicknames so they can display correctly in table
     *
     * @brief set correct nickname for every pokemon in every turn (State)
     */
    void updateNicks();

    const State &operator[](size_t turn) const;
};


#endif // GAME_H
