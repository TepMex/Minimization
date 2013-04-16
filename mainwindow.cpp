#include <QString>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "quine.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(this->ui->minimizeButton,SIGNAL(clicked()),SLOT(getInputValues()));
    QObject::connect(this,SIGNAL(inputComplete()),SLOT(printResult()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setResultText(QString s)
{
    this->ui->resultFuncText->setText(s);
}

void MainWindow::getInputValues()
{
    this->text0 = this->ui->set0input->text();
    this->text1 = this->ui->set1input->text();
    emit inputComplete();
}

void MainWindow::printResult()
{
    int s1[MAX_LENGHT];
    int s0[MAX_LENGHT];

    QString delimiter(",");
    QStringList sets1;
    QStringList sets0;

    sets1 = this->text1.split(delimiter);
    sets0 = this->text0.split(delimiter);

    int i;
    for(i = 0; i<sets1.length(); i++)
    {
        QString str;
        str = sets1[i];
        s1[i] = str.toInt();

    }
    s1[i] = END;
    for(i = 0; i<sets0.length(); i++)
    {
        QString str;
        str = sets0[i];
        s0[i] = str.toInt();

    }
    s0[i] = END;

    setResultText(quine_start(s1,s0));
}

