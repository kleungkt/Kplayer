#ifndef MESSAGEFORM_H
#define MESSAGEFORM_H
#include <Windows.h>
#include <QtWin>
#include <QWidget>
#include <QImage>

namespace Ui
{
    class MessageForm;
}

class MessageForm : public QWidget
{
    Q_OBJECT

public:
    explicit MessageForm(QWidget* parent = nullptr);
    ~MessageForm();
    void set_widget(QWidget* bkgnd)
    {
        backgnd = bkgnd;
    }
    void full_size()
    {
        setGeometry(0, 0, screen_width, 200);
    }
    void setText(const QString& text);
protected:
    virtual void paintEvent(QPaintEvent* event);
    QImage CopyDCToBitmap(HWND hWnd);
private:
    Ui::MessageForm* ui;
    QWidget* backgnd;
    QImage* top;
    int screen_width;
    QString text;
};

#endif // MESSAGEFORM_H
