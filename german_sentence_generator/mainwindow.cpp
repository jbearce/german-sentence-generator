#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "displaywordsdialog.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->germanWordsDisplay->setText(mySentence.output("german"));
    ui->englishWordsDisplay->setText(mySentence.output("english"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generateSentenceButton_released()
{
    mySentence.generate();
    ui->germanWordsDisplay->setText(mySentence.output("german"));
    ui->englishWordsDisplay->setText(mySentence.output("english"));
}

void MainWindow::on_displayWordsButton_clicked()
{
    DisplayWordsDialog d;
    d.setDisplay(mySentence.get_words("german"), 0);
    d.setDisplay(mySentence.get_words("english"), 1);
    d.setModal(true);
    d.exec();
}
