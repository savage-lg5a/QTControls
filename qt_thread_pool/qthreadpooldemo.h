#ifndef QTHREADPOOLDEMO_H
#define QTHREADPOOLDEMO_H

#include <QObject>
#include <QRunnable>
#include <QDebug>
#include <QThread>
#include <QDateTime>
#include <QProgressBar>
#include <QRandomGenerator>

///
///
class Task : public QObject, public QRunnable
{
    Q_OBJECT

    public:
    Task(int id, QString progId, QObject *parent = nullptr) : QObject(parent),
        m_id(id),
        m_progObjName(progId)
    {

    }

    ~Task()
    {
        qDebug().noquote() << QString("~Task() with ID %1").arg(m_id); // 方便查看对象是否被 delete
    }

    void run()
    {
        qDebug().noquote() << QString("Start thread %1 at %2").arg(m_id).arg(QDateTime::currentDateTime().toString("mm:ss.z"));

        updateProgValue(m_progObjName, 0);
        QThread::msleep(500);
        updateProgValue(m_progObjName, 30);

        QThread::msleep(500 + QRandomGenerator::global()->bounded(0, 2000));
        updateProgValue(m_progObjName, 60);

        QThread::msleep(500 + QRandomGenerator::global()->bounded(0, 2000));
        updateProgValue(m_progObjName, 100);

        qDebug().noquote() << QString("End   thread %1 at %2").arg(m_id).arg(QDateTime::currentDateTime().toString("mm:ss.z"));
    }

private:
    int m_id;                   // 线程的 ID
    QString m_progObjName;      // 进度条名字

signals:

    void updateProgValue(QString name, int value);
};

///
/// \brief The QThreadPoolDemo class
///
namespace Ui {
class QThreadPoolDemo;
}

class QThreadPoolDemo : public QWidget
{
    Q_OBJECT

public:
    explicit QThreadPoolDemo(QWidget *parent = nullptr);
    ~QThreadPoolDemo();

private slots:
    void on_btn_start_clicked();
    void OnUpdateValue(QString name, int value);

private:
    Ui::QThreadPoolDemo *ui;
};

#endif // QTHREADPOOLDEMO_H
