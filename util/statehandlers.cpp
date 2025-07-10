#include "statehandlers.h"
#include "moves.cpp"

#include <QRegularExpression>

#define SPLITNICK lines[1].split(QRegularExpression(": "))


#define MOVE_WEIGHT 1
#define CRIT_WEIGHT 1.3
#define SECONDARY_WEIGHT 0.5

void upkeep(State &state)
{
    state.resetPendingSecondary();
    state.setMove(QString());
}


void handleDamage(State &state, const QStringList &lines)
{
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
    std::string move = lines[2].toStdString();

    state.setMove(move);

    if (secondary.at(move) != 0 && secondary.at(move) != 1) {
        state.setSecondary(effecttype.at(move));
    }

    // 4 - no miss, 5 - miss
    if (lines.size() == 4) {
        state.updateLuck(moveLuck(state, move, lines, true));
    } else {
        state.updateLuck(moveLuck(state, move, lines, false));
    }
}



void handleCrit(State &state, const QStringList &lines)
{
    QString player = SPLITNICK[0];

    // check whether move always crits
    if (state.pendingSecondary() && state.secondaryType() == 'a') {
        state.resetPendingSecondary();
        return;
    }

    // this needs to check for crit chance raises
    double critchance = 1 / 24;
    double critluck = (1 - critchance) * CRIT_WEIGHT; // 2
    // player2 got a crit on the move
    if (player == "p1a")
        critluck *= -1;

    state.updateLuck(critluck);
}


void handleStatus(State &state, const QStringList &lines)
{
    std::string lastmove = state.lastMove();

    if (state.pendingSecondary() && state.secondaryType() == 's') {
        state.updateLuck(secondaryLuck(state, lastmove, lines, true));
    }
}



double secondaryLuck(State& state, const std::string &move, const QStringList &lines, bool hit)
{
    QString player = SPLITNICK[0];

    double acc = secondary.at(move);

    if (!hit)
        acc = 1 - acc;

    double luckchange = acc * SECONDARY_WEIGHT;

    if (luckchange == 0)
        return luckchange;

    QString log;
    for (const auto &line : lines)
        log += (line + "|");

    state.addLog(QString::number(luckchange) + " " + log);

    if (player == "p1a") {
        return luckchange;
    }
    return -1 * luckchange;
}

double moveLuck(State& state, const std::string& move, const QStringList &lines, bool hit)
{
    QString player = SPLITNICK[0];

    double acc = moves.at(move);

    // move cannot be missed - e.g. protect or whirlwind
    if (acc == 2)
        return 0;

    // check evasion/acc changes
    double actualacc = acc;
    double luckchange;

    if (hit)
        actualacc = 1 - actualacc;

    luckchange = actualacc * MOVE_WEIGHT;

    if (luckchange == 0)
        return luckchange;

    QString log;
    for (const auto &line : lines)
        log += (line + "|");

    state.addLog(QString::number(luckchange) + " " + log);

    if (player == "p1a") {
        return luckchange;
    }
    return -1 * luckchange;
}
