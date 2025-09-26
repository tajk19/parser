#include "Parser.h"

Parser::Parser(){}

Parser::~Parser(){
}


QString parseContData(const QString &data, const QString &type) {
    if (type == "A") {
        // ASCII: каждые 2 символа — Hex, преобразуем в char
        QString result;
        for (int i = 0; i < data.length(); i += 2) {
            bool ok;
            int byte = data.mid(i, 2).toInt(&ok, 16);
            if (ok) result.append(QChar(byte));
        }
        return result;
    } else if (type == "H" || type == "B") {
        // Hex или байты: оставляем как есть
        return data;
    } else if (type == "N") {
        // Десятичные данные: оставляем как есть
        return data;
    }
    return data;
}

QJsonArray Parser::parseXML(QString path){
    QJsonArray data;
    int size = 0;

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file";
        return data;
    }
    QXmlStreamReader xml(&file);
    bool isRequest = true; // первый тег - запрос

    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::StartElement && xml.name() == "TContextCMD") {
            QString commandData = xml.attributes().value("Data").toString();
            QString type = isRequest ? "Request" : "Response";

            QJsonObject item;
            item[type] = commandData;
            data.append(item);
            item.remove(type);
            size++;
            // парсим вложенные поля
            while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "TContextCMD")) {
                xml.readNext();
                if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == "TCont") {
                    QString name = xml.attributes().value("Name").toString();

                    QString fieldType = xml.attributes().value("Type").toString();

                    QString fieldData = xml.attributes().value("Data").toString();

                    QString value = parseContData(fieldData, fieldType);
                    size++;

                    item["Name"] = name;
                    item["Value"] = value;
                    data.append(item);
                    item.remove("Name");
                    item.remove("Value");
                    }
            }
            isRequest = !isRequest; // чередуем запрос и ответ
        }
    }


    if (xml.hasError()) {
        qDebug() << "XML Error:" << xml.errorString();
    }
    emit dataReady(data, size);
    return data;
}
