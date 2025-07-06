#include "state.h"

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


    SWITCH,
    MOVE,

    CHAT,
    JOIN,
    LEAVE,

    DAMAGE,
    HEAL,
    CRIT,
    MISS,
    SUPEREFF,
    RESISTED,
    IMMUNE,

    UNKNOWN,

};

lineid lineEnum(const QString &field)
{
    if (field == "player") {
        return PLAYER;
    } else if (field == "poke") {
        return POKE;
    } else if (field == "rule") {
        return RULE;
    } else if (field == "gametype") {
        return GAMETYPE;
    } else if (field == "gen") {
        return GEN;
    } else if (field == "TIER") {
        return TIER;
    } else if (field == "start") {
        return START;
    } else if (field == "switch") {
        return SWITCH;
    } else if (field == "move") {
        return SWITCH;
    } else if (field == "c") {
        return CHAT;
    } else if (field == "j") {
        return JOIN;
    } else if (field == "l") {
        return LEAVE;
    } else if (field == "-damage") {
        return DAMAGE;
    } else if (field == "-heal") {
        return HEAL;
    } else if (field == "-crit") {
        return CRIT;
    } else if (field == "-miss") {
        return MISS;
    } else if (field == "-supereffective") {
        return SUPEREFF;
    } else if (field == "-resisted") {
        return RESISTED;
    } else if (field == "-immune") {
        return IMMUNE;
    } else {
        return UNKNOWN;
    }
}

State::State(const QStringList &lines)
{
    for (const auto &line : lines) {
        QStringList fields = line.split(u'|', Qt::SkipEmptyParts);
        if (fields.size() == 0)
            continue;
        enum lineid linetype = lineEnum(fields[0]);
        switch (linetype) {
        case PLAYER:
            fields[1] == "p1" ? player1 = Player(fields[2], fields[3])
                              : player2 = Player(fields[2], fields[3]);
            break;
        case POKE:
            fields[1] == "p1" ? player1.addPokemon(fields[2]) : player2.addPokemon(fields[2]);
            break;
        default:
            break;
        }
    }
}

InitialState initialState(const QStringList &lines)
{
    InitialState state;
    for (const auto &line : lines) {
        QStringList fields = line.split(u'|', Qt::SkipEmptyParts);
        if (fields.size() == 0)
            continue;
        enum lineid linetype = lineEnum(fields[0]);
        switch (linetype) {
        case PLAYER:
            fields[1] == "p1" ? state.player1 = Player(fields[2], fields[3])
                              : state.player2 = Player(fields[2], fields[3]);
            break;
        case POKE:
            fields[1] == "p1" ? state.player1.addPokemon(fields[2])
                              : state.player2.addPokemon(fields[2]);
            break;
        case TEAMSIZE:
            fields[1] == "p1" ? state.player1.setTeamSize(fields[2].toULongLong())
                              : state.player2.setTeamSize(fields[2].toULongLong());
        case GEN:
            state.setGen(fields[1].toInt());
            break;
        case RULE:
            state.addRule(fields[1]);
            break;
        case GAMETYPE:
            state.setGametype(fields[1]);
            break;
        case TIER:
            state.setTier(fields[1]);
            break;
        case START:
            return state;
        default:
            break;
        }
    }
    // this should be an error actually - no start means the replay is bad
    return InitialState();
}

