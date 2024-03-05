#include <QtTest>
#include <QCoreApplication>
#include "loginform.h"
#include "ui_loginForm.h"
#pragma comment(lib, "Shell32.lib")
// add necessary includes here

class testVideoPlayer : public QObject
{
    Q_OBJECT

public:
    testVideoPlayer();
    ~testVideoPlayer();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_LoginForm();
    void test_LoginForm_data();

};

testVideoPlayer::testVideoPlayer()
{

}

testVideoPlayer::~testVideoPlayer()
{

}

void testVideoPlayer::initTestCase()
{

}

void testVideoPlayer::cleanupTestCase()
{

}

void testVideoPlayer::test_LoginForm()
{
    LoginForm login;//Avoid using 'new' if possible
    QCOMPARE(login.ui->nameEdit->text(),"12345678");
    QCOMPARE(login.ui->pwdEdit->text(),"test");
    for(int i=0;i<3;i++){
        login.ui->nameEdit->clear();
        login.ui->pwdEdit->clear();
        QFETCH(QString,user);
        QFETCH(QString,pwd);
        qDebug()<<user<<pwd;
        QTest::keyClicks(login.ui->nameEdit, user);
        QTest::keyClicks(login.ui->pwdEdit,pwd);
        QCOMPARE(login.ui->nameEdit->text(),user);
        QCOMPARE(login.ui->pwdEdit->text(),pwd);
    }
}

void testVideoPlayer::test_LoginForm_data()
{
    QTest::addColumn<QString>("user");
    QTest::addColumn<QString>("pwd");
    QTest::newRow("001")<<"12345678"<<"test";
    QTest::newRow("002")<<"1817619619"<<"test";
    QTest::newRow("003")<<"1069619619"<<"test";
}

QTEST_MAIN(testVideoPlayer)

#include "tst_testvideoplayer.moc"
