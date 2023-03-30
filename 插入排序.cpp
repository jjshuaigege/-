#include <iostream>
using namespace std;

//最好时间复杂度 O(n)
//最坏和平均 O(n^2) 
//如果本身就是基本有序的序列，则有利
 
//直接插入排序 
void insert_sort(int a[],int N)
{
	int i,j;
	for(i = 1;i <= N-1;i++)
	{
		int temp = a[i];
		for(j = i-1; j>=0 && a[j]>temp; j--)
		{
			a[j+1] = a[j];	
		}
		a[j+1] = temp;
	
		//调试代码 
		cout<<"第"<<i<<"趟:";
		for(int i = 0;i<N;i++)
		{
			cout<<a[i]<<" ";
		}
		cout<<endl;
	}
}

int binary_search(int x,int a[], int start, int end)
{	
	while(start <= end)
	{
		int mid = (start+end)/2;
		if(a[mid] <= x)
		{
			start = mid + 1;   //到右边去 		
		}
		else
		{
			end = mid - 1;       //到左边去 
		}	
	}
	return start;
}
//对半插入排序     (没啥卵用)
void binary_search_insert_sort(int a[],int N)
{
	for(int i = 1;i<=N-1;i++)
	{
		int temp = a[i];
		
		//二分查找找到要插入的地方
		int obj_index = binary_search(temp,a,0,i-1);
		
		for(int j = i-1;j>=obj_index;j--)
		{
			a[j+1]=a[j];
		}
		a[obj_index] = temp;
		
		//调试代码 
		cout<<"第"<<i<<"趟:";
		for(int i = 0;i<N;i++)
		{
			cout<<a[i]<<" ";
		}
		cout<<endl;
			
	}	
} 
int main(int argc,char* args[])
{
	int a[]={91,8,66,45,6};
//	int a[]={6,8,91,56,44,94,12,31};
	binary_search_insert_sort(a,5);
	for(int x:a)
	{
		cout<<x<<" ";
	}
	cout<<endl;
 	return 0;
}

