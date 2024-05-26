// SPDX-License-Identifier: MIT
// Copyright (c) 2024 Pedro López-Cabanillas <plcl@users.sf.net>

#include <QDebug>
#include <QHostAddress>
#include <QHostInfo>
#include <QMenu>
#include <QMenuBar>

#include "ConsoleWidget.h"
#include "fluidcompleter.h"
#include "mainwindow.h"
#include "netclient.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    m_client = new NetClient(this);
    m_completer = new FluidCompleter(this);
    m_console = new ConsoleWidget(this);
    m_console->setCompleter(m_completer);
    m_console->setFont(QFont("Monospace"));
    m_console->writeStdOut("Type 'help' for help topics.\n");
    setCentralWidget(m_console);
    setWindowTitle("FluidSynth network interface");
    QMenu *file = menuBar()->addMenu("&File");
    file->addAction("E&xit", QKeySequence::Quit, this, &MainWindow::close);
    connect(m_client, &NetClient::dataRead, this, &MainWindow::consoleOutput);
    connect(m_console->device(), &QIODevice::readyRead, this, &MainWindow::consoleInput);
}

bool MainWindow::openConnection(const QString &host, const QString &port)
{
    QHostInfo hostInfo = QHostInfo::fromName(host);
    QHostAddress hostAddress = hostInfo.addresses().first();
    int portNumber = port.toInt();
    return m_client->connectToHost(hostAddress, portNumber);
}

void MainWindow::consoleOutput(const QByteArray &data)
{
    m_console->writeStdOut(QString::fromUtf8(data));
    m_console->setMode(ConsoleWidget::Input);
}

void MainWindow::consoleInput()
{
    QByteArray text = m_console->device()->readAll();
    m_client->writeToSocket(text);
    if (text == "quit\n") {
        close();
    }
}
