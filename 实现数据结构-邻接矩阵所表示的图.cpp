#include <iostream>
#include <climits>
#include <cfloat>
#define MaxVertexNum 100
#define EdgeNull 0   //�����ڽӾ�����Ȩ��ʱ������Ϊ0����Ȩ��ʱ�������ΪINT_MAX 
//#define vertex int
#define DataType char
#define WeightType int
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
MGraph buildGraph()
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
typedef PtrToGNode MGraph;




int main(int argc,char* args[])
{
	MGraph sp = buildGraph();
	
 	return 0;
}

