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
	cout<<"���ʶ���"<<v<<endl;	
}
//�������ڵ�һ���֣�ͼ


int indegree[MaxVertexNum];
queue<vertex> temp;
vector<vertex> oc;
void topsort(MGraph g)
{
	//�����������г�ʼ�� 
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
		//��������Ϊ0�������temp����
		if(indegree[v]==0)
		{
			temp.push(v);
		}
	}
	
	while(temp.size() && oc.size() < g->getVnum())
	{
		//temp�����г���һ��Ԫ��v 
		vertex v = temp.front();
		temp.pop();
		//v����������
		oc.push_back(v);
		//v�������ھ���ȼ�1
		for(vertex w = 0;w<g->getVnum();w++)
		{
			if(g->getAdjust(v,w)>0 && g->getAdjust(v,w)<infinity)
			{
				indegree[w]--; 
				//�����ȼ�Ϊ0�������temp����
				if(indegree[w]==0)
				{
					temp.push(w);
				}
			}
		}
		
	}
	
	if(oc.size() < g->getVnum())
	{
		cout<<"error!ԭͼ���������޻�ͼ(DAG)"<<endl;
	}	
}
void PrintOC_top(MGraph g)
{
	cout<<"��������Ϊ:";
	for(auto i = oc.begin(); i!=oc.end();i++)
	{
		cout<<(*i+1)<<" ";
	}
	cout<<endl;
}
//�������ڵڶ����֣���������
//�������ڵڶ����֣��������� 


//˼·��
//AOE��ǰ�û������������� 

//��4����
//0.����������� 
//1.�������״̬�����緢��ʱ��
//2.�������״̬��������ʱ��
//3.���������Ļ���ʱ�� 

//���Ĵ���
struct activity
{
	vertex start;
	vertex end;
	int CostTime;
	int FreeTime;	
};
struct stateNode
{
	int EarlistTime;
	int LatestTime;
};

//vector<activity> oc_final;
vector<activity> ActSet;
stateNode StateSet[MaxVertexNum];     //�����±��������� 

//int indegree[MaxVertexNum];
//queue<vertex> temp;
//queue<vertex> oc;


void KeyPath(MGraph g)
{	
	topsort(g);
	if(oc.size()==g->getVnum())      //�������ȷ�� 
	{
		//��ʼ��
		for(int i = 0;i<MaxVertexNum;i++)
		{
			StateSet[i].EarlistTime=0;
			StateSet[i].LatestTime=infinity;
			 
		} 
		
		//���������������μ�������ʱ��    ��ʽ��EarlistTime(i) = ��i������ǰ���ھ�j��max:{EarlistTime(j)+E<j,i>} 
		for(auto i = oc.begin();i!=oc.end();i++)   //*i��vertex 
		{
			vertex v = *i;
			//Ѱ��v��ǰ����� w,����w�����緢��ʱ�����v�����緢��ʱ�� 
			for(vertex w=0;w<g->getVnum();w++)
			{
				if(g->getAdjust(w,v)>0 && g->getAdjust(w,v)<infinity)
				{
					if(StateSet[v].EarlistTime < StateSet[w].EarlistTime + g->getAdjust(w,v))
					{
						StateSet[v].EarlistTime = StateSet[w].EarlistTime + g->getAdjust(w,v);
					}
				}
			}
		}
		
		
		//��������ʱ��֮ǰҪ�Ƚ��г�ʼ��
		bool flag = false; 
		for(vertex v = 0;v<g->getVnum();v++)
		{
			flag = false;
			
			for(vertex w = 0; w<g->getVnum();w++)
			{
				if(g->getAdjust(v,w)>0 && g->getAdjust(v,w)<infinity)
				{
					flag = true;    //�г���	
					break;
				}			
			}
			
			if(flag == false)
			{
				StateSet[v].LatestTime = StateSet[v].EarlistTime;     //û�к�̵Ķ��㣬����ʱ���������ʱ�� 
			}
		}
		
		//���������������������ʱ��   ��ʽ��LatestTime(i) = ��i�����к���ھ�j(���������ǰ��)��min:{LatestTime(j)-E<i,j>} 
		for(auto i = oc.rbegin();i!=oc.rend();i++)
		{
			vertex v = *i;
			//Ѱ��v�ĺ�̽�� w,����w��������ʱ�����v��������ʱ�� 
			for(vertex w=0;w<g->getVnum();w++)
			{
				if(g->getAdjust(v,w)>0 && g->getAdjust(v,w)<infinity)
				{
					if(StateSet[v].LatestTime > StateSet[w].LatestTime - g->getAdjust(v,w))
					{
						StateSet[v].LatestTime = StateSet[w].LatestTime - g->getAdjust(v,w);
					}
				}
			}	
		}
		
		//���������Ļ���ʱ�� ��ͬʱ�������������ڻ������֮�У� 
		for(auto i = oc.begin();i!=oc.end();i++)   //*i��vertex 
		{
			vertex v = *i;
			//Ѱ��v�ĺ�̽�� w(����),���ߣ����Ϣ�����뼯��     �����Ϊi���յ�Ϊj�ıߣ���freetime = latest(j) - earlist(i) - E<i,j>
			for(vertex w=0;w<g->getVnum();w++)
			{
				if(g->getAdjust(v,w)>0 && g->getAdjust(v,w)<infinity)
				{				
					vertex start = v;
					vertex end = w;
					int CostTime = g->getAdjust(v,w);
					int FreeTime = StateSet[w].LatestTime - StateSet[v].EarlistTime - g->getAdjust(v,w);
					ActSet.push_back({start,end,CostTime,FreeTime});
//					if(StateSet[v].EarlistTime < StateSet[w].EarlistTime + g->getAdjust(w,v))
//					{
//						StateSet[v].EarlistTime = StateSet[w].EarlistTime + g->getAdjust(w,v);
//					}
				}
			}
		}
		
	}
	
}
void PrintOC_KP(MGraph g)
{
	for(vertex v = 0;v<g->getVnum();v++)
	{
		cout<<"���"<<v<<"�����緢��ʱ�䣺"<<StateSet[v].EarlistTime<<",������ʱ�䣺"<<StateSet[v].LatestTime<<endl;	
	}
	
	for(auto i = ActSet.begin();i!=ActSet.end();i++)
	{
		cout<<i->start<<"��"<<i->end<<","<<"����Ϊ"<<i->CostTime<<",����ʱ��Ϊ:"<<i->FreeTime<<endl;	
	}	
}

int main(int argc,char* args[])
{
	
	MGraph mg;
	mg = buildMGraph();
	KeyPath(mg);
//	cout<<"����11111 "<<ufs.a[6]<<endl;
//	ufs.find(6);
//	cout<<"����11111 "<<ufs.a[6]<<endl;
	PrintOC_KP(mg);
 	return 0;
}

