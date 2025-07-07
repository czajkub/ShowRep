#include "game.h"
#include "lineid.h"

#include <QRegularExpression>

void Game::init(QStringList &lines)
{
    initialState_ = InitialState(lines);
    State state;
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
        case PLAYER:
            fields[1] == "p1" ? state.setPlayer(1, Player(fields[2], fields[3]))
                              : state.setPlayer(2, Player(fields[2], fields[3]));
            break;
        case POKE:
            fields[1] == "p1" ? state.player1().addPokemon(fields[2])
                              : state.player2().addPokemon(fields[2]);
            break;
        case DAMAGE:
            handleDamage(state, fields);
            break;
        case FAINT:
            handleFaint(state, fields);
            break;
        default:
            break;
        }
    }
}

void Game::handleDamage(State &state, const QStringList &lines)
{
    QStringList pokemon = lines[1].split(QRegularExpression(": "));
    QString player = pokemon[0];
    QString nick = pokemon[1];
    // looks different for faint: |-damage|p1a: Earfquake|0 fnt
    if (lines[2] == "0 fnt") {
        if (player == "p1a") {
            state.player1().setHp(nick, 0);
            state.player1().setFaint(nick);
        } else {
            state.player2().setHp(nick, 0);
            state.player2().setFaint(nick);
        }
        return;
    }

    int newhp = lines[2].split(u'/')[0].toInt(); // eg. 18/100
    if (player == "p1a") {
        state.player1().setHp(nick, newhp);
    } else {
        state.player2().setHp(nick, newhp);
    }
}

void Game::handleFaint(State &state, const QStringList &lines)
{
    QStringList pokemon = lines[1].split(QRegularExpression(": "));
    QString player = pokemon[0];
    QString nick = pokemon[1];
    if (player == "p1a") {
        state.player1().setHp(nick, 0);
        state.player1().setFaint(nick);
    } else {
        state.player2().setHp(nick, 0);
        state.player2().setFaint(nick);
    }
}

const State &Game::operator[](size_t turn) const
{
    if (turn > turn_.size())
        throw std::out_of_range("Wrong turn number");
    return turn_[turn];
}
