#include "state.h"
#include "lineid.h"


State::State(QStringList &lines)
{
    for (const auto &line : lines) {
        QStringList fields = line.split(u'|', Qt::SkipEmptyParts);
        if (fields.size() == 0)
            continue;
        enum lineid linetype = lineEnum(fields[0]);
        switch (linetype) {
        case PLAYER:
            fields[1] == "p1" ? player1_ = Player(fields[2], fields[3])
                              : player2_ = Player(fields[2], fields[3]);
            break;
        case POKE:
            fields[1] == "p1" ? player1_.addPokemon(fields[2]) : player2_.addPokemon(fields[2]);
            break;
        default:
            break;
        }
    }
}


InitialState::InitialState(QStringList& lines) {
    for (const auto &line : lines) {
        QStringList fields = line.split(u'|', Qt::SkipEmptyParts);
        if (fields.size() == 0)
            continue;
        enum lineid linetype = lineEnum(fields[0]);
        switch (linetype) {
        case PLAYER:
            fields[1] == "p1" ? setPlayer(1, Player(fields[2], fields[3]))
                              : setPlayer(2, Player(fields[2], fields[3]));
            break;
        case POKE:
            fields[1] == "p1" ? player1().addPokemon(fields[2])
                              : player2().addPokemon(fields[2]);
            break;
        case TEAMSIZE:
            fields[1] == "p1" ? player1().setTeamSize(fields[2].toULongLong())
                              : player2().setTeamSize(fields[2].toULongLong());
            break;
        case GEN:
            setGen(fields[1].toInt());
            break;
        case RULE:
            addRule(fields[1]);
            break;
        case GAMETYPE:
            setGametype(fields[1]);
            break;
        case TIER:
            setTier(fields[1]);
            break;
        case START:
            lines.remove(0, lines.indexOf(line));
            return;
        default:
            break;
        }
    }

}

// InitialState initialState(QStringList &lines)
// {
//     InitialState state;
//     for (const auto &line : lines) {
//         QStringList fields = line.split(u'|', Qt::SkipEmptyParts);
//         if (fields.size() == 0)
//             continue;
//         enum lineid linetype = lineEnum(fields[0]);
//         switch (linetype) {
//         case PLAYER:
//             fields[1] == "p1" ? state.setPlayer(1, Player(fields[2], fields[3]))
//                               : state.setPlayer(2, Player(fields[2], fields[3]));
//             break;
//         case POKE:
//             fields[1] == "p1" ? state.player1().addPokemon(fields[2])
//                               : state.player2().addPokemon(fields[2]);
//             break;
//         case TEAMSIZE:
//             fields[1] == "p1" ? state.player1().setTeamSize(fields[2].toULongLong())
//                               : state.player2().setTeamSize(fields[2].toULongLong());
//             break;
//         case GEN:
//             state.setGen(fields[1].toInt());
//             break;
//         case RULE:
//             state.addRule(fields[1]);
//             break;
//         case GAMETYPE:
//             state.setGametype(fields[1]);
//             break;
//         case TIER:
//             state.setTier(fields[1]);
//             break;
//         case START:
//             lines.remove(0, lines.indexOf(line));
//             return state;
//         default:
//             break;
//         }
//     }
//     // this should be an error actually - no start means the replay is bad
//     return InitialState();
// }
