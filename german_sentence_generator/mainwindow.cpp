#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "displaywordsdialog.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->germanWordsDisplay->setText(mySentence.output(0));
    ui->englishWordsDisplay->setText(mySentence.output(1));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generateSentenceButton_released()
{
    mySentence.generate();
    ui->germanWordsDisplay->setText(mySentence.output(0));
    ui->englishWordsDisplay->setText(mySentence.output(1));
}

void MainWindow::on_displayWordsButton_clicked()
{
    DisplayWordsDialog d;
    d.setDisplay(mySentence.getWords(0), 0);
    d.setDisplay(mySentence.getWords(1), 1);
    d.setModal(true);
    d.exec();
}
