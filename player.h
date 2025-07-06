#ifndef PLAYER_H
#define PLAYER_H

#include <QStringList>
#include "pokemon.h"

class Player
{
public:
    Player() = default;
    Player(const QString &name, const QString &avatar)
        : name_(name)
        , avatar_(avatar)
    {}

    QString name() const { return name_; }

    void setTeamSize(size_t size) { teamsize_ = size; }
    void addPokemon(const QString &line);

    std::vector<Pokemon> pokes() const { return mons_; }

private:
    QString name_;
    QString avatar_;
    size_t teamsize_ = 6;
    std::vector<Pokemon> mons_;
};

#endif // PLAYER_H
