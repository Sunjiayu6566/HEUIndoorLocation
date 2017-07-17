#include "filterset.h"
#include "ui_filterset.h"

FilterSet::FilterSet(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FilterSet)
{
    ui->setupUi(this);

    QVBoxLayout *v1 =new QVBoxLayout();
    v1->setSpacing(10);
    v1->setAlignment(Qt::AlignLeft);
    v1->setContentsMargins(10,0,10,10);

    QWidget *widget =new QWidget();
    setCentralWidget(widget);
    widget->setLayout(v1);

    QHBoxLayout *h3 = new QHBoxLayout();
    h3->setContentsMargins(0,0,0,0);
    h3->setAlignment(Qt::AlignLeft);
    systemset = new QLabel();
    systemset->setText(QStringLiteral("系统配置"));
    h3->addWidget(systemset);

    QHBoxLayout *h2 = new QHBoxLayout();
    h2->setAlignment(Qt::AlignLeft);
    h2->setContentsMargins(0,0,0,0);
    h2->setSpacing(10);

    reset = new QToolButton();
    reset->setText(QStringLiteral("还原默认"));

    fresh = new QToolButton();
    fresh->setText(QStringLiteral("还原默认"));
    h2->addWidget(reset);
    h2->addWidget(fresh);

    QHBoxLayout *h1 =new QHBoxLayout();
    h1->setSpacing(10);
    list1=new QListView();
    list1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy :: Expanding);

    table1 = new QTableView();
    table1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy :: Expanding);

    h1->addWidget(list1,1);
    h1->addWidget(table1,4);

    QHBoxLayout *h4 =new QHBoxLayout();
    h4->setContentsMargins(0,0,0,0);
    h4->setAlignment(Qt::AlignLeft);
    h4->setSpacing(0);
    widget1 = new QWidget();
    widget1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy :: Expanding);

    v1->addLayout(h3,1);
    v1->addLayout(h2,1);
    v1->addLayout(h1,10);
    v1->addLayout(h4,4);

}

FilterSet::~FilterSet()
{
    delete ui;
}
