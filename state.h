#ifndef STATE_H
#define STATE_H

#include <QStringList>

class Pokemon
{
public:
    explicit Pokemon(QString name, QChar gender)
        : name_(name)
        , gender_(gender)
    {}
    explicit Pokemon(QString name)
        : name_(name)
        , gender_('U')
    {}

    void setNick(QString nick) { nickname_ = nick; }
    QString printable() const {
        return (nickname_ == QString()) ? name_ : ( name_ + " (" + nickname_ + ")" );
    }

private:
    QString name_;
    QString nickname_;
    QChar gender_;
};

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
