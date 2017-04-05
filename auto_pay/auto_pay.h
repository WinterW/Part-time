#ifndef AUTO_PAY_H
#define AUTO_PAY_H

#include "auto_pay_global.h"
class CWebHandler;
class AUTO_PAYSHARED_EXPORT Auto_pay
{
private:
    CWebHandler* m_pWebHandler;
public:
    Auto_pay();
    ~Auto_pay();
    void showWidget();
    int loadUrl(QString url);
    QString getPayPage();
    int submitGraphVerify(QString graphVerify);
    int submitPhoneNumVerify(QString phoneNum);
    int submitPayForm(QString verifyCode);
    void window_join(int time);
    void shutDown();
};

#endif // AUTO_PAY_H
