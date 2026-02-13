#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>
#include <QDebug>
#include <QRegularExpression>
#include <QTimer>
#include <QProcess>


class TCPSocket : public QObject
{
    Q_OBJECT

public:

    explicit TCPSocket(bool debugMode, QString programName, QStringList pArgs, QObject *parent = nullptr);

    ~TCPSocket();

    //Connects to TCP Socket and Waits for Connection
    void Connect();
    //Disconnects the TCP Socket
    void Disconnect();

public slots:

    //Read Data from TCP Socket
    void TCPReadData();

    //When TCP Connects
    void SocketConnected();

    //When TCP Socket Disconnects
    void SocketDisconnected();

    //When Connection Times Out
    void TCPConnectionTimeOut();


signals:


private:


    ///////////////////////////////////////////////////////////////////////////

    //TCP Socket Connection
    QTcpSocket *p_hookSocket;
    bool isConnected;

    //Timer
    QTimer *p_waitingForConnection;

    //read Data
    QByteArray readData;

    //Process
    QProcess process;

    //Variables
    bool debug;
    QString program;
    QStringList programArguments;
    QString romName;


};

#endif // TCPSOCKET_H
