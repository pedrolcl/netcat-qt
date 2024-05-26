// SPDX-License-Identifier: MIT
// Copyright (c) 2024 Pedro López-Cabanillas <plcl@users.sf.net>

#include <QApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <QString>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    using namespace Qt::Literals::StringLiterals;

    QCoreApplication::setApplicationName("netcat-qt");
    QCoreApplication::setApplicationVersion(QT_STRINGIFY(VERSION));
    QApplication app(argc, argv);
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption addressOption({"a", "address"},
                                     "The name or address of the host to connect [localhost].",
                                     "hostAddress",
                                     "localhost");
    parser.addOption(addressOption);
    QCommandLineOption portOption({"p", "port"},
                                  "The port number of the service to connect [9800].",
                                  "portNumber",
                                  "9800");
    parser.addOption(portOption);
    parser.process(app);

    MainWindow w;
    if (w.openConnection(parser.value(addressOption), parser.value(portOption))) {
        w.show();
        return app.exec();
    }
    return EXIT_FAILURE;
}
