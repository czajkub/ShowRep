#ifndef STATE_H
#define STATE_H

#include <QStringList>
#include "player.h"

class State
{
public:
    State() = default;
    State(const QStringList& lines);


    Player player1;
    Player player2;

    //double luckscore;


};

class InitialState : public State
{
    std::vector<QString> rules_;
    int gen_;
    QString gametype_;
    QString tier_;

public:
    void addRule(const QString &rule) { rules_.push_back(rule); }
    void setGen(int gen) { gen_ = gen; }
    void setGametype(const QString &gtype) { gametype_ = gtype; }
    void setTier(const QString &tier) { tier_ = tier; }

    std::vector<QString> rules() const { return rules_; }
    int gen() { return gen_; }
    QString gametype() { return gametype_; }
    QString tier() { return tier_; }

};

#endif // STATE_H
