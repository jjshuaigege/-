#include <iostream>
using namespace std;

//快排的核心思想和方法是划分，即选定一段序列中的一个元素作为主元，进行一系列操作，使得最终比主元大的元素被放在主元右边，比主元小 
int N = 19;
//通用的划分（选取第一个位置的元素作为主元） 
int partition(int a[], int left, int right)
{
//	//调试 
//	int cnt = 0;
//	//
	
	
	int temp = a[left];
//	a[left] = -999;     // 调试代码，代表空 
	int i = left,j = right;
	while(i != j)
	{
		while(i != j && a[j] > temp)     //等于的时候也做交换，这样对于“全元素相等的数组”这类特殊情况，划分完成的最后，主元会处于中间位置，原元素序列等分为两组序列 
		{
			j--;	
		}
		
		if(i != j)
		{
			a[i] = a[j];
//			a[j] = -999;	//调试代码，代表空
			i++;
		}
		
//		//调试代码
//		cout<<"第"<<++cnt<<"趟:";
//		for(int i = 0;i<N;i++)
//		{
//			cout<<a[i]<<" ";
//		}
//		cout<<endl;
		
		
		while(i != j && a[i] < temp)
		{
			i++;
		}
		
		if(i != j)
		{
			a[j] = a[i];
//			a[i] = -999;    //调试代码，代表空 
			j--;			
		}
		
//		//调试代码
//		cout<<"第"<<++cnt<<"趟:";
//		for(int i = 0;i<N;i++)
//		{
//			cout<<a[i]<<" ";
//		}
//		cout<<endl;
		
					
	}
	
	//主元插入空位置（i、j指针共同指向的位置） 
	a[i] = temp;
	
	return i;
//	//调试代码
//	cout<<"最终结果：";
//	for(int i = 0;i<N;i++)
//	{
//		cout<<a[i]<<" ";
//	}
//	cout<<endl;
	
} 

//三者取中法的划分 
int partition_advanced(int a[], int left, int right)     //    一般来说right-left>=1，即至少两个元素，否则没必要划分    对只有两个元素的情况，需要特殊处理 
{
	//调试 
//	int cnt = 0; 
	int ret;
	
	int mid = (left+right)/2;
	if(a[left] > a[right])
	{
		swap(a[left], a[right]);
	}
	if(a[left] > a[mid])
	{
		swap(a[left], a[mid]);
	}
	if(a[mid] > a[right])
	{
		swap(a[mid], a[right]);
	}
	swap(a[mid],a[right-1]);    //将主元藏到right-1的位置 
	//考虑 "N==1" 的情况？ 
	int temp = a[right-1];
	
//	调试代码
	cout<<"经过三者取中法选择主元后，主元的值为"<<temp<<"\n";
	
//	调试代码
	cout<<"调整主元后的初始阶段：";      
	for(int i = 0;i<N;i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
	 
	
	
	int i = left + 1;
	int j = right - 2;
	
	while(i<=j)
	{
		while(a[i]<temp)
		{
			i++;
		}
		
		while(a[j]>temp)
		{
			j--;
		}
		if(i<=j)     // 如果i已经越过j了，这时就不能交换了 
		{
			swap(a[i],a[j]);
			i++;               //以i为主，交换完了，立即移动i的位置，这样能保证最终i的位置一定在j的后面 
		}
		
		
		//调试代码
//		cout<<"i:"<<i<<"j:"<<j<<"a[i]="<<a[i]<<"第"<<++cnt<<"次交换两个元素之后：";   
//		for(int i = 0;i<N;i++)
//		{
//			cout<<a[i]<<" ";
//		}
//		cout<<"\n";
		
	}
	if(i<right-1)
	{
		swap(a[i],a[right-1]);
		ret = i;
	}
	else
	{
		ret = right-1;
	}
	
	return ret;
	//调试代码
//	cout<<"最终结果：";
//	for(int i = 0;i<N;i++)
//	{
//		cout<<a[i]<<" ";
//	}
//	cout<<endl;

}

void quick_sort_main(int a[], int left, int right)
{
	if(right>left)
	{     
		int ele_index = partition_advanced(a,left,right);
//		调试代码  
		cout<<left<<"到"<<right<<"的划分完成后\n";
		for(int i = 0;i<N;i++)
		{
			cout<<a[i]<<" ";
		}
		cout<<"\n";
		
		quick_sort_main(a,left,ele_index-1);
		quick_sort_main(a,ele_index+1,right);
	}
}

void quick_sort(int a[],int N)    //统一函数接口为“void (*)(int a[], int N)”的形式 
{
	quick_sort_main(a,0,N-1);
}
int main(int argc,char* args[])
{
//	int a[]={48,8,91,56,44,94,12,31,49,67,89,13,64,94,13,65,12,78,64};
//	quick_sort(a,19);
	int a[]={48,8};
	quick_sort(a,2);
//	
	//调试代码
	cout<<"最终结果：";
	for(int i = 0;i<N;i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
	
 	return 0;
}

