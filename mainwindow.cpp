#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <QVector>
#include <parser.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
Parser parser;

QString e = "2.718281828459045";
QString pi = "3.141592653589793";
QString a = "0.0000000000000000000000000000000006626068";
QString g = "0.0000000000667300";

void MainWindow::on_input_textChanged(){
    QString s = ui->input->toPlainText().replace('e',e);
    s = s.replace("pi",pi);
    s = s.replace('a',a); //6.626068e-34
    s = s.replace('g',g); //6.67300e-11
    try{
        NodePtr root = parser.parse(s.toStdString());
        ui->answer->setText(QString::number(root->evaluate()));
    }catch(...){

    }


}


bool notOperator(QString t){
    if (t != '*' || t != '/' || t != '-' || t != '+'){
        return true;
    }
    return false;
}

QString combine(QString prev,QString symbol){
    if (prev.length() != 0 && notOperator(prev[prev.length()-1])){
        return prev+"*"+symbol;
    }
    return prev+symbol;
}

void MainWindow::on_eButton_clicked()
{
    QString t = ui->input->toPlainText();
    ui->input->setText(combine(t,"e"));
}


void MainWindow::on_pieButton_clicked()
{
    QString t = ui->input->toPlainText();
    ui->input->setText(combine(t,"pi"));
}


void MainWindow::on_pushButton_clicked()
{
    QString t = ui->input->toPlainText();
    ui->input->setText(combine(t,"g"));
}


void MainWindow::on_pushButton_2_clicked()
{
    QString t = ui->input->toPlainText();
    ui->input->setText(combine(t,"a"));
}

