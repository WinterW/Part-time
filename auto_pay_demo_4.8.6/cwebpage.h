#ifndef CWEBPAGE_H
#define CWEBPAGE_H

#include <QtWebKit/QWebPage>

class CWebPage : public QWebPage
{
protected:
    QString userAgentForUrl(QUrl url);
    
};

#endif // CWEBPAGE_H
