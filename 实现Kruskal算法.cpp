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
	MGraph mg = new GNode(Nv);
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


//以数组顺序结构实现并查集，数组的下标等于对应元素的数据的值
class UFset
{
	private:
		int size;
	public:
		int* a;
	public:
		UFset(int size):size(size)
		{
			if(a)
			{
				delete[] a;
			}
			a = new int[size];
			
			for(int i = 0;i<size;i++)
			{
				a[i] = -1;    //初始的时候，每个结点的父节点都是自己，因此小于0；每个集合所包含的结点的个数都是1，因此绝对值为1；综合起来，初始化为-1	
			}	
		}
		
	//寻找结点value的根节点 
	int find(int value)
	{
		
		if(a[value]>=0)
		{
			//找本节点双亲结点的根节点，并赋值给本节点的双亲结点(实现了路径压缩)
			a[value] = find(a[value]);
			return a[value];
		}
		else
		{
			return value;	
		}
		
//		//不使用路径压缩的非递归算法 
//		int parent = a[value];
//		while(parent>=0)
//		{
//			value = parent;
//			parent = a[value];
//		}
//	
//		return value;
		
		
	}
	
	//判断结点x1和x2是否属于同一个集合
	bool judge_same(int x1, int x2)
	{
		int r1 = find(x1);
		int r2 = find(x2);
		if(r1 == r2)
		{
			return true;
		}
		else
		{
			return false;
		}	
	} 
	
	//合并结点x1和结点x2分别所在的集合 
	void Union_o(int x1,int x2)
	{
		int r1 = find(x1);
		int r2 = find(x2);
	
		if(r1!=r2)
		{	
			//按秩归并，包含两类：（1）按树高归并、（2）按结点数归并。两类算法均使得最后查找任一结点的时候，时间复杂度均为O(logn) 
			//此处使用按结点数归并 
			//根节点r的a[r]均为负数，绝对值代表了所包含的结点数，a[r1] a[r2]均为负数，所以更小的一方集合所包含的结点数更多 
			if(a[r1]<=a[r2])
			{
				a[r1] += a[r2];
				a[r2] = r1;
			}
			else
			{
				a[r2] += a[r1];
				a[r1] = r2;
			}
			
//			//按树高归并的算法
//			if(a[r1]<=a[r2])
//			{
//				if(a[r1]==a[r2])
//				{
//					a[r1]--;   //总树高加一 
//				}
//				a[r2] = r1;  //r2的双亲指针指向r1					
//			}
//			else
//			{
//				a[r1] = r2;
//			 } 
			
		}
	}
	void show()
	{
		for(int i = 0;i<size;i++)
		{
			cout<<"a["<<i<<"]="<<a[i]<<endl;
		}
	}
	
			
} ;
//以上属于第二部分：并查集 


//Kruskal伪码描述

//void Kruskal(MGraph g)
//{
//	MST = {}
//	while(MST中的边数小于V-1 && E中还有边)
//	{
//		e = E中权值最小的边		 //用小跟堆来实现 
//		if(e加入后有回路)        //用并查集来实现 
//		{
//			彻底无视，将e抛弃（从小跟堆里出去） 
//			continue;	
//		}
//		else
//		{
//			将e加入集合MST之中   //用并查集来实现	
//		}
//	}
//	if(MST中的边数小于V-1)	
//	{
//		cout<<"失败"<<endl;
//	}	
//} 

//struct ENode
//{
//	vertex v1;
//	vertex v2;
//	int weight;
//	bool operator > (const ENode& x)
//	{
//		return weight > x.weight;
//	}
//};
//typedef ENode* PtrToEdge;
//typedef PtrToEdge Edge;


priority_queue<ENode,vector<ENode>,greater<ENode> > pq;
UFset ufs(MaxVertexNum);
vector<ENode> MST;

bool judgeValid(ENode e)
{
	
	return !(ufs.judge_same(e.v1, e.v2));
}
void Kruskal(MGraph g)
{
	//初始化
	MST.clear();
	for(int j = 0;j<g->getVnum();j++)
	{
		for(int i = 0;i<=j;i++)
		{
			if(g->getAdjust(i,j)>0 && g->getAdjust(i,j)<infinity)   //存在一条边，则进入小根堆 
			pq.push({i,j,g->getAdjust(i,j)}); 	
		}
	}
	ufs=g->getVnum();   //size为图的顶点数目，全部赋值为-1 
	
	//
	while(MST.size()<g->getVnum()-1 && !pq.empty())
	{
		ENode e = pq.top();
		pq.pop();
		if(judgeValid(e))
		{
			ufs.Union_o(e.v1,e.v2);   //合并该边两端的顶点，使二者变成同一个集合 
			MST.push_back(e);         //将边加入集合 
//			cout<<"加入边"<<e.v1<<":"<<e.v2<<":"<<e.weight<<endl;
//			cout<<"查看并查集。。。"<<endl;
//			for(int i =0;i<g->getVnum();i++)
//			{
//				cout<<"a["<<i<<"]="<<ufs.a[i]<<endl;
//			}
			
		}
		
	}
	
	if(MST.size()<g->getVnum()-1)
	{
		cout<<"最小生成树失败，原图不是连通的"<<endl;
	}
	
}
void PrintOC(MGraph g)
{
	int weight=0;
	for(auto i=MST.begin();i<MST.end();i++)
	{
		weight += i->weight;
		cout<<(i->v1+1)<<"到"<<(i->v2+1)<<",权值为"<<i->weight<<endl;
	}
	
}

int main(int argc,char* args[])
{

 	MGraph mg;
	mg = buildMGraph();
	Kruskal(mg);
//	cout<<"调试11111 "<<ufs.a[6]<<endl;
//	ufs.find(6);
//	cout<<"调试11111 "<<ufs.a[6]<<endl;
	PrintOC(mg);
 	return 0;
}

