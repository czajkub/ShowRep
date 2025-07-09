#ifndef POKEMON_H
#define POKEMON_H

#include <QStringList>

class Pokemon
{
public:
    Pokemon() = default;
    explicit Pokemon(QString name, QChar gender)
        : name_(name),
        nickname_(name),
        gender_(gender),
        hp_(100),
        alive_(true)
    {}
    explicit Pokemon(QString name)
        : name_(name),
        nickname_(name),
        gender_('U'),
        hp_(100),
        alive_(true)
    {}

    void setNick(QString nick) { nickname_ = nick; }
    /**
     * @brief returns a QString in the following format: name (nickname)
     */
    QString printable() const {
        return (nickname_ == name_) ? name_ : ( name_ + " (" + nickname_ + ")" );
    }

    QString name() const { return name_; }
    QString nickname() const { return nickname_; }

    void setHp(int hp) { hp_ = hp; }
    QString hp() const { return (QString::number(hp_) + "/100"); }

    void fainted() { alive_ = false; }
    bool isalive() const { return alive_; }

private:
    QString name_;
    QString nickname_;
    QChar gender_;
    int hp_;
    bool alive_ = true;
};


#endif // POKEMON_H
