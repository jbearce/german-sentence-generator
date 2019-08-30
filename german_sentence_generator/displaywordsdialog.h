#ifndef DISPLAYWORDSDIALOG_H
#define DISPLAYWORDSDIALOG_H
#include "sentence.h"
#include <QDialog>

namespace Ui {
class DisplayWordsDialog;
}

class DisplayWordsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayWordsDialog(QWidget *parent = nullptr);
    ~DisplayWordsDialog();
    void setDisplay(QString, int);
private slots:

private:
    Ui::DisplayWordsDialog *ui;
    sentence mySentence;
};

#endif // DISPLAYWORDSDIALOG_H
