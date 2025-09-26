#include "mainwindow.h"
#include "Parser.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1080, 720);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    qDebug()<< "Начался парсинг файла: " << fileName;
    emit parseXML(fileName);
}


void MainWindow::on_pushButton_2_clicked()
{
    while(1){
        QString path = QFileDialog::getOpenFileName(this, "Выберите файл", "", "Все файлы (*.*);; XML файлы (*.xml)");
        if (path.isEmpty()) {
            return;
        }

        QFileInfo fileInfo(path);
        if (fileInfo.suffix()!= "xml"){
            QMessageBox::critical(this, "ОШИБКА","Выбран файл не того формата");
            continue;
        }
        fileName = path;
        ui->lineEdit->setText(fileName);
        ui->lineEdit->setCursorPosition(0);
        ui->pushButton->setEnabled(true);
        return;
    }

}

void MainWindow::takeDataFromParse(QJsonArray data, int size){
    auto table = ui->mainTable;
    table->setRowCount(size);
    table->setColumnCount(2);
    size_t step = 0;
    for(size_t i = 0; i != data.size(); i++){
        QJsonObject obj = data.at(i).toObject();
        for (auto it = obj.begin(); it != obj.end(); it++) {
            if (it.key() == "Name"){
                table->setItem(step, 0, new QTableWidgetItem(it.value().toString()));
                continue;
            }
            if(it.key() == "Value"){
                table->setItem(step, 1, new QTableWidgetItem(it.value().toString()));
                step++;
                continue;
            }
            table->setItem(step, 0, new QTableWidgetItem(it.key()));
            table->setItem(step, 1, new QTableWidgetItem(it.value().toString()));
            step++;
        }
    };
    ui->mainTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->mainTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui->mainTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    table->show();
};

void MainWindow::on_lineEdit_returnPressed()
{
    QString path = ui->lineEdit->text();
        QFileInfo fileInfo(path);

        if (!fileInfo.exists() || !fileInfo.isFile()) {
            QMessageBox::warning(this, "Ошибка", "Файл не найден или неверный путь!");
            return;
        }

        if (fileInfo.suffix() != "xml") {  // например, только .json
            QMessageBox::warning(this, "Ошибка", "Неверный тип файла (ожидался .xml)");
            return;
        }
        fileName = path;
        ui->lineEdit->setText(fileName);
        ui->lineEdit->setCursorPosition(0);
        ui->pushButton->setEnabled(true);
        return;
}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    ui->pushButton->setEnabled(false);
}
