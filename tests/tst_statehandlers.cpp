#include <QtTest>

#include "util/statehandlers.h"


namespace fs = std::filesystem;

class statehandlers : public QObject
{
    Q_OBJECT
private:
    QStringList loadReplayFile(fs::path path);

public:
    statehandlers();
    ~statehandlers();

private slots:
    void damageTest();
    void switchTest();
    void moveTest();
};

statehandlers::statehandlers() {}

statehandlers::~statehandlers() {}

void statehandlers::damageTest() {
    fs::path path = "../../tests/logs/kubercikkacperol.log.txt";
    auto lines = loadReplayFile(path);
    InitialState istate(lines);
    State state;
    istate.copyToState(state);
    QStringList damage1;
    damage1 << "-damage" << "p1a: Landorus-Therian" << "27/120";
    handleDamage(state, damage1);

    QCOMPARE(state.mons1().at("Landorus-Therian").hp(), "27");
    QCOMPARE(state.mons1().at("Landorus-Therian").maxhp(), "120");

    QStringList damage2;
    damage1 << "-damage" << "p1a: Landorus-Therian" << "145/120";
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,
                             handleDamage(state, damage2));

    QStringList damage3;
    damage3 << "af|iosnsoa|psf|jas|fpa";
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,
                             handleDamage(state, damage3));


}


void statehandlers::switchTest()
{
    fs::path path = "../../tests/logs/kubercikkacperol.log.txt";
    auto lines = loadReplayFile(path);
    InitialState istate(lines);
    State state;
    istate.copyToState(state);

    QCOMPARE(state.mons1().size(), 6);
    QCOMPARE(state.mons2().size(), 6);

    QCOMPARE(state.mons1().count("Landorus-Therian"), 1);
    QCOMPARE(state.mons1().count("Earfquake"), 0);

    QStringList line;
    line << "switch" << "p1a: Earfquake" << "Landorus-Therian, M" << "100/100";

    handleSwitch(state, line);

    QCOMPARE(state.mons1().count("Landorus-Therian"), 0);
    QCOMPARE(state.mons1().count("Earfquake"), 1);
}


void statehandlers::moveTest()
{
    fs::path path = "../../tests/logs/kubercikmiking.log.txt";
    auto lines = loadReplayFile(path);
    InitialState istate(lines);
    State state;
    istate.copyToState(state);

    QCOMPARE(state.luckscore(), 0);
    QCOMPARE(state.log().size(), 0);

    QStringList move1;
    QStringList move2;
    QStringList move3;

    // hydro pump - 80% accurate move with no special effects
    move1 << "move" << "p1a: Chaos Space Marine" << "Hydro Pump" << "p2a: Skuntank";
    move2 << "move" << "p1a: Chaos Space Marine" << "Hydro Pump" << "p2a: Skuntank" << "[miss]";
    move3 << "move" << "p1a: Chaos Space Marine" << "Hydro Pump" << "p2a: Skuntank" << "[notarget]";

    double luck1 = moveLuck(state, move1, true).luck;
    double luck2 = moveLuck(state, move1, false).luck;
    double luck3 = 0;


    handleMove(state, move1);
    QCOMPARE(state.luckscore(), luck1);

    handleMove(state, move2);
    QCOMPARE(state.luckscore(), luck1 + luck2);

    handleMove(state, move3);
    QCOMPARE(state.luckscore(), luck1 + luck2 + luck3);

    // 3rd entry doesnt produce a log
    QCOMPARE(state.log().size(), 2);
}










QStringList statehandlers::loadReplayFile(fs::path path)
{
    QFile inputFile(path);
    inputFile.open(QIODevice::ReadOnly);


    QTextStream in(&inputFile);
    QStringList lines;
    QString line;
    do {
        line = in.readLine();
        lines << line;
    } while (line != QString());

    inputFile.close();

    return lines;

}


QTEST_APPLESS_MAIN(statehandlers)



#include "tst_statehandlers.moc"
