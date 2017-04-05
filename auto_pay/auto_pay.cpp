#include "auto_pay.h"
#include "cwebhandler.h"


Auto_pay::Auto_pay()
{
    //qDebug()<<"sdfdddddddddddddddddddddddddddddddddddddddd";
    m_pWebHandler = new CWebHandler(0);
}

Auto_pay::~Auto_pay()
{
    //qDebug()<<"sdffffffffffffffffffffffffffffffffffff";
    if (NULL != m_pWebHandler)
    {
        delete m_pWebHandler;
        m_pWebHandler = NULL;
    }
}

void Auto_pay::showWidget()
{
    return m_pWebHandler->showWidget();
}

int Auto_pay::loadUrl(QString url)
{
    return m_pWebHandler->loadUrl(url);
}

QString Auto_pay::getPayPage()
{
    return m_pWebHandler->getPayPage();
}
int Auto_pay::submitGraphVerify(QString graphVerify)
{
    return m_pWebHandler->submitGraphVerify(graphVerify);
}
int Auto_pay::submitPhoneNumVerify(QString phoneNum)
{
    return m_pWebHandler->submitPhoneNumVerify(phoneNum);
}
int Auto_pay::submitPayForm(QString verifyCode)
{
    return m_pWebHandler->submitPayForm(verifyCode);
}
void Auto_pay::window_join(int time)
{
    return m_pWebHandler->window_join(time);
}
void Auto_pay::shutDown()
{
    return m_pWebHandler->shutDown();
}
