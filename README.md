# NetCat implementation using Qt

This is a basic `netcat` implementation ( see [nc(1)](https://linux.die.net/man/1/nc) ), using Qt6 widgets and Qt6 Network. The console window is based on ConsoleWidget (see below).

The defaults are the same as the FluidSynth shell interface, and that is why this app has been developed. You can start the synth with a `-s` command line argument, and then use this program to connect to fluidsynth, even from another computer!

```shell
$ fluidsynth -s
```

```shell
$ netcat-qt -a localhost -p 9800
```

![screenshot](screenshot.png)

Another alternative providing a GUI shell interface for the FluidSynth library is [fluidsynt-qt-gui](https://github.com/pedrolcl/fluidsynth-qt-gui).

# ConsoleWidget

This component was developed by George Apostolopoulos in 2020 as part of [**QDaq** - Qt-based Data Acquisition](https://gitlab.com/qdaq/qdaq) and forked by Pedro López-Cabanillas in 2024 from [this GitHub repository](https://github.com/gapost/qconsolewidget).

This is a lightweight Qt console widget based on QPlainTextEdit providing also a QIODevice interface.

It can be used as an interactive scripting terminal or a log window. Features include standard console-like editing, command history, formatted input, output & error streams.

TODO: syntax highlighting

## Usage

Instantiate the widget and set it to input mode. Connect a QObject slot
to the consoleCommand signal to receive the user input.

```c++
ConsoleWidget w;
w.writeStdOut("enter command> ");
w.setMode(ConsoleWidget::Input);
QObject::connect(&w,SIGNAL(consoleCommand(QString)),MyQObject,SLOT(evalCommand(QString)))
...
MyQObjet::evalCommand(const QString& code)
{
    ...
}
```

Alternatively you can use a QTextStream to interact with ConsoleWidget:

```c++
ConsoleWidget w;
w.device()->open(QIODevice::ReadWrite); // open the console's QIODevice
QTextStream stream(w.device());
stream << "Hello World!" << endl; // output goes to the widget
```

The stream can also be used for input

```c++
stream << "Enter an integer n = " << flush;
int n;
stream.device()->waitForReadyRead();
stream >> n;
```
The call to ```waitForReadyRead()``` enters a local loop waiting for
the user to enter a command and hit return. 

## License

SPDX-License-Identifier: MIT  
Copyright (c) 2020 George Apostolopoulos  
Copyright (c) 2024 Pedro López-Cabanillas <plcl@users.sf.net>
