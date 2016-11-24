
package auto_pay;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.HttpURLConnection;
import java.net.URL;

//import org.apache.http.client.methods.HttpGet;

public class HttpClient {
	// 发送一个GET请求
	public static String get(String path) throws Exception {
		HttpURLConnection httpConn = null;
		BufferedReader in = null;
		try {
			URL url = new URL(path);
			httpConn = (HttpURLConnection) url.openConnection();

			// 读取响应
			if (httpConn.getResponseCode() == HttpURLConnection.HTTP_OK) {
				StringBuffer content = new StringBuffer();
				String tempStr = "";
				in = new BufferedReader(new InputStreamReader(httpConn.getInputStream()));
				while ((tempStr = in.readLine()) != null) {
					content.append(tempStr);
				}
				return content.toString();
			} else {
				throw new Exception("请求出现了问题!");
			}
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			in.close();
			httpConn.disconnect();
		}
		return null;
	}

	public static void main(String[] args) throws Exception {
		// String
		// resMessage=HttpClient.get("http://localhost:3000/hello?hello=hello
		// get");
		String resMessage1 = HttpClient
				.get("http://wap.dm.10086.cn/capability/capacc/imgCode?session=1054667335&amp;randnum=520690");
		System.out.println(resMessage1);
		String resMessage2 = HttpClient
				.get("http://wap.dm.10086.cn/capability/capacc/imgCode?session=1054667335&amp;randnum=520690");
		System.out.println(resMessage2);
		System.out.println(resMessage1.compareTo(resMessage2));
	}

}