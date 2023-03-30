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
/*
׼����������D[g->vnum][g->vnum]��path[g->vnum][g->vnum] 
˼·����ʼʱpath�����е�����Ԫ����Ϊ-1����D����һ��ʼ�����ڽӾ��������趨ֵ����������������� 
1.�ڵ�x���Լ������D[x][x]��Ϊ0 
2.���������ͬ�ڵ�x��y֮���бߣ���ôD[x][y]ֵ��Ϊ�ñߵ�Ȩ��
3.���������ͬ�ڵ�x��y֮��û�бߣ���D[x][y]��ֵ��Ϊ����� 

���ж��ֵ���
��һ���������Ե�0Ϊ��ת�㣬���¸�����֮������·��	
�ڶ����������Ե�1Ϊ��ת��(�����˵�0)�����¸�����֮������·��
�������������Ե�2Ϊ��ת��(�����˵�0��1)�����¸�����֮������·��
...
��g->vnum����... 
*/

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
int D[MaxVertexNum][MaxVertexNum];
int path[MaxVertexNum][MaxVertexNum];
void floyd(MGraph g)
{
	//��ʼ��D����,path���� 
	for(int i = 0;i<g->getVnum();i++)
	{
		for(int j = 0;j<g->getVnum();j++)
		{
			path[i][j] = -1;
			D[i][j] = g->getAdjust(i,j);
			
			
		} 
	}
	
	//��һ���������Ե�0Ϊ��ת�㣬���¸�����֮������·��	
	//�ڶ����������Ե�1Ϊ��ת��(�����˵�0)�����¸�����֮������·��
	//�������������Ե�2Ϊ��ת��(�����˵�0��1)�����¸�����֮������·��
	for(int k=0;k<g->getVnum();k++)
		for(int i=0;i<g->getVnum();i++)
			for(int j=0;j<g->getVnum();j++)
			{
				if(D[i][j]>D[i][k]+D[k][j])
				{
					D[i][j]=D[i][k]+D[k][j];
					path[i][j] = k;
				}
			}
}

void PrintPATH(MGraph g,vertex start,vertex end)
{
	if(path[start][end]!=-1)
	{
		PrintPATH(g,start,path[start][end]);
		cout<<path[start][end]<<" ";
		PrintPATH(g,path[start][end],end);
	}
	
}
void PrintOC(MGraph g)
{
	for(int i = 0;i<g->getVnum();i++)
	{
		for(int j = 0;j<g->getVnum();j++)
		{
			
			cout<<i<<"��"<<j<<"�����·������:";
			if(D[i][j]<infinity)
			{
				cout<<D[i][j]<<",���ξ���"<<i<<" ";
				PrintPATH(g, i, j);
				cout<<j<<endl;
			}
			else
			{
				cout<<"�޷��ִ�"<<endl;
			}
			
		}
	}
}
int main(int argc,char* args[])
{
	MGraph mg;
	mg = buildMGraph();
	floyd(mg);
	PrintOC(mg);
 	return 0;
}

