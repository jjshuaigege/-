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
/*
准备两个矩阵D[g->vnum][g->vnum]和path[g->vnum][g->vnum] 
思路：初始时path矩阵中的所有元素设为-1，而D矩阵一开始根据邻接矩阵的情况设定值，具体有三种情况： 
1.节点x到自己本身的D[x][x]设为0 
2.如果两个不同节点x到y之间有边，那么D[x][y]值设为该边的权重
3.如果两个不同节点x到y之间没有边，则D[x][y]的值设为无穷大 

进行多轮迭代
第一步：允许以点0为中转点，更新各个点之间的最短路径	
第二步：允许以点1为中转点(包括了点0)，更新各个点之间的最短路径
第三步：允许以点2为中转点(包括了点0、1)，更新各个点之间的最短路径
...
第g->vnum步：... 
*/

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
int D[MaxVertexNum][MaxVertexNum];
int path[MaxVertexNum][MaxVertexNum];
void floyd(MGraph g)
{
	//初始化D矩阵,path矩阵 
	for(int i = 0;i<g->getVnum();i++)
	{
		for(int j = 0;j<g->getVnum();j++)
		{
			path[i][j] = -1;
			D[i][j] = g->getAdjust(i,j);
			
			
		} 
	}
	
	//第一步：允许以点0为中转点，更新各个点之间的最短路径	
	//第二步：允许以点1为中转点(包括了点0)，更新各个点之间的最短路径
	//第三步：允许以点2为中转点(包括了点0、1)，更新各个点之间的最短路径
	for(int k=0;k<g->getVnum();k++)
		for(int i=0;i<g->getVnum();i++)
			for(int j=0;j<g->getVnum();j++)
			{
				if(D[i][j]>D[i][k]+D[k][j])
				{
					D[i][j]=D[i][k]+D[k][j];
					path[i][j] = k;
				}
			}
}

void PrintPATH(MGraph g,vertex start,vertex end)
{
	if(path[start][end]!=-1)
	{
		PrintPATH(g,start,path[start][end]);
		cout<<path[start][end]<<" ";
		PrintPATH(g,path[start][end],end);
	}
	
}
void PrintOC(MGraph g)
{
	for(int i = 0;i<g->getVnum();i++)
	{
		for(int j = 0;j<g->getVnum();j++)
		{
			
			cout<<i<<"到"<<j<<"的最短路径长度:";
			if(D[i][j]<infinity)
			{
				cout<<D[i][j]<<",依次经过"<<i<<" ";
				PrintPATH(g, i, j);
				cout<<j<<endl;
			}
			else
			{
				cout<<"无法抵达"<<endl;
			}
			
		}
	}
}
int main(int argc,char* args[])
{
	MGraph mg;
	mg = buildMGraph();
	floyd(mg);
	PrintOC(mg);
 	return 0;
}

