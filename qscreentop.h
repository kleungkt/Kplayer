#ifndef QSCREENTOP_H
#define QSCREENTOP_H

#include <QObject>
#include <QWidget>

class QScreenTop : public QWidget
{
    Q_OBJECT
public:
    explicit QScreenTop(QWidget* parent = nullptr);
    void setText(const QString& text);
protected:
    //virtual void paintEvent(QPaintEvent* event);
signals:

private:
    QString m_text;
};

#endif // QSCREENTOP_H
