#include <iostream>
#include <algorithm>
using namespace std;
/*
��������������N��������Ai��z��������{A1,A2,A3,...,AN},����f(i,j) = max {0,(��ʽ��Ak,k=i��j���)}�����ֵ 
*/ 
//�㷨1������㷨
//�㷨���Ӷ�ΪO(n^3) 
int alg1(int a[],int n)
{
	int V;
	int max=0;
	for(int i=0;i<n;i++)
	{
		for(int j=i;j<n;j++)
		{
			V = 0;
			for(int k=i;k<=j;k++)
			{
				V += a[k];	
			}
			if(V>max)
			{
				max = V;
			}
		}
	}
	return max;
}
//�㷨2���Ľ���,˼·������㲻�䣬�յ�����ƶ�ʱ��ÿ��ֻ���һ��Ԫ�أ��������͵Ĺ����в�����ͷ��ʼ�����ܺͣ���ֻ�轫��͵Ĳ���Sij:=Sij+a[k]
//�㷨���Ӷ�ΪO(n^2) 
int alg2(int a[],int n)
{
	int V;
	int max=0;
	for(int i=0;i<n;i++)
	{
		V=0;
		
		for(int j=i;j<n;j++)
		{
			V += a[j];	

			if(V>max)
			{
				max = V;
			}
		}
	}
	return max; 
}
 
//�㷨3������,˼·����1��N��������к�R1Nʱ���ɻ���Ϊ�����������һ���������⣬�ֱ���1��N/2��N/2+1��N���������R1,N/2��RN/2+1,N��������к͡�
// �Լ��������⣺�Կ�Խ�������еķֽ��ߵ�����������У����ڿ�Խ�ֽ��ߣ����Էֽ���Ϊ��㣬���������Ѱ�ҳ�������������е������벿�֣�
//���ұ�����Ѱ�ҳ�������������е�����Ұ벿��
//�㷨���Ӷ�ΪO(nlogn) 
int cross(int a[],int n)
{
	int left_p=0,left_p_max=0,right_p=0,right_p_max=0;
	for(int i = n/2-1;i>=0;i--)
	{
		left_p += a[i];
		if(left_p>left_p_max)
		{
			left_p_max = left_p;
		} 
	}	
	for(int i = n/2;i<n;i++)
	{
		right_p += a[i];
		if(right_p>right_p_max)
		{
			right_p_max = right_p;
		} 
	}
	return left_p_max+right_p_max;
} 
int alg3(int a[],int n)
{
	if(n>1)
	{
//		int t1=alg3(a,n/2);
//		int t2=alg3(&a[n/2],n-n/2);
//		int temp = t1>t2?t1:t2;
//		int t3 = cross(a,n);
//		temp = temp>t3?temp:t3;
		
		int temp = max(alg3(a,n/2),alg3(&a[n/2],n-n/2));
		temp = max(temp,cross(a,n));
		return temp;
	}
	
	return a[0];
}


//�㷨4,���ߴ����ص��������գ��� ˼·���������ҿ�ʼ���������ϵؼ����µ�Ԫ��������֮�У����������е��ܳ��ȡ� 
//(1).�������µ�Ԫ�غ��ܳ���Ϊ������ֱ������ǰ�������Ԫ�أ���Ϊ������ʹ�ú���ĳ��������� �� 
//(2).�������µ�Ԫ�غ��ܳ��ȱ���󳤶Ȼ����������󳤶�Ϊ��ǰ���ȡ� 
//�㷨���Ӷ�ΪO(n) 
int alg4(int a[],int n)
{
	int maxV=0,V=0;
	for(int i = 0; i < n; i++)
	{
		V+=a[i];
		if(V<0)
		{
			V=0;
		}
		if(maxV<V)
		{
			maxV = V;
		}
		
	}
	return maxV;
}

int main(int argc,char* args[])
{
	int N; 
	cin>>N;
	int a[N];
	for(int i=0;i<N;i++)
	{
		cin>>a[i];
	}
	cout<<alg1(a,N)<<endl<<alg2(a,N)<<endl<<alg3(a,N)<<endl<<alg4(a,N)<<endl;
 	return 0;
}

