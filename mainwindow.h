#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QSettings>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void readPreferences();
    void savePreferences();
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_actionAbout_triggered();
    void on_actionEnter_Names_triggered();
    void on_actionGet_Result_triggered();
    void on_actionChange_Language_triggered();

private:
    Ui::MainWindow *ui;
    QVector<int> players {};
    QStringList names;
    bool calculate(int N);
    bool isGreek;
    int calcCount;
};

#endif // MAINWINDOW_H
