#include <QTimer>
#include <QDateTime>
#include <QtGui/QApplication>
#include <QCoreApplication>
#include <QtGui/QMouseEvent>
#include <QtWebKit/QWebFrame>
#include "cwebhandler.h"
#include "comm.h"
#include "cwebpage.h"
#include "cnetworkaccessmanager.h"

CWebHandler::CWebHandler(QWidget *parent):QMainWindow(parent)
{
    m_iUrlNum = 0;
    inspector= new QWebInspector();
    browser = new QWebView(parent);
    browser->setPage(new CWebPage());
    browser->setGeometry(0, 0, 10, 10);
    browser->setTextSizeMultiplier(0.5);
    inspector->setPage(browser->page());

    browser->setAttribute(Qt::WA_DeleteOnClose,true);
    browser->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
    browser->settings()->setAttribute(QWebSettings::FrameFlatteningEnabled, true);
    browser->settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows, true);
    browser->settings()->setAttribute(QWebSettings::AutoLoadImages, true);
    browser->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    browser->settings()->setAttribute(QWebSettings::JavaEnabled, true);
    browser->settings()->setAttribute(QWebSettings::DnsPrefetchEnabled, true);
    browser->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    browser->settings()->setAttribute(QWebSettings::LocalContentCanAccessFileUrls, true);
    browser->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
    //browser.page().setLinkDelegationPolicy(QWebPage.LinkDelegationPolicy.DelegateAllLinks);
    browser->page()->setNetworkAccessManager(new CNetWorkAccessManager());
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
    QObject::connect(browser, SIGNAL(loadStarted(bool)), this, SLOT(loadStarted()));
    QObject::connect(browser, SIGNAL(loadProgress(bool)), this, SLOT(loadProgress()));
    QObject::connect(browser, SIGNAL(urlChanged(bool)), this, SLOT(urlChanged(QUrl)));
    QObject::connect(browser, SIGNAL(loadFinished(bool)), this, SLOT(loadDone()));
    QObject::connect(m_load_timer1, SIGNAL(timeout()), this, SLOT(timeOut()));
    QObject::connect(m_load_timer2, SIGNAL(timeout()), this, SLOT(timeOut()));
    QObject::connect(browser->page()->networkAccessManager(), SIGNAL(finished()), this, SLOT(HttpResponseFinished(QNetworkReply)), Qt::AutoConnection);
}

CWebHandler::~CWebHandler()
{
    QObject::disconnect(browser, SIGNAL(loadStarted(bool)), this, SLOT(loadStarted()));
    QObject::disconnect(browser, SIGNAL(loadProgress(bool)), this, SLOT(loadProgress()));
    QObject::disconnect(browser, SIGNAL(urlChanged(bool)), this, SLOT(urlChanged(QUrl)));
    QObject::disconnect(browser, SIGNAL(loadFinished(bool)), this, SLOT(loadDone()));
    QObject::disconnect(m_load_timer1, SIGNAL(timeout()), this, SLOT(timeOut()));
    QObject::disconnect(m_load_timer2, SIGNAL(timeout()), this, SLOT(timeOut()));
    QObject::disconnect(browser->page()->networkAccessManager(), SIGNAL(finished()), this, SLOT(HttpResponseFinished(QNetworkReply)));
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

void CWebHandler::urlChanged(QUrl url)
{
    m_strDestUrl = url.toString();
    //logger.debug("Url changed to: " + m_strDestUrl);
}

void CWebHandler::loadStarted()
{
    //logger.debug("Starting to load: " + m_strLoadingUrl);
    //statusBar().showMessage("Starting to load: " + m_strLoadingUrl);
}

void CWebHandler::loadDone()
{
    //browser->page()->mainFrame().evaluateJavaScript(jQuery);
    //browser->page()->mainFrame().evaluateJavaScript(css3);
    //browser->page()->mainFrame().evaluateJavaScript(html5);
    //logger.debug("Loading done...");
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
int CWebHandler::inputGraphicVerification(QString graphVerify){
    QWebElement input = findTagElement(GRAPHIC_VERIFICATION);
    return inputStrToElement(graphVerify, input);
}

int CWebHandler::inputVerificationCode(QString verifyCode){
    QWebElement input = findTagElement(VERIFICATION_CODE);
    return inputStrToElement(verifyCode, input);
}

int CWebHandler::inputPhoneNum(QString phoneNum){
    QWebElement input = findTagElement(PHONE_NUM);
    return inputStrToElement(phoneNum, input);
}

int  CWebHandler::inputStrToElement(QString str, QWebElement input){
    /*
        if(input.geometry().width() < WIDGET_WIDTH_MIN_VALUE || input.geometry().height() < WIDGET_HEIGHT_MIN_VALUE)
        {
            logger.error("Input element error.");
            logger.info("width:" + input.geometry().width() + " heigth" + input.geometry().height());
            return -1;
        }
        */
    //logger.info("width:" + input.geometry().width() + " heigth" + input.geometry().height());
    getAndClickInputPos(input);
    mdelay(10);
    input.evaluateJavaScript("this.value += \"" + str + "\"");
    return 0;
}

void CWebHandler::getAndClickInputPos(QWebElement &input){
    int input_width  = input.geometry().width();
    int input_height = input.geometry().height();
    int input_click_x = input.geometry().left() + INPUT_TEXT_WIDTH_BOUND + (rand() % (input_width  - INPUT_TEXT_WIDTH_BOUND));
    int input_click_y = input.geometry().top()  + INPUT_TEXT_HEIGHT_BOUND + (rand() % (input_height - INPUT_TEXT_HEIGHT_BOUND));
    input.evaluateJavaScript("this.value = \"\"");
    QPoint pos = QPoint(input_click_x, input_click_y);

    QMouseEvent event0(QEvent::MouseButtonPress, pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QApplication::sendEvent(browser->page(), &event0);
    QMouseEvent event1(QEvent::MouseButtonRelease, pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QApplication::sendEvent(browser->page(), &event1);
    QApplication::processEvents();
}

QWebElement CWebHandler::findTagElement(QString tagStr)
{
    QWebElement dom, input;
    dom = browser->page()->mainFrame()->documentElement();
    input = dom.findFirst(tagStr);
    return input;
}

void CWebHandler::clickButton(QWebElement btn)
{
    int scroll_height = browser->page()->mainFrame()->scrollPosition().y();
    QRect btnRect = btn.geometry();
    int width = btnRect.width();
    int height = btnRect.height();
    int btn_x = btnRect.left() + (rand() % ( width - BUTTON_ENSURE_INLINE_RANGE_MEASURE ) ) + BUTTON_MISTAKE_REPAIR_START_MEASURE;
    int btn_y = btnRect.top()  + (rand() % ( height - BUTTON_ENSURE_INLINE_RANGE_MEASURE ) ) - scroll_height + BUTTON_MISTAKE_REPAIR_START_MEASURE;
    QPoint pos(btn_x, btn_y);
    //logger.info("Point_x:" + btn_x + " Point_y:" + btn_y);
    QMouseEvent event0(QEvent::MouseButtonPress, pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QApplication::sendEvent(browser->page(), &event0);
    QMouseEvent event1(QEvent::MouseButtonRelease, pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QApplication::sendEvent(browser->page(), &event1);
    QApplication::processEvents();
}

void CWebHandler::clickConfirmBtn()
{
    QWebElement btn = findTagElement(CONFIRM_BUTTON);
    clickButton(btn);
    mdelay(10);
}

void CWebHandler::clickGetVerifyCodeBtn()
{
    QWebElement btn = findTagElement(GET_VERIFY_CODE_BUTTON);
    clickButton(btn);
    mdelay(10);
}

void CWebHandler::clickCommitBtn()
{
    mdelay(1000);
    QWebElement btn = findTagElement(COMMIT_BUTTON);
    clickButton(btn);
    mdelay(10);
    //browser.page().mainFrame().evaluateJavaScript("checkSmsCode();");
}

void CWebHandler::clickConfirmPayBtn()
{
    mdelay(1000);
    QWebElement btn = findTagElement(CONFIRM_PAY_BUTTON);
    clickButton(btn);
    mdelay(10);
    //browser.page().mainFrame().evaluateJavaScript("window.location.href = \'http://www.baidu.com\';");
}

void CWebHandler::clickConfirmSuccessBtn()
{
    mdelay(1000);
    QWebElement btn = findTagElement(CONFIRM_PAY_SUCCESS_BUTTON);
    //this.mdelay(3000);
    clickButton(btn);
    //browser.page().mainFrame().evaluateJavaScript("window.location.href = \'http://www.baidu.com\';");
}

void CWebHandler::loadStarUrl(QString url){
    m_strStartUrl = url;
    m_strLoadingUrl = m_strStartUrl;
    browser->load(url);
    mdelay(100);
}

void CWebHandler::loadDestUrl(QString url)
{
    m_strDestUrl = url;
    m_strStartUrl = m_strDestUrl;
    browser->load(url);
    mdelay(10);
}

/************************************reserved interface***************************************************/
void CWebHandler::setTimeOut(int time){
    m_iTimeOut = time;
}

int CWebHandler::inputStrToElement(QString str, QWebElement dom, QString strTag){
    QWebElement input;
    input = dom.findFirst(strTag);
    /*
        if(input.geometry().width() < WIDGET_WIDTH_MIN_VALUE || input.geometry().height() < WIDGET_HEIGHT_MIN_VALUE)
        {
            logger.error("Input element error.");
            return -1;
        }
        */
    return inputStrToElement(str, input);
}


/*****************************************interface*****************************************************/
void CWebHandler::showWidget()
{
    this->show();
    QApplication::processEvents();
    mdelay(10);
    //logger.info("tttttttttttt");
    //browser.page().mainFrame().evaluateJavaScript("window.location.href = \'http://www.baidu.com\';");
}
int CWebHandler::loadUrl(QString url)
{
    QString strReplyContent1;

    m_load_timer1->setSingleShot(true);
    m_load_timer1->start(m_iTimeOut);
    loadStarUrl(url);
    m_eventLoop->exec();
    if(START_URL_LOAD_SUCCESSED == m_EnUrlLoadStatus){
        strReplyContent1 = browser->page()->mainFrame()->documentElement().toPlainText();

    }
    else if (START_URL_LOAD_FAILED == m_EnUrlLoadStatus){
        //logger.error("Start url load failed.");
        return -1;
    }
    else{
        //logger.error("Unknown start url Loading status.");
        return -1;
    }


    //this.open("http://223.111.8.142:8080/migunetsdk/webJs/frame.html?netId=cc5be2d06bfa401ebc7db42de4ce7504&umark=Common");

    m_load_timer2->setSingleShot(true);
    m_load_timer2->start(m_iTimeOut);
    loadDestUrl(strReplyContent1);
    m_eventLoop->exec();
    if(DEST_URL_LOAD_SUCCESSED == m_EnUrlLoadStatus){
        m_strPayPage = browser->page()->mainFrame()->documentElement().toOuterXml();
    }
    else if (DEST_URL_LOAD_FAILED == m_EnUrlLoadStatus){
        //logger.error("Dest url load failed.");
        return -1;
    }
    else{
        //logger.error("Unknown dest url Loading status.");
        return -1;
    }

    return 0;
}
QString CWebHandler::getPayPage()
{
    //return m_strPayPage;
    return browser->page()->mainFrame()->documentElement().toOuterXml();
}

int CWebHandler::submitGraphVerify(QString graphVerify)
{
    int iRet = 0;
    iRet = inputGraphicVerification(graphVerify);
    if(iRet != 0){
        //logger.error("Input graphic verification error.");
        iRet = -1;
    }
    clickConfirmBtn();
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
    clickGetVerifyCodeBtn();
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
    clickCommitBtn();

    clickConfirmSuccessBtn();

    return 0;
}

void CWebHandler::shutDown()
{
    //QApplication.shutdown();
    ;
}

