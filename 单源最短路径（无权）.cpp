//省去了visited数组 ,增加了path数组和dist数组
//思路：选定某一个结点v进行BFS搜索，path[w]的意思是结点w在以v为源点的BFS搜索中的前继结点（如对x出栈，对x的邻居结点y1、y2、y3...等依次进行访问并且入栈，则x是y1（y2,y3）的前继结点)
//dist[w]是指从v到w所经过的距离（层数） 
#include <iostream>
#include <climits>
#include <cfloat>
#include <queue>
#define MaxVertexNum 100
#define EdgeNull 0   //用于邻接矩阵，无权的时候设置为0，有权的时候可设置为INT_MAX 
//#define vertex int
#define DataType char
#define WeightType int

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
		bool AdjustMatrix[MaxVertexNum][MaxVertexNum];
		DataType data[MaxVertexNum];;
	public:
		//建立一个有VertexNum个顶点的图，初始时没有任何一条边 
		GNode(int VertexNum,int HasDirection = 0, DataType* data=nullptr):Vnum(VertexNum),HasDirection(HasDirection),Enum(0)
		{
			initialize();
		}
		const bool& getAdjust(vertex x, vertex y)
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
queue<int> qu;
vertex path[MaxVertexNum];
int dist[MaxVertexNum];
void SoloSrcShortestCut(MGraph g, vertex v)
{
	//dist数组和path数组进行初始化 
	for(int i = 0; i<MaxVertexNum; i++)
	{
		path[i] = -1;
		dist[i] = -1;
	}
	
	visit(v);
	path[v] = -1;
	dist[v] = 0;
	qu.push(v);
	while(!qu.empty())
	{
		v = qu.front();
		qu.pop();
		for (vertex w = 0; w<g->getVnum(); w++) 
		{
			if(g->getAdjust(v,w))  //访问v的每个邻居，细节解释：邻接矩阵按下标索引所对应的值为true，说明是邻居 
			{
				if(dist[w]<0)
				{
					visit(w);
					path[w] = v;
					dist[w] = dist[v]+1;
					qu.push(w);
				}
			}
			
		} 
	}
}

//打印到w的最短路径 
void printShortestCut(vertex w)
{
	if(path[w]!=-1)
	{
		printShortestCut(path[w]);
	}
	cout<<w<<"\t";
}

int main(int argc,char* args[])
{	

	
	MGraph mg;
	mg = buildMGraph();
	SoloSrcShortestCut(mg,1);
	for(int i=0;i<mg->getVnum();i++)
	{
		cout<<"到"<<i<<"的最短路径,共"<<dist[i]<<"步:";
		printShortestCut(i);
		cout<<endl;
	}
	
 	return 0;
}

