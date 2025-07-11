#include <QtTest>

#include "util/statehandlers.h"

class statehandlers : public QObject
{
    Q_OBJECT
private:
    QStringList loadReplayFile(QString fname);

public:
    statehandlers();
    ~statehandlers();

private slots:
    void damageTest();
};

statehandlers::statehandlers() {}

statehandlers::~statehandlers() {}

void statehandlers::damageTest() {
    auto lines = loadReplayFile("logs/kubercikkacperol.log.txt");
    InitialState istate(lines);
    State state;
    istate.copyToState(state);
    QStringList damage;
    damage << "-damage" << "p1a: Landorus-Therian" << "27/120";
    handleDamage(state, damage);

    QCOMPARE(state.mons1().at("Landorus-Therian").hp(), "27");
    QCOMPARE(state.mons1().at("Landorus-Therian").maxhp(), "120");
}

QStringList statehandlers::loadReplayFile(QString fname)
{
    QFile inputFile(fname);
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
