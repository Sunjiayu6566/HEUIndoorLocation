#include "basestation/basestationdao.h"

BaseStationDao::BaseStationDao() : QObject()
{
    // create connection
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("sql.db");
    if( !db.open()) {
        qDebug() << QString::fromLocal8Bit("can not connect");
    } else {
        qDebug() << "connect success";
        this->qry = new QSqlQuery(db);
        // create table
        qDebug() << create_sql <<endl;
        if(qry->exec(create_sql)){
            qDebug() << QString::fromLocal8Bit("create BaseStationTable success");
        }else{
            qDebug() << QString::fromLocal8Bit("create BaseStationTable fail");
        }
    }

}

//向数据库中插入记录
bool BaseStationDao::insert(BaseInfo b) {

    //QSqlDatabase db = QSqlDatabase::database("QSQLITE"); //建立数据库连接

    int max_id = 0;
    this->qry = new QSqlQuery(db);
    qry->prepare(select_max_sql);
    if(!qry->exec())
    {
        qDebug()<<"max id error";
        qDebug()<<qry->lastError();
        return false;
    }
    else
    {
        while(qry->next())
        {
            max_id = qry->value(0).toInt();
            qDebug()<<QString("max id:%1").arg(max_id);
        }
    }
    qry->prepare(this->insert_sql);
    qry->addBindValue(max_id+1);
    qry->addBindValue(b.GetbaseMac());
    qry->addBindValue(b.GetbaseType());
    qry->addBindValue(b.GetbaseX());
    qry->addBindValue(b.GetbaseY());
    qry->addBindValue(b.GetbaseZ());
    qry->addBindValue(b.GetbaseRemark());
    if( !qry->exec() ){
     qDebug()<<"insert error";
     return false;
    }else
       return true;
}

 QVector<BaseInfo> BaseStationDao::getPageList(BaseInfo info,int page,int pageSize){
     QVector<BaseInfo> list;
     QString sql = this->select_all_sql+" where 1=1";
      this->qry = new QSqlQuery(db);
     qry->prepare(sql);
     if(!qry->exec())
     {
        qDebug()<<qry->lastError();
     }
     else
     {
         while(qry->next())
         {
             BaseInfo info;
             info.SetbaseID(qry->value(0).toString());
             info.SetbaseMac( qry->value(1).toString());
             info.SetbaseType(qry->value(2).toString());
             info.SetbaseX(qry->value(3).toString());
             info.SetbaseY(qry->value(4).toString());
             info.SetbaseZ(qry->value(5).toString());
             info.SetbaseRemark(qry->value(6).toString());
             list.push_back(info);
         }
     }
     return list;
 }

bool BaseStationDao::deleteById(int id){
     this->qry = new QSqlQuery(db);
   qry->prepare(this->delete_sql);
   qry->addBindValue(id);
   if(qry->exec()){
       return true;
   }else{
       qDebug()<<qry->lastError()<<endl;
       return false;
   }

}
bool BaseStationDao::update(BaseInfo info){
     this->qry = new QSqlQuery(db);
    qry->prepare(this->update_sql);
    qry->bindValue(":mac",info.GetbaseMac());
    qry->bindValue(":x",info.GetbaseX());
    qry->bindValue(":y",info.GetbaseY());
    qry->bindValue(":z",info.GetbaseZ());
    qry->bindValue(":remark",info.GetbaseRemark());
    qry->bindValue(":bstype",info.GetbaseType());
    qry->bindValue(":id",info.GetbaseID());
    if(qry->exec()){
        return true;
    }else{
        qDebug()<<qry->lastError()<<endl;
        return false;
    }
}
