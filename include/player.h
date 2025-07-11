#ifndef PLAYER_H
#define PLAYER_H

#include <QStringList>
#include "pokemon.h"

class Player
{
public:
    Player() = default;
    explicit Player(const QString &name, const QString &avatar)
        : name_(name)
        , avatar_(avatar)
    {}

    QString name() const { return name_; }

    /**
     * @brief set player team size
     * @param size - new size
     */
    void setTeamSize(size_t size) { teamsize_ = size; }

    /**
     * happens only during constructing the initial state
     *
     * @brief insert pokemon into unordered_map
     * @param line - log line representing pokemon
     */
    void addPokemon(const QString &line);

    /**
     * @brief change a pokemon's HP
     * @param nick of pokemon
     * @param newhp
     * @param maxhp
     */
    void setHp(const QString &nick, int newhp, int maxhp);

    void setHp(const QString &nick, int newhp);

    /**
     * @brief set pokemon's status to fainted
     * @param nick - nickname of pokemon
     */
    void setFaint(const QString& nick);

    /**
     * happens only if they differ
     *
     * @brief change nickname of pokemon to newname from oldname
     * @param oldname - old name of pokemon (usually actual pokemon name)
     * @param newname - the nickname we want to set it to
     */
    void setNick(const QString &oldname, const QString &newname);


    //std::vector<Pokemon> pokes() const { return mons_; }
    /**
     * @return mons_ map
     */
    const std::unordered_map<QString, Pokemon>& pokes() const { return mons_; }

private:
    QString name_;
    QString avatar_;
    size_t teamsize_ = 6;
    //std::vector<Pokemon> mons_;
    std::unordered_map<QString, Pokemon> mons_;
};

#endif // PLAYER_H
