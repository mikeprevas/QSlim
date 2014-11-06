#include "responseitem.h"

ResponseItem::ResponseItem(QString id, QString response)
  :response(response),
  id(id)
{
}

QString ResponseItem::serialize()
{
    QString res;
    res = res.sprintf("[%06d:%06d:%s:%06d:%s:]", 2, id.length(), id.toUtf8().data(), response.length(), response.toUtf8().data());
    return res;
}
