#include <bits/stdc++.h>
using namespace std;
/*
举个例子，序列： 7 2 3 4 5 6 1   该序列有个特征：它是基本有序的 
此种情况插入排序优于冒泡排序 
*/ 

//最好时间复杂度 O(n)
//最坏和平均 O(n^2) 
void bubble_sort(int a[], int N)
{
	bool flag = false;
	for(int i = 0;i<N-1;i++)
	{
		
		flag = false;
		for(int j = 0;j < N-1-i;j++)
		{
			if(a[j]>a[j+1])
			{
				flag = true;
				swap(a[j],a[j+1]);
			}
		}
		
		//调试代码
		cout<<"第"<<i+1<<"趟:";
		for(int i = 0;i<N;i++)
		{
			cout<<a[i]<<" ";
		}
		cout<<endl;
		 
		if(flag == false)   //一轮冒泡过后，没有交换元素，说明是有序的，提前退出 
		{
			cout<<"进行完第"<<i+1<<"轮，已经有序。"; 
			break;
		}
	}
}
int main(int argc,char* args[])
{
	int a[]={6,8,91,56,44,94,12,31};
	bubble_sort(a,8);
	for(int x:a)
	{
		cout<<x<<" ";
	}
	cout<<endl;
 	return 0;
}

