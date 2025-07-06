#ifndef STATE_H
#define STATE_H

#include <QStringList>
#include "player.h"

class State
{
public:
    State(const QStringList& lines);

    Player player1;
    Player player2;

    //double luckscore;

    //std::vector<Rule> rules;
    //int gen;
    //QString gametype;
    //QString tier;


};

class Game
{
    std::vector<State> turn;
    State initialState;
public:

};



#endif // STATE_H
