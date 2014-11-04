#include "item.h"
#include "commandexecuter.h"

CommandExecuter::CommandExecuter(QList <Item*>&ref)
    :command(ref.at(0)->dataString)
{
    if (command == "make")
    {

    }
}
