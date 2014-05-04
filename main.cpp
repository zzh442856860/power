//my include
#include "mypower.h"

//qt include
#include <QtCore/QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>



void customMsgHandler(QtMsgType type, const char *msg)
{
    QString txt;
    switch(type){
    case QtDebugMsg:
        txt = QString("%1Debug:%2").arg(QDateTime::currentDateTime().toString(Qt::ISODate)).arg(msg);
        break;
    default:break;
    }
    QFile dplFile("debugWirelessLog.txt");
    dplFile.open(QIODevice::ReadWrite| QIODevice::Append);
    QTextStream ts(&dplFile);
    ts<<txt<<endl;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qInstallMsgHandler(customMsgHandler);

    myPower xx;
    return a.exec();
}
