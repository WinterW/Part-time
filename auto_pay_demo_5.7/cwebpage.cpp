
#include "cwebpage.h"
CWebPage::CWebPage(QObject *parent):QWebEnginePage(parent)
{
    m_EnImgVerifyCodeStatus = IMG_CODE_STATUS_INIT;
    m_EnPhoneCodeStatus = PHONE_CODE_STATUS_INIT;
    m_EnSmsVerifyCodeStatus = SMS_CODE_STATUS_INIT;
}

CWebPage::~CWebPage()
{

}

QString CWebPage::userAgentForUrl(QUrl url)
{
    url = url;
    return "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.71 Safari/537.36";
}

void CWebPage::javaScriptAlert(const QUrl &securityOrigin, const QString &msg)
{
    Q_UNUSED(securityOrigin);
    qDebug() << msg;
    if(msg.indexOf("图形") >= 0)
    {
        m_EnImgVerifyCodeStatus = IMG_CODE_STATUS_FAILED;
        qDebug() << "Graph code verify failed.";
    }
    else if(msg.indexOf("手机") >= 0)
    {
        m_EnPhoneCodeStatus = PHONE_CODE_STATUS_FAILED;
        qDebug() << "Phone num verify failed.";
    }
    else if(msg.indexOf("短信") >= 0)
    {
        m_EnSmsVerifyCodeStatus = SMS_CODE_STATUS_FAILED;
        qDebug() << "Sms verify code failed.";
    }

}
bool CWebPage::javaScriptConfirm(const QUrl &securityOrigin, const QString &msg)
{
    Q_UNUSED(securityOrigin);
    qDebug() << msg ;
    return true;
}


