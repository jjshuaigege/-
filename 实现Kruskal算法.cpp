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
	cout<<"���ʶ���"<<v<<endl;	
}
//�������ڵ�һ���֣�ͼ


//������˳��ṹʵ�ֲ��鼯��������±���ڶ�ӦԪ�ص����ݵ�ֵ
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
				a[i] = -1;    //��ʼ��ʱ��ÿ�����ĸ��ڵ㶼���Լ������С��0��ÿ�������������Ľ��ĸ�������1����˾���ֵΪ1���ۺ���������ʼ��Ϊ-1	
			}	
		}
		
	//Ѱ�ҽ��value�ĸ��ڵ� 
	int find(int value)
	{
		
		if(a[value]>=0)
		{
			//�ұ��ڵ�˫�׽��ĸ��ڵ㣬����ֵ�����ڵ��˫�׽��(ʵ����·��ѹ��)
			a[value] = find(a[value]);
			return a[value];
		}
		else
		{
			return value;	
		}
		
//		//��ʹ��·��ѹ���ķǵݹ��㷨 
//		int parent = a[value];
//		while(parent>=0)
//		{
//			value = parent;
//			parent = a[value];
//		}
//	
//		return value;
		
		
	}
	
	//�жϽ��x1��x2�Ƿ�����ͬһ������
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
	
	//�ϲ����x1�ͽ��x2�ֱ����ڵļ��� 
	void Union_o(int x1,int x2)
	{
		int r1 = find(x1);
		int r2 = find(x2);
	
		if(r1!=r2)
		{	
			//���ȹ鲢���������ࣺ��1�������߹鲢����2����������鲢�������㷨��ʹ����������һ����ʱ��ʱ�临�ӶȾ�ΪO(logn) 
			//�˴�ʹ�ð�������鲢 
			//���ڵ�r��a[r]��Ϊ����������ֵ�������������Ľ������a[r1] a[r2]��Ϊ���������Ը�С��һ�������������Ľ�������� 
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
			
//			//�����߹鲢���㷨
//			if(a[r1]<=a[r2])
//			{
//				if(a[r1]==a[r2])
//				{
//					a[r1]--;   //�����߼�һ 
//				}
//				a[r2] = r1;  //r2��˫��ָ��ָ��r1					
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
//�������ڵڶ����֣����鼯 


//Kruskalα������

//void Kruskal(MGraph g)
//{
//	MST = {}
//	while(MST�еı���С��V-1 && E�л��б�)
//	{
//		e = E��Ȩֵ��С�ı�		 //��С������ʵ�� 
//		if(e������л�·)        //�ò��鼯��ʵ�� 
//		{
//			�������ӣ���e��������С�������ȥ�� 
//			continue;	
//		}
//		else
//		{
//			��e���뼯��MST֮��   //�ò��鼯��ʵ��	
//		}
//	}
//	if(MST�еı���С��V-1)	
//	{
//		cout<<"ʧ��"<<endl;
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
	//��ʼ��
	MST.clear();
	for(int j = 0;j<g->getVnum();j++)
	{
		for(int i = 0;i<=j;i++)
		{
			if(g->getAdjust(i,j)>0 && g->getAdjust(i,j)<infinity)   //����һ���ߣ������С���� 
			pq.push({i,j,g->getAdjust(i,j)}); 	
		}
	}
	ufs=g->getVnum();   //sizeΪͼ�Ķ�����Ŀ��ȫ����ֵΪ-1 
	
	//
	while(MST.size()<g->getVnum()-1 && !pq.empty())
	{
		ENode e = pq.top();
		pq.pop();
		if(judgeValid(e))
		{
			ufs.Union_o(e.v1,e.v2);   //�ϲ��ñ����˵Ķ��㣬ʹ���߱��ͬһ������ 
			MST.push_back(e);         //���߼��뼯�� 
//			cout<<"�����"<<e.v1<<":"<<e.v2<<":"<<e.weight<<endl;
//			cout<<"�鿴���鼯������"<<endl;
//			for(int i =0;i<g->getVnum();i++)
//			{
//				cout<<"a["<<i<<"]="<<ufs.a[i]<<endl;
//			}
			
		}
		
	}
	
	if(MST.size()<g->getVnum()-1)
	{
		cout<<"��С������ʧ�ܣ�ԭͼ������ͨ��"<<endl;
	}
	
}
void PrintOC(MGraph g)
{
	int weight=0;
	for(auto i=MST.begin();i<MST.end();i++)
	{
		weight += i->weight;
		cout<<(i->v1+1)<<"��"<<(i->v2+1)<<",ȨֵΪ"<<i->weight<<endl;
	}
	
}

int main(int argc,char* args[])
{

 	MGraph mg;
	mg = buildMGraph();
	Kruskal(mg);
//	cout<<"����11111 "<<ufs.a[6]<<endl;
//	ufs.find(6);
//	cout<<"����11111 "<<ufs.a[6]<<endl;
	PrintOC(mg);
 	return 0;
}

