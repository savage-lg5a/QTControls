#include "qthreadpooldemo.h"
#include "ui_qthreadpooldemo.h"
#include <QDebug>
#include <QThreadPool>

QThreadPoolDemo::QThreadPoolDemo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QThreadPoolDemo)
{
    ui->setupUi(this);
}

QThreadPoolDemo::~QThreadPoolDemo()
{
    delete ui;
}

void QThreadPoolDemo::on_btn_start_clicked()
{
    qDebug()<< "start";

    // 获取进度条指针
    QStringList progObjName;
    QList<QProgressBar*> progBars;
    progBars << ui->progressBar<< ui->progressBar_2 << ui->progressBar_3 << ui->progressBar_4
             << ui->progressBar_5<< ui->progressBar_6<< ui->progressBar_7<< ui->progressBar_8
             << ui->progressBar_9<< ui->progressBar_10<< ui->progressBar_11<< ui->progressBar_12
             << ui->progressBar_13<< ui->progressBar_14<< ui->progressBar_15<< ui->progressBar_16;

    for(auto iter : qAsConst(progBars))
    {
        progObjName << iter->objectName();
        iter->setValue(0);
    }

    QThreadPool::globalInstance()->setMaxThreadCount(4);

    for (int i = 0; i < progObjName.size(); ++i)
    {
           Task *task = new Task(i, progObjName.at(i));         // 创建任务
           QThreadPool::globalInstance()->start(task);          // 提交任务给线程池，在线程池中执行
           connect(task, SIGNAL(updateProgValue(QString, int)),
                   this, SLOT(OnUpdateValue(QString, int)));
    }
}

void QThreadPoolDemo::OnUpdateValue(QString name, int value)
{
    QProgressBar* progBar = findChild<QProgressBar*>(name);
    if(nullptr != progBar)
    {
        progBar->setValue(value);
    }
}

