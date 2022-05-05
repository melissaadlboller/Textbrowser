#include "httpclient.h"
#include <QDebug
#include <QTcpSocket>
#include <QCoreApplication>

HttpClient::HttpClient(int argc, char* argv[], QObject *parent) : QObject(parent)
{
    qDebug("Argc = %d", argc);
    for ( int i = 0; i < argc; i++)
        qDebug("argc %d = %s", i, argv[i]);

    QTcpSocket* socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::connected, this, &HttpClient::connected);
    connect(socket, &QTcpSocket::readyRead, this, &HttpClient::readyRead);

    if ( argc == 2 )
    {
        QString host = argv[1];
        quint16 port;

        for ( port = 1; port < 1024; port++)
        {
            socket->connectToHost( host, port);

            if (!socket->waitForConnected(TIMEOUT))
            {
                //qDebug("Port %d: Can not connect", port);
            }
            else
            {
                qDebug("Port %d: Connected !", port);
                socket->disconnectFromHost();
            }
       }
    }
}
