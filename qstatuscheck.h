#ifndef QSTATUSCHECK_H
#define QSTATUSCHECK_H

#include <QObject>
#include <QThread>

class QStatusCheck : public QThread
{
    Q_OBJECT
public:
    explicit QStatusCheck(QObject* parent = nullptr);
protected:
    virtual void run();
signals:
    void postStatus();
private:
    bool m_status;
};

#endif // QSTATUSCHECK_H
