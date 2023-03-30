#include <iostream>
#include <climits>
#include <cfloat>
#include <queue>
#define MaxVertexNum 100

//#define vertex int
#define DataType char
#define WeightType int
#define infinity 99999
#define EdgeNull 0   //�����ڽӾ�����Ȩ��ʱ������Ϊ0����Ȩ��ʱ�������ΪINT_MAX 
//ǰ�ô��룬�������ط�copy�� 
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
		//��������֮���Ƿ��б� 
		//true�����бߣ�false����û�� 
		int AdjustMatrix[MaxVertexNum][MaxVertexNum];
		DataType data[MaxVertexNum];;
	public:
		//����һ����VertexNum�������ͼ����ʼʱû���κ�һ���� 
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
	cout<<"���ʶ���"<<v<<endl;	
}




//���Ĵ���
vertex path[MaxVertexNum];
int dist[MaxVertexNum];
bool IsJoin[MaxVertexNum];

//��ӡ��w�����·�� 
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
		if(!IsJoin[i])   // δ����ļ���֮�� 
		{
			if(dist[i]<minDist)  //ѡ��С�� 
			{
				minDist = dist[i];
				ret = i;
			}
		}
		
	}
	return ret;   //���ط��������ĵ�,������-1�����û�ҵ� 
}
void dijkstra(MGraph g, vertex v)
{
	//��ʼ��
	for(vertex i = 0;i<g->getVnum();i++)
	{
		path[i] = -1;
		dist[i] = infinity;
		IsJoin[i] = false;	
	}
	dist[v] = 0;
	
	while(true)
	{
		//��δ����ĵ���ѡȡһ��dist��С�ģ���������������뵽����֮�� 
		v = getMin(g);
		if(v==-1)
		{
			break;
		}
		
		IsJoin[v] = true;
		
		
		//����֮�󣬸��ݱ��������̣������¼���ĵ���ھӵ�״�� 
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
		cout<<"-----------------------------�����ķָ���-----------------------------"<<endl<<endl<<endl;
		for(int i=0;i<mg->getVnum();i++)
		{
			cout<<"��"<<i<<"�����·������";
			if(dist[i]!=infinity)
			{
				cout<<"·������Ϊ"<<dist[i]<<",���ξ���:";
				printShortestCut(i);
			}
			else
			{
				cout<<"�޷��ִ�!";
			}
			
			cout<<endl;
		}
	}
	
	
 	return 0;
}

