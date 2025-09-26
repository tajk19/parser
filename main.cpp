#include "mainwindow.h"
#include "Parser.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    Parser parser;
    QObject::connect(&w, &MainWindow::parseXML, &parser, &Parser::parseXML);
    QObject::connect(&parser, &Parser::dataReady, &w, &MainWindow::takeDataFromParse);
    w.show();
    return a.exec();
}
