#include "mainmenu.h"

MainMenu::MainMenu(QWidget *widget)
    : QMenu(widget)
{
    this->createActions();
    this->translateActions();
}

void MainMenu::createActions()
{
    //创建菜单项
    action_location = new QAction(this);
    action_data = new QAction(this);
    action_filter = new QAction(this);
    action_logs = new QAction(this);
    action_aboutus = new QAction(this);

//    action_about_us->setIcon(QIcon(":/mainMenu/about"));

    //添加菜单项
    this->addAction(action_location);
    this->addAction(action_data);
    this->addAction(action_filter);
    this->addAction(action_logs);
    this->addAction(action_aboutus);

    //设置信号连接
    QObject::connect(action_location, SIGNAL(triggered()), this, SIGNAL(showLocationInterface()));
    QObject::connect(action_data, SIGNAL(triggered()), this, SIGNAL(showDataTrans()));
    QObject::connect(action_filter, SIGNAL(triggered()), this, SIGNAL(showFilterSet()));
    QObject::connect(action_logs, SIGNAL(triggered()), this, SIGNAL(showLogs()));
    QObject::connect(action_aboutus, SIGNAL(triggered()), this, SIGNAL(showAboutUs()));

}

void MainMenu::translateActions()
{
    action_location->setText(QStringLiteral("定位接口配置"));
    action_data->setText(QStringLiteral("数据转发配置"));
    action_filter->setText(QStringLiteral("过滤器参数及设置"));
    action_logs->setText(QStringLiteral("日志"));
    action_aboutus->setText(QStringLiteral("关于我们"));

}
