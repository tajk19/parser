#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QXmlStreamReader>

class Parser : public QObject {
Q_OBJECT
public:
    Parser();
    ~Parser();

public slots:
    QJsonArray parseXML(QString path);
signals:
    void dataReady(QJsonArray data, int size);
};

#endif // PARSER_H
