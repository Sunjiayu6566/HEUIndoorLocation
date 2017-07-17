#include "dijkstrafindpath.h"
#include <QStack>
#include <qDebug>
DijkstraFindPath::DijkstraFindPath(int vexs[], int vlen, EData *edges[], int elen)
{
    int c1, c2;
    int i, p1, p2;
    int weight;
    ENode *node1, *node2;

    // 初始化"顶点数"和"边数"
    mVexNum = vlen;
    mEdgNum = elen;
    // 初始化"邻接表"的顶点
    for(i=0; i<mVexNum; i++)
    {
        mVexs[i].data = vexs[i];
        mVexs[i].firstEdge = nullptr;
    }

    // 初始化"邻接表"的边
    for(i=0; i<mEdgNum; i++)
    {
        // 读取边的起始顶点和结束顶点
        c1 = edges[i]->start;
        c2 = edges[i]->end;
        weight = edges[i]->weight;

        p1 = getPosition(c1);
        p2 = getPosition(c2);
        // 初始化node1
        node1 = new ENode();
        node1->ivex = p2;
        node1->weight = weight;
        // 将node1链接到"p1所在链表的末尾"
        if(mVexs[p1].firstEdge == nullptr)
          mVexs[p1].firstEdge = node1;
        else
            linkLast(mVexs[p1].firstEdge, node1);
        // 初始化node2
        node2 = new ENode();
        node2->ivex = p1;
        node2->weight = weight;
        // 将node2链接到"p2所在链表的末尾"
        if(mVexs[p2].firstEdge == nullptr)
          mVexs[p2].firstEdge = node2;
        else
            linkLast(mVexs[p2].firstEdge, node2);
    }
}

void DijkstraFindPath::linkLast(ENode *list, ENode *node)
{
    ENode *p = list;
    while(p->nextEdge)
        p = p->nextEdge;
    p->nextEdge = node;
}



int DijkstraFindPath::getPosition(char ch)
{
    int i;
    for(i=0; i<mVexNum; i++)
        if(mVexs[i].data==ch)
            return i;
    return -1;
}
int DijkstraFindPath::getWeight(int start, int end)
{
    ENode *node;

    if (start==end)
        return 0;

    node = mVexs[start].firstEdge;
    while (node!=nullptr)
    {
        if (end==node->ivex)
            return node->weight;
        node = node->nextEdge;
    }

    return INF;
}

QStack<int> DijkstraFindPath::dijkstra(int vs, int es,int prev[], int dist[])
{
    int i,j,k;
    int min;
    int tmp;
    int flag[MAX];      // flag[i]=1表示"顶点vs"到"顶点i"的最短路径已成功获取。

    // 初始化
    for (i = 0; i < mVexNum; i++)
    {
        flag[i] = 0;                // 顶点i的最短路径还没获取到。
        prev[i] = 0;                // 顶点i的前驱顶点为0。
        dist[i] = getWeight(vs, i);  // 顶点i的最短路径为"顶点vs"到"顶点i"的权。
    }

    // 对"顶点vs"自身进行初始化
    flag[vs] = 1;
    dist[vs] = 0;

    // 遍历mVexNum-1次；每次找出一个顶点的最短路径。
    for (i = 1; i < mVexNum; i++)
    {
        // 寻找当前最小的路径；
        // 即，在未获取最短路径的顶点中，找到离vs最近的顶点(k)。
        min = INF;
        for (j = 0; j < mVexNum; j++)
        {
            if (flag[j]==0 && dist[j]<min)
            {
                min = dist[j];
                k = j;
            }
        }
        // 标记"顶点k"为已经获取到最短路径
        flag[k] = 1;

        // 修正当前最短路径和前驱顶点
        // 即，当已经"顶点k的最短路径"之后，更新"未获取最短路径的顶点的最短路径和前驱顶点"。
        for (j = 0; j < mVexNum; j++)
        {
            tmp = getWeight(k, j);
            tmp = (tmp==INF ? INF : (min + tmp)); // 防止溢出
            if (flag[j] == 0 && (tmp  < dist[j]) )
            {
                dist[j] = tmp;
                prev[j] = k;
            }
        }
    }

    //将vs->es的点序列存储在栈中
    QStack<int> st;
    if(vs == 0){
    st.push(es);
    //qDebug() <<es;
    int sign = prev[es];
    st.push(sign);
    while(sign!=0){
        sign = prev[sign];
        st.push(sign);
    }
    st.push(vs);
    }
    else{
        st.push(es);
        int sign = prev[es];
        while(sign!=0){
            st.push(sign);
            sign = prev[sign];
        }
        st.push(vs);
    }
    return st;
    // 打印dijkstra最短路径的结果
    //std::cout << "dijkstra(" << mVexs[vs].data << "): " << endl;
    //for (i = 0; i < mVexNum; i++)
      //  cout << "  shortest(" << mVexs[vs].data << ", " << mVexs[i].data << ")=" << dist[i] << endl;
}

DijkstraFindPath::~DijkstraFindPath(){}
