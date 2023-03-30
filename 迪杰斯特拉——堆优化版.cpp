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
	cout<<"容器元素的结构:dist,path,vertex"<<endl;
	return mg;
}

void visit(vertex v)
{
	cout<<"访问顶点"<<v<<endl;	
}




//核心代码
struct DistPathIndex
{
	int dist; 
	int path;
	int index;
	bool operator > (const DistPathIndex& x) const
	{
		return this->dist>x.dist;
	}
};

struct DistPath
{
	int dist;
	int path;
};

bool IsJoin[MaxVertexNum];
priority_queue<DistPathIndex,vector<DistPathIndex>,greater<DistPathIndex>> distCT;    //默认大根堆，此处应用小根堆 
vector<DistPath> distVE(MaxVertexNum,{infinity, -1});
//打印到w的最短路径 
void printShortestCut(vertex w)
{
	if(distVE[w].path!=-1)
	{
		printShortestCut(distVE[w].path);
	}
	cout<<w<<" ";
}

DistPathIndex* getMin()
{
	DistPathIndex* ret = new DistPathIndex;
	DistPathIndex x;
	int index=-1;
	if(!distCT.empty())
	{
		do
		{
			x = distCT.top();
			distCT.pop();
			cout<<"容器弹出"<<x.dist<<","<<x.path<<","<<x.index<<endl;
			index = x.index;	
		}while(!distCT.empty()&&IsJoin[index]);
		
		
		
	}
	if(index>=0&&!IsJoin[index])
	{
		ret->dist=x.dist;
		ret->index=x.index;
		ret->path=x.path;
	}
	else
	{
		ret=nullptr;
	}
	
	return ret;   //返回符合条件的点,若返回-1则代表没找到 
}
void dijkstra(MGraph g, vertex v)
{
	DistPathIndex* p1;
	//初始化
	distVE = {MaxVertexNum,{infinity, -1}};
	for(vertex i = 0;i<g->getVnum();i++)
	{
		IsJoin[i] = false;	
	}
	cout<<"容器放入"<<0<<","<<-1<<","<<v<<endl;
	distCT.push({0, -1, v});
	
	while(true)
	{
		//从未加入的点中选取一个dist最小的（不能是无穷），加入到集合之中 
		p1 = getMin();
		if(!p1)
		{
			break;
		}
		
		v=p1->index;
		distVE.at(v)={p1->dist,p1->path};    //存放结果的vector 
		IsJoin[v] = true;
		
		
 
		//加入之后，把加入点的邻居的状况也全部放入大根堆 
		
		for(vertex w=0;w<g->getVnum();w++)
		{
			if(g->getAdjust(v,w))
			{
				cout<<"容器放入"<<p1->dist + g->getAdjust(v,w)<<","<<v<<","<<w<<endl;
				distCT.push({p1->dist + g->getAdjust(v,w), v, w});
			}
		}
	}
	
} 


int main(int argc,char* args[])
{
	MGraph mg;
	mg = buildMGraph();
	dijkstra(mg, 1);
	cout<<"-----------------------------华丽的分隔线-----------------------------"<<endl<<endl<<endl;
	for(int i=0;i<mg->getVnum();i++)
	{
		cout<<"到"<<i<<"的最短路径——";
		if(distVE[i].dist<infinity)
		{
			cout<<"路径长度为"<<distVE[i].dist<<",依次经过:";
			printShortestCut(i);
		}
		else
		{
			cout<<"无法抵达!";
		}
		
		cout<<endl;
	}
	
	dijkstra(mg, 2);
	cout<<"-----------------------------华丽的分隔线-----------------------------"<<endl<<endl<<endl;
	for(int i=0;i<mg->getVnum();i++)
	{
		cout<<"到"<<i<<"的最短路径——";
		if(distVE[i].dist<infinity)
		{
			cout<<"路径长度为"<<distVE[i].dist<<",依次经过:";
			printShortestCut(i);
		}
		else
		{
			cout<<"无法抵达!";
		}
		
		cout<<endl;
	}
	
	
 	return 0;
}




