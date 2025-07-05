#include "state.h"

enum lineid {

    // first few lines of log
    PLAYER,
    POKE,
    RULE,
    GAMETYPE,
    TEAMSIZE,
    GEN,


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
        enum lineid linetype = lineEnum(fields[1]);
        switch (linetype) {
        case PLAYER:
            fields[2] == "p1" ? player1 = Player(fields[3], fields[4])
                              : player2 = Player(fields[3], fields[4]);
            break;
        case POKE:
            fields[2] == "p1" ? player1.addPokemon(fields[3]) : player2.addPokemon(fields[3]);
            break;
        default:
            break;
        }
    }
}

void Player::addPokemon(const QString &line)
{
    QStringList fields = line.split(u',', Qt::SkipEmptyParts);
    if (fields.size() == 1) {
        mons.emplace_back(fields[0]);
    } else {
        mons.emplace_back(fields[0], fields[1][1]);
    }
    if(mons.size() > 6 || mons.size() > teamsize) {
        // TODO: throw some sort of error message to user !
    }
}
