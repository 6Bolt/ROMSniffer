#include "TCPSocket.h"

#define WAITCONNECTION      10000
#define WAITTIMER           10300

#define TCPPORT             8000

#define ROMVAR              "%r%"


TCPSocket::TCPSocket(bool debugMode, QString programName, QStringList pArgs, QObject *parent)
    : QObject{parent}
{

    isConnected = false;
    program = programName;
    programArguments = pArgs;
    debug = debugMode;

    //Create the New TCP Socket
    p_hookSocket = new QTcpSocket(this);

    //Connect Signal of when there is read data, to the slot that will read it
    connect(p_hookSocket,SIGNAL(readyRead()), this, SLOT(TCPReadData()));
    connect(p_hookSocket,SIGNAL(connected()), this, SLOT(SocketConnected()));
    connect(p_hookSocket,SIGNAL(disconnected()), this, SLOT(SocketDisconnected()));

    //Setup Wait For Connection Timer
    p_waitingForConnection = new QTimer(this);
    p_waitingForConnection->setInterval (WAITTIMER);
    p_waitingForConnection->setSingleShot (true);
    connect(p_waitingForConnection, SIGNAL(timeout()), this, SLOT(TCPConnectionTimeOut()));

}


TCPSocket::~TCPSocket()
{
    if(isConnected)
        p_hookSocket->close();

    delete p_hookSocket;

}


//public:

void TCPSocket::Connect()
{

    if(debug)
    {
        qDebug() << "Waiting for a TCP Connection";
    }

    //Set the Address for the TCP Socket
    p_hookSocket->connectToHost (QHostAddress("127.0.0.1"), TCPPORT);

    //Start Timer first before waiting
    p_waitingForConnection->start();

    //Wait for Connection - For 10s
    p_hookSocket->waitForConnected (WAITCONNECTION);

}


void TCPSocket::Disconnect()
{
    //qDebug() << "Closed TCP Connection - Disconnect";

    //Close TCP Socket
    if(isConnected)
        p_hookSocket->close ();
    else
        p_waitingForConnection->stop();
}



//public slots:

void TCPSocket::TCPReadData()
{
    bool foundROM = false;

    //Read the TCP Socket Data
    readData = p_hookSocket->readAll ();

    QString message = QString::fromStdString (readData.toStdString ());

    //Remove the \r at the end
    if(message.endsWith('\r') || message.endsWith('\n'))
        message.chop(1);

    //If Multiple Data Lines, they will be seperated into lines, using \r or \n
    //If it had 2 data lines together, then \r would be at end which is chopped off, and middle
    //QRegularExpression endLines("[\r\n]");
    QStringList tcpSocketReadData = message.split(QRegularExpression("[\r\n]"), Qt::SkipEmptyParts);

    for(quint8 x = 0; x < tcpSocketReadData.count(); x++)
    {
        if(tcpSocketReadData[x].startsWith("mame_start") && tcpSocketReadData[x] != "mame_start = ___empty")
        {
            QStringList splitData = tcpSocketReadData[x].split("=", Qt::SkipEmptyParts);
            splitData[1] = splitData[1].trimmed ();
            romName = splitData[1];
            foundROM = true;
        }
        else if(tcpSocketReadData[x].startsWith("game ="))
        {
            QStringList splitData = tcpSocketReadData[x].split("=", Qt::SkipEmptyParts);
            splitData[1] = splitData[1].trimmed ();
            romName = splitData[1];
            foundROM = true;
        }
    }


    if(foundROM)
    {
        if(debug)
            qDebug() << "Found ROM:" << romName;

        quint8 i;
        QStringList tempArg = programArguments;
        QString argAll;
        for(i = 0; i < tempArg.count(); i++)
        {
            if(tempArg[i].contains(ROMVAR))
                tempArg[i].replace(ROMVAR, romName);

            argAll.append(tempArg[i]);
            argAll.append(" ");
        }

        process.startDetached (program, tempArg);

        if(debug)
            qDebug() << "Started Program:" << program << argAll;

    }

}


void TCPSocket::SocketConnected()
{
    p_waitingForConnection->stop ();

    isConnected = true;

    if(debug)
    {
        qDebug() << "TCP Socket is Connected";
    }
}


void TCPSocket::SocketDisconnected()
{
    isConnected = false;

    if(debug)
    {
        qDebug() << "TCP Socket has been Disconnected, and Searching for New Connection";
    }

    Connect();
}

void TCPSocket::TCPConnectionTimeOut()
{
    if(!isConnected)
    {
        //Set the Address for the TCP Socket
        p_hookSocket->connectToHost (QHostAddress("127.0.0.1"), TCPPORT);

        //Start Wait for Connection Timer
        p_waitingForConnection->start ();

        //Wait for Connection
        p_hookSocket->waitForConnected (WAITCONNECTION);
    }
}



