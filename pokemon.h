#ifndef POKEMON_H
#define POKEMON_H

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


#endif // POKEMON_H
