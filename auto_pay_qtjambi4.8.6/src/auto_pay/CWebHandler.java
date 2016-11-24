package auto_pay;

import com.trolltech.qt.core.*;
import com.trolltech.qt.core.Qt.ConnectionType;
import com.trolltech.qt.gui.*;
import com.trolltech.qt.webkit.*;
import com.trolltech.qt.network.*;

import org.apache.logging.log4j.LogManager;  
import org.apache.logging.log4j.Logger;  
  
/*
        Logger logger = LogManager.getLogger(Test01.class.getName());   
        logger.trace("trace");  
        logger.debug("debug");  
        logger.info("hello");  
        logger.warn("warn");  
        logger.error("error");  
        logger.fatal("fatal");  
*/
//@com.trolltech.examples.QtJambiExample(name="Hello WebKit")
public final class CWebHandler extends QMainWindow {

	private static final Logger logger = LogManager.getLogger();  
    private QWebView browser;
    QWebInspector inspector = new QWebInspector();
    private String m_strStartUrl;
	private String m_strDestUrl;
    private String m_strPayPage;
    private String m_strLoadingUrl;
    private int m_iTimeOut;
    private QTimer m_load_timer1;
    private QTimer m_load_timer2;
    private EnUrlLoadStatus m_EnUrlLoadStatus;
    private QEventLoop m_eventLoop;
    private String jQuery;
    private String css3;
    private String html5;
    
    public static final int INPUT_TEXT_WIDTH_BOUND = 5;
    public static final int INPUT_TEXT_HEIGHT_BOUND = 2;
    public static final int BUTTON_MISTAKE_REPAIR_START_MEASURE = 2;
    public static final int BUTTON_ENSURE_INLINE_RANGE_MEASURE = 4;
    public static final int WIDGET_WIDTH_MIN_VALUE = 200;
    public static final int WIDGET_HEIGHT_MIN_VALUE = 100;
    
    public static final String GRAPHIC_VERIFICATION = "div input#authCodeInput._text";
    public static final String VERIFICATION_CODE = "div input#CheckCode._text";
    public static final String PHONE_NUM = "div input#msisdn._text";
    public static final String CONFIRM_BUTTON = "div input#authCodeSwitch._button";
    public static final String GET_VERIFY_CODE_BUTTON = "div input#sendSMS._button";
    public static final String COMMIT_BUTTON = "div.btn a.c";
    public static final String CONFIRM_PAY_BUTTON = "div#payDetail.payDetail.onkey a";
    public static final String CONFIRM_PAY_SUCCESS_BUTTON = "div.buy_success p.p2 a";
    
    
    static int iUrlNum = 0;
    public enum EnUrlLoadStatus{
    	START_URL_LOAD_SUCCESSED,
    	START_URL_LOAD_FAILED,
    	DEST_URL_LOAD_SUCCESSED,
    	DEST_URL_LOAD_FAILED
    };
    //public static final String 
    public CWebHandler() {
    this(null);
    }

    public CWebHandler(QWidget parent) {
    super(parent);

        browser = new QWebView();
        browser.setPage(new WebPage ());
        browser.setGeometry(0, 0, 10, 10);
        browser.setTextSizeMultiplier(0.5);
        inspector.setPage(browser.page());
        
        QFile file1 = new QFile();
        file1.setFileName("D:/jquery-3.1.1.js");
        //file.setFileName("D:/jquery.min.js");
        file1.open(QIODevice.OpenModeFlag.ReadOnly);
        jQuery = file1.readAll().toString();
   
        QFile file2 = new QFile();
        file2.setFileName("D:/selectivizr.js");
        //file.setFileName("D:/jquery.min.js");
        file1.open(QIODevice.OpenModeFlag.ReadOnly);
        css3 = file2.readAll().toString();
        
        QFile file3 = new QFile();
        file3.setFileName("D:/html5.js");
        //file.setFileName("D:/jquery.min.js");
        file3.open(QIODevice.OpenModeFlag.ReadOnly);
        html5 = file3.readAll().toString();
        //logger.info(jQuery);
        file1.close();
        file2.close();
        file3.close();
        
        //browser.page().mainFrame().documentElement().
        browser.setAttribute(Qt.WidgetAttribute.WA_DeleteOnClose,true);
        browser.settings().setAttribute(QWebSettings.WebAttribute.PluginsEnabled, true);
        browser.settings().setAttribute(QWebSettings.WebAttribute.FrameFlatteningEnabled, true);
        browser.settings().setAttribute(QWebSettings.WebAttribute.JavascriptCanOpenWindows, true);
        browser.settings().setAttribute(QWebSettings.WebAttribute.AutoLoadImages, true);
        browser.settings().setAttribute(QWebSettings.WebAttribute.JavascriptEnabled, true);
        browser.settings().setAttribute(QWebSettings.WebAttribute.JavaEnabled, true);
        browser.settings().setAttribute(QWebSettings.WebAttribute.DnsPrefetchEnabled, true);
        browser.settings().setAttribute(QWebSettings.WebAttribute.DeveloperExtrasEnabled, true);
        browser.settings().setAttribute(QWebSettings.WebAttribute.LocalContentCanAccessFileUrls, true);
        browser.settings().setAttribute(QWebSettings.WebAttribute.LocalContentCanAccessRemoteUrls, true);
        //browser.page().setLinkDelegationPolicy(QWebPage.LinkDelegationPolicy.DelegateAllLinks);
        browser.page().setNetworkAccessManager(new NetWorkAccessManager());
        setCentralWidget(browser);
        statusBar().show();

        setWindowTitle("copyright ©fssb");
        setWindowIcon(new QIcon("classpath:com/trolltech/images/qt-logo.png"));	

        m_eventLoop  = new QEventLoop();
        m_load_timer1 = new QTimer();
        m_load_timer2 = new QTimer();
        m_iTimeOut = 3000;
        browser.loadStarted.connect(this, "loadStarted()");
        browser.loadProgress.connect(this, "loadProgress(int)");
        browser.loadFinished.connect(this, "loadDone()");
        browser.urlChanged.connect(this, "urlChanged(QUrl)");
        m_load_timer1.timeout.connect(this, "timeOut()");
        m_load_timer2.timeout.connect(this, "timeOut()");
        browser.page().networkAccessManager().finished.connect(this, "HttpResponseFinished(QNetworkReply)", ConnectionType.AutoConnection);
    }
    /*
    protected void finalize(){
    	super.finalize();
    };
    */
    /************************************signal handler*************************************************/
    protected void timeOut(){

    	if ( m_load_timer1.isActive())
    	{
    		logger.error("Shut up the QTimer1.");
    	    m_load_timer1.stop();
    	}
    	if ( m_load_timer2.isActive())
    	{
    		logger.error("Shut up the QTimer2.");
    	    m_load_timer2.stop();
    	}
    	
    	if(m_eventLoop.isRunning()){
        	m_eventLoop.quit();
    	}
    }
    protected void urlChanged(QUrl url) {
    	m_strDestUrl = url.toString();
    	logger.debug("Url changed to: " + m_strDestUrl);
    }

    protected void loadStarted() {
    	logger.debug("Starting to load: " + m_strLoadingUrl);
        statusBar().showMessage("Starting to load: " + m_strLoadingUrl);
    }

    protected void loadDone() {
    	browser.page().mainFrame().evaluateJavaScript(jQuery);
    	browser.page().mainFrame().evaluateJavaScript(css3);
    	browser.page().mainFrame().evaluateJavaScript(html5);
    	logger.debug("Loading done...");
    	iUrlNum += 1;
    	if (iUrlNum == 1){
    		if(m_load_timer1.isActive())
    		{
    		    logger.debug("Shut up the QTimer1.");
    		    m_load_timer1.stop();
    		}
    		m_EnUrlLoadStatus = EnUrlLoadStatus.START_URL_LOAD_SUCCESSED;
    	}else if(iUrlNum == 2){
    		if(m_load_timer2.isActive())
    		{
    		    logger.debug("Shut up the QTimer2.");
    		    m_load_timer2.stop();
    		}
    		
    		m_EnUrlLoadStatus = EnUrlLoadStatus.DEST_URL_LOAD_SUCCESSED;
    	}
    	
    	if(m_eventLoop.isRunning()){
    		m_eventLoop.quit();
    	}
        statusBar().showMessage("Loading done...");
    }

    protected void loadProgress(int x) {
        statusBar().showMessage("Loading: " + x + " %");
    }

    protected void open(String url) {

        if (url.indexOf("://") < 0)
        	url = "http://" + url;

        browser.load(new QUrl(url));
    }

    @Override
    protected void closeEvent(QCloseEvent event) {
        browser.loadProgress.disconnect(this);
        browser.loadFinished.disconnect(this);
        browser.loadStarted.disconnect(this);
        browser.urlChanged.disconnect(this);
        m_load_timer1.timeout.disconnect(this);
        m_load_timer2.timeout.disconnect(this);
    }
    
    
    void HttpResponseFinished(QNetworkReply reply)
    {
      QUrl failed_url = reply.url();
      String network_reply_url = failed_url.toString();
      String debug_str;
      String http_message = "";//reply.readAll().toString();

      debug_str = " reply_url["+ network_reply_url + "] http_response[" + http_message + "]";
      logger.info(debug_str);
      return;
    }
    /******************************************inner function***************************************/
    private int inputGraphicVerification(String graphVerify){
    	QWebElement input = findTagElement(GRAPHIC_VERIFICATION);
    	return inputStrToElement(graphVerify, input);
    }
    
    private int inputVerificationCode(String verifyCode){
    	QWebElement input = findTagElement(VERIFICATION_CODE);
    	return inputStrToElement(verifyCode, input);
    }
    
    private int inputPhoneNum(String phoneNum){
    	QWebElement input = findTagElement(PHONE_NUM);
    	return inputStrToElement(phoneNum, input);
    }
    
    private int  inputStrToElement(String str, QWebElement input){
    	/*
        if(input.geometry().width() < WIDGET_WIDTH_MIN_VALUE || input.geometry().height() < WIDGET_HEIGHT_MIN_VALUE)
        {
            logger.error("Input element error.");
            logger.info("width:" + input.geometry().width() + " heigth" + input.geometry().height());
            return -1;
        }
        */
    	logger.info("width:" + input.geometry().width() + " heigth" + input.geometry().height());
        getAndClickInputPos(input);
        this.mdelay(10);
    	input.evaluateJavaScript("this.value += \"" + str + "\"");
    	return 0;
    }
    
    private void getAndClickInputPos(QWebElement input){
    	  int input_width  = input.geometry().width();
    	  int input_height = input.geometry().height();
    	  int input_click_x = input.geometry().left() + INPUT_TEXT_WIDTH_BOUND + ((int)System.currentTimeMillis() % (input_width  - INPUT_TEXT_WIDTH_BOUND));
    	  int input_click_y = input.geometry().top()  + INPUT_TEXT_HEIGHT_BOUND + ((int)System.currentTimeMillis() % (input_height - INPUT_TEXT_HEIGHT_BOUND));
    	  input.evaluateJavaScript("this.value = \"\"");
          QPoint pos = new QPoint(input_click_x, input_click_y); 

          QMouseEvent event0 = new QMouseEvent(QEvent.Type.MouseButtonPress, pos, Qt.MouseButton.LeftButton, new Qt.MouseButtons(Qt.MouseButton.LeftButton), new Qt.KeyboardModifiers(Qt.KeyboardModifier.NoModifier));
          QApplication.sendEvent(browser.page(), event0);
          QMouseEvent event1 = new QMouseEvent(QEvent.Type.MouseButtonRelease, pos, Qt.MouseButton.LeftButton, new Qt.MouseButtons(Qt.MouseButton.LeftButton), new Qt.KeyboardModifiers(Qt.KeyboardModifier.NoModifier));
          QApplication.sendEvent(browser.page(), event1);
          QApplication.processEvents();
    }
    
    private QWebElement findTagElement(String tagStr){
    	QWebElement dom, input;
    	dom = browser.page().mainFrame().documentElement();
    	input = dom.findFirst(tagStr);
    	return input;
    }
    
    private void clickButton(QWebElement btn){
    	int scroll_height = browser.page().mainFrame().scrollPosition().y();
    	QRect btnRect = btn.geometry();
    	int width = btnRect.width();
    	int height = btnRect.height();
    	int btn_x = btnRect.left() + ((int)System.currentTimeMillis() % ( width - BUTTON_ENSURE_INLINE_RANGE_MEASURE ) ) + BUTTON_MISTAKE_REPAIR_START_MEASURE;
    	int btn_y = btnRect.top()  + ((int)System.currentTimeMillis() % ( height - BUTTON_ENSURE_INLINE_RANGE_MEASURE ) ) - scroll_height + BUTTON_MISTAKE_REPAIR_START_MEASURE;
        QPoint pos = new QPoint(btn_x, btn_y); 
        logger.info("Point_x:" + btn_x + " Point_y:" + btn_y);
        QMouseEvent event0 = new QMouseEvent(QEvent.Type.MouseButtonPress, pos, Qt.MouseButton.LeftButton, new Qt.MouseButtons(Qt.MouseButton.LeftButton), new Qt.KeyboardModifiers(Qt.KeyboardModifier.NoModifier));
        QApplication.sendEvent(browser.page(), event0);
        QMouseEvent event1 = new QMouseEvent(QEvent.Type.MouseButtonRelease, pos, Qt.MouseButton.LeftButton, new Qt.MouseButtons(Qt.MouseButton.LeftButton), new Qt.KeyboardModifiers(Qt.KeyboardModifier.NoModifier));
        QApplication.sendEvent(browser.page(), event1);
        QApplication.processEvents();
    }
    
    private void clickConfirmBtn(){
    	QWebElement btn = findTagElement(CONFIRM_BUTTON);
    	clickButton(btn);
    	this.mdelay(10);
    }
    
    private void clickGetVerifyCodeBtn(){
    	QWebElement btn = findTagElement(GET_VERIFY_CODE_BUTTON);
    	clickButton(btn);
    	this.mdelay(10);
    }
    
    private void clickCommitBtn(){
    	this.mdelay(1000);
    	QWebElement btn = findTagElement(COMMIT_BUTTON);
    	clickButton(btn);
    	this.mdelay(10);
    	//browser.page().mainFrame().evaluateJavaScript("checkSmsCode();");
    }
    
    private void clickConfirmPayBtn(){
    	this.mdelay(1000);
    	QWebElement btn = findTagElement(CONFIRM_PAY_BUTTON);
    	clickButton(btn);
    	this.mdelay(10);
    	//browser.page().mainFrame().evaluateJavaScript("window.location.href = \'http://www.baidu.com\';");
    }
    
    private void clickConfirmSuccessBtn(){
    	this.mdelay(1000);
    	QWebElement btn = findTagElement(CONFIRM_PAY_SUCCESS_BUTTON);
    	//this.mdelay(3000);
    	clickButton(btn);
    	//browser.page().mainFrame().evaluateJavaScript("window.location.href = \'http://www.baidu.com\';");
    }
    
    private void loadStarUrl(String url){
    	m_strStartUrl = url;
    	m_strLoadingUrl = m_strStartUrl;
    	this.open(url);
    	this.mdelay(100);
    }
    
    private void loadDestUrl(String url){
    	m_strDestUrl = url;
    	m_strStartUrl = m_strDestUrl;
    	this.open(url);
    	this.mdelay(10);
    }
    
    private void mdelay( int millisecondsToWait )
    {
        QTime dieTime = QTime.currentTime().addMSecs( millisecondsToWait );
        while( QTime.currentTime().compareTo(dieTime) < 0 )
        {
            QCoreApplication.processEvents(QEventLoop.ProcessEventsFlag.AllEvents);
        }
    }

    /************************************reserved interface***************************************************/
    @SuppressWarnings("unused")
	private void setTimeOut(int time){
    	m_iTimeOut = time;
    }
    
    @SuppressWarnings("unused")
	private int inputStrToElement(String str, QWebElement dom, String strTag){
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
    
    private void showWidget(){
    	this.show();
    	QApplication.processEvents();
    	this.mdelay(10);
    	//logger.info("tttttttttttt");
    	//browser.page().mainFrame().evaluateJavaScript("window.location.href = \'http://www.baidu.com\';");
    }
    /*****************************************interface*****************************************************/
    public int loadUrl(String url){
    	String strReplyContent1;
    	
    	m_load_timer1.setSingleShot(true);
        m_load_timer1.start(m_iTimeOut);
    	loadStarUrl(url);
    	m_eventLoop.exec();
        if(EnUrlLoadStatus.START_URL_LOAD_SUCCESSED == m_EnUrlLoadStatus){
        	strReplyContent1 = browser.page().mainFrame().documentElement().toPlainText();

        }
        else if (EnUrlLoadStatus.START_URL_LOAD_FAILED == m_EnUrlLoadStatus){
        	logger.error("Start url load failed.");
        	return -1;
        }
        else{
        	logger.error("Unknown start url Loading status.");
        	return -1;
        }
        
        
        //this.open("http://223.111.8.142:8080/migunetsdk/webJs/frame.html?netId=cc5be2d06bfa401ebc7db42de4ce7504&umark=Common");

        
        
    	m_load_timer2.setSingleShot(true);
        m_load_timer2.start(m_iTimeOut);
        loadDestUrl(strReplyContent1);
        m_eventLoop.exec();
        if(EnUrlLoadStatus.DEST_URL_LOAD_SUCCESSED == m_EnUrlLoadStatus){
        	m_strPayPage = browser.page().mainFrame().documentElement().toOuterXml();
        }
        else if (EnUrlLoadStatus.DEST_URL_LOAD_FAILED == m_EnUrlLoadStatus){
        	logger.error("Dest url load failed.");
        	return -1;
        }
        else{
        	logger.error("Unknown dest url Loading status.");
        	return -1;
        }

        return 0;
    }	
    public String getPayPage(){
    	//return m_strPayPage;
    	return browser.page().mainFrame().documentElement().toOuterXml();
    }
    
    public int submitGraphVerify(String graphVerify){
    	int iRet = 0;
    	iRet = inputGraphicVerification(graphVerify);
    	if(iRet != 0){
    		logger.error("Input graphic verification error.");
    		iRet = -1;
    	}
    	clickConfirmBtn();
    	return 0;
    }
    
    public int submitPhoneNumVerify(String phoneNum){
    	int iRet = 0;
    	iRet = inputPhoneNum(phoneNum);
    	if(iRet != 0){
    		logger.error("Input phone num error.");
    		iRet = -1;
    	}
    	clickGetVerifyCodeBtn();
    	return 0;
    }
    
    public int submitPayForm(String verifyCode){
    	int iRet = 0;
        inputVerificationCode(verifyCode);
        if(iRet != 0){
        	logger.error("Input verification code error.");
        	iRet = -1;
        }
        clickCommitBtn();
        
        clickConfirmSuccessBtn();

    	return 0;
    }
    
    public void shutDown(){
    	//QApplication.shutdown();
    }
    
    static class CWebHandlerContext{
    	static void initialize(String args[]){
    		QApplication.initialize(args);
    	}
    	
    	static void uninitialize(){
            //QApplication.execStatic();
            //QApplication.shutdown();
    		QApplication.exec();
    	}
    }
    
    public static void main(String args[]) {
        //final Logger LOG = LogManager.getLogger("main"); 
        CWebHandlerContext.initialize(args);
        String strGraphVerify = "123";
        String strPhoneNum = "18210315658";
        String strVerifyCode = "123";
        int iRet = 0;
        
        CWebHandler autoPayHandler = new CWebHandler();
        autoPayHandler.loadUrl("http://121.42.145.138:8080/test/ddourl?pid=70488801");
        //autoPayHandler.loadStarUrl("http://www.cnblogs.com/lhb25/archive/2011/01/16/1936669.html");
        //autoPayHandler.loadStarUrl("http://wap.dm.10086.cn/apay/orderHandle.jsp?RequestID=6111618020215690&AppID=300000007946&PayCode=300007946001&TimeStamp=1479290541&ChannelID=700003913&Signature=QUMxOUEwNDA5MTUxRTU4NjZGNEQ2NjEwRUU2MTZEOTk=");
        //autoPayHandler.loadStarUrl("http://www.sunchateau.com/free/UA.htm");
        //autoPayHandler.loadStarUrl("http://wap.dm.10086.cn/apay/orderSuccess.jsp?totalprice=0.1&telephone=4000889115&orderId=1479109547300&noticeUrl=index.jsp&status=0&orderType=1");
        autoPayHandler.showWidget();
        autoPayHandler.mdelay(3000);
        //autoPayHandler.mdelay(1000);
        //autoPayHandler.clickConfirmSuccessBtn();
        @SuppressWarnings("unused")
		String payWebStr = autoPayHandler.getPayPage();
        //logger.info(payWebStr);
        /*....your function*/
        
        do{
            iRet = autoPayHandler.submitGraphVerify(strGraphVerify);
            if(iRet != 0)
            {
            	iRet = -1;
            	break;
            }
            autoPayHandler.submitPhoneNumVerify(strPhoneNum);
            if(iRet != 0)
            {
            	iRet = -1;
            	break;
            }
            autoPayHandler.submitPayForm(strVerifyCode);
            if(iRet != 0)
            {
            	iRet = -1;
            	break;
            }
        }while(false);
        
        CWebHandlerContext.uninitialize();
    }
    
}
