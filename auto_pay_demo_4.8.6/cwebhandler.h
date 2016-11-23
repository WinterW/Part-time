#ifndef CWEBHANDLER_H
#define CWEBHANDLER_H
#include <QtWebKit/QWebView>
#include <QtWebKit/QWebInspector>
#include <QtWebKit/QWebElement>
#include <QtGui/QMainWindow>
#include <QEventLoop>
#include "comm.h"
class CWebHandler : public QMainWindow
{
    Q_OBJECT
public:
    explicit CWebHandler(QWidget *parent = 0);
    virtual ~CWebHandler();
    void mdelay( int millisecondsToWait );
    
signals:
    
public slots:
    void timeOut();
    void urlChanged(QUrl url);
    void loadStarted();
    void loadDone();
    void loadProgress(int x);
    void HttpResponseFinished(QNetworkReply* reply);
private:
    int m_iUrlNum;
    QWebView *browser;
    QWebInspector *inspector;
    QString m_strStartUrl;
    QString m_strDestUrl;
    QString m_strPayPage;
    QString m_strLoadingUrl;
    int m_iTimeOut;
    QTimer *m_load_timer1;
    QTimer *m_load_timer2;
    EnUrlLoadStatus m_EnUrlLoadStatus;
    QEventLoop *m_eventLoop;
    QString jQuery;
    QString css3;
    QString html5;
private:/******************************************inner function***************************************/
    int inputGraphicVerification(QString graphVerify);
    int inputVerificationCode(QString verifyCode);
    int inputPhoneNum(QString phoneNum);
    int  inputStrToElement(QString str, QWebElement input);
    void getAndClickInputPos(QWebElement &input);
    QWebElement findTagElement(QString tagStr);
    void clickButton(QWebElement btn);
    void clickCommitBtn();
    void clickConfirmPayBtn();
    void clickConfirmBtn();
    void clickGetVerifyCodeBtn();
    void clickConfirmSuccessBtn();
    void loadStarUrl(QString url);
    void loadDestUrl(QString url);
    void open(QString url);
    /************************************reserved interface***************************************************/
    void setTimeOut(int time);
    int inputStrToElement(QString str, QWebElement dom, QString strTag);
public:
    void showWidget();
    int loadUrl(QString url);
    QString getPayPage();
    int submitGraphVerify(QString graphVerify);
    int submitPhoneNumVerify(QString phoneNum);
    int submitPayForm(QString verifyCode);
    void shutDown();
};

#endif // CWEBHANDLER_H
