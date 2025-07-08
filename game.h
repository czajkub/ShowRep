#ifndef GAME_H
#define GAME_H

#include "state.h"

class Game
{
    std::vector<State> turn_;
    InitialState initialState_;

public:
    /**
     * @brief Load game state from lines of log
     * @param QStringList consisting of separate lines of the log
     */
    void init(QStringList &lines);
    void addTurn(const State &turn) { turn_.push_back(turn); }
    int turns() { return turn_.size(); }

    void handleDamage(State &state, const QStringList &lines);
    void handleFaint(State &state, const QStringList &lines);
    void handleSwitch(State &state, const QStringList &lines);

    void updateNicks();

    const State &operator[](size_t turn) const;
};


#endif // GAME_H
