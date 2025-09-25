#include "mainwindow.h"
#include "parser.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1080, 720);

    ui->lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui->pushButton_2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    //Поправить
    auto layout = this->layout();
    layout->setContentsMargins(5,5,5,5);
    layout->setSpacing(5);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    emit parseXML();
    takeDataFromParse();
    QJsonObject* data;
    ui->mainTable->setHorizontalHeaderLabels({});
}


void MainWindow::on_pushButton_2_clicked()
{
    while(1){
        QString fileName = QFileDialog::getOpenFileName(this, "Выберите файл", "", "Все файлы (*.*);; XML файлы (*.xml)");
        if (fileName.isEmpty()) {
            return;
        }

        QFileInfo fileInfo(fileName);
        if (fileInfo.suffix()!= "xml"){
            QMessageBox::critical(this, "ОШИБКА","Выбран файл не того формата");
            continue;
        }

        ui->lineEdit->setText(fileName);
        ui->pushButton->setEnabled(true);
        return;
    }

}

