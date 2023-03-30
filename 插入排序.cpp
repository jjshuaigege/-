#include <iostream>
using namespace std;

//���ʱ�临�Ӷ� O(n)
//���ƽ�� O(n^2) 
//���������ǻ�����������У�������
 
//ֱ�Ӳ������� 
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
	
		//���Դ��� 
		cout<<"��"<<i<<"��:";
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
			start = mid + 1;   //���ұ�ȥ 		
		}
		else
		{
			end = mid - 1;       //�����ȥ 
		}	
	}
	return start;
}
//�԰��������     (ûɶ����)
void binary_search_insert_sort(int a[],int N)
{
	for(int i = 1;i<=N-1;i++)
	{
		int temp = a[i];
		
		//���ֲ����ҵ�Ҫ����ĵط�
		int obj_index = binary_search(temp,a,0,i-1);
		
		for(int j = i-1;j>=obj_index;j--)
		{
			a[j+1]=a[j];
		}
		a[obj_index] = temp;
		
		//���Դ��� 
		cout<<"��"<<i<<"��:";
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

