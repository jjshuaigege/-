#include <iostream>
#include <climits>
#include <cfloat>
#include <queue>
#define MaxVertexNum 100
#define EdgeNull 0   //用于邻接矩阵，无权的时候设置为0，有权的时候可设置为INT_MAX 
//#define vertex int
#define DataType char
#define WeightType int

using namespace std;
typedef int vertex;
bool visited[MaxVertexNum];
queue<int> qu;



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
//以上是邻接矩阵的实现 





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
		eNode_* temp;
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
		const int& getVnum()
		{
			return Vnum;
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
					
				if(!HasDirection) // v2 到 v1 
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
		friend void DFS_LG(LGNode* g, vertex v);
		friend void BFS_LG(LGNode* g, vertex v);
		
};
typedef LGNode *PtrToLGNode,*LGraph;
LGraph buildLGraph()
{
	int Nv,Ne;
	cin>>Nv;
	cin>>Ne;
//	GNode(int VertexNum,int HasDirection = 0, DataType* data=nullptr):Vnum(VertexNum),HasDirection(HasDirection),Enum(0)
//	LGNode(int VertexNum,bool HasDirection=false, DataType* data=nullptr):Vnum(VertexNum),Enum(0),HasDirection(HasDirection)
	LGraph mg = new LGNode(Nv);
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
//以上是邻接表的实现 


void visit(vertex v)
{
	cout<<"访问顶点"<<v<<endl;	
}


//DFS遍历，伪代码描述 
//template<typename graph>
//void DFS(graph g, vertex v)
//{
//	visit(v);
//	visited[v] = true;
//	for (顶点v的每个邻接点w) 
//	{
//		if(!visited[w])	
//		{
//			DFS(g, w);	
//		}
//	} 
//}

//对邻接矩阵进行DFS(无权重) 
void DFS_MG(MGraph g, vertex v)
{
	visit(v);
	visited[v] = true;
	for (vertex w = 0; w<g->getVnum(); w++) 
	{
		if(g->getAdjust(v,w))  //访问v的每个邻居，细节解释：邻接矩阵按下标索引所对应的值为true，说明是邻居 
		{
			if(!visited[w])	
			{
				DFS_MG(g, w);	
			}
		}
		
	} 
}
//对邻接矩阵进行BFS(无权重) 
void BFS_MG(MGraph g, vertex v)
{
	visit(v);
	visited[v] = true;
	qu.push(v);
	while(!qu.empty())
	{
		v = qu.front();
		qu.pop();
		for (vertex w = 0; w<g->getVnum(); w++) 
		{
			if(g->getAdjust(v,w))  //访问v的每个邻居，细节解释：邻接矩阵按下标索引所对应的值为true，说明是邻居 
			{
				if(!visited[w])
				{
					visit(w);
					visited[w] = true;
					qu.push(w);
				}
			}
			
		} 
	}
	
}



//对邻接表进行DFS
void DFS_LG(LGraph g, vertex v)
{
	visit(v);
	visited[v] = true;
	for(eNode_* p = g->G[v]->FirstAdj;p!=nullptr;p=p->nextvNode_)
	{
		vertex w = p->EndvNodeIndex;
		if(!visited[w])
		{
			DFS_LG(g,w);
		}
	}	
} 
//对邻接表进行BFS
void BFS_LG(LGraph g, vertex v)
{
	//tail每次都指向最新入栈的那个结点，last指向本层的最后一个结点
	//当出队的那个结点(v)刚好为本层的最后一个结点(last)时，tail所指向的结点为下层的最后一个结点，所以此时可以把last:=tail 
	vertex tail = v;
	vertex last = tail; 
	int level = 1;
	cout<<"第"<<level<<"层：";
	visit(v);
	visited[v] = true;
	qu.push(v);
	level++;
	while(!qu.empty())
	{
		
		v = qu.front();
		qu.pop();
		
		
		
		
		for(eNode_* p = g->G[v]->FirstAdj;p!=nullptr;p=p->nextvNode_)
		{
			vertex w = p->EndvNodeIndex;
			if(!visited[w])
			{
				cout<<"第"<<level<<"层：";
				visit(w);
				visited[w] = true;
				qu.push(w);
				tail = w;
			}
		}
		
		if(v == last)
		{
			last = tail;
			level++;
		}
		
	}
}
//输入格式
//建立图的过程: 
//声明点和边的个数： 
//Vnum Enum
//建立边： 
//起始点编号   终止点编号 	边的权重
//起始点编号   终止点编号 	边的权重
//...
//起始点编号   终止点编号 	边的权重

template<typename graph>
void doing_DFS_MG(void (*func)(graph,vertex),graph g)
{
	
	int cnt=0;
	for(vertex v = 0;v<g->getVnum();v++)
	{
		if(!visited[v])
		{
			cout<<"以顶点"<<v<<"为根节点，进行DFS搜索..."<<endl; 
			func(g,v);
			cnt++;
		}
	}
	cout<<"对图的DFS搜索结束，共有"<<cnt<<"个极大连通子图"<<endl;
	
	for(int i = 0;i<MaxVertexNum;i++)
	{
		visited[i] = false;
	}
}

int main(int argc,char* args[])
{
	for(int i = 0;i<MaxVertexNum;i++)
	{
		visited[i] = false;
	}
	
	LGraph lg;
	lg = buildLGraph();
	BFS_LG(lg,1);
	
 	return 0;
}

