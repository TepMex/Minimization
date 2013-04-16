#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    QString text1;
    QString text0;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setResultText(QString s);
private:
    Ui::MainWindow *ui;
private slots:
    void getInputValues();
    void printResult();
signals:
    void inputComplete();
};

#endif // MAINWINDOW_H
