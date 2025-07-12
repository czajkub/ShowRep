#include "include/game.h"
#include "util/lineid.h"
#include "util/statehandlers.h"


#include <QRegularExpression>

void Game::init(QStringList &lines)
{
    initialState_ = InitialState(lines);
    State state;
    initialState_.copyToState(state);
    addTurn(state); // add empty turn: we want to index turns from 1

    for (const auto &line : std::as_const(lines)) {
        QStringList fields = line.split(u'|', Qt::SkipEmptyParts);
        if (fields.size() == 0)
            continue;
        enum lineid linetype = lineEnum(fields[0]);

        switch (linetype) {

        case TURN:
            if (line == "|turn|1") {
                break;
            }
            addTurn(state);
            state.setTurn(fields[1].toInt());
            break;

        case UPKEEP:
            upkeep(state);
            break;

        case SWITCH:
            handleSwitch(state, fields);
            break;

        case MOVE:
            handleMove(state, fields);
            break;

        case DAMAGE:
            handleDamage(state, fields);
            break;

        case HEAL:
            handleDamage(state, fields);
            break;

        case CRIT:
            handleCrit(state, fields);
            break;


        case STATUS: case CANT:
            handleStatus(state, fields);
            break;


        case WIN:
            addTurn(state);
            updateNicks();
            init_ = true;
            return;

        default:
            break;
        }
    }

}





void Game::updateNicks()
{
    State lastState = turn_[turns() - 1];
    QStringList nicknames1;
    QStringList nicknames2;
    std::unordered_map<QString, QString> nicks1;
    std::unordered_map<QString, QString> nicks2;

    for (const auto &[nick, mon] : lastState.mons1()) {
        nicknames1 << nick;
        nicks1[nick] = mon.name();
    }
    for (const auto &[nick, mon] : lastState.mons2()) {
        nicknames2 << nick;
        nicks2[nick] = mon.name();
    }

    for (auto &state : turn_) {
        for (auto &[nick, mon] : nicks1) {
            if (state.mons1().count(nick) == 0) {
                state.player1().setNick(nicks1[nick], nick);
            }
        }
        for (auto &[nick, mon] : nicks2) {
            if (state.mons2().count(nick) == 0) {
                state.player2().setNick(nicks2[nick], nick);
            }
        }
    }


}





const State &Game::operator[](size_t turn) const
{
    if (turn > turn_.size())
        throw std::out_of_range("Wrong turn number");
    return turn_[turn];
}
