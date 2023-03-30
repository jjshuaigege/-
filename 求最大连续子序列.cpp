#include <iostream>
#include <algorithm>
using namespace std;
/*
问题描述：给定N个整数（Ai∈z）的序列{A1,A2,A3,...,AN},求函数f(i,j) = max {0,(公式：Ak,k=i到j求和)}的最大值 
*/ 
//算法1，最笨的算法
//算法复杂度为O(n^3) 
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
//算法2，改进版,思路：当起点不变，终点进行移动时，每次只相隔一个元素，因此在求和的过程中不必重头开始计算总和，而只需将求和的部分Sij:=Sij+a[k]
//算法复杂度为O(n^2) 
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
 
//算法3，分治,思路：求1到N的最大子列和R1N时，可划分为两个子问题和一个额外问题，分别求1到N/2和N/2+1到N的最大子列R1,N/2和RN/2+1,N的最大子列和。
// 以及额外问题：以跨越两个子列的分界线的最大连续序列，由于跨越分界线，可以分界线为起点，向左遍历，寻找出跨界限连续子列的最大左半部分，
//向右遍历，寻找出跨界限连续子列的最大右半部分
//算法复杂度为O(nlogn) 
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


//算法4,在线处理（重点理解和掌握！） 思路：从左向右开始遍历，不断地加入新的元素至序列之中，并更新序列的总长度。 
//(1).若加入新的元素后，总长度为负，则直接抛弃前面的所有元素（因为不可能使得后面的长度增长） 。 
//(2).若加入新的元素后，总长度比最大长度还大，则更新最大长度为当前长度。 
//算法复杂度为O(n) 
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

