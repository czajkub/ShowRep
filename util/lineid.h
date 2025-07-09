#ifndef LINEID_H
#define LINEID_H

#include <QString>

enum lineid {

    // first few lines of log
    // only updated in initialState, then discarded
    PLAYER,
    POKE,
    RULE,
    GAMETYPE,
    TEAMSIZE,
    GEN,
    TIER,
    START,

    // upkeep updates some state values, like pending secondary effects
    // turn adds turn to game, moves turn number
    UPKEEP,
    TURN,


    // switches can change nicknames
    // damage changes a mon's hp stat
    // dragging (e.g. via red card) also count as a switch
    SWITCH,


    // damage handling
    DAMAGE,
    HEAL,


    // this is gonna impact the luck score
    MOVE,
    CRIT,


    // associated with secondary effects of moves
    CANT,
    STATUS,


    // not handled
    SUPEREFF,
    RESISTED,
    IMMUNE,
    FAINT,
    MISS,


    // chat messages: not handled ATP
    CHAT,
    JOIN,
    LEAVE,


    // adds last turn, updates nicks, finishes parsing
    WIN,


    // some lines arent handled yet
    UNKNOWN,

};

/**
 * @brief function converting QString to an enum value to handle a switch statement
 * @param first part of line in log, e.g. "turn" in "|turn|1"
 * @return enum value of line
 */
lineid lineEnum(const QString &line);


#endif // LINEID_H
