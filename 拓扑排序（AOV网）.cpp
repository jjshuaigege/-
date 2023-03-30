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
	bool operator > (const ENode& x) const
	{
		return weight > x.weight;
	}
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
		cin>>(eg->v1);
		eg->v1--;
		cin>>(eg->v2);
		eg->v2--;
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
//以上属于第一部分：图

//核心代码 
int indegree[MaxVertexNum];
queue<vertex> temp;
vector<vertex> oc;
void topsort(MGraph g)
{
	//对入度数组进行初始化 
	for(vertex v = 0; v<g->getVnum(); v++)
	{
		indegree[v] = 0;
		for(vertex w = 0; w<g->getVnum(); w++)
		{
			if(g->getAdjust(w,v)>0 && g->getAdjust(w,v)<infinity)
			{
				indegree[v]++;	
			}	
		}
		//如果入度仍为0，则进入temp容器
		if(indegree[v]==0)
		{
			temp.push(v);
		}
	}
	
	while(temp.size() && oc.size() < g->getVnum())
	{
		//temp队列中出队一个元素v 
		vertex v = temp.front();
		temp.pop();
		//v加入结果队列
		oc.push_back(v);
		//v的所有邻居入度减1
		for(vertex w = 0;w<g->getVnum();w++)
		{
			if(g->getAdjust(v,w)>0 && g->getAdjust(v,w)<infinity)
			{
				indegree[w]--; 
				//如果入度减为0，则进入temp容器
				if(indegree[w]==0)
				{
					temp.push(w);
				}
			}
		}
		
	}
	
	if(oc.size() < g->getVnum())
	{
		cout<<"error!原图不是有向无环图(DAG)"<<endl;
	}	
}
void PrintOC_top(MGraph g)
{
	cout<<"拓扑序列为:";
	for(auto i = oc.begin(); i!=oc.end();i++)
	{
		cout<<(*i+1)<<" ";
	}
	cout<<endl;
}
//以上属于第二部分：拓扑排序 

int main(int argc,char* args[])
{
	MGraph mg;
	mg = buildMGraph();
	topsort(mg);
//	cout<<"调试11111 "<<ufs.a[6]<<endl;
//	ufs.find(6);
//	cout<<"调试11111 "<<ufs.a[6]<<endl;
	PrintOC_top(mg);
 	return 0;
}

