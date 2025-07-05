#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "state.h"

#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>

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
    State state = loadReplayFile(filename);
    fillTable(state);
}

State MainWindow::loadReplayFile(QString fname)
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

    return State(lines);

    // ui->textEdit->setPlainText(lines[1]);
    // QTextCursor cursor = ui->textEdit->textCursor();
    // cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor, 1);

}

void MainWindow::fillTable(const State &state)
{
    int count = 0;
    for (const auto &mon : state.player1.pokes()) {
        ui->pokemonTable->setItem(count, 0, new QTableWidgetItem(mon.printable()));
        ++count;
    }

    count = 0;
    for (const auto &mon : state.player2.pokes()) {
        ui->pokemonTable->setItem(count, 1, new QTableWidgetItem(mon.printable()));
        ++count;
    }

}
