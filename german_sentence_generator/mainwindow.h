#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "sentence.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_generateSentenceButton_released();

    void on_displayWordsButton_clicked();

private:
    Ui::MainWindow *ui;
    sentence mySentence;
};

#endif // MAINWINDOW_H
