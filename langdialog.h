#ifndef LANGDIALOG_H
#define LANGDIALOG_H

#include <QDialog>


namespace Ui {
class LangDialog;
}


class LangDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LangDialog(QWidget *parent = nullptr);
    ~LangDialog();
    bool greek;

private slots:
    void on_engBtn_clicked();
    void on_greBtn_clicked();

private:
    Ui::LangDialog *ui;
};

#endif // LANGDIALOG_H
