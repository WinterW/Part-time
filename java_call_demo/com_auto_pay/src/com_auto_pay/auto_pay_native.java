package com_auto_pay;

public class auto_pay_native {
	static
	{
		System.loadLibrary("auto_pay");
	}
	public native void init_context();/**/
	public native void destory_context();
	public native int createObject(int num);
	public native void deleteObject();
	public native int loadUrl(String url, int index);
	public native int showWidget(int index);
	public native String getPayPage(int index);
	public native int submitGraphVerify(String graphVerify, int index);
	public native int submitPhoneNumVerify(String phoneNum, int index);
	public native int submitPayForm(String verifyCode, int index);
	public native int window_join(int time, int index);
	public native int shutDown(int index);
	
	public static void main(String[] args){
		auto_pay_native pay_handler = new auto_pay_native();
		pay_handler.init_context();
        String strGraphVerify = "123";
        String strPhoneNum = "18210315658";
        String strVerifyCode = "123";
        int iRet = 0;
        
        pay_handler.createObject(2);
        pay_handler.loadUrl("http://121.42.145.138:8080/test/ddourl?pid=70488801", 0);
        pay_handler.showWidget(0);
        pay_handler.loadUrl("http://121.42.145.138:8080/test/ddourl?pid=70488801", 1);
        pay_handler.showWidget(1);
		//String payWebStr = pay_handler.getPayPage(0);
        
        do{
            iRet = pay_handler.submitGraphVerify(strGraphVerify, 0);
            iRet = pay_handler.submitGraphVerify("234", 1);
            if(iRet != 0)
            {
            	iRet = -1;
            	break;
            }
            pay_handler.submitPhoneNumVerify(strPhoneNum, 0);
            if(iRet != 0)
            {
            	iRet = -1;
            	break;
            }
            pay_handler.submitPayForm(strVerifyCode, 0);
            if(iRet != 0)
            {
            	iRet = -1;
            	break;
            }
        }while(false);
        pay_handler.shutDown(0);
        pay_handler.window_join(10000, 0);
        
        pay_handler.deleteObject();
        pay_handler.destory_context();
	}
}
