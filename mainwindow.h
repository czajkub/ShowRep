#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <state.h>

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

private:
    Ui::MainWindow *ui;
    State loadReplayFile(QString fname);
    void fillTable(const State& state);
};
#endif // MAINWINDOW_H
