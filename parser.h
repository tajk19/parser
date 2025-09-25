#ifndef PARSER_H
#define PARSER_H

#include <QObject>

class parser {

public:
    parser();
    ~parser();
public slots:
QJsonObject parseXML(QString path);

private:




};

#endif // PARSER_H
