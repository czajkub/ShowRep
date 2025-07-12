#ifndef STATEHANDLERS_H
#define STATEHANDLERS_H

#include "include/state.h"

#include <QStringList>


void upkeep(State &state);

/**
     * change the HP stat in the correct Player object
     * of the pokemon whose HP was changed
     * @brief handles damage dealt to pokemon
     * @param state - current state
     * @param lines - current line of the log
     */
void handleDamage(State &state, const QStringList &lines);


/**
     * If the nickname (set to the pokemon name by default) is different
     * from the nickname by which it is referred to in the log, the name
     * of the pokemon and map key are changed
     *
     * @brief change nickname of Pokemon
     * @param state - current state
     * @param lines - current line of the log
     */
void handleSwitch(State &state, const QStringList &lines);


/**
     * will be weighted somehow and also checks for things like
     * evasion or other accuracy changes
     *
     * @brief check move accuracy and update luck score
     * @param state - current state
     * @param lines - current line of the log
     */
void handleMove(State &state, const QStringList &lines);


/**
 * checks whether the move always crits and should sometime
 * check whether crit chance is raised or smth
 * for example special moves with raised crit chance?
 *
 * @brief update luckscore
 * @param state
 * @param lines
 */
void handleCrit(State &state, const QStringList &lines);





void handleStatus(State &state, const QStringList &lines);


struct Luck
{
    double luck;
    QString log;
};



Luck secondaryLuck(const std::string& lastmove, const QStringList &lines, bool hit);


/**
 * @brief calculate luck score based on move and whether it hit
 * @param state
 * @param lines
 * @param hit - whether the move hit or not
 * @return
 */
Luck moveLuck(const QStringList &lines, bool hit);

#endif // STATEHANDLERS_H
