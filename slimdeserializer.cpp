/** Quick Port from Java SlimDeserializer
*/

/* this class is called from SlimIncomingHandler when data has been received from Fitnesse server
   its job is to make up a list with command/class/cunctions that shall be executed
*/

#include <QDebug>
#include <iostream>

#include "syntaxerror.h"
#include "slimdeserializer.h"



// ================================================================= //
SlimDeserializer::SlimDeserializer(QString input, QObject *parent) :
    QObject(parent),
    index(0),
    serialized(input),
    subser(),
    result()
{
}

SlimDeserializer::~SlimDeserializer()
{
    qDebug() << "~SlimDeserialize 1";
    foreach (Item *item, result)
    {
        delete item;
    }
    result.clear();

    qDebug() << "~SlimDeserialize 2";
    foreach (SlimDeserializer *sub, subser)
    {
        delete sub;
    }
    subser.clear();
}

QList<Item*> &SlimDeserializer::deserialize()
{
        ///  try {
    qDebug() << "deserialize" << serialized;
    checkSerializedStringIsValid();
    deserializeString();
    qDebug() << (result);
    // } catch (...) {
   // throw "Exception";
  //}
    return result;
}

void SlimDeserializer::checkSerializedStringIsValid()
{
  if (serialized == "")
    throw SyntaxError("Can't deserialize empty");
  else if (serialized.length() == 0)
    throw SyntaxError("Can't deserialize empty string");
}

QList<Item*> &SlimDeserializer::deserializeString()
{
  checkForOpenBracket();
  deserializeList();
  checkForClosedBracket();
  return result;
}

void SlimDeserializer::checkForClosedBracket()
{
  if (!charsLeft() || getChar() != ']')

    throw SyntaxError(QString("Serialized list has no ending ] at position %1 char was %2 charsLeft %3").arg(index-1).arg(serialized[index-1].toLatin1()).arg(charsLeft()));
}

bool SlimDeserializer::charsLeft()
{
  return index < serialized.length();
}

void SlimDeserializer::checkForOpenBracket()
{
  if (getChar() != '[')
    throw SyntaxError(QString("Can't find open bracket position %1").arg(index-1));
}

QList<Item*> &SlimDeserializer::deserialize(QString substring)
{
    SlimDeserializer *subs;
    subs = new SlimDeserializer(substring, this);
    subser.append(subser);
    return subs->deserialize();
}

QList<Item*> &SlimDeserializer::deserializeList()
{
  int itemCount = getLength();
  for (int i = 0; i < itemCount; i++)
    deserializeItem();

  return result;
}

void SlimDeserializer::deserializeItem()
{
  int itemLength = getLength();
  QString str = getString(itemLength);
  QList<Item*> sublist = maybeReadList(str);
  if (sublist.isEmpty()) // if list empty insert string
    result.append(new Item(str)); // insert as string since its not a list
  else //
    result.append(new Item(sublist)); // insert list
}

/**
 * @return the string parsed as a list if possible, null otherwise
 */

QList<Item*> &SlimDeserializer::maybeReadList(QString string)
{
  if (string.trimmed()=="" || !string.startsWith("["))
    return nullList;

  qDebug() << "subserialize" << string;
  return deserialize(string);

  try {
    return deserialize(string);
  } catch (...) {
    qDebug() << "exception in maybeReadList";
    return nullList;
  }
}

QString SlimDeserializer::getString(int length) {
  QString result = serialized.mid(index, length);
  index += length;
  checkForColon("String");
  return result;
}

void SlimDeserializer::checkForColon(QString itemType)
{
  if (getChar() != ':')
    throw SyntaxError((itemType + " in serialized list not terminated by colon. index is %1").arg(index));
}

QChar SlimDeserializer::getChar()
{
//  qDebug() << "wuut " << serialized << QString("%1").arg(serialized[index].toLatin1()) << " index is " << index;
  return serialized[index++];
}

int SlimDeserializer::getLength()
{
  try {
    return tryGetLength();
  } catch (...) {
    throw "getLength exception";
  }
}

int SlimDeserializer::tryGetLength() {
  int lengthSize = 6;
  QString lengthString = serialized.mid(index, lengthSize);
  int length = lengthString.toInt();
  index += lengthSize;

  int next;
  while ((next = maybeReadDigit()) != -1)
        length = length * 10 + next;

  checkForColon("Length");
  return length;

}

int SlimDeserializer::maybeReadDigit()
{
  QChar next = serialized[index];
  if (next.isDigit()) {
    index++;
    return next.digitValue();
  }

  return -1;
}


