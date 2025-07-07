#include "lineid.h"

lineid lineEnum(const QString &line)
{
    if (line == "player") {
        return PLAYER;
    } else if (line == "poke") {
        return POKE;
    } else if (line == "rule") {
        return RULE;
    } else if (line == "gametype") {
        return GAMETYPE;
    } else if (line == "gen") {
        return GEN;
    } else if (line == "tier") {
        return TIER;
    } else if (line == "start") {
        return START;
    } else if (line == "turn") {
        return TURN;
    } else if (line == "switch") {
        return SWITCH;
    } else if (line == "move") {
        return SWITCH;
    } else if (line == "c") {
        return CHAT;
    } else if (line == "j") {
        return JOIN;
    } else if (line == "l") {
        return LEAVE;
    } else if (line == "-damage") {
        return DAMAGE;
    } else if (line == "-heal") {
        return HEAL;
    } else if (line == "-crit") {
        return CRIT;
    } else if (line == "-miss") {
        return MISS;
    } else if (line == "-supereffective") {
        return SUPEREFF;
    } else if (line == "-resisted") {
        return RESISTED;
    } else if (line == "-immune") {
        return IMMUNE;
    } else if (line == "faint") {
        return FAINT;
    } else {
        return UNKNOWN;
    }
}
