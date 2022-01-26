#include "webclient.h"

Webclient::Webclient(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    m_socket = new QTcpSocket(this);
    connect(m_socket, &QTcpSocket::connected, this, &Webclient::Connected);
    connect(m_socket, &QTcpSocket::readyRead, this, &Webclient::ReadyRead);
}


void Webclient::on_Button_clicked()
{
    Ausgabe->clear();
    if(!Adresse->text().isEmpty()){

        m_address=Adresse->text();
        m_socket->connectToHost(m_address, m_port);
        if(!m_socket->waitForConnected(5000))
        {
           Ausgabe->setText("Konnte nicht verbinden");
        m_socket->reset();
        }
    }
    else
    {
        Ausgabe->setText("Keine Eingabe");
    }
}

void Webclient::Connected()
{
    m_socket->write(QString("GET / HTTP/1.1\r\nHost:" + m_address + "\r\n\r\n").toLocal8Bit());
}

void Webclient::ReadyRead()
{
    Ausgabe->setText(m_socket->readAll());
    m_socket->disconnectFromHost();
}
