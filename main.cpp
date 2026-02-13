#include <QCoreApplication>
#include <QDebug>

#include "TCPSocket.h"

#include <windows.h>

//Sub Fuctions
void ShowHelp();


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.



    bool debug = false;
    bool noHide = false;
    QStringList arguments;
    QString programName;
    QStringList programArguments;
    quint8 count = 0;

    if(argc > 1)
    {
        //Move Arguments to QStrings in a QStringList
        for(quint8 i = 1; i < argc; i++)
            arguments << argv[i];

        //Check for Help or Debug
        for(quint8 i = 0; i < arguments.count(); i++)
        {
            if(arguments[i] == "-h")
            {
                //Show Help and Quit
                ShowHelp();
                return 1;
            }
            else if(arguments[i] == "-ddd")
            {
                debug = true;
            }
            else if(arguments[i] == "-noHide")
            {
                noHide = true;
            }
            else
            {
                if(count == 0)
                {
                    programName = arguments[i];
                    count++;
                }
                else
                {
                    programArguments << arguments[i];
                    count++;
                }

            }
        }

        if(count == 0)
        {
            //Show Help and Quit
            ShowHelp();
            return 1;
        }
    }
    else
    {
        //Show Help and Quit
        ShowHelp();
        return 1;
    }

    if(noHide && !debug)
        ShowWindow(GetConsoleWindow(), SW_MINIMIZE);
    else if(!debug)
        ShowWindow(GetConsoleWindow(), SW_HIDE);

    TCPSocket socketConnection(debug, programName, programArguments);


    socketConnection.Connect ();


    return a.exec();
}


//Show Help
void ShowHelp()
{
    qDebug() << "v1.0 of ROMSniffer";
    qDebug() << "ROMSniffer Program Arguments";
    qDebug() << "The ROM name can be used as %r% in the Arguments. The %r% will be replaced by the ROM name.";
    qDebug() << "Example: .\\ROMSniffer.exe Program.exe -x %r%.json";
    qDebug() << "Options";
    qDebug() << "-h: Shows Help Info, which is this. Also doesn't run program and quits.";
    qDebug() << "-ddd: Shows Debug Info when program is running. Doesn't hide command prompt.";
    qDebug() << "-noHide: Doesn't hide the command prompt, but minimizes it.";
    qDebug() << "Stop Program";
    qDebug() << "CNTRL-C: To stop the program";
}
