#include <iostream>
using namespace std;
void selection_sort(int a[],int N)
{
	int min_index = 0;
	for(int i = 0;i<=N-2;i++)     //选取最小元素，重复N-1次 
	{
		int min_index = i;
		for(int j = i+1; j<N; j++)
		{
			if(a[min_index]>a[j])
			{
				min_index = j;
			}
		}
		swap(a[i],a[min_index]);
		cout<<"第"<<i+1<<"趟:";
		for(int i = 0;i<N;i++)
		{
			cout<<a[i]<<" ";
		}
		cout<<endl;	
		
	}
	
}
int main(int argc,char* args[])
{
	int a[]={6,8,91,56,44,94,12,31,49,67,89,13,64,94,13,65,12,78,64};
	selection_sort(a,19);
	for(int x:a)
	{
		cout<<x<<" ";
	}
	cout<<endl;
 	return 0;
 	return 0;
}

