#include <QObject>
#include <QList>
#include <QString>
#include <QDebug>
#include <exception>

class Item:public QObject{
        QString dataString;
        QList<Item*> *items; // a list with items
    public:
        Item(QString data)
            :dataString(data),
              items(0)
        {}

        Item(QList<Item*>* data):dataString(),items(data){}
        void printDebug();
};

class SlimDeserializer : public QObject
{
    Q_OBJECT
    int index;
    QString serialized;
    QList<Item*>result;
  public:
    explicit SlimDeserializer(QString input, QObject *parent = 0);

    QList<Item*> *deserialize();
    QList<Item*> *deserialize(QString sub);
  private:
    void checkSerializedStringIsValid();

    void checkForClosedBracket();
    bool charsLeft();

    void checkForOpenBracket();
    QList<Item*> *deserializeString();
    QList<Item*> *deserializeList();

    void deserializeItem();

private:

    /**
     * @return the string parsed as a list if possible, null otherwise
     */

    QList<Item*> *maybeReadList(QString string);

    QString getString(int length);

    void checkForColon(QString itemType);

    QChar getChar();

    int getLength();

    int tryGetLength();

    int maybeReadDigit();
};
