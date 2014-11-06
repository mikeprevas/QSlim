#include <QObject>
#include <QList>
#include <QString>
#include <QDebug>
#include <exception>
#include "instruction.h"

class SlimDeserializer : public QObject
{
    Q_OBJECT
    int index;
    QString serialized;
    QList<SlimDeserializer*>subser;
    QList<Instruction*>result;
    QList<Instruction*>nullList;
  public:
    explicit SlimDeserializer(QString input, QObject *parent = 0);
    ~SlimDeserializer();

    QList<Instruction*> &deserialize();
    QList<Instruction*> &deserialize(QString sub);
    int getLength();
  private:
    void checkSerializedStringIsValid();

    void checkForClosedBracket();
    bool charsLeft();

    void checkForOpenBracket();
    QList<Instruction*> &deserializeString();
    QList<Instruction*> &deserializeList();

    void deserializeInstruction();
    int tryGetLength();

private:

    /**
     * @return the string parsed as a list if possible, null otherwise
     */

    QList<Instruction*> &maybeReadList(QString string);

    QString getString(int length);

    void checkForColon(QString InstructionType);

    QChar getChar();



    int maybeReadDigit();
};
