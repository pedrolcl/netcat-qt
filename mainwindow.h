// SPDX-License-Identifier: MIT
// Copyright (c) 2024 Pedro López-Cabanillas <plcl@users.sf.net>

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>

class ConsoleWidget;
class NetClient;
class FluidCompleter;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    FluidCompleter *m_completer{nullptr};
    ConsoleWidget *m_console{nullptr};
    NetClient *m_client{nullptr};

public:
    explicit MainWindow(QWidget *parent = nullptr);

    bool openConnection(const QString &host, const QString &port);

public slots:
    void consoleOutput(const QByteArray &data);
    void consoleInput();
};

#endif // MAINWINDOW_H
