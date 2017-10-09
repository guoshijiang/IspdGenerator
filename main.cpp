#include "mainwindow.h"

#include <QApplication>
#include <QString>
#include <QTextStream>
#include <QDateTime>
#include <QDate>
#include <QFile>
#include <QDir>
#include <QMessageLogContext>
#include <QMutex>
#include <QMutexLocker>
#include <QTextCodec>
#include <QDebug>
#include <QtGlobal>
#include <QMessageBox>

QFile* global_log_file = NULL;

#define _TIME_ qPrintable (QTime::currentTime ().toString ("hh:mm:ss:zzz"))


void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context)
    if  (NULL == global_log_file)
        return;
    QString mstr;
    switch (type)
    {
        case QtDebugMsg:
            mstr = "[D]: " + msg;
            break;
        case QtInfoMsg:
            mstr = "[I]: " + msg;
            break;
        case QtWarningMsg:
            mstr = "[W]: " + msg;
            break;
        case QtCriticalMsg:
            mstr = "[C]: " + msg;
            break;
        case QtFatalMsg:
            mstr = "[F]: " + msg;
            abort();
    }
    QTextStream Output(global_log_file);
    Output << mstr << endl;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString path = QCoreApplication::applicationDirPath();
    QString filename = path + "/data/data.log";
    global_log_file = new QFile(filename);
    if (!global_log_file->open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        delete global_log_file;
        global_log_file = NULL;
    }
    //qInstallMessageHandler(myMessageOutput);

    MainWindow w; 
    w.start();
    return a.exec();
}
