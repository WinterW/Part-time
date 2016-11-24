package auto_pay;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import com.trolltech.qt.core.*;
import com.trolltech.qt.gui.*;
import com.trolltech.qt.webkit.*;
import com.trolltech.qt.network.*;

public class NetWorkAccessManager extends QNetworkAccessManager {
	private static final Logger logger = LogManager.getLogger();  
	@Override
	protected QNetworkReply createRequest(Operation op, QNetworkRequest req, QIODevice outgoingData){
		
		String req_url = req.url().toEncoded().toString();
		logger.info("CreateRequest: " + req_url);
		QNetworkReply reply = super.createRequest(op, req, outgoingData);
		
		/*
		QNetworkRequest request = new QNetworkRequest(new QUrl("http://223.111.8.142:8080/migunetsdk/webJs/frame.html?netId=cc5be2d06bfa401ebc7db42de4ce7504&umark=Common"));
		if(req_url.indexOf("imgCode") > 0)
		{
			logger.info("CreateRequest: " + request);
			reply =  super.createRequest(op, request);
		}
		
		request = new QNetworkRequest(new QUrl("http://wsdkdl.migu.cn:8080/comic/Common/style.css?v=0odOihMX9fBUJwfcPvokYh"));
		if(req_url.indexOf("imgCode") > 0)
		{
			logger.info("CreateRequest: " + request);
			reply =  super.createRequest(op, request);
		}
		
		request = new QNetworkRequest(new QUrl("http://wsdkdl.migu.cn:8080/cc5be2d06bfa401ebc7db42de4ce7504/1478624500413/netsdk.js?v=0odOihMX9fBUJwfcPvokYh"));
		if(req_url.indexOf("imgCode") > 0)
		{
			logger.info("CreateRequest: " + request);
			reply =  super.createRequest(op, request);
		}
		
		request = new QNetworkRequest(new QUrl("http://wsdkdl.migu.cn:8080/cc5be2d06bfa401ebc7db42de4ce7504/1478624500413/netsdk.bin?v=0odOihMX9fBUJwfcPvokYh"));
		if(req_url.indexOf("imgCode") > 0)
		{
			logger.info("CreateRequest: " + request);
			reply =  super.createRequest(op, request);
		}
		
		*/
		return reply;

		  //reply->ignoreSslErrors();
	}

}
