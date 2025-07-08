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
    /**
     * @brief insert turn into turn_ vector
     * @param current state
     */
    void addTurn(const State &turn) { turn_.push_back(turn); }
    /**
     * @return size of turn_ vector
     */
    int turns() { return turn_.size(); }

    /**
     * change the HP stat in the correct Player object
     * of the pokemon whose HP was changed
     * @brief handles damage dealt to pokemon
     * @param state - current state
     * @param lines - current line of the log
     */
    void handleDamage(State &state, const QStringList &lines);
    /**
     * @brief set the alive_ boolean of correct Pokemon to false
     * @param state - current state
     * @param lines - current line of the log
     */
    void handleFaint(State &state, const QStringList &lines);
    /**
     * If the nickname (set to the pokemon name by default) is different
     * from the nickname by which it is referred to in the log, the name
     * of the pokemon and map key are changed
     *
     * @brief change nickname of Pokemon
     * @param state - current state
     * @param lines - current line of the log
     */
    void handleSwitch(State &state, const QStringList &lines);

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
