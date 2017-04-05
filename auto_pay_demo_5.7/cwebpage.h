#ifndef CWEBPAGE_H
#define CWEBPAGE_H

#include <QtWebEngineWidgets/QWebEnginePage>
enum EnImgVerifyCodeStatus
{
    IMG_CODE_STATUS_FAILED = -1,
    IMG_CODE_STATUS_INIT = 0,
    IMG_CODE_STATUS_SUCCESSED = 1
};

enum EnPhoneCodeStatus
{
    PHONE_CODE_STATUS_FAILED = -1,
    PHONE_CODE_STATUS_INIT = 0,
    PHONE_CODE_STATUS_SUCCESSED = 1
};

enum EnSmsVerifyCodeStatus
{
    SMS_CODE_STATUS_FAILED = -1,
    SMS_CODE_STATUS_INIT = 0,
    SMS_CODE_STATUS_SUCCESSED = 1
};
class CWebPage : public QWebEnginePage
{
public:
    CWebPage(QObject *parent = 0);
    ~CWebPage();
public:

    volatile EnImgVerifyCodeStatus m_EnImgVerifyCodeStatus;
    volatile EnPhoneCodeStatus m_EnPhoneCodeStatus;
    volatile EnSmsVerifyCodeStatus m_EnSmsVerifyCodeStatus;
protected:
    QString userAgentForUrl(QUrl url);
    void javaScriptAlert(const QUrl &securityOrigin, const QString &msg);
    bool javaScriptConfirm(const QUrl &securityOrigin, const QString &msg);
    
};

#endif // CWEBPAGE_H
