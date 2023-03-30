#include <iostream>
using namespace std;
merge_operation(int a[], int temp[], int left, int left_end, int right)
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
	
	//temp的内容拷贝回去 
	for(int i = left;i<=right;i++)
	{
		a[i] = temp[i];
	}	
}

void merge_sort_main(int a[], int temp[],int left,int right)
{
	if(left==right)
	{
		return;
	}
	else
	{
		int mid = (left + right)/2;
		merge_sort_main(a,temp,left,mid);
		merge_sort_main(a,temp,mid+1,right);     //递归排序，使得左右两部分的内部各自是有序的 
		merge_operation(a,temp,left,mid,right);  //将两段有序序列进行归并操作，使得整体有序 
		
		//调试代码 
		cout<<"规模为"<<right-left+1<<"的归并";
		for(int i = left;i<=right;i++)
		{
			cout<<a[i]<<" ";
		}
		cout<<endl;	
	}
}
void merge_sort(int a[], int N)
{
	int* temp = new int[N];
	merge_sort_main(a,temp,0,N-1);
}
int main(int argc,char* args[])
{
	int a[]={6,8,91,56,44,94,12,31,49,67,89,13,64,94,13,65,12,78,64};
	merge_sort(a,19);

 	return 0;
}

