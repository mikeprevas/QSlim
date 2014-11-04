#include <QObject>
#include <QList>
#include <QString>
#include <QDebug>
#include <exception>
#include "item.h"

class SlimDeserializer : public QObject
{
    Q_OBJECT
    int index;
    QString serialized;
    QList<SlimDeserializer*>subser;
    QList<Item*>result;
    QList<Item*>nullList;
  public:
    explicit SlimDeserializer(QString input, QObject *parent = 0);
    ~SlimDeserializer();

    QList<Item*> &deserialize();
    QList<Item*> &deserialize(QString sub);
    int getLength();
  private:
    void checkSerializedStringIsValid();

    void checkForClosedBracket();
    bool charsLeft();

    void checkForOpenBracket();
    QList<Item*> &deserializeString();
    QList<Item*> &deserializeList();

    void deserializeItem();
    int tryGetLength();

private:

    /**
     * @return the string parsed as a list if possible, null otherwise
     */

    QList<Item*> &maybeReadList(QString string);

    QString getString(int length);

    void checkForColon(QString itemType);

    QChar getChar();



    int maybeReadDigit();
};
