#include "messageform.h"
#include "ui_messageform.h"
#include <QDebug>
#include <QtWin>
#include <QPainter>
#include <QDesktopWidget>

RECT rect;

MessageForm::MessageForm(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::MessageForm)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//No border
    setAttribute(Qt::WA_TranslucentBackground);//transparent background
    top = new QImage(":/UI/images/"); //half transparent png as background image
    screen_width = QApplication::desktop()->width();
}


MessageForm::~MessageForm()
{
    delete ui;
    delete top;
}

void MessageForm::setText(const QString& text)
{
    this->text = text;
}


void MessageForm::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QRect r = frameGeometry();
    POINT pt = {r.right() / 2, r.bottom() + 5};
    HWND hWndBack = WindowFromPoint(pt);
    QImage image = CopyDCToBitmap(hWndBack);
    QFont font = painter.font();//(u8"Blackbody", 12, QFont::Bold, true);
    font.setPixelSize(18);
    painter.setFont(font);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.drawImage(0, 0, image, 0, 0);
    painter.drawImage(0, 0, *top, 0, 0);
    QPen pen = painter.pen();
    pen.setColor(QColor(255, 255, 255));
    painter.setPen(pen);
    r.setLeft(r.left() + 50);
    r.setTop(r.top() + 50);
    painter.drawText(r, text);
}

QImage MessageForm::CopyDCToBitmap(HWND hWnd)
{
    HDC hDC = GetWindowDC(hWnd);
    if(!hDC)
    {
        return QImage();
    }
    RECT wndRect;
    HDC hMemDC;
    HBITMAP hBitmap, hOldBitmap;
    int nWidth, nHeight;
    GetWindowRect(hWnd, &wndRect);
    nWidth = wndRect.right - wndRect.left;
    nHeight = wndRect.bottom - wndRect.top;
    hMemDC = CreateCompatibleDC(hDC);
    hBitmap = ::CreateCompatibleBitmap(hDC, nWidth, nHeight); //similar as screenshot
    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
    ::PrintWindow(hWnd, hMemDC, PW_CLIENTONLY | PW_RENDERFULLCONTENT); //same as screenshot 
    hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);
    DeleteObject(hOldBitmap);
    QImage ret = QtWin::imageFromHBITMAP(hBitmap);
    //bitmap to image, the bitmap is a capscreen of our designated window
    DeleteObject(hBitmap);
    return ret;
}
