# SPDX-License-Identifier: MIT
# Copyright (c) 2024 Pedro López-Cabanillas <plcl@users.sf.net>

cmake_minimum_required(VERSION 3.19)

project( netcat-qt
    VERSION 0.0.1
    LANGUAGES CXX
)

find_package (Qt6 REQUIRED COMPONENTS Core Gui Widgets Network)

qt_standard_project_setup()

qt_add_executable( ${PROJECT_NAME}
    ConsoleIODevice.cpp
    ConsoleIODevice.h
    ConsoleWidget.cpp
    ConsoleWidget.h
    fluidcompleter.h
    fluidcompleter.cpp
    main.cpp
    mainwindow.h
    mainwindow.cpp
    netclient.h
    netclient.cpp
)

target_compile_definitions( ${PROJECT_NAME} PRIVATE
    VERSION=${PROJECT_VERSION}
)

target_link_libraries ( ${PROJECT_NAME} PRIVATE
    Qt::Core
    Qt::Gui
    Qt::Widgets
    Qt::Network
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
