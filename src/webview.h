#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QObject>
#include <QWebEngineView>
#include <QWidget>

class WebView : public QWebEngineView
{
    Q_OBJECT

public:
    WebView(QWidget *parent = nullptr);
};

#endif // WEBVIEW_H
