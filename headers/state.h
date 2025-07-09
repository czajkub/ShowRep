#ifndef STATE_H
#define STATE_H

#include <QStringList>
#include "player.h"

class State
{
protected:
    Player player1_;
    Player player2_;

    // positive luck - in favour of player1,
    // negative - in favour of player2
    double luckscore_ = 0;

    int currTurn_ = 1;

    // used to determine whether move missed or not
    std::string lastMove_;

    // used to determine whether secondary effect of a move triggered
    bool pendingsecondary_ = false;
    char secondarytype_ = '0';
public:
    State() = default;
    explicit State(QStringList &lines);

    Player& player1() { return player1_; }
    Player& player2() { return player2_; }

    QString p1name() const { return player1_.name(); }
    QString p2name() const { return player2_.name(); }


    void updateLuck(double value) { luckscore_ += value; }
    double luckscore() const { return luckscore_; }


    void setMove(const std::string &move) { lastMove_ = move; }
    void setMove(const QString &move) { lastMove_ = move.toStdString(); }
    const std::string &lastMove() const { return lastMove_; }


    void resetPendingSecondary()
    {
        pendingsecondary_ = false;
        secondarytype_ = '0';
    }
    void setSecondary(const char &type) {
        pendingsecondary_ = true;
        secondarytype_ = type;
    }

    bool pendingSecondary() const { return pendingsecondary_; }
    char secondaryType() const { return secondarytype_; }


    const std::unordered_map<QString, Pokemon>& mons1() const { return player1_.pokes();
    }
    const std::unordered_map<QString, Pokemon>& mons2() const { return player2_.pokes();
    }



    void setPlayer(int num, Player player)
    {
        if (num != 1 && num != 2)
            throw std::out_of_range("Wrong player number");
        num == 1 ? player1_ = player : player2_ = player;
    }

    void setTurn(int turn) { currTurn_ = turn; }
    int turn() { return currTurn_; }
    //double luckscore;

};




class InitialState : public State
{
    std::vector<QString> rules_;
    int gen_ = 9;
    QString gametype_;
    QString tier_;

public:
    InitialState() = default;
    explicit InitialState(QStringList &lines);

    void addRule(const QString &rule) { rules_.push_back(rule); }
    void setGen(int gen) { gen_ = gen; }
    void setGametype(const QString &gtype) { gametype_ = gtype; }
    void setTier(const QString &tier) { tier_ = tier; }

    std::vector<QString> rules() const { return rules_; }
    int gen() const { return gen_; }
    QString gametype() const { return gametype_; }
    QString tier() const { return tier_; }

    /**
     * This needs to happen this way since the corresponding
     * lines of log are deleted from the QStringList during
     * the constrion of this class
     *
     * @brief set the Player objects of passed State
     * @param state which the data is copied to
     */
    void copyToState(State &state);
};


#endif // STATE_H
