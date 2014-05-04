//mu include
#include "mypower.h"

//qt include
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <QTimer>
#include <QDebug>

const int kTimeOut = 500;

myPower::myPower(QObject *parent) :
    QObject(parent)
{
    InitXml();
    timer = new QTimer(this);
    timer->start(kTimeOut);
    connect(timer, SIGNAL(timeout()),this, SLOT(ReadXml()));
}

void myPower::InitXml()
{
    QFile power_xml("power.xml");
    if(!power_xml.open(QIODevice::WriteOnly)){
        qDebug()<<QString("Init power_xml Fail! \033[31mError\033[0m: %1").arg(power_xml.errorString());
        return;
    }
    QXmlStreamWriter flagXmlWriter(&power_xml);
    flagXmlWriter.setAutoFormatting(true);
    flagXmlWriter.writeStartDocument();
    flagXmlWriter.writeStartElement("power");
    flagXmlWriter.writeTextElement(QString("flag"), QString("%1").arg(0));  //0: insignificance  1:shut down now  2:reboot
    flagXmlWriter.writeEndElement();
    flagXmlWriter.writeEndDocument();
    power_xml.close();
    system("chmod 777 power.xml");

}

void myPower::ReadXml()
{
    QFile file("power.xml");
    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<QString("Open power.xml Fail in ReadXml! \033[31mError\033[0m: %1").arg(file.errorString());
        return;
    }
    int flag = 0;
    bool ok = 0;
    QXmlStreamReader xmlReader(&file);

    while(!xmlReader.atEnd()){
        xmlReader.readNext();
        if(xmlReader.name() == "flag"){
            flag = xmlReader.readElementText().toInt(&ok);
        }
    }
    file.close();
    this->InitXml();

    if(flag==1){
        qDebug()<<"flag==1";
        system("shutdown -h now");
    }else if(flag==2){
        qDebug()<<"flag==2";
        system("reboot");
    }else{

    }
}

