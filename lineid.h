#ifndef LINEID_H
#define LINEID_H

#include <QString>

enum lineid {

    // first few lines of log
    PLAYER,
    POKE,
    RULE,
    GAMETYPE,
    TEAMSIZE,
    GEN,
    TIER,
    START,

    CHAT,
    JOIN,
    LEAVE,

    TURN,
    SWITCH,
    MOVE,

    DAMAGE,
    HEAL,
    CRIT,
    MISS,
    SUPEREFF,
    RESISTED,
    IMMUNE,
    FAINT,

    UNKNOWN,

};

lineid lineEnum(const QString &line);


#endif // LINEID_H
