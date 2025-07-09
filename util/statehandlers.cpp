#include "statehandlers.h"

#include <QRegularExpression>

void handleDamage(State &state, const QStringList &lines)
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

void handleFaint(State &state, const QStringList &lines)
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

void handleSwitch(State &state, const QStringList &lines)
{
    QStringList switched = lines[1].split(QRegularExpression(": "));
    QString player = switched[0];
    QString nick = switched[1];
    QStringList oldPokemon = lines[2].split(QRegularExpression(", "), Qt::SkipEmptyParts);
    QString oldnick = oldPokemon[0];

    if (player == "p1a") {
        state.player1().setNick(oldnick, nick);
    } else {
        state.player2().setNick(oldnick, nick);
    }
}
