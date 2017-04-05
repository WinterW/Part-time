#include <QTimer>
#include <QDateTime>
#include <QtWidgets/QApplication>
#include <QCoreApplication>
#include <QtWebEngineWidgets/QWebEngineSettings>
#include <QtNetwork/QNetworkReply>
#include <QtGui/QMouseEvent>
//#include <QtTest/qtest.h>
#include "cwebhandler.h"
#include "comm.h"

CWebHandler::CWebHandler(QWidget *parent):QMainWindow(parent)
{
    //qDebug()<<"eeeeeeeeeeeeeeeeeeeeeeeeeeeeeee";
    m_iUrlNum = 0;
    //inspector= new QWebInspector();
    browser = new QWebEngineView(parent);
    page = new CWebPage();
    browser->setPage(page);
    browser->setGeometry(0, 0, 10, 10);
    browser->setZoomFactor(0.5);
    //browser->setTextSizeMultiplier(0.5);
    //inspector->setPage(browser->page());

    browser->setAttribute(Qt::WA_DeleteOnClose,true);
    browser->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    //browser->settings()->setAttribute(QWebEngineSettings::FrameFlatteningEnabled, true);
    browser->settings()->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows, true);
    browser->settings()->setAttribute(QWebEngineSettings::AutoLoadImages, true);
    browser->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
    //browser->settings()->setAttribute(QWebEngineSettings::JavaEnabled, true);
    //browser->settings()->setAttribute(QWebEngineSettings::DnsPrefetchEnabled, true);
    //browser->settings()->setAttribute(QWebEngineSettings::DeveloperExtrasEnabled, true);
    browser->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessFileUrls, true);
    browser->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);;
    browser->setFixedSize(400,600);
    setCentralWidget(browser);
    //statusBar().show();

    //setWindowTitle("copyright ©fssb");
    //setWindowIcon(new QIcon("classpath:com/trolltech/images/qt-logo.png"));

    m_eventLoop  = new QEventLoop();
    m_load_timer1 = new QTimer();
    m_load_timer2 = new QTimer();
    m_iTimeOut = 3000;
    //QObject::connect(m_webview->page(), SIGNAL(linkClicked(QUrl)), this, SLOT(LinkClick(QUrl)));
    //QObject::connect(m_network_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(HttpResponseFinished(QNetworkReply *)));
    QObject::connect(browser, SIGNAL(loadStarted()), this, SLOT(loadStarted()));
    QObject::connect(browser, SIGNAL(loadProgress(int)), this, SLOT(loadProgress(int)));
    //QObject::connect(browser, SIGNAL(urlChanged(QUrl)), this, SLOT(urlChanged(QUrl)));
    QObject::connect(browser, SIGNAL(loadFinished(bool)), this, SLOT(loadDone(bool)));
    QObject::connect(m_load_timer1, SIGNAL(timeout()), this, SLOT(timeOut()));
    QObject::connect(m_load_timer2, SIGNAL(timeout()), this, SLOT(timeOut()));
    //QObject::connect(browser->page()->networkAccessManager(), SIGNAL(finished()), this, SLOT(HttpResponseFinished(QNetworkReply)), Qt::AutoConnection);
}

CWebHandler::~CWebHandler()
{
    QObject::disconnect(browser, SIGNAL(loadStarted()), this, SLOT(loadStarted()));
    QObject::disconnect(browser, SIGNAL(loadProgress(int)), this, SLOT(loadProgress(int)));
    QObject::disconnect(browser, SIGNAL(urlChanged(QUrl)), this, SLOT(urlChanged(QUrl)));
    QObject::disconnect(browser, SIGNAL(loadFinished(bool)), this, SLOT(loadDone(bool)));
    QObject::disconnect(m_load_timer1, SIGNAL(timeout()), this, SLOT(timeOut()));
    QObject::disconnect(m_load_timer2, SIGNAL(timeout()), this, SLOT(timeOut()));
    //QObject::disconnect(browser->page()->networkAccessManager(), SIGNAL(finished()), this, SLOT(HttpResponseFinished(QNetworkReply)));
    if(browser != NULL) {delete browser;browser = NULL;}
    if(page != NULL){delete page; page = NULL;}
    if(m_eventLoop != NULL){delete m_eventLoop; m_eventLoop = NULL;}
    if(m_load_timer1 != NULL){delete m_load_timer1; m_load_timer1 = NULL;}
    if(m_load_timer2 != NULL){delete m_load_timer2; m_load_timer2 = NULL;}
}

void CWebHandler::mdelay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100);
    }
}
/************************************signal handler*************************************************/
void CWebHandler::timeOut()
{

    if ( m_load_timer1->isActive())
    {
        //logger.error("Shut up the QTimer1.");
        m_load_timer1->stop();
    }
    if ( m_load_timer2->isActive())
    {
        //logger.error("Shut up the QTimer2.");
        m_load_timer2->stop();
    }

    if(m_eventLoop->isRunning()){
        m_eventLoop->quit();
    }
}

void CWebHandler::urlChanged(QUrl &url)
{
    m_strDestUrl = url.toString();
    //logger.debug("Url changed to: " + m_strDestUrl);
}

void CWebHandler::loadStarted()
{
    //logger.debug("Starting to load: " + m_strLoadingUrl);
    //statusBar().showMessage("Starting to load: " + m_strLoadingUrl);
}

void CWebHandler::loadDone(bool result)
{
    //browser->page()->mainFrame().evaluateJavaScript(jQuery);
    //browser->page()->mainFrame().evaluateJavaScript(css3);
    //browser->page()->mainFrame().evaluateJavaScript(html5);
    qDebug()<<"Loading done..." << result;
    m_iUrlNum += 1;
    if (m_iUrlNum == 1){
        if(m_load_timer1->isActive())
        {
            //logger.debug("Shut up the QTimer1.");
            m_load_timer1->stop();
        }
        m_EnUrlLoadStatus = START_URL_LOAD_SUCCESSED;
    }else if(m_iUrlNum == 2){
        if(m_load_timer2->isActive())
        {
            //logger.debug("Shut up the QTimer2.");
            m_load_timer2->stop();
        }

        m_EnUrlLoadStatus = DEST_URL_LOAD_SUCCESSED;
    }

    if(m_eventLoop->isRunning()){
        m_eventLoop->quit();
    }
    //statusBar().showMessage("Loading done...");
}

void CWebHandler::loadProgress(int x)
{
    Q_UNUSED(x);
    //statusBar().showMessage("Loading: " + x + " %");
}

void CWebHandler::open(QString url) {

    if (url.indexOf("://") < 0)
        url = "http://" + url;
    QUrl link_url = QUrl(url);
    browser->load(link_url);
}

/*
    void CWebHandler::closeEvent(QCloseEvent event) {

    }

*/
void CWebHandler::HttpResponseFinished(QNetworkReply* reply)
{
    QUrl failed_url = reply->url();
    QString network_reply_url = failed_url.toString();
    QString debug_str;
    QString http_message = "";//reply.readAll().toString();

    debug_str = " reply_url["+ network_reply_url + "] http_response[" + http_message + "]";
    //logger.info(debug_str);
    return;
}
/******************************************inner function***************************************/
int CWebHandler::inputGraphicVerification(QString graphVerify)
{
    browser->page()->runJavaScript("document.getElementById('authCodeInput').value = " + graphVerify);
    mdelay(1000);
    return 0;
}

int CWebHandler::inputVerificationCode(QString verifyCode)
{
    browser->page()->runJavaScript("document.getElementById('CheckCode').value = " + verifyCode);
    mdelay(1000);
    return 0;
}

int CWebHandler::inputPhoneNum(QString phoneNum){
     browser->page()->runJavaScript("document.getElementById('msisdn').value = " + phoneNum);
    mdelay(1000);
     return 0;
}

bool CWebHandler::isJsFunctionExist(QString jsString)
{
    bool isTagExist = false;
    int loopCount = 0;
    while( !isTagExist && (loopCount++ < 3))
    {
        browser->page()->runJavaScript(jsString,
                                       [&isTagExist](const QVariant &result)
        {
            if( result.toString() == "function" )
                isTagExist = true;
        });
        mdelay(500);
    }

    return isTagExist;
}
int CWebHandler::clickConfirmBtn()
{
    bool isJsTagExist = true;
    isJsTagExist = isJsFunctionExist("typeof(checkImgCode)");
    if(!isJsTagExist)
    {
        return -1;
    }

    browser->page()->runJavaScript("checkImgCode();");
    mdelay(1000);

    /*check execute result*/
    isJsTagExist = isJsFunctionExist("typeof(checkImgCode)");
    if(!isJsTagExist)
    {
        return -1;
    }

    return 0;
}

int CWebHandler::clickGetVerifyCodeBtn()
{
    bool isJsTagExist = true;
    isJsTagExist = isJsFunctionExist("typeof(getCheckCode)");
    if(!isJsTagExist)
    {
        return -1;
    }

    browser->page()->runJavaScript("getCheckCode();");
    mdelay(1000);

    isJsTagExist = isJsFunctionExist("typeof(getCheckCode)");
    if(!isJsTagExist)
    {
        return -1;
    }
    return 0;
}

int CWebHandler::clickCommitBtn()
{
    bool isJsTagExist = true;
    isJsTagExist = isJsFunctionExist("typeof(checkSmsCode)");
    if(!isJsTagExist)
    {
        return -1;
    }

    browser->page()->runJavaScript("checkSmsCode()");
    mdelay(1000);

    isJsTagExist = isJsFunctionExist("typeof(checkSmsCode)");
    if(!isJsTagExist)
    {
        return -1;
    }

    return 0;
}

int CWebHandler::clickConfirmPayBtn()
{
//document.getElementById('payDetailTag').contentWindow.document.getElementById('okPay')
    //QString element = NULL;

    bool okPay_tag = false;
    int loopCount =0;
    while( !okPay_tag && (loopCount++ < 5))
    {
        browser->page()->runJavaScript("typeof(document.getElementById('frame').contentDocument.getElementById('okPay'))",
                                       [&okPay_tag](const QVariant &result)
        {
            //QString element = result.toString();
            //qDebug()<< element + "aa";
            if( result.toString() == "object" )
                okPay_tag = true;
        });
        mdelay(1000);
    }

    if(!okPay_tag)
    {
        return -1;
    }

    //mdelay(1000);
    browser->page()->runJavaScript("document.getElementById('frame').contentDocument.getElementById('okPay').click();");
    mdelay(3000);
    /*
    int start_x = 400;
    int start_y = 540;
    QPoint pos = QPoint(start_x, start_y);
    QTest::mouseClick(browser,Qt::LeftButton, Qt::NoModifier, QPoint(start_x, start_y), 10);

    mdelay(20000);
    start_x = 400;
    start_y = 550;
    pos = QPoint(start_x, start_y);
    QTest::mouseClick(this,Qt::LeftButton, Qt::NoModifier, QPoint(start_x, start_y), 10);\

    mdelay(20000);
    start_x = 400;
    start_y = 540;
    pos = QPoint(start_x, start_y);
    QTest::mouseClick(this,Qt::LeftButton, Qt::NoModifier, QPoint(start_x, start_y), 10);

    mdelay(20000);
    QTest::mouseClick(browser,Qt::LeftButton);
    */
    /*
    QMouseEvent moveToStartEvent = QMouseEvent(QEvent::MouseMove, pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QApplication::sendEvent(browser->page(), &moveToStartEvent);
    qDebug() << "move";
    mdelay(5000);
    QMouseEvent pressEvent = QMouseEvent(QEvent::MouseButtonPress, pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QApplication::sendEvent(browser->page(), &pressEvent);
    qDebug() << "press";
    mdelay(100);
    QMouseEvent releaseEvent = QMouseEvent(QEvent::MouseButtonRelease, pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QApplication::sendEvent(browser->page(), &releaseEvent);
    qDebug() << "release";
    */
    return 0;
}

int CWebHandler::clickConfirmSuccessBtn()
{
    //browser->page()->runJavaScript("checkSmsCode()");

    mdelay(100);
    return 0;
}

void CWebHandler::loadStarUrl(QString url){
    m_strStartUrl = url;
    m_strLoadingUrl = m_strStartUrl;
    browser->load(url);
}

void CWebHandler::loadDestUrl(QString url)
{
    m_strDestUrl = url;
    m_strStartUrl = m_strDestUrl;
    browser->load(url);
}
/*****************************************interface*****************************************************/

/************add for slide *******************************/
/*
void dragAndDrop(int start_x, int start_y, int end_x, int end_y)
{

    QPoint start_pos = QPoint(start_x, start_y);
    QMouseEvent moveToStartEvent = QMouseEvent(QEvent::MouseMove, start_pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QApplication.sendEvent(browser->page(), moveToStartEvent);
    QMouseEvent pressEvent = QMouseEvent(QEvent::MouseButtonPress, start_pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QApplication.sendEvent(browser->page(), pressEvent);


    QPoint end_pos = QPoint(start_x, start_y);
    QMouseEvent moveToEndEvent = QMouseEvent(QEvent::MouseMove, end_pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QApplication.sendEvent(browser->page(), moveToEndEvent);

    QMouseEvent event1 = QMouseEvent(QEvent::MouseButtonRelease, end_pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QApplication.sendEvent(browser->page(), event1);

}
*/
void CWebHandler::showWidget()
{
    this->show();
    qDebug()<<"webhandler show widget";
    QCoreApplication::processEvents();
    mdelay(1000);
    //logger.info("tttttttttttt");
    //browser.page().mainFrame().evaluateJavaScript("window.location.href = \'http://www.baidu.com\';");
}
int CWebHandler::loadUrl(QString url)
{
    QString strReplyContent1 = "";

    m_load_timer1->setSingleShot(true);
    m_load_timer1->start(m_iTimeOut);
    loadStarUrl(url);
    m_eventLoop->exec();
    if(START_URL_LOAD_SUCCESSED == m_EnUrlLoadStatus)
    {
        //strReplyContent1 = browser->page()->toPlainText();
        browser->page()->toPlainText([&strReplyContent1](const QString &result){ strReplyContent1=result; });
        qDebug()<<strReplyContent1;
    }
    else if (START_URL_LOAD_FAILED == m_EnUrlLoadStatus){
        qDebug()<< "Start url load failed.";
        return -1;
    }
    else{
        qDebug()<<"Unknown start url Loading status.";
        return -1;
    }
    // *textEdit must remain valid until the functor is called.
    //this.open("http://223.111.8.142:8080/migunetsdk/webJs/frame.html?netId=cc5be2d06bfa401ebc7db42de4ce7504&umark=Common");
    QTime dieTime1 = QTime::currentTime().addMSecs( 5000 );
    while( QTime::currentTime() < dieTime1 )
    {
        if( strReplyContent1 != "")
        {
            break;
        }
        else
        {
            mdelay(1000);
        }
    }

    m_load_timer2->setSingleShot(true);
    m_load_timer2->start(m_iTimeOut);
    loadDestUrl(strReplyContent1);
    m_eventLoop->exec();
    if(DEST_URL_LOAD_SUCCESSED == m_EnUrlLoadStatus){
        //m_strPayPage = browser->page()->toHtml();
        browser->page()->toHtml([this](const QString &result){ this->m_strPayPage=result; });
    }
    else if (DEST_URL_LOAD_FAILED == m_EnUrlLoadStatus){
        //logger.error("Dest url load failed.");
        return -1;
    }
    else{
        //logger.error("Unknown dest url Loading status.");
        return -1;
    }

    QTime dieTime2 = QTime::currentTime().addMSecs( 5000 );
    while( QTime::currentTime() < dieTime2 )
    {

        if( m_strPayPage != "")
        {
            break;
        }
        else
        {
            mdelay(1000);
        }
    }

    bool migusdk_not_load = true;
    QTime dieTime3 = QTime::currentTime().addMSecs( 5000 );
    while( QTime::currentTime() < dieTime3 )
    {

        if(migusdk_not_load)
        {
            browser->page()->runJavaScript("typeof(migusdk)",
                                           [&migusdk_not_load](const QVariant &v){
                qDebug() << v.toString();
                if(v.toString() != "undefined")
                    migusdk_not_load = false;
            });
            break;
        }
        else
        {
            mdelay(1000);
        }
    }

    browser->setZoomFactor(qreal(0.5));
    return 0;
}
QString CWebHandler::getPayPage()
{
    return m_strPayPage;
    //return browser->page()->toHtml();
}

int CWebHandler::submitGraphVerify(QString graphVerify)
{
    mdelay(1000);
    int iRet = 0;
    iRet = inputGraphicVerification(graphVerify);
    if(iRet != 0){
        //logger.error("Input graphic verification error.");
        iRet = -1;
    }
    iRet = clickConfirmBtn();
    if(iRet !=0)
    {
        return -1;
    }

    mdelay(3000);
    int imgVerifyCodStatus = page->m_EnImgVerifyCodeStatus;
    page->m_EnImgVerifyCodeStatus = IMG_CODE_STATUS_INIT;
    if(imgVerifyCodStatus == IMG_CODE_STATUS_FAILED)
    {
        return -1;
    }
    else
    {
        return 0;
    }
    return 0;
}

int CWebHandler::submitPhoneNumVerify(QString phoneNum)
{
    int iRet = 0;
    iRet = inputPhoneNum(phoneNum);
    if(iRet != 0){
        //logger.error("Input phone num error.");
        iRet = -1;
    }
    iRet = clickGetVerifyCodeBtn();
    if(iRet !=0)
    {
        return -1;
    }
    mdelay(100);
    int phoneVerifyCodStatus = page->m_EnPhoneCodeStatus;
    page->m_EnPhoneCodeStatus = PHONE_CODE_STATUS_INIT;
    if(phoneVerifyCodStatus == PHONE_CODE_STATUS_FAILED)
    {
        return -1;
    }
    else
    {
        return 0;
    }

    return 0;
}

int CWebHandler::submitPayForm(QString verifyCode)
{
    int iRet = 0;
    inputVerificationCode(verifyCode);
    if(iRet != 0){
        //logger.error("Input verification code error.");
        iRet = -1;
    }

    iRet = clickCommitBtn();
    if(iRet !=0)
    {
        return -1;
    }
    mdelay(100);

    int smsVerifyCodStatus = SMS_CODE_STATUS_INIT;
    QTime dieTime = QTime::currentTime().addMSecs( 3000 );
    while( QTime::currentTime() < dieTime )
    {

        smsVerifyCodStatus = page->m_EnSmsVerifyCodeStatus;
        if( smsVerifyCodStatus != SMS_CODE_STATUS_INIT) {
            break;
        } else {
            mdelay(100);
        }
    }

    page->m_EnSmsVerifyCodeStatus = SMS_CODE_STATUS_INIT;
    if(smsVerifyCodStatus == SMS_CODE_STATUS_FAILED)
    {
        return -1;
    }

    mdelay(1000);

    iRet = clickConfirmPayBtn();
    if(iRet !=0)
    {
        return -1;
    }
    return 0;
}

void CWebHandler::shutDown()
{
    //QApplication.shutdown();
    this->close();
    ;
}

void CWebHandler::window_join(int time)
{
    mdelay(time);
}

