#include "player.h"

#include <QRegularExpression>
#include <QMessageBox>

void Player::addPokemon(const QString &line)
{
    QStringList fields = line.split(QRegularExpression(", "), Qt::SkipEmptyParts);

    // weird edge case: during switch it shows up as
    // Urshifu instead of Urshifu-* and crashes the program
    if (fields[0] == "Urshifu-*")
        fields[0] = "Urshifu";

    if (fields.size() == 1) {
        // mons_[fields[0]] = Pokemon(fields[0]);
        mons_.insert(std::make_pair(fields[0], Pokemon(fields[0])));
    } else {
        // mons_[fields[0]] = Pokemon(fields[0], fields[1][0]);
        mons_.insert(std::make_pair(fields[0], Pokemon(fields[0], fields[1][0])));
    }

    if(mons_.size() > 6 || mons_.size() > teamsize_) {
        // TODO: throw some sort of error message to user !
    }
}

void Player::setHp(const QString& nick, int hp)
{
    if (mons_.count(nick) == 0)
        return;
    mons_[nick].setHp(hp);
}

void Player::setFaint(const QString &nick)
{
    if (mons_.count(nick) == 0)
        return;
    mons_[nick].fainted();
}


void Player::setNick(const QString &oldname, const QString &newname)
{
    if (mons_.count(oldname) == 0) {
        if (mons_.count(newname) == 1)
            return;
        QMessageBox msgBox;
        msgBox.setText(
            "Something went wrong with the replay file; make sure you uploaded correct replay.");
        msgBox.exec();
        return;
    }

    // switch the actual pokemon object's nickname
    mons_.at(oldname).setNick(newname);

    // switch key in mons_ map
    auto it = mons_.find(oldname);
    if (it != mons_.end()) {
        auto mon = mons_.at(oldname);
        mons_.erase(oldname);
        mons_.insert(it, std::make_pair(newname, mon));
    }

    // auto mon = mons_.at(oldname);
    // mons_.erase(oldname);
    // mons_.insert(std::make_pair(newname, mon));

    /* this doesnt work for some reason? looks better though :(
    auto node = mons_.extract(oldname);
    node.key() = newname;
    mons_.insert(std::move(node));
    */

}
