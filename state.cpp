#include "state.h"

#include <QRegularExpression>

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

void Player::addPokemon(const QString &line)
{
    QStringList fields = line.split(QRegularExpression(", "), Qt::SkipEmptyParts);
    if (fields.size() == 1) {
        mons_.emplace_back(fields[0]);
    } else {
        mons_.emplace_back(fields[0], fields[1][0]);
    }
    if(mons_.size() > 6 || mons_.size() > teamsize_) {
        // TODO: throw some sort of error message to user !
    }
}
