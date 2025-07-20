#ifndef POKEMON_H
#define POKEMON_H

#include <QStringList>

enum status { HEALTHY, BURN, PARALYSIS, FREEZE, POISON, TOXIC, SLEEP, CONFUSION };

struct Status
{
    status type;
    int length;
};

QString toQString(const Status s);


class Pokemon
{
public:
    Pokemon() = default;
    explicit Pokemon(QString name, QChar gender)
        : name_(name),
        nickname_(name),
        gender_(gender),
        hp_(100),
        maxhp_(100),
        // alive_(true),
        status_(Status())
    {}
    explicit Pokemon(QString name)
        : name_(name)
        , nickname_(name)
        , gender_('U')
        , hp_(100)
        , maxhp_(100)
        // , alive_(true)
        , status_(Status())
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


    void setHp(int newhp, int maxhp) {
        hp_ = newhp; maxhp_ = maxhp;
    }
    void setHp(int newhp) { hp_ = newhp; }


    QString hp() const { return QString::number(hp_); }
    QString maxhp() const { return QString::number(maxhp_); }


    double healthPercent() const { return static_cast<double>(hp_) / static_cast<double>(maxhp_) * 100;}

    void setStatus(status status) { status_ = Status{status, 0}; }
    void resetStatus() { status_ = Status(); }
    void updateStatus() { ++status_.length; }
    const Status& status() const { return status_; }

    // void fainted() { alive_ = false; }
    // bool isalive() const { return alive_; }

private:
    QString name_;
    QString nickname_;
    QChar gender_;
    int hp_;
    int maxhp_;
    // bool alive_ = true;
    Status status_{};
};


#endif // POKEMON_H
