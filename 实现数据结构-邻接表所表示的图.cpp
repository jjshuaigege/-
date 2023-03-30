#include <iostream>
#define MaxVertexNum 50
#define DataType char
#define WeightType int
using namespace std;

typedef int vertex;

struct Edgenode_
{
	vertex v1;
	vertex v2;
	int weight;
};
typedef Edgenode_* PtrToEdge;
typedef PtrToEdge Edge;



/*
��Ϊ���飺������ͱ߽��
�������������ţ���Ž������ݣ���һ���ڽӵ�ĵ�ַ
�߽�����������ʽ��ţ���űߵ��յ㶥����±꣬�ߵ�Ȩ�أ���һ���߽�㣨�ھӣ��ĵ�ַ 
*/


struct eNode_

{
	vertex EndvNodeIndex;
	WeightType weight;
	eNode_* nextvNode_;
	
};


typedef struct vNode_
{
	DataType data;
	eNode_* FirstAdj;
} *AdjList;

class LGNode
{
	private:
		int Vnum;
		int Enum;
		AdjList G[MaxVertexNum];
		bool HasDirection;
	public:
		LGNode(int VertexNum,bool HasDirection=false, DataType* data=nullptr):Vnum(VertexNum),Enum(0),HasDirection(HasDirection)
		{
			initialize(data);
		}
		
		//��ͼ���½��г�ʼ��(ȥ�����бߣ��������һ�����飬�����ո�������Ϊ�������㸳ֵ�����򶥵��ֵ����ԭ��) 
		void initialize(DataType* data=nullptr)
		{
			for(vertex i=0;i<Vnum;i++)
			{
				//��ָ������ĸ���ָ�����һƬ�ռ�
				G[i] = new vNode_; 
				if(data)
				{
					//��������㸳ֵ
					G[i]->data = data[i];
				}
				//�������߸�ֵ 
				G[i]->FirstAdj=nullptr;
				
			}
				
		}
		void insertNode()
		{
			Vnum++;
		}
		bool insertEdge(Edge eg)
		{
			bool ret = true;
			vertex v1 = eg->v1;
			vertex v2 = eg->v2;
			if(v1 == v2 || v1>=Vnum || v2>=Vnum)    //����ߵ����߶���ĺϷ��� 
			{
				ret=false;
			}
			else
			{
				// v1 �� v2 
				//�½�һ���߽�� 
				eNode_* temp = new eNode_;
				temp->EndvNodeIndex = v2;
				temp->weight = eg->weight;
				//ͷ�巨 
				temp->nextvNode_ = G[v1]->FirstAdj;
				G[v1]->FirstAdj = temp;
					
				if(HasDirection) // v2 �� v1 
				{
					//�½�һ���߽�� 
					temp = new eNode_;
					temp->EndvNodeIndex = v1;
					temp->weight = eg->weight;
					//ͷ�巨 
					temp->nextvNode_ = G[v2]->FirstAdj;
					G[v2]->FirstAdj = temp;
				}
				Enum++;   //��ɺ�,Enum+1 
			}
			if(ret==false)
			{
				cout<<"����ʧ��"<<endl;
			}
			return ret;
			
		
		
		}
};
typedef LGNode *PtrToLGNode,*LGraph;
LGraph buildGraph()
{
	int Nv,Ne;
	cin>>Nv;
	cin>>Ne;
//	GNode(int VertexNum,int HasDirection = 0, DataType* data=nullptr):Vnum(VertexNum),HasDirection(HasDirection),Enum(0)
//	LGNode(int VertexNum,bool HasDirection=false, DataType* data=nullptr):Vnum(VertexNum),Enum(0),HasDirection(HasDirection)
	LGraph mg = new LGNode(Nv);
	for(int i = 0;i<Ne;i++)
	{
		Edge eg = new Edgenode_;
		cin>>eg->v1;
		cin>>eg->v2;
		cin>>eg->weight;
		
		mg->insertEdge(eg);
	}
	cout<<"build successfully"<<endl; 
	return mg;
}



int main(int argc,char* args[])
{
	LGraph lg;
	lg = buildGraph();
 	return 0;
}

