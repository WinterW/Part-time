#include "com_auto_pay_auto_pay_native.h"
#include "auto_pay.h"
#include "auto_pay_context.h"
//#include "qdebug.h"
static Auto_pay_context* pApp;
static Auto_pay* pAryInstance;
static char *argv[] = {"java","--disable-web-security", "--user-data-dir=~", NULL};
static int argc = 3;

//static char*argv[] = {"java",NULL};
//static int argc = 1;
//"java","--disable-web-security", "--user-data-dir=~"
jstring charTojstring(JNIEnv* env, const char* pat) {
    //定义java String类 strClass
    jclass strClass = (env)->FindClass("Ljava/lang/String;");
    //获取String(byte[],String)的构造器,用于将本地byte[]数组转换为一个新String
    jmethodID ctorID = (env)->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    //建立byte数组
    jbyteArray bytes = (env)->NewByteArray(strlen(pat));
    //将char* 转换为byte数组
    (env)->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*) pat);
    // 设置String, 保存语言类型,用于byte数组转换至String时的参数
    jstring encoding = (env)->NewStringUTF("GB2312");
    //将byte数组转换为java String,并输出
    return (jstring) (env)->NewObject(strClass, ctorID, bytes, encoding);
}

char* jstringToChar(JNIEnv* env, jstring jstr) {
    char* rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("GB2312");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char*) malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    return rtn;
}

JNIEXPORT void JNICALL Java_com_1auto_1pay_auto_1pay_1native_init_1context(JNIEnv *, jobject)
{
    //char *argv[] = {"java","--disable-web-security", "--user-data-dir=~", NULL};
    //"java","--disable-web-security", "--user-data-dir=~"
    //int argc = 3;
    pApp = new Auto_pay_context(argc, argv);
}
JNIEXPORT void JNICALL Java_com_1auto_1pay_auto_1pay_1native_destory_1context(JNIEnv *, jobject)
{
    if(NULL != pApp)
    {
        pApp->exit();
        delete pApp;
        pApp = NULL;
    }
}

JNIEXPORT jint JNICALL Java_com_1auto_1pay_auto_1pay_1native_createObject(JNIEnv *, jobject, jint num)
{
    /*
    Auto_pay *pAuto_pay = new Auto_pay[num];
    typedef Auto_pay*  Auto_pay_ptr;
    pAryInstance = new Auto_pay_ptr;
    *pAryInstance = pAuto_pay;
    */
    //int *a=new int[10];
    //pAryInstance = new Auto_pay;//[num];
    //pAryInstance = new Auto_pay[num];
    pAryInstance = new Auto_pay[num];
    if(pAryInstance == NULL)
    {
        return -1;
    }

/*
    pAryInstance = new Auto_pay*[num];
    if(pAryInstance == NULL)
    {
        return -1;
    }

    for(int i=0; i<num; i++)
    {
        pAryInstance[i] = new Auto_pay;
        if (pAryInstance[i] == NULL)
        {
            return -1;
        }
    }
*/
    return 0;
}

JNIEXPORT void JNICALL Java_com_1auto_1pay_auto_1pay_1native_deleteObject(JNIEnv *, jobject)
{
    delete[] pAryInstance;
    pAryInstance = NULL;
}
JNIEXPORT jint JNICALL Java_com_1auto_1pay_auto_1pay_1native_loadUrl(JNIEnv * env, jobject, jstring url, jint index)
{
    //qDebug()<<"load_url";
    if((NULL == pAryInstance) || NULL == pAryInstance + index)
    {
        return -1;
    }
    int iRet = 0;
    char* charUrl = jstringToChar(env, url);
    iRet = (pAryInstance+index)->loadUrl(charUrl);
    return iRet;
}

JNIEXPORT jint JNICALL Java_com_1auto_1pay_auto_1pay_1native_showWidget(JNIEnv *, jobject, jint index)
{
    //qDebug()<<"show widget";
    if((NULL == pAryInstance) || NULL == pAryInstance + index)
    {
        return -1;
    }
    (pAryInstance+index)->showWidget();
    return 0;
}

JNIEXPORT jstring JNICALL Java_com_1auto_1pay_auto_1pay_1native_getPayPage(JNIEnv * env, jobject, jint index)
{
    jstring retPage = NULL;
    if((NULL == pAryInstance) || NULL == (pAryInstance + index))
    {
        return retPage;
    }

    QString QStrPage = "";
    QStrPage = pAryInstance[index].getPayPage();
    std::string strPage = QStrPage.toStdString();
    const char *charPage = strPage.c_str();
    retPage = charTojstring(env, charPage);
    return retPage;
}

JNIEXPORT jint JNICALL Java_com_1auto_1pay_auto_1pay_1native_submitGraphVerify(JNIEnv * env, jobject, jstring graphVerify, jint index)
{
    if((NULL == pAryInstance) || NULL == (pAryInstance + index))
    {
        return -1;
    }
    int iRet = 0;
    char* chargraphVerify = jstringToChar(env, graphVerify);
    iRet = (pAryInstance+index)->submitGraphVerify(chargraphVerify);
    return iRet;
}

JNIEXPORT jint JNICALL Java_com_1auto_1pay_auto_1pay_1native_submitPhoneNumVerify(JNIEnv * env, jobject, jstring phoneNum, jint index)
{
    if((NULL == pAryInstance) || NULL == (pAryInstance + index))
    {
        return -1;
    }
    int iRet = 0;
    char* charphoneNum = jstringToChar(env, phoneNum);
    iRet = (pAryInstance+index)->submitPhoneNumVerify(charphoneNum);
    return iRet;
}

JNIEXPORT jint JNICALL Java_com_1auto_1pay_auto_1pay_1native_submitPayForm(JNIEnv * env, jobject, jstring verifyCode, jint index)
{
    if((NULL == pAryInstance) || NULL == (pAryInstance + index))
    {
        return -1;
    }
    int iRet = 0;
    char* charverifyCode = jstringToChar(env, verifyCode);
    iRet = (pAryInstance+index)->submitPayForm(charverifyCode);
    return iRet;
}

JNIEXPORT jint JNICALL Java_com_1auto_1pay_auto_1pay_1native_window_1join(JNIEnv *, jobject, jint time, jint index)
{
    if((NULL == pAryInstance) || NULL == (pAryInstance + index))
    {
        return -1;
    }
    (pAryInstance+index)->window_join(time);
    return 0;
}

JNIEXPORT jint JNICALL Java_com_1auto_1pay_auto_1pay_1native_shutDown(JNIEnv *, jobject, jint index)
{
    if((NULL == pAryInstance) || NULL == (pAryInstance + index))
    {
        return -1;
    }
    (pAryInstance+index)->shutDown();
    return 0;
}


