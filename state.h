#ifndef STATE_H
#define STATE_H

#include <QStringList>

class Pokemon
{
public:
    explicit Pokemon(QString name, QChar gender)
        : name(name)
        , gender(gender)
    {}
    explicit Pokemon(QString name)
        : name(name)
        , gender('U')
    {}

    void setNick(QString nick) { nickname = nick; }
    QString printable() const { return (name + '(' + nickname + ')'); }

private:
    QString name;
    QString nickname;
    QChar gender;
};

class Player
{
public:
    Player() = default;
    Player(const QString &name, const QString &avatar)
        : name(name)
        , avatar(avatar)
    {}

    void setTeamSize(size_t size) { teamsize = size; }
    void addPokemon(const QString &line);

    std::vector<Pokemon> pokes() const { return mons; }

private:
    QString name;
    QString avatar;
    size_t teamsize = 6;
    std::vector<Pokemon> mons;
};


class State
{
public:
    State(const QStringList& lines);

    Player player1;
    Player player2;

    //std::vector<Rule> rules;
    //int gen;
    //QString gametype;
    //QString tier;


};


#endif // STATE_H
