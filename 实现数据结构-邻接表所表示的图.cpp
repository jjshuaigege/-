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
分为两块：顶点结点和边结点
顶点结点以数组存放，存放结点的数据，第一个邻接点的地址
边结点以链表的形式存放，存放边的终点顶点的下标，边的权重，下一个边结点（邻居）的地址 
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
		
		//对图重新进行初始化(去掉所有边，如果给出一个数组，则依照给定数组为各个顶点赋值，否则顶点的值保持原样) 
		void initialize(DataType* data=nullptr)
		{
			for(vertex i=0;i<Vnum;i++)
			{
				//给指针数组的各个指针分配一片空间
				G[i] = new vNode_; 
				if(data)
				{
					//给各个结点赋值
					G[i]->data = data[i];
				}
				//给各个边赋值 
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
			if(v1 == v2 || v1>=Vnum || v2>=Vnum)    //检验边的两边顶点的合法性 
			{
				ret=false;
			}
			else
			{
				// v1 到 v2 
				//新建一个边结点 
				eNode_* temp = new eNode_;
				temp->EndvNodeIndex = v2;
				temp->weight = eg->weight;
				//头插法 
				temp->nextvNode_ = G[v1]->FirstAdj;
				G[v1]->FirstAdj = temp;
					
				if(HasDirection) // v2 到 v1 
				{
					//新建一个边结点 
					temp = new eNode_;
					temp->EndvNodeIndex = v1;
					temp->weight = eg->weight;
					//头插法 
					temp->nextvNode_ = G[v2]->FirstAdj;
					G[v2]->FirstAdj = temp;
				}
				Enum++;   //完成后,Enum+1 
			}
			if(ret==false)
			{
				cout<<"插入失败"<<endl;
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

