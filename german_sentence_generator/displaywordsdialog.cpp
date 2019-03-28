#include "displaywordsdialog.h"
#include "ui_displaywordsdialog.h"
#include "sentence.h"
DisplayWordsDialog::DisplayWordsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayWordsDialog)
{
    ui->setupUi(this);
}

DisplayWordsDialog::~DisplayWordsDialog()
{
    delete ui;
}

void DisplayWordsDialog::setSentence(sentence& input) {
    mySentence = input;
}

void DisplayWordsDialog::setDisplay(QString input, int displayNum) {
    if (0 == displayNum) {
        ui->textBrowserGerman->setText(input);
    } else if (1 == displayNum) {
        ui->textBrowserEnglish->setText(input);
    }
}
