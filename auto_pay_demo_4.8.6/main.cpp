

#include <QFile>

#include <QDir>
#include <qmutex.h>
//#include <QEvent/QCloseEvent>
#include <QtGui/QApplication>
#include "cwebhandler.h"

class CWebHandlerContext{
private:
    CWebHandlerContext(){}
    ~CWebHandlerContext(){}
    static QApplication* m_instance;
public:
    static void initialize(int argc, char *argv[]){
        if (NULL == m_instance)
        {
            m_instance = new QApplication(argc, argv);
        }
    }

    static void uninitialize(){
        m_instance->exec();
        m_instance->exit();
    }
};

QApplication* CWebHandlerContext::m_instance = NULL;
int main(int argc, char *argv[]) {
    //final Logger LOG = LogManager.getLogger("main");
    //CWebHandlerContext::initialize(argc, argv);
    QApplication app(argc, argv);
    QString strGraphVerify = "123";
    QString strPhoneNum = "18210315658";
    QString strVerifyCode = "123";
    int iRet = 0;

    CWebHandler autoPayHandler;
    autoPayHandler.loadUrl("http://121.42.145.138:8080/test/ddourl?pid=70488801");
    //autoPayHandler.loadStarUrl("http://www.cnblogs.com/lhb25/archive/2011/01/16/1936669.html");
    //autoPayHandler.loadStarUrl("http://wap.dm.10086.cn/apay/orderHandle.jsp?RequestID=6111618020215690&AppID=300000007946&PayCode=300007946001&TimeStamp=1479290541&ChannelID=700003913&Signature=QUMxOUEwNDA5MTUxRTU4NjZGNEQ2NjEwRUU2MTZEOTk=");
    //autoPayHandler.loadStarUrl("http://www.sunchateau.com/free/UA.htm");
    //autoPayHandler.loadStarUrl("http://wap.dm.10086.cn/apay/orderSuccess.jsp?totalprice=0.1&telephone=4000889115&orderId=1479109547300&noticeUrl=index.jsp&status=0&orderType=1");
    autoPayHandler.showWidget();
    //autoPayHandler.mdelay(1000);
    //autoPayHandler.clickConfirmSuccessBtn();
    QString payWebStr = autoPayHandler.getPayPage();
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

    app.exec();
    app.exit();
    //CWebHandlerContext::uninitialize();
    return 0;
}
