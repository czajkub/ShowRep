#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "include/game.h"
#include "include/pokemon.h"

#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <cmath>


#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QPointF>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_fileButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Add replay file", QDir::homePath());
    QStringList list = loadReplayFile(filename);

    game.init(list);


    ui->turnSlider->setMinimum(0);
    ui->turnSlider->setMaximum(game.turns() - 1);
    ui->turnSlider->setValue(0);

    //ui->turnSliderEdit->setAlignment(Qt::AlignCenter);
    ui->turnSliderEdit->setText("0");

    plotGraph(game);

    fillTable(game[0]);
}

QStringList MainWindow::loadReplayFile(QString fname)
{
    QFile inputFile(fname);
    bool ok = inputFile.open(QIODevice::ReadOnly);
    if (!ok) {
        QMessageBox errorbox;
        errorbox.setText("Error opening log");
        errorbox.exec();
        QStringList list;
        return list;
    }

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

void MainWindow::fillTable(const State &state)
{
    ui->player1table->clear();
    ui->player2table->clear();

    ui->player1table->setColumnCount(1);
    ui->player2table->setColumnCount(1);

    for (const auto & [nick, mon] : state.mons1()) {
        auto poke = new QTreeWidgetItem(ui->player1table);
        poke->setText(0, mon.printable());

        new QTreeWidgetItem(poke, QStringList(mon.name()));
        new QTreeWidgetItem(poke, QStringList(mon.hp() + "/" + mon.maxhp()));
        new QTreeWidgetItem(poke, QStringList(toQString(mon.status())));


        // QMessageBox msgBox;
        // msgBox.setText(mon.printable());
        // msgBox.exec();
    }
    for (const auto & [nick, mon] : state.mons2()) {
        auto poke = new QTreeWidgetItem(ui->player2table);
        poke->setText(0, mon.printable());

        new QTreeWidgetItem(poke, QStringList(mon.printable()));
        new QTreeWidgetItem(poke, QStringList(mon.hp()));
        new QTreeWidgetItem(poke, QStringList(toQString(mon.status())));
    }

    ui->player1tableLabel->setText(state.p1name());
    ui->player2tableLabel->setText(state.p2name());

}

void MainWindow::on_turnSlider_valueChanged(int value)
{
    fillTable(game[value]);
    ui->turnSliderEdit->setText(QString::number(value));
}


void MainWindow::plotGraph(const Game &game)
{
    QLineSeries *series = new QLineSeries();
    for (int i = 0; i < game.turns(); i++) {
        series->append(i, game[i].luckscore());
    }

    QBrush brush(Qt::white, Qt::Dense1Pattern);

    QFont font;
    font.setBold(true);
    font.setWeight(QFont::Bold);

    series->setBrush(brush);
    series->setColor(Qt::white);

    QChart *chart = new QChart();
    chart->addSeries(series);

    chart->createDefaultAxes();
    for (auto axis : chart->axes()) {
        if (QValueAxis *valaxis = qobject_cast<QValueAxis *>(axis)) {
            valaxis->setLabelsFont(font);
            valaxis->setLabelsBrush(brush);
        }
    }

    // auto xAxis = chart->axes(Qt::Horizontal).constFirst();
    // auto yAxis = chart->axes(Qt::Vertical).constFirst();
    // xAxis->setTitleBrush(brush);
    // xAxis->setTitleFont(font);
    // yAxis->setTitleBrush(brush);
    // yAxis->setTitleFont(font);


    chart->setBackgroundVisible(false);

    chart->setTitleBrush(brush);
    chart->setTitleFont(font);

    chart->setTitle("Luck Score");


    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);

    QWidget *luckGraph = ui->luckGraph;

    QVBoxLayout *layout = new QVBoxLayout(luckGraph);
    layout->addWidget(chartview);
    luckGraph->setLayout(layout);



    std::vector<QString> log = game[game.turns() - 1].log();

    QTextEdit *luckedit = new QTextEdit(this);
    luckedit->setReadOnly(true);
    for (const auto &line : log)
        luckedit->append(line);



    QWidget *luckLog = ui->luckLog;

    QVBoxLayout *loglayout = new QVBoxLayout(luckLog);
    loglayout->addWidget(luckedit);

}

void MainWindow::on_turnSliderEdit_textChanged()
{
    // if (!game.initialised())
    //     return;

    // // doesnt work??

    // bool ok;
    // int turn = ui->turnSliderEdit->toPlainText().toInt(&ok, 10);
    // bool correctturn = (turn >= ui->turnSlider->minimum() && turn <= ui->turnSlider->maximum());
    // if (ok && correctturn) {
    //     ui->turnSlider->setValue(turn);
    //     fillTable(game[turn]);
    //     return;
    // }

    // ui->turnSlider->setValue(0);
    // fillTable(game[0]);
    // ui->turnSliderEdit->setText("");
}

void MainWindow::on_urlButton_clicked() {
    QString replayURL = ui->urlTextEdit->toPlainText().trimmed();
    QStringList lines = getReplayFromUrl(replayURL);

    game.init(lines);

    ui->turnSlider->setMinimum(0);
    ui->turnSlider->setMaximum(game.turns() - 1);
    ui->turnSlider->setValue(0);

    //ui->turnSliderEdit->setAlignment(Qt::AlignCenter);
    ui->turnSliderEdit->setText("0");

    plotGraph(game);

    fillTable(game[0]);
}
