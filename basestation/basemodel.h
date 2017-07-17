#ifndef BASEMODEL_H
#define BASEMODEL_H
#include<QAbstractTableModel>
#include<QApplication>
#include "basestationdao.h"

class BaseStationDao;
class BaseInfo{
public:
    BaseInfo() {}
    void SetbaseID(const QString &baseID) { this->baseID = baseID; }
    QString GetbaseID() const { return baseID; }
    void SetbaseType(const QString &baseType) { this->baseType = baseType; }
    QString GetbaseType() const { return baseType; }
    void SetbaseRemark(const QString &baseRemark) { this->baseRemark = baseRemark; }
    QString GetbaseRemark() const { return baseRemark; }
    void SetbaseX( QString x) { this->baseX = x; }
    QString GetbaseX() const{ return baseX; }
    void SetbaseY( QString y)  { this->baseY = y; }
    QString GetbaseY() const{ return baseY; }
    void SetbaseZ( QString z) { this->baseZ = z; }
    QString GetbaseZ() const{ return baseZ; }
    void SetbaseMac( QString mac) { this->baseMac = mac; }
    QString GetbaseMac() const{ return baseMac; }

private:
    QString baseMac;
    QString baseID;
    QString baseType;
    QString baseRemark;
    QString baseX;
    QString baseY;
    QString baseZ;

};


class BaseModel:public QAbstractTableModel
{
    Q_OBJECT



public:
    /*
    BaseModel(const int totalColumn, const int aColumnNumWithChechBox = 0, QObject *parent = 0)
    :totalColumn(totalColumn),colNumberWithCheckBox(aColumnNumWithChechBox),
    QAbstractTableModel(parent)
    {
        dao = new BaseStationDao(0);
        rowCheckStateMap.clear();

    }
    */
    BaseModel(const int totalColumn, const int aColumnNumWithChechBox = 0, QObject *parent = 0);

public:
    typedef QVector<BaseInfo> BaseInfos;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    BaseInfos getBaseInfo(){
        return this->baseInfos;
    }

public:
    void AddBaseInfo(const BaseInfo &baseInfo);
    void appendBaseInfos(const QVector<BaseInfo> &infos);
    void removeRow(int row);
    void freshModel();
    signals:
    void BaseInfoIsChecked(const BaseInfo &baseInfo);
private:

    BaseInfos baseInfos;
    int totalColumn;
    int colNumberWithCheckBox;
    BaseStationDao *dao;

public:
    QMap<int, Qt::CheckState> rowCheckStateMap;
};










#endif // BASEMODEL_H
