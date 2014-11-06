#ifndef RESPONSEITEM_H
#define RESPONSEITEM_H

#include <QObject>
#include <QString>
class ResponseItem
{

public:
    QString response;
    QString id;
    explicit ResponseItem(QString id, QString response);
    QString  serialize();
signals:

public slots:

};

#endif // RESPONSEITEM_H
