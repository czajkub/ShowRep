#include "statehandlers.h"
#include "moves.cpp"

#include <QRegularExpression>

#define SPLITNICK lines[1].split(QRegularExpression(": "))


#define MOVE_WEIGHT 1
#define CRIT_WEIGHT 2


void handleDamage(State &state, const QStringList &lines)
{
    double luckchange = resolveMove(state, lines);
    state.updateLuck(luckchange);

    QStringList pokemon = SPLITNICK;
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
    int maxhp = lines[2].split(u'/')[1].toInt();
    if (player == "p1a") {
        state.player1().setHp(nick, newhp, maxhp);
    } else {
        state.player2().setHp(nick, newhp, maxhp);
    }
}

void handleFaint(State &state, const QStringList &lines)
{
    QStringList pokemon = SPLITNICK;
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
    QStringList switched = SPLITNICK;
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

void handleMove(State &state, const QStringList &lines)
{
    QString move = lines[2];

    state.enqueueMove(move);
}



void handleCrit(State &state, const QStringList &lines)
{
    double luckchange = resolveMove(state, lines);

    QString player = SPLITNICK[0];

    double critchance = 1 / 24;
    double critluck = (1 - critchance) * CRIT_WEIGHT;
    // player2 got a crit on the move
    if (player == "p1a")
        critluck *= -1;

    luckchange += critluck;
    state.updateLuck(luckchange);
}


void handleMiss(State &state, const QStringList &lines)
{
    // we multiply by -1 since the miss applies to the other player
    double luckchange = resolveMove(state, lines) * -1;

    state.updateLuck(luckchange);
}


double resolveMove(State &state, const QStringList &lines)
{
    if (!state.moveIsPending())
        return 0;

    QString player = SPLITNICK[0];

    std::string move = state.dequeueMove().toStdString();


    double acc = moves.at(move);

    // move cannot be missed - e.g. protect or whirlwind
    if (acc == 2)
        return 0;

    // add some handling of evasion and accuracy stats at this stage !!!

    double complement = 1 - acc;

    if (complement == 0)
        return 0;

    if (player == "p2a")
        complement *= -1;

    double luckchange = complement * MOVE_WEIGHT; // 1

    return luckchange;
}
