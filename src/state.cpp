#include "headers/state.h"
#include "util/lineid.h"


State::State(QStringList &lines)
{
    for (const auto &line : lines) {
        QStringList fields = line.split(u'|', Qt::SkipEmptyParts);
        if (fields.size() == 0)
            continue;
        enum lineid linetype = lineEnum(fields[0]);
        switch (linetype) {
        case PLAYER:
            fields[1] == "p1" ? player1_ = Player(fields[2], fields[3])
                              : player2_ = Player(fields[2], fields[3]);
            break;
        case POKE:
            fields[1] == "p1" ? player1_.addPokemon(fields[2]) : player2_.addPokemon(fields[2]);
            break;
        default:
            break;
        }
    }
}


InitialState::InitialState(QStringList& lines) {
    for (const auto &line : lines) {
        QStringList fields = line.split(u'|', Qt::SkipEmptyParts);
        if (fields.size() == 0)
            continue;
        enum lineid linetype = lineEnum(fields[0]);
        switch (linetype) {
        case PLAYER:
            fields[1] == "p1" ? setPlayer(1, Player(fields[2], fields[3]))
                              : setPlayer(2, Player(fields[2], fields[3]));
            break;
        case POKE:
            fields[1] == "p1" ? player1().addPokemon(fields[2])
                              : player2().addPokemon(fields[2]);
            break;
        case TEAMSIZE:
            fields[1] == "p1" ? player1().setTeamSize(fields[2].toULongLong())
                              : player2().setTeamSize(fields[2].toULongLong());
            break;
        case GEN:
            setGen(fields[1].toInt());
            break;
        case RULE:
            addRule(fields[1]);
            break;
        case GAMETYPE:
            setGametype(fields[1]);
            break;
        case TIER:
            setTier(fields[1]);
            break;
        case START:
            lines.remove(0, lines.indexOf(line));
            return;
        default:
            break;
        }
    }

}

void InitialState::copyToState(State &state)
{
    state.player1() = player1();
    state.player2() = player2();
    state.setTurn(1);
}

QString State::dequeueMove()
{
    pending_ = false;
    QString move = pendingMove_;
    pendingMove_ = QString();
    return move;
}
