#ifndef BASESTATIONASESTATIONDAO_H
#define BASESTATIONASESTATIONDAO_H

#include <QObject>
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>
#include <QSqlError>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>
#include "basemodel.h"
class BaseInfo;
class BaseStationDao : public QObject
{
    Q_OBJECT

private:
    const QString dataBaseName = "baseStationTable";

    QString create_sql = "create table if not exists "+dataBaseName
            +"(id integer primary key, mac varchar,bstype varchar,x int, y int, z int,remark varchar)";
    QString select_max_sql = "select max(id) from "+dataBaseName;
    QString insert_sql = "insert into "+dataBaseName+"(id,mac,bstype,x,y,z,remark) values(?,?,?,?,?,?,?)";
    QString update_sql = "update "+dataBaseName+"set mac:=mac, bstype:=bstype, x:=x, y:=y, z:=z, remark:=remark where id=:id";
    QString select_all_sql = "select id,mac,bstype,x,y,z,remark from "+dataBaseName;
    QString delete_sql = "delete from "+dataBaseName+" where id =?";
    QString clear_sql = "delete from "+dataBaseName;
    QSqlDatabase db;// = QSqlDatabase::database("QSQLITE"); //建立数据库连接
    QSqlQuery* qry;
public:
    BaseStationDao();
    bool insert(BaseInfo b);            //出入数据
    QVector<BaseInfo> getPageList(BaseInfo info,int page = 1,int pageSize = 10);
    bool deleteById(int id);
    bool update(BaseInfo info);

signals:

public slots:

};

#endif // BASESTATIONASESTATIONDAO_H
