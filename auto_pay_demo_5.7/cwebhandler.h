#ifndef CWEBHANDLER_H
#define CWEBHANDLER_H
#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWidgets/QMainWindow>
#include <QEventLoop>
#include "comm.h"
#include "cwebpage.h"
class CWebHandler : public QMainWindow
{
    Q_OBJECT
public:
    explicit CWebHandler(QWidget *parent = 0);
    virtual ~CWebHandler();
    void mdelay( int millisecondsToWait );
    /*
    struct SetPlainTextFunctor {
        SetPlainTextFunctor(){ }
        void operator()(const QString &result) {
            m_strPayPage = result;
        }
    };
    */
signals:
    
public slots:
    void timeOut();
    void urlChanged(QUrl &url);
    void loadStarted();
    void loadDone(bool result);
    void loadProgress(int x);
    void HttpResponseFinished(QNetworkReply* reply);
private:
    int m_iUrlNum;
    QWebEngineView *browser;
    CWebPage *page;
    QString m_strStartUrl;
    QString m_strDestUrl;
    QString m_strPayPage;
    QString m_strLoadingUrl;
    int m_iTimeOut;
    QTimer *m_load_timer1;
    QTimer *m_load_timer2;
    EnUrlLoadStatus m_EnUrlLoadStatus;
    QEventLoop *m_eventLoop;
private:/******************************************inner function***************************************/
    int inputGraphicVerification(QString graphVerify);
    int inputVerificationCode(QString verifyCode);
    int inputPhoneNum(QString phoneNum);
    int clickCommitBtn();
    int clickConfirmPayBtn();
    int clickConfirmBtn();
    int clickGetVerifyCodeBtn();
    int clickConfirmSuccessBtn();
    bool isJsFunctionExist(QString jsString);
public:
    void loadStarUrl(QString url);
    void loadDestUrl(QString url);
    void open(QString url);
    /************************************reserved interface***************************************************/
    void setTimeOut(int time);
public:
    void showWidget();
    int loadUrl(QString url);
    QString getPayPage();
    int submitGraphVerify(QString graphVerify);
    int submitPhoneNumVerify(QString phoneNum);
    int submitPayForm(QString verifyCode);
    void window_join(int time = 10);
    void shutDown();
};

#endif // CWEBHANDLER_H
