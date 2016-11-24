package auto_pay;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import com.trolltech.qt.core.*;
import com.trolltech.qt.script.*;
import com.trolltech.qt.gui.*;
import com.trolltech.qt.webkit.*;
import com.trolltech.qt.network.*;
public class QScriptTest extends QObject{
	private static final Logger logger = LogManager.getLogger();  
	private int cpp_func(int a, int b)
	{
	    return a + b;
	}
	 
	private QScriptValue cpp_func_wrapper(QScriptContext ctx, QScriptEngine eng)
	{
	    int a = ctx.argument(0).toInt32();
	    int b = ctx.argument(1).toInt32();
	    return new QScriptValue(cpp_func(a, b));
	}
	 
	public static void main(String args[]){
		QApplication.initialize(args);
		QScriptEngine engine1 = new QScriptEngine();
		//向js中传递全局可用数
		engine1.globalObject().setProperty("name", new QScriptValue("liyangyao"));
		//向js中传递全局可用函数指针 (需要经过一层包装, 符合签名)
		//QScriptValue cpp_func_ref = engine1.newFunction(cpp_func_wrapper);
		//engine.globalObject().setProperty("cpp_func", cpp_func_ref);
		 
		//载入js
	    //读取js文件  
		String contents = "";
		logger.info("aaaaaaaaaa");
		try{
		    String fileName ="C:/migu.js";  
		    QFile scriptFile = new QFile(fileName);  
		    scriptFile.open(QIODevice.OpenModeFlag.ReadOnly);  
		    QTextStream stream = new QTextStream(scriptFile);  
		    contents = stream.readAll();  
		    scriptFile.close();  
		    logger.info("bbbbbbbbbbbb");
		    logger.info(contents);
		}catch(Exception e)
		{
			logger.info("cccccccccccccc");
		}
	    
		QScriptValue object = engine1.evaluate(contents);
		if (object.isError())
		{
		    logger.info("line:" + object.property("lineNumber").toInt32() + " error:" + object.toString());
		}
		 /*
		//调用js中的全局函数
		qDebug()<<"execute script time:"<<time(NULL);
		QScriptValue func = engine.globalObject().property("js_func");
		if (func.isValid())
		{
		    QScriptValue result = func.call(object, QScriptValueList()<<17);
		    qDebug()<<"js_func return->"<<result.toString();
		    //获取js中的全局变量
		    qDebug()<<"context="<< engine.globalObject().property("context").toString();
		}
		else{
		    qDebug()<<"js_func is not valid";
		}
		*/
        //QApplication.execStatic();
        //QApplication.shutdown();
		QApplication.exec();
	}
}
