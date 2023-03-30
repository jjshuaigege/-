#include <iostream>
#include <cmath>
using namespace std;


//������˳��ṹʵ�ֲ��鼯��������±���ڶ�ӦԪ�ص����ݵ�ֵ
class UFset
{
	private:
		int size;
		int* a;
	public:
		UFset(int size):size(size),a(new int[size])
		{
			for(int i = 0;i<size;i++)
			{
				a[i] = -1;    //��ʼ��ʱ��ÿ�����ĸ��ڵ㶼���Լ������С��0��ÿ�������������Ľ��ĸ�������1����˾���ֵΪ1���ۺ���������ʼ��Ϊ-1	
			}	
		}
		
	//Ѱ�ҽ��value�ĸ��ڵ� 
	int find(int value)
	{
		
		if(a[value]>0)
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
//		while(parent>0)
//		{
//			value = parent;
//			parent = a[value];
//		}
	
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





int main(int argc,char* args[])
{
	UFset uf(7);
	uf.Union_o(2,5);
	uf.Union_o(4,3);
	uf.Union_o(2,4);
	uf.Union_o(6,1);
	uf.Union_o(6,0);
//	uf.find(3);
	uf.show();
	
//	cout<<INT_MAX<<endl;
 	return 0;
}

