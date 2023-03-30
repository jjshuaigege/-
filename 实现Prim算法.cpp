#include <iostream>
#include <climits>
#include <cfloat>
#include <queue>
#define MaxVertexNum 100

//#define vertex int
#define DataType char
#define WeightType int
#define infinity 99999
#define EdgeNull infinity   //用于邻接矩阵，无权的时候设置为0，有权的时候可设置为INT_MAX 

using namespace std;


//前置代码，从其它地方copy的 

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
					if(v==w)
					{
						AdjustMatrix[v][w] = 0;
					}
					else
					{
						AdjustMatrix[v][w] = EdgeNull;
					}
					
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
	MGraph mg = new GNode(Nv);
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
//思路：最好准备三个数组，这样可以
//1.计算权重之和  
//2.计算最小生成树的顶点之间,各条边的连接关系 
//3.适用于负权边   
vertex parent[MaxVertexNum];
int dist[MaxVertexNum];
bool isjoin[MaxVertexNum]; 



vertex getMin(MGraph g)
{
	int mindist = infinity;
	vertex ret = -1;
	for(int i = 0;i<g->getVnum();i++)
	{
		if(!isjoin[i] && mindist>dist[i])
		{
			mindist = dist[i];
			ret = i;
		}
	}
	return ret;   //返回-1代表没找到 
}

//核心代码  
bool Prim(MGraph g,vertex v)     //以v为起始点，形成最小生成树 
{
	//初始化
	for(int i=0;i<g->getVnum();i++)
	{
		parent[i] = -1;
		dist[i] = infinity; 
		isjoin[i] = false;	
	} 
	dist[v] = 0;
	
	
	while(true)
	{
		v = getMin(g);
		if(v==-1)
		{
			break;
		}
		//v点加入集合之中
		isjoin[v] = true; 
		
		for(vertex w=0;w<g->getVnum();w++)
		{
			if(g->getAdjust(v,w)>0 && g->getAdjust(v,w)<infinity)  //w是v的邻居 
			{
				
				if(isjoin[w] == false && g->getAdjust(v,w)<dist[w]) //w没有加入集合，并且新加入的点到w的距离更小，则更新dist[w] 
				{
					dist[w] = g->getAdjust(v,w);
					parent[w] = v;
				}
			}
	 	}
	}
	for(int i = 0;i<g->getVnum();i++)
	{
		if(isjoin[i]==false)
		{
			cout<<"形成最小生成树失败，因为原图不是连通图"<<endl;
			return false;
		}
	}
	return true;
		
}
Printpath(MGraph g, vertex v)
{
	if(parent[v]!=-1)
	{
		Printpath(g,parent[v]);
	}
	cout<<v<<" ";
 } 
void PrintOC(MGraph g)
{
	bool flag = Prim(g,1);
	if(flag)
	{
		//权重
		int weight;
		//路径
		 
		for(int i = 0;i<g->getVnum();i++)
		{
			weight+=dist[i];
			cout<<1<<"到"<<i<<"的路径为：";
			Printpath(g,i);
			cout<<endl;
		 } 
		cout<<"权重之和为"<<weight;
			
	}	
}


int main(int argc,char* args[])
{
	MGraph mg;
	mg = buildMGraph();
	PrintOC(mg);
 	return 0;
}

