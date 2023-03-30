#include <iostream>
using namespace std;

void merge_operation(int a[], int temp[], int left, int left_end, int right)
{
	int p = left;
	int q = left_end+1;
	int r = left;
	while(p <= left_end && q <= right)
	{
		if(a[p] <= a[q])
		{
			temp[r++] = a[p++];
		}
		else
		{
			temp[r++] = a[q++];
		}
	}
	
	while(p<=left_end)
	{
		temp[r++] = a[p++];
	}
	
	while(q<=right)
	{
		temp[r++] = a[q++];
	}
	
//	//temp的内容拷贝回去 
//	for(int i = left;i<=right;i++)
//	{
//		a[i] = temp[i];
//	}
	
}


void merge_func(int a[],int temp[],int length,int N)
{
	
	int i;
	for(i = 0; i<=N-2*length; i+=2*length)
	{
		merge_operation(a,temp,i,i+length-1,i+2*length-1);
	}
	
	if(i+length < N)    //够两个子列 
	{
		merge_operation(a,temp,i,i+length-1,N-1);
	}
	else
	{
		while(i<N)
		{
			temp[i] = a[i];
//			temp[i++] = a[i++];
			i++;
		}
		
	}
	
	//调试代码 
	cout<<"调试)";
	for(int i = 0;i<N;i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;	
	
	//调试代码 
	cout<<"各个子序列规模为"<<length<<"的各自归并为规模"<<2*length<<"（如果允许的话)";
	for(int i = 0;i<N;i++)
	{
		cout<<temp[i]<<" ";
	}
	cout<<endl;	
}


//归并排序的非递归写法 
void merge_sort(int a[],int N)
{
	int* temp = new int[N];
	for(int length = 1;length<N;)
	{
		
		merge_func(a,temp,length,N);
		length *=2;
		merge_func(temp,a,length,N);
		length *= 2;
	}
}



	

int main(int argc,char* args[])
{
	int a[]={6,8,91,56,44,94,12,31,49,67,89,13,64,94,13,65,12,78,64};
	merge_sort(a,19);

	
//	int a[]={5,2,3};
//	merge_sort(a,3);
 	return 0;
}

