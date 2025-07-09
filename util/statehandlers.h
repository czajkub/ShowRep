#ifndef STATEHANDLERS_H
#define STATEHANDLERS_H

#include "headers/state.h"

#include <QStringList>


/**
     * change the HP stat in the correct Player object
     * of the pokemon whose HP was changed
     * @brief handles damage dealt to pokemon
     * @param state - current state
     * @param lines - current line of the log
     */
void handleDamage(State &state, const QStringList &lines);


/**
     * @brief set the alive_ boolean of correct Pokemon to false
     * @param state - current state
     * @param lines - current line of the log
     */
void handleFaint(State &state, const QStringList &lines);


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


void handleCrit(State &state, const QStringList &lines);


void handleMiss(State &state, const QStringList &lines);


double resolveMove(State &state, const QStringList &lines);

#endif // STATEHANDLERS_H
