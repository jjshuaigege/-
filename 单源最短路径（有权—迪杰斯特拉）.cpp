#include <iostream>
#include <climits>
#include <cfloat>
#include <queue>
#define MaxVertexNum 100

//#define vertex int
#define DataType char
#define WeightType int
#define infinity 99999
#define EdgeNull 0   //用于邻接矩阵，无权的时候设置为0，有权的时候可设置为INT_MAX 
//前置代码，从其它地方copy的 
using namespace std;


typedef int vertex;
struct ENode
{
	vertex v1;
	vertex v2;
	int weight;
};
//using ENode* = PtrToEdge;
//using PtrToEdge = Edge;
typedef ENode* PtrToEdge;
typedef PtrToEdge Edge;


class GNode
{
	private:
		bool HasDirection;
		int Vnum;
		int Enum;
		//两个顶点之间是否有边 
		//true代表有边，false代表没有 
		int AdjustMatrix[MaxVertexNum][MaxVertexNum];
		DataType data[MaxVertexNum];;
	public:
		//建立一个有VertexNum个顶点的图，初始时没有任何一条边 
		GNode(int VertexNum,int HasDirection = 0, DataType* data=nullptr):Vnum(VertexNum),HasDirection(HasDirection),Enum(0)
		{
			initialize();
		}
		const int& getAdjust(vertex x, vertex y)
		{
			return AdjustMatrix[x][y];
		}
		const int& getVnum()
		{
			return Vnum; 
		}
		
		void initialize()
		{
			//对各个顶点赋值
			if(data)
			{
				for(vertex v = 0; v<Vnum; v++)
				{
					this->data[v] = data[v];		
				}
				
			}
			 
			//对各个边赋值 
			for(vertex v = 0;v<Vnum;v++)
			{
				for(vertex w = 0;w<Vnum;w++)
				{
					
					AdjustMatrix[v][w] = EdgeNull;
				}
			}
		}
		bool insertEdge(Edge e)
		{
			bool ret = true;
			if(e->v1 == e->v2) //不允许指向自己的边 
			{
				ret = false; 
			}
			else if(e->v1<Vnum&&e->v2<Vnum)   //检验边的两边顶点下标的合法性 
			{
				AdjustMatrix[e->v1][e->v2] = e->weight;
				Enum++;
				//对无向图的额外处理  
				if(!HasDirection)
				{
					AdjustMatrix[e->v2][e->v1] = e->weight;
				} 
			}
			else
			{
				ret = false;
			}
			if(ret==false)
			{
				cout<<"插入边失败"<<endl;
			}
			return ret;
		}
		void insertNode()
		{
			Vnum++;
		}
		
		/*
		输入格式
		Nv Ne
		V1 V2 Weight
		... 
		*/	
};
typedef GNode* PtrToGNode;
typedef PtrToGNode MGraph;
MGraph buildMGraph()
{
	int Nv,Ne;
	cin>>Nv;
	cin>>Ne;
//	GNode(int VertexNum,int HasDirection = 0, DataType* data=nullptr):Vnum(VertexNum),HasDirection(HasDirection),Enum(0)
	MGraph mg = new GNode(Nv,1);
	for(int i = 0;i<Ne;i++)
	{
		Edge eg = new ENode;
		cin>>eg->v1;
		cin>>eg->v2;
		cin>>eg->weight;
		
		mg->insertEdge(eg);
	}
	cout<<"build successfully"<<endl; 
	return mg;
}

void visit(vertex v)
{
	cout<<"访问顶点"<<v<<endl;	
}




//核心代码
vertex path[MaxVertexNum];
int dist[MaxVertexNum];
bool IsJoin[MaxVertexNum];

//打印到w的最短路径 
void printShortestCut(vertex w)
{
	if(path[w]!=-1)
	{
		printShortestCut(path[w]);
	}
	cout<<w<<" ";
}

vertex getMin(MGraph g)
{
	int minDist=infinity;
	vertex ret = -1;
	for(vertex i = 0;i<g->getVnum();i++)
	{
		if(!IsJoin[i])   // 未加入的集合之中 
		{
			if(dist[i]<minDist)  //选最小的 
			{
				minDist = dist[i];
				ret = i;
			}
		}
		
	}
	return ret;   //返回符合条件的点,若返回-1则代表没找到 
}
void dijkstra(MGraph g, vertex v)
{
	//初始化
	for(vertex i = 0;i<g->getVnum();i++)
	{
		path[i] = -1;
		dist[i] = infinity;
		IsJoin[i] = false;	
	}
	dist[v] = 0;
	
	while(true)
	{
		//从未加入的点中选取一个dist最小的（不能是无穷），加入到集合之中 
		v = getMin(g);
		if(v==-1)
		{
			break;
		}
		
		IsJoin[v] = true;
		
		
		//加入之后，根据贝尔曼方程，更改新加入的点的邻居的状况 
		for(vertex w=0;w<g->getVnum();w++)
		{
			if(g->getAdjust(v,w))
			{
				if(dist[v] + g->getAdjust(v,w) < dist[w])
				{
					path[w] = v; 
					dist[w] = dist[v] + g->getAdjust(v,w);
				}
			}
		}
	}
	
} 


int main(int argc,char* args[])
{
	MGraph mg;
	mg = buildMGraph();
	for(int i = 0;i<mg->getVnum();i++)
	{
		dijkstra(mg, i);
		cout<<"-----------------------------华丽的分隔线-----------------------------"<<endl<<endl<<endl;
		for(int i=0;i<mg->getVnum();i++)
		{
			cout<<"到"<<i<<"的最短路径——";
			if(dist[i]!=infinity)
			{
				cout<<"路径长度为"<<dist[i]<<",依次经过:";
				printShortestCut(i);
			}
			else
			{
				cout<<"无法抵达!";
			}
			
			cout<<endl;
		}
	}
	
	
 	return 0;
}

