#include <Windows.h>
#include "qscreentop.h"
#include <QPainter>
#include <QBrush>
#include <QDebug>
/*RECT rect;
WNDPROC lpfnOldProc = 0;
LRESULT CALLBACK SCWndProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);
*/
QScreenTop::QScreenTop(QWidget* parent) : QWidget(parent)
{
}



void QScreenTop::setText(const QString& text)
{
    m_text = text;
}
/*
void QScreenTop::paintEvent(QPaintEvent* /*event* /)
{
    QPainter parent(parentWidget());
    QPainter painter(this);
    painter.begin(painter.device());
    QColor color(128, 128, 128, 128);
    QBrush brush(color);
    painter.setBrush(brush);
    painter.fillRect(frameGeometry(), brush);
}
*/
