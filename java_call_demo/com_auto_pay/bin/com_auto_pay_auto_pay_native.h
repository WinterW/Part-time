/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_auto_pay_auto_pay_native */

#ifndef _Included_com_auto_pay_auto_pay_native
#define _Included_com_auto_pay_auto_pay_native
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_auto_pay_auto_pay_native
 * Method:    init_context
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_1auto_1pay_auto_1pay_1native_init_1context
  (JNIEnv *, jobject);

/*
 * Class:     com_auto_pay_auto_pay_native
 * Method:    destory_context
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_1auto_1pay_auto_1pay_1native_destory_1context
  (JNIEnv *, jobject);

/*
 * Class:     com_auto_pay_auto_pay_native
 * Method:    createObject
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_com_1auto_1pay_auto_1pay_1native_createObject
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_auto_pay_auto_pay_native
 * Method:    loadUrl
 * Signature: (Ljava/lang/String;I)I
 */
JNIEXPORT jint JNICALL Java_com_1auto_1pay_auto_1pay_1native_loadUrl
  (JNIEnv *, jobject, jstring, jint);

/*
 * Class:     com_auto_pay_auto_pay_native
 * Method:    showWidget
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_1auto_1pay_auto_1pay_1native_showWidget
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_auto_pay_auto_pay_native
 * Method:    getPayPage
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_1auto_1pay_auto_1pay_1native_getPayPage
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_auto_pay_auto_pay_native
 * Method:    submitGraphVerify
 * Signature: (Ljava/lang/String;I)I
 */
JNIEXPORT jint JNICALL Java_com_1auto_1pay_auto_1pay_1native_submitGraphVerify
  (JNIEnv *, jobject, jstring, jint);

/*
 * Class:     com_auto_pay_auto_pay_native
 * Method:    submitPhoneNumVerify
 * Signature: (Ljava/lang/String;I)I
 */
JNIEXPORT jint JNICALL Java_com_1auto_1pay_auto_1pay_1native_submitPhoneNumVerify
  (JNIEnv *, jobject, jstring, jint);

/*
 * Class:     com_auto_pay_auto_pay_native
 * Method:    submitPayForm
 * Signature: (Ljava/lang/String;I)I
 */
JNIEXPORT jint JNICALL Java_com_1auto_1pay_auto_1pay_1native_submitPayForm
  (JNIEnv *, jobject, jstring, jint);

/*
 * Class:     com_auto_pay_auto_pay_native
 * Method:    window_join
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_com_1auto_1pay_auto_1pay_1native_window_1join
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     com_auto_pay_auto_pay_native
 * Method:    shutDown
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_1auto_1pay_auto_1pay_1native_shutDown
  (JNIEnv *, jobject, jint);

#ifdef __cplusplus
}
#endif
#endif
