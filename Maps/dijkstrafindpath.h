#ifndef DIJKSTRAFINDPATH_H
#define DIJKSTRAFINDPATH_H
#include <QStack>


class EData
{
    public:
        int start; // �ߵ����
        int end;   // �ߵ��յ�
        int weight; // �ߵ�Ȩ��
    public:
        EData(){}
        EData(int s, int e, int w):start(s),end(e),weight(w){}
};



class DijkstraFindPath
{
    static const int MAX = 31;
    static const int INF = 999999;
       // ���ֵ(��0X7FFFFFFF)
 private: // �ڲ���
        // �ڽӱ��б��Ӧ������Ķ���
        class ENode
        {
            int ivex;           // �ñ���ָ��Ķ����λ��
            int weight;         // �ñߵ�Ȩ
            ENode *nextEdge;    // ָ����һ������ָ��
            friend class DijkstraFindPath;
        };

        // �ڽӱ��б�Ķ���
        class VNode
        {
            int data;          // ������Ϣ
            ENode *firstEdge;   // ָ���һ�������ö���Ļ�
            friend class DijkstraFindPath;
        };

    private: // ˽�г�Ա
        int mVexNum;             // ͼ�Ķ������Ŀ
        int mEdgNum;             // ͼ�ıߵ���Ŀ
        VNode mVexs[MAX];
    public:
        // �����ڽӱ��Ӧ��ͼ(�Լ�����)
        DijstraFindPath();
        // �����ڽӱ��Ӧ��ͼ(�����ṩ������)
       DijkstraFindPath(int vexs[], int vlen, EData *edges[], int elen);
        ~DijkstraFindPath();
       QStack<int> dijkstra(int vs, int es,int prev[], int dist[]);

    private:
        // ����ch��λ��
        int getPosition(char ch);
        // ���������������ͼ�ĵݹ�ʵ��
        void linkLast(ENode *list, ENode *node);
        // ��ȡ��<start, end>��Ȩֵ����start��end������ͨ�ģ��򷵻������
        int getWeight(int start, int end);
        // ��ȡͼ�еı�
};

#endif // DIJKSTRAFINDPATH_H
