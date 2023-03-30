#include <iostream>
#include <climits>
#include <cfloat>
#include <queue>
#define MaxVertexNum 100

//#define vertex int
#define DataType char
#define WeightType int
#define infinity 99999
#define EdgeNull infinity   //�����ڽӾ�����Ȩ��ʱ������Ϊ0����Ȩ��ʱ�������ΪINT_MAX 

using namespace std;


//ǰ�ô��룬�������ط�copy�� 

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
//˼·�����׼���������飬��������
//1.����Ȩ��֮��  
//2.������С�������Ķ���֮��,�����ߵ����ӹ�ϵ 
//3.�����ڸ�Ȩ��   
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
	return ret;   //����-1����û�ҵ� 
}

//���Ĵ���  
bool Prim(MGraph g,vertex v)     //��vΪ��ʼ�㣬�γ���С������ 
{
	//��ʼ��
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
		//v����뼯��֮��
		isjoin[v] = true; 
		
		for(vertex w=0;w<g->getVnum();w++)
		{
			if(g->getAdjust(v,w)>0 && g->getAdjust(v,w)<infinity)  //w��v���ھ� 
			{
				
				if(isjoin[w] == false && g->getAdjust(v,w)<dist[w]) //wû�м��뼯�ϣ������¼���ĵ㵽w�ľ����С�������dist[w] 
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
			cout<<"�γ���С������ʧ�ܣ���Ϊԭͼ������ͨͼ"<<endl;
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
		//Ȩ��
		int weight;
		//·��
		 
		for(int i = 0;i<g->getVnum();i++)
		{
			weight+=dist[i];
			cout<<1<<"��"<<i<<"��·��Ϊ��";
			Printpath(g,i);
			cout<<endl;
		 } 
		cout<<"Ȩ��֮��Ϊ"<<weight;
			
	}	
}


int main(int argc,char* args[])
{
	MGraph mg;
	mg = buildMGraph();
	PrintOC(mg);
 	return 0;
}

