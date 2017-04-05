#include <QtWidgets/QApplication>
#include "cwebhandler.h"
int main(int argc, char *argv[]) {

    qputenv("QTWEBENGINE_REMOTE_DEBUGGING", "9000");
    QApplication app(argc, argv);
    QString strGraphVerify = "123";
    //QString strPhoneNum = "18210315658";
    QString strPhoneNum = "13810055034";
    QString strVerifyCode = "123";
    int iRet = 0;

    CWebHandler autoPayHandler;
    autoPayHandler.loadUrl("http://121.42.145.138:8080/test/ddourl?pid=70488801");
    autoPayHandler.showWidget();
    QString payWebStr = autoPayHandler.getPayPage();
    //logger.info(payWebStr);
    /*....your function*/

    do{
        iRet = autoPayHandler.submitGraphVerify(strGraphVerify);
        iRet = autoPayHandler.submitGraphVerify(strGraphVerify);
        if(iRet != 0)
        {
            iRet = -1;
            break;
        }

        iRet = autoPayHandler.submitPhoneNumVerify(strPhoneNum);

        if(iRet != 0)
        {
            iRet = -1;
            break;
        }

        iRet = autoPayHandler.submitPayForm(strVerifyCode);

        if(iRet != 0)
        {
            iRet = -1;
            break;
        }

    }while(false);

    autoPayHandler.window_join(10000);
    app.exit();
    return 0;
}
