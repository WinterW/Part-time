package auto_pay;

import com.trolltech.qt.core.*;
import com.trolltech.qt.gui.*;
import com.trolltech.qt.webkit.*;


public class CTest extends QObject { 


public static void main(String args[]) { 

QApplication.initialize(args); 

QWebView view = new QWebView();
//view.settings().
view.setGeometry(50, 50, 800, 600);

//view.setHtml("<button onclick=\"alert('����ֵ�');\" style=\"width:100px; height:100px; border-radius:100px; border:1px solid #ccc; background:#f3f3f3; font-size:12px; color:#000; cursor:pointer;\">����һ����ť</button>");

view.load(new QUrl("http://www.baidu.com")); 

view.show();

//QApplication.execStatic(); 

QApplication.quit(); 

} 

} 

/*
public class CWebHandler extends QMainWindow {

    private QWebView browser;
    private QLineEdit field;

    private QAction forward;
    private QAction backward;
    private QAction reload;
    private QAction stop;

    public CWebHandler() {
    this(null);
    }

    public CWebHandler(QWidget parent) {
    super(parent);

        field = new QLineEdit();
        browser = new QWebView();

        // Toolbar...
        QToolBar toolbar = addToolBar("Actions");
        backward = toolbar.addAction("Backward");
        forward = toolbar.addAction("Forward");
        reload = toolbar.addAction("Reload");
        stop = toolbar.addAction("Stop");
        toolbar.addWidget(field);
        toolbar.setFloatable(false);
        toolbar.setMovable(false);

        setCentralWidget(browser);
        statusBar().show();

	setWindowTitle("Hello WebKit");
        setWindowIcon(new QIcon("classpath:com/trolltech/images/qt-logo.png"));	

        // Connections
        field.returnPressed.connect(this, "open()");

        browser.loadStarted.connect(this, "loadStarted()");
        browser.loadProgress.connect(this, "loadProgress(int)");
        browser.loadFinished.connect(this, "loadDone()");
        browser.urlChanged.connect(this, "urlChanged(QUrl)");

        forward.triggered.connect(browser, "forward()");
        backward.triggered.connect(browser, "back()");
        reload.triggered.connect(browser, "reload()");
        stop.triggered.connect(browser, "stop()");



        // Set an initial loading page once its up and showing...
        QApplication.invokeLater(new Runnable() {
                public void run() {
                    field.setText("http://www.qtsoftware.com");
                    open();
                }
            });
    }

    public void urlChanged(QUrl url) {
        field.setText(url.toString());
    }

    public void loadStarted() {
        statusBar().showMessage("Starting to load: " + field.text());
    }

    public void loadDone() {
        statusBar().showMessage("Loading done...");
    }

    public void loadProgress(int x) {
        statusBar().showMessage("Loading: " + x + " %");
    }

    public void open() {
        String text = field.text();

        if (text.indexOf("://") < 0)
            text = "http://" + text;

        browser.load(new QUrl(text));
    }

    @Override
    protected void closeEvent(QCloseEvent event) {
        browser.loadProgress.disconnect(this);
        browser.loadFinished.disconnect(this);
    }
    
    public static void main(String args[]) {
        QApplication.initialize(args);

        CWebHandler widget = new CWebHandler();
        widget.show();

        QApplication.execStatic();
        QApplication.shutdown();
    }
    
}
*/
