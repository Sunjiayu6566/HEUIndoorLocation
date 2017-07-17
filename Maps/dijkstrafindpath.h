#ifndef DIJKSTRAFINDPATH_H
#define DIJKSTRAFINDPATH_H
#include <QStack>


class EData
{
    public:
        int start; // 边的起点
        int end;   // 边的终点
        int weight; // 边的权重
    public:
        EData(){}
        EData(int s, int e, int w):start(s),end(e),weight(w){}
};



class DijkstraFindPath
{
    static const int MAX = 31;
    static const int INF = 999999;
       // 最大值(即0X7FFFFFFF)
 private: // 内部类
        // 邻接表中表对应的链表的顶点
        class ENode
        {
            int ivex;           // 该边所指向的顶点的位置
            int weight;         // 该边的权
            ENode *nextEdge;    // 指向下一条弧的指针
            friend class DijkstraFindPath;
        };

        // 邻接表中表的顶点
        class VNode
        {
            int data;          // 顶点信息
            ENode *firstEdge;   // 指向第一条依附该顶点的弧
            friend class DijkstraFindPath;
        };

    private: // 私有成员
        int mVexNum;             // 图的顶点的数目
        int mEdgNum;             // 图的边的数目
        VNode mVexs[MAX];
    public:
        // 创建邻接表对应的图(自己输入)
        DijstraFindPath();
        // 创建邻接表对应的图(用已提供的数据)
       DijkstraFindPath(int vexs[], int vlen, EData *edges[], int elen);
        ~DijkstraFindPath();
       QStack<int> dijkstra(int vs, int es,int prev[], int dist[]);

    private:
        // 返回ch的位置
        int getPosition(char ch);
        // 深度优先搜索遍历图的递归实现
        void linkLast(ENode *list, ENode *node);
        // 获取边<start, end>的权值；若start和end不是连通的，则返回无穷大。
        int getWeight(int start, int end);
        // 获取图中的边
};

#endif // DIJKSTRAFINDPATH_H
