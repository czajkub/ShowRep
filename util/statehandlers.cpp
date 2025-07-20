#include "statehandlers.h"
#include "moves.cpp"
#include "../include/pokemon.h"

#include <QRegularExpression>

#define SPLITNICK lines[1].split(QRegularExpression(": "))


#define MOVE_WEIGHT 1
#define CRIT_WEIGHT 1.3
#define SECONDARY_WEIGHT 0.5

void upkeep(State &state)
{
    if(state.pendingSecondary()) {
        Luck luck = secondaryLuck(state, false);
        state.resetPendingSecondary();
        if (luck.log != "")
            state.addLog(luck.log);
        state.updateLuck(luck.luck);
    }
    state.resetPendingSecondary();
    state.setMove(QString());
    state.player1().updateStatuses();
    state.player2().updateStatuses();

}



void handleDamage(State &state, const QStringList &lines)
{
    if (lines.size() < 3) {
        std::string error = "wrong damage line format on line " + std::to_string(state.turn());
        throw std::invalid_argument(error);
    }

    QStringList pokemon = SPLITNICK;
    QString player = pokemon[0];
    QString nick = pokemon[1];
    // looks different for faint: |-damage|p1a: Earfquake|0 fnt
    if (lines[2] == "0 fnt") {
        if (player == "p1a") {
            state.player1().setHp(nick, 0);
        } else if (player == "p2a") {
            state.player2().setHp(nick, 0);
        } else {
            std::string error = "wrong player name on line " + std::to_string(state.turn());
            throw std::invalid_argument(error);
        }
        return;
    }
    QString hp = lines[2].split(u' ')[0];

    int newhp = hp.split(u'/')[0].toInt(); // eg. 18/100
    int maxhp = hp.split(u'/')[1].toInt();

    if(newhp < 0 || maxhp < 0){
        std::string error = "negative hp or maxhp on line " + std::to_string(state.turn());
        throw std::invalid_argument(error);
    }


    if (newhp > maxhp){
        std::string error = "hp larger than maxhp on line " + std::to_string(state.turn());
        throw std::invalid_argument(error);
    }

    if (player == "p1a") {
        state.player1().setHp(nick, newhp, maxhp);
    } else {
        state.player2().setHp(nick, newhp, maxhp);
    }
}


void handleSwitch(State &state, const QStringList &lines)
{
    if (lines.size() != 4 && lines.size() != 5) {
        std::string error = "wrong switch line format on line " + std::to_string(state.turn());
        throw std::invalid_argument(error);
    }

    QStringList switched = SPLITNICK;
    QString player = switched[0];
    QString nick = switched[1];
    QStringList oldPokemon = lines[2].split(QRegularExpression(", "), Qt::SkipEmptyParts);
    QString oldnick = oldPokemon[0];

    if (player == "p1a") {
        state.player1().setNick(oldnick, nick);
    } else if (player == "p2a") {
        state.player2().setNick(oldnick, nick);
    } else {
        std::string error = "wrong player name on line " + std::to_string(state.turn());
        throw std::invalid_argument(error);
    }
}

void handleMove(State &state, const QStringList &lines)
{
    if (lines.size() != 4 && lines.size() != 5) {
        std::string error = "wrong move line format on line " + std::to_string(state.turn());
        throw std::invalid_argument(error);
    }

    upkeep(state);

    std::string move = lines[2].toStdString();

    state.setMove(move);

    QString player = SPLITNICK[0];

    if (secondary.at(move) != 0 && secondary.at(move) != 1) {
        state.setSecondary(player);
    }

    // 4 - no miss, 5 - miss only if last part is [miss]
    if (lines.size() == 4 && lines[3] != "[still]") {
        Luck luck = moveLuck(state, lines, true);
        if(luck.log != "") state.addLog(luck.log);
        state.updateLuck(luck.luck);
    }
    else if(lines.size() == 5 && lines[4]=="[miss]") {
        Luck luck = moveLuck(state, lines, false);
        if(luck.log != "") state.addLog(luck.log);
        state.updateLuck(luck.luck);
    }
}



void handleCrit(State &state, const QStringList &lines)
{
    QString player = SPLITNICK[0];

    const std::string lastmove = state.lastMove();

    // check whether move always crits
    if (critmoves.count(lastmove) == 1){
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
    if (lines.size() < 3) {
        std::string error = "wrong move line format on line " + std::to_string(state.turn());
        throw std::invalid_argument(error);
    }

    QStringList pokemon = SPLITNICK;

    QString player = pokemon[0];
    QString nick = pokemon[1];

    QString stat = lines[2];
    status type;

    if (stat == "brn") {
        type = BURN;
    } else if (stat == "par") {
        type = PARALYSIS;
    } else if (stat == "frz") {
        type = FREEZE;
    } else if (stat == "psn") {
        type = POISON;
    } else if (stat == "tox") {
        type = TOXIC;
    } else if (stat == "slp") {
        type = SLEEP;
    }

    if (player == "p1a") {
        state.player1().setStatus(nick, type);
    }
    else if (player == "p2a") {
        state.player2().setStatus(nick, type);
    }
    else {
        std::string error = "wrong player name on line " + std::to_string(state.turn());
        throw std::invalid_argument(error);
    }

    if (!state.pendingSecondary())
        return;


    Luck luck = secondaryLuck(state, lines, true);
    state.resetPendingSecondary();
    if (luck.log != "")
        state.addLog(luck.log);
    state.updateLuck(luck.luck);

}

Luck secondaryLuck(const State &state, bool hit)
{
    QString player = state.pendingSecondaryPlayer();
    std::string lastmove = state.lastMove();

    double acc = secondary.at(lastmove);

    if (!hit)
        acc = 1 - acc;

    double luckchange = acc * SECONDARY_WEIGHT;

    if (luckchange == 0)
        return Luck{0, ""};

    Luck luck;

    if (player == "p1a") {
        luck.luck = luckchange;
    } else if (player == "p2a") {
        luck.luck = -1 * luckchange;
    } else
        throw std::invalid_argument("wrong player name");

    QString log;
    player == "p1a" ? log += state.p1name() : log += state.p2name();
    log += " Missed secondary effect of  "
           + QString::fromStdString(lastmove);

    luck.log = QString::number(luckchange) + ": " + log;

    return luck;
}


Luck secondaryLuck(const State& state, const QStringList &lines, bool hit)
{
    if(lines.size() < 3) {
        std::string error = "wrong move line format on line " + std::to_string(state.turn());
        throw std::invalid_argument(error);
    }

    if(lines.size() == 4 && lines[3].startsWith("[from]")) {
        return Luck{0, ""};
    }

    if(!state.pendingSecondary()) {
        return Luck{0, ""};
    }

    QString player = SPLITNICK[0];

    std::string lastmove = state.lastMove();

    double acc = secondary.at(lastmove);

    if (!hit)
        acc = 1 - acc;

    double luckchange = acc * SECONDARY_WEIGHT;

    if (luckchange == 0)
        return Luck{0, ""};

    Luck luck;

    if (player == "p1a") {
        luck.luck = luckchange;
    } else if (player == "p2a") {
        luck.luck = -1 * luckchange;
    } else
        throw std::invalid_argument("wrong player name");

    QString log;
    log += player == "p1a" ? state.p1name() : state.p2name();
    log += hit ? " hit" : " missed";
    log += " secondary effect";

    luck.log = QString::number(luckchange) + ": " + log;

    return luck;
}

Luck moveLuck(const State& state, const QStringList &lines, bool hit)
{
    QString player = SPLITNICK[0];
    QString pokemon = SPLITNICK[1];

    std::string move = lines[2].toStdString();


    double acc = moves.at(move);

    // move cannot be missed - e.g. protect or whirlwind
    if (acc == 2)
        return Luck{0,""};

    // check evasion/acc changes
    double actualacc = acc;
    double luckchange;

    if (hit)
        actualacc = 1 - actualacc;

    luckchange = actualacc * MOVE_WEIGHT;

    if (luckchange == 0)
        return Luck{0,""};


    Luck luck;

    if (player == "p1a") {
        luck.luck = luckchange;
    } else if (player == "p2a") {
        luck.luck = -1 * luckchange;
    } else
        throw std::invalid_argument("wrong player name");


    QString log;
    log += player == "p1a" ? state.p1name() : state.p2name();
    log += "'s " + pokemon;
    log += hit ? " hit " : " missed ";
    log += QString::fromStdString(move);

    luck.log = QString::number(luckchange) + ": " + log;

    return luck;
}
