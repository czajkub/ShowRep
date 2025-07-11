#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "include/game.h"

#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <cmath>


#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
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
    //fillTable(state);
    game.init(list);
    ui->turnSlider->setMinimum(0);
    ui->turnSlider->setMaximum(game.turns() - 1);
    ui->turnSlider->setValue(0);

    plotGraph(game);

    fillTable(game[0]);
}

QStringList MainWindow::loadReplayFile(QString fname)
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

    //QString line = in.readAll();

    inputFile.close();

    return lines;

    // ui->textEdit->setPlainText(lines[1]);
    // QTextCursor cursor = ui->textEdit->textCursor();
    // cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor, 1);

}

void MainWindow::fillTable(const State &state)
{

    int count = 0;
    for (const auto & [nick, mon] : state.mons1()) {
        QTableWidgetItem *name = new QTableWidgetItem(mon.printable());
        double health = std::floor(mon.healthPercent() * 10) / 10;
        QString hpstr = QString::number(health) + "%";
        QTableWidgetItem *hp = new QTableWidgetItem(hpstr);

        // QMessageBox msgBox;
        // msgBox.setText(mon.printable());
        // msgBox.exec();

        ui->player1table->setItem(count, 0, name);
        ui->player1table->setItem(count, 1, hp);
        ++count;
    }
    count = 0;
    for (const auto & [nick, mon] : state.mons2()) {
        QTableWidgetItem *name = new QTableWidgetItem(mon.printable());
        double health = std::floor(mon.healthPercent() * 10) / 10;
        QString hpstr = QString::number(health) + "%";
        QTableWidgetItem *hp = new QTableWidgetItem(hpstr);

        ui->player2table->setItem(count, 0, name);
        ui->player2table->setItem(count, 1, hp);
        ++count;
    }

    ui->player1tableLabel->setText(state.p1name());
    ui->player2tableLabel->setText(state.p2name());

}

void MainWindow::on_turnSlider_valueChanged(int value)
{
    fillTable(game[value]);
}


void MainWindow::plotGraph(const Game &game)
{
    QLineSeries *series = new QLineSeries();
    for (int i = 0; i < game.turns(); i++) {
        series->append(i, game[i].luckscore());
    }

    series->setColor(Qt::blue);
    series->setPen(QPen(Qt::green, 2));

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->createDefaultAxes();

    chart->setTitle("Luck score");

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
