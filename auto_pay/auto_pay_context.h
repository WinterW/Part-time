#ifndef AUTO_PAY_CONTEXT_H
#define AUTO_PAY_CONTEXT_H

#include <QtWidgets/QApplication>
#include "auto_pay_global.h"

class AUTO_PAYSHARED_EXPORT Auto_pay_context:public QApplication
{
public:
    Auto_pay_context(int &argc, char **argv);
    ~Auto_pay_context(){}
};

#endif // AUTO_PAY_CONTEXT_H
