#include "player.h"

#include <QRegularExpression>

void Player::addPokemon(const QString &line)
{
    QStringList fields = line.split(QRegularExpression(", "), Qt::SkipEmptyParts);
    if (fields.size() == 1) {
        mons_.emplace_back(fields[0]);
    } else {
        mons_.emplace_back(fields[0], fields[1][0]);
    }
    if(mons_.size() > 6 || mons_.size() > teamsize_) {
        // TODO: throw some sort of error message to user !
    }
}
