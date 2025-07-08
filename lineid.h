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

    // chat messages: not handled ATP
    CHAT,
    JOIN,
    LEAVE,

    // adds turn to game, moves turn number
    TURN,

    // switches can change nicknames
    // damage changes a mon's hp stat
    SWITCH,
    DAMAGE,

    // this is gonna impact the luck score
    MOVE,
    HEAL,
    CRIT,
    MISS,
    FAINT,

    // not handled
    SUPEREFF,
    RESISTED,
    IMMUNE,

    // adds last turn, updates nicks, finishes parsing
    WIN,

    // some lines arent handled yet
    UNKNOWN,

};

/**
 * @brief function converting QString to an enum value to handle a switch statement
 * @param first part of line in log, e.g. turn in |turn|1
 * @return enum value of line
 */
lineid lineEnum(const QString &line);


#endif // LINEID_H
