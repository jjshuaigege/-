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
	cout<<"����Ԫ�صĽṹ:dist,path,vertex"<<endl;
	return mg;
}

void visit(vertex v)
{
	cout<<"���ʶ���"<<v<<endl;	
}




//���Ĵ���
struct DistPathIndex
{
	int dist; 
	int path;
	int index;
	bool operator > (const DistPathIndex& x) const
	{
		return this->dist>x.dist;
	}
};

struct DistPath
{
	int dist;
	int path;
};

bool IsJoin[MaxVertexNum];
priority_queue<DistPathIndex,vector<DistPathIndex>,greater<DistPathIndex>> distCT;    //Ĭ�ϴ���ѣ��˴�Ӧ��С���� 
vector<DistPath> distVE(MaxVertexNum,{infinity, -1});
//��ӡ��w�����·�� 
void printShortestCut(vertex w)
{
	if(distVE[w].path!=-1)
	{
		printShortestCut(distVE[w].path);
	}
	cout<<w<<" ";
}

DistPathIndex* getMin()
{
	DistPathIndex* ret = new DistPathIndex;
	DistPathIndex x;
	int index=-1;
	if(!distCT.empty())
	{
		do
		{
			x = distCT.top();
			distCT.pop();
			cout<<"��������"<<x.dist<<","<<x.path<<","<<x.index<<endl;
			index = x.index;	
		}while(!distCT.empty()&&IsJoin[index]);
		
		
		
	}
	if(index>=0&&!IsJoin[index])
	{
		ret->dist=x.dist;
		ret->index=x.index;
		ret->path=x.path;
	}
	else
	{
		ret=nullptr;
	}
	
	return ret;   //���ط��������ĵ�,������-1�����û�ҵ� 
}
void dijkstra(MGraph g, vertex v)
{
	DistPathIndex* p1;
	//��ʼ��
	distVE = {MaxVertexNum,{infinity, -1}};
	for(vertex i = 0;i<g->getVnum();i++)
	{
		IsJoin[i] = false;	
	}
	cout<<"��������"<<0<<","<<-1<<","<<v<<endl;
	distCT.push({0, -1, v});
	
	while(true)
	{
		//��δ����ĵ���ѡȡһ��dist��С�ģ���������������뵽����֮�� 
		p1 = getMin();
		if(!p1)
		{
			break;
		}
		
		v=p1->index;
		distVE.at(v)={p1->dist,p1->path};    //��Ž����vector 
		IsJoin[v] = true;
		
		
 
		//����֮�󣬰Ѽ������ھӵ�״��Ҳȫ���������� 
		
		for(vertex w=0;w<g->getVnum();w++)
		{
			if(g->getAdjust(v,w))
			{
				cout<<"��������"<<p1->dist + g->getAdjust(v,w)<<","<<v<<","<<w<<endl;
				distCT.push({p1->dist + g->getAdjust(v,w), v, w});
			}
		}
	}
	
} 


int main(int argc,char* args[])
{
	MGraph mg;
	mg = buildMGraph();
	dijkstra(mg, 1);
	cout<<"-----------------------------�����ķָ���-----------------------------"<<endl<<endl<<endl;
	for(int i=0;i<mg->getVnum();i++)
	{
		cout<<"��"<<i<<"�����·������";
		if(distVE[i].dist<infinity)
		{
			cout<<"·������Ϊ"<<distVE[i].dist<<",���ξ���:";
			printShortestCut(i);
		}
		else
		{
			cout<<"�޷��ִ�!";
		}
		
		cout<<endl;
	}
	
	dijkstra(mg, 2);
	cout<<"-----------------------------�����ķָ���-----------------------------"<<endl<<endl<<endl;
	for(int i=0;i<mg->getVnum();i++)
	{
		cout<<"��"<<i<<"�����·������";
		if(distVE[i].dist<infinity)
		{
			cout<<"·������Ϊ"<<distVE[i].dist<<",���ξ���:";
			printShortestCut(i);
		}
		else
		{
			cout<<"�޷��ִ�!";
		}
		
		cout<<endl;
	}
	
	
 	return 0;
}




