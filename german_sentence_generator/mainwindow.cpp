#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sentence_main.cpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generateSentenceButton_released()
{
    sentence mySentence = populate_sentence();
    mySentence.generate();
    ui->germanWordsDisplay->setText(mySentence.output(0));
    ui->englishWordsDisplay->setText(mySentence.output(1));
}
