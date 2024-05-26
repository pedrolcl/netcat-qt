// SPDX-License-Identifier: MIT
// Copyright (c) 2024 Pedro López-Cabanillas <plcl@users.sf.net>

#include "netclient.h"

#include <QTcpSocket>
#include <QDebug>

NetClient::NetClient(QObject *parent)
    : QObject(parent)
{}

NetClient::~NetClient()
{
    if (m_tcpSocket) {
        m_tcpSocket->close();
    }
}

bool NetClient::connectToHost(QHostAddress hostAddress, int port)
{
    m_tcpSocket = new QTcpSocket(this);
    m_tcpSocket->setReadBufferSize(1024 * 1024);
    m_tcpSocket->connectToHost(hostAddress, port);
    if (!m_tcpSocket->waitForConnected()) {
        qWarning() << "Couldn't connect to host.";
        delete m_tcpSocket;
        return false;
    }
    connect(m_tcpSocket, &QTcpSocket::readyRead, this, &NetClient::readFromSocket);
    connect(m_tcpSocket, &QTcpSocket::disconnected, this, &NetClient::closedConnection);
    emit connectionOpened();
    return true;
}

bool NetClient::isConnected()
{
    if (m_tcpSocket) {
        return m_tcpSocket->isOpen();
    }
    return false;
}

void NetClient::readFromSocket()
{
    if (m_tcpSocket) {
        QByteArray buffer = m_tcpSocket->readAll();
        while (m_tcpSocket->waitForReadyRead(1)) {
            buffer += m_tcpSocket->readAll();
        }
        emit dataRead(buffer);
    }
}

void NetClient::writeToSocket(const QByteArray &bytes)
{
    if (m_tcpSocket) {
        m_tcpSocket->write(bytes);
        m_tcpSocket->flush();
    }
}

void NetClient::closedConnection()
{
    if (m_tcpSocket) {
        m_tcpSocket->deleteLater();
        emit connectionClosed();
    }
}
