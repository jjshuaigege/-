#include <iostream>
#include <climits>
#include <cfloat>
#include <queue>
#define MaxVertexNum 100
#define EdgeNull 0   //�����ڽӾ�����Ȩ��ʱ������Ϊ0����Ȩ��ʱ�������ΪINT_MAX 
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
		//��������֮���Ƿ��б� 
		//true�����бߣ�false����û�� 
		bool AdjustMatrix[MaxVertexNum][MaxVertexNum];
		DataType data[MaxVertexNum];;
	public:
		//����һ����VertexNum�������ͼ����ʼʱû���κ�һ���� 
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
			//�Ը������㸳ֵ
			if(data)
			{
				for(vertex v = 0; v<Vnum; v++)
				{
					this->data[v] = data[v];		
				}
				
			}
			 
			//�Ը����߸�ֵ 
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
			if(e->v1 == e->v2) //������ָ���Լ��ı� 
			{
				ret = false; 
			}
			else if(e->v1<Vnum&&e->v2<Vnum)   //����ߵ����߶����±�ĺϷ��� 
			{
				AdjustMatrix[e->v1][e->v2] = e->weight;
				Enum++;
				//������ͼ�Ķ��⴦��  
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
				cout<<"�����ʧ��"<<endl;
			}
			return ret;
		}
		void insertNode()
		{
			Vnum++;
		}
		
		/*
		�����ʽ
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
//�������ڽӾ����ʵ�� 





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
		eNode_* temp;
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
					
				if(!HasDirection) // v2 �� v1 
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
//�������ڽӱ��ʵ�� 


void visit(vertex v)
{
	cout<<"���ʶ���"<<v<<endl;	
}


//DFS������α�������� 
//template<typename graph>
//void DFS(graph g, vertex v)
//{
//	visit(v);
//	visited[v] = true;
//	for (����v��ÿ���ڽӵ�w) 
//	{
//		if(!visited[w])	
//		{
//			DFS(g, w);	
//		}
//	} 
//}

//���ڽӾ������DFS(��Ȩ��) 
void DFS_MG(MGraph g, vertex v)
{
	visit(v);
	visited[v] = true;
	for (vertex w = 0; w<g->getVnum(); w++) 
	{
		if(g->getAdjust(v,w))  //����v��ÿ���ھӣ�ϸ�ڽ��ͣ��ڽӾ����±���������Ӧ��ֵΪtrue��˵�����ھ� 
		{
			if(!visited[w])	
			{
				DFS_MG(g, w);	
			}
		}
		
	} 
}
//���ڽӾ������BFS(��Ȩ��) 
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
			if(g->getAdjust(v,w))  //����v��ÿ���ھӣ�ϸ�ڽ��ͣ��ڽӾ����±���������Ӧ��ֵΪtrue��˵�����ھ� 
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



//���ڽӱ����DFS
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
//���ڽӱ����BFS
void BFS_LG(LGraph g, vertex v)
{
	//tailÿ�ζ�ָ��������ջ���Ǹ���㣬lastָ�򱾲�����һ�����
	//�����ӵ��Ǹ����(v)�պ�Ϊ��������һ�����(last)ʱ��tail��ָ��Ľ��Ϊ�²�����һ����㣬���Դ�ʱ���԰�last:=tail 
	vertex tail = v;
	vertex last = tail; 
	int level = 1;
	cout<<"��"<<level<<"�㣺";
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
				cout<<"��"<<level<<"�㣺";
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
//�����ʽ
//����ͼ�Ĺ���: 
//������ͱߵĸ����� 
//Vnum Enum
//�����ߣ� 
//��ʼ����   ��ֹ���� 	�ߵ�Ȩ��
//��ʼ����   ��ֹ���� 	�ߵ�Ȩ��
//...
//��ʼ����   ��ֹ���� 	�ߵ�Ȩ��

template<typename graph>
void doing_DFS_MG(void (*func)(graph,vertex),graph g)
{
	
	int cnt=0;
	for(vertex v = 0;v<g->getVnum();v++)
	{
		if(!visited[v])
		{
			cout<<"�Զ���"<<v<<"Ϊ���ڵ㣬����DFS����..."<<endl; 
			func(g,v);
			cnt++;
		}
	}
	cout<<"��ͼ��DFS��������������"<<cnt<<"��������ͨ��ͼ"<<endl;
	
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

