#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <headers/state.h>
#include <headers/game.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_fileButton_clicked();

    void on_turnSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    Game game;
    QStringList loadReplayFile(QString fname);
    void plotGraph(const Game &game);
    void fillTable(const State& state);
};
#endif // MAINWINDOW_H
