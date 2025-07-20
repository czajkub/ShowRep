#include "include/pokemon.h"

QString toQString(const Status s)
{
    QString print;
    switch (s.type) {
    case HEALTHY:
        print = "Healthy";
        break;
    case BURN:
        print = "Burn";
        break;
    case PARALYSIS:
        print = "Paralysis";
        break;
    case FREEZE:
        print = "Freeze";
        break;
    case POISON:
        print = "Poison";
        break;
    case TOXIC:
        print = "Toxic";
        break;
    case SLEEP:
        print = "Sleep";
        break;
    case CONFUSION:
        print = "Confusion";
        break;
    default:
        print = "Healthy";
        break;
    }
    return ( print + ": " + QString::number(s.length) + " turns" );
}
