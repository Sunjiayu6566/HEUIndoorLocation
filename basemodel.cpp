#include "basemodel.h"
#include <QDebug>
//�������ݵ�����

int BaseModel::rowCount( const QModelIndex &parent ) const
{
if (parent.isValid())
return 0;
return baseInfos.size();
}


//�������ݵ�����
int BaseModel::columnCount( const QModelIndex &parent ) const
{
if (parent.isValid())
return 0;
return totalColumn;
}

QVariant BaseModel::data( const QModelIndex &index, int role ) const
{
if (role == Qt::DisplayRole)
{
if (index.column() == 0)
return QString::number(index.row()+1);
if (index.column() == 1)
return baseInfos[index.row()].GetbaseID();
if (index.column() == 2)
return baseInfos[index.row()].GetbaseType();
if (index.column() == 3)
return baseInfos[index.row()].GetbaseX();
if (index.column() == 4)
return baseInfos[index.row()].GetbaseY();
if (index.column() == 5)
return baseInfos[index.row()].GetbaseZ();
if (index.column() == 6)
return baseInfos[index.row()].GetbaseRemark();
}
if (role == Qt::CheckStateRole) {
    if(index.column() == colNumberWithCheckBox) {
    if(rowCheckStateMap.contains(index.row()))
    return rowCheckStateMap[index.row()] == Qt::Checked ? Qt::Checked :
    Qt::Unchecked; return Qt::Unchecked;
    } }
    return QVariant();
}


QVariant BaseModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
{
if (section == 0)
return QString::fromLocal8Bit("���");
if (section == 1)
return QString::fromLocal8Bit("��վID");
if (section == 2)
return QString::fromLocal8Bit("��վ����");
if (section == 3)
return QString::fromLocal8Bit("��վX����");
if (section == 4)
return QString::fromLocal8Bit("��վY����");
if (section == 5)
return QString::fromLocal8Bit("��վZ����");
if (section == 6)
return QString::fromLocal8Bit("��ע");
if (section == 7)
return QString::fromLocal8Bit("ȷ��");
}

return QVariant();
}


Qt::ItemFlags BaseModel::flags( const QModelIndex &index ) const
{
    if
    (!index.isValid())
    return 0;
    if (index.column() == colNumberWithCheckBox)
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;

    return  Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}


bool BaseModel::setData( const QModelIndex &index, const QVariant &value, int role )
{
    if(!index.isValid())
        return false;
    if (role == Qt::CheckStateRole && index.column() == colNumberWithCheckBox)
    {
        if (value == Qt::Checked) //
        {
            rowCheckStateMap[index.row()] = Qt::Checked;
            if(baseInfos.size() > index.row())
            emit BaseInfoIsChecked(baseInfos[index.row()]);
        }
        else
        {
            rowCheckStateMap[index.row()] = Qt::Unchecked;
        }
    }
    return true;
}


void BaseModel::AddBaseInfo( const BaseInfo &baseInfo )
{
baseInfos.push_back(baseInfo);  //�ѻ�վ��Ϣ���뵽ҪbaseInfos�����С�
beginResetModel(); //��ʼ��ʼ��BaseModel������QTableView��������ʾ
endResetModel(); //��ʾbaseInfo�����е�ѧ����Ϣ
}


  void BaseModel::freshModel(){
      beginResetModel();
      endResetModel();
  }




