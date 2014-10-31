#ifndef SYNTAXERROR_H
#define SYNTAXERROR_H
using namespace std;
class SyntaxError{
public:
        SyntaxError(QString whut) {cout << whut.toStdString() << endl; }
};

#endif // SYNTAXERROR_H
