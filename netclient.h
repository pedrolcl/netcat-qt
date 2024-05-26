// SPDX-License-Identifier: MIT
// Copyright (c) 2024 Pedro López-Cabanillas <plcl@users.sf.net>

#ifndef NETCLIENT_H
#define NETCLIENT_H

#include <QHostAddress>
#include <QPointer>

class QTcpSocket;
class NetClient : public QObject
{
    Q_OBJECT

    QPointer<QTcpSocket> m_tcpSocket;

public:
    explicit NetClient(QObject *parent = nullptr);
    ~NetClient();

    bool connectToHost(QHostAddress address, int port);
    bool isConnected();

signals:
    void dataRead(const QByteArray &bytes);
    void connectionOpened();
    void connectionClosed();

public slots:
    void readFromSocket();
    void writeToSocket(const QByteArray &bytes);
    void closedConnection();
};

#endif // NETCLIENT_H
