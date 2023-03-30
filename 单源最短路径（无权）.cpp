//ʡȥ��visited���� ,������path�����dist����
//˼·��ѡ��ĳһ�����v����BFS������path[w]����˼�ǽ��w����vΪԴ���BFS�����е�ǰ�̽�㣨���x��ջ����x���ھӽ��y1��y2��y3...�����ν��з��ʲ�����ջ����x��y1��y2,y3����ǰ�̽��)
//dist[w]��ָ��v��w�������ľ��루������ 
#include <iostream>
#include <climits>
#include <cfloat>
#include <queue>
#define MaxVertexNum 100
#define EdgeNull 0   //�����ڽӾ�����Ȩ��ʱ������Ϊ0����Ȩ��ʱ�������ΪINT_MAX 
//#define vertex int
#define DataType char
#define WeightType int

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

void visit(vertex v)
{
	cout<<"���ʶ���"<<v<<endl;	
}



//���Ĵ��� 
queue<int> qu;
vertex path[MaxVertexNum];
int dist[MaxVertexNum];
void SoloSrcShortestCut(MGraph g, vertex v)
{
	//dist�����path������г�ʼ�� 
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
			if(g->getAdjust(v,w))  //����v��ÿ���ھӣ�ϸ�ڽ��ͣ��ڽӾ����±���������Ӧ��ֵΪtrue��˵�����ھ� 
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

//��ӡ��w�����·�� 
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
		cout<<"��"<<i<<"�����·��,��"<<dist[i]<<"��:";
		printShortestCut(i);
		cout<<endl;
	}
	
 	return 0;
}

