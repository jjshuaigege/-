#include <bits/stdc++.h>
using namespace std;
/*
�ٸ����ӣ����У� 7 2 3 4 5 6 1   �������и����������ǻ�������� 
�������������������ð������ 
*/ 

//���ʱ�临�Ӷ� O(n)
//���ƽ�� O(n^2) 
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
		
		//���Դ���
		cout<<"��"<<i+1<<"��:";
		for(int i = 0;i<N;i++)
		{
			cout<<a[i]<<" ";
		}
		cout<<endl;
		 
		if(flag == false)   //һ��ð�ݹ���û�н���Ԫ�أ�˵��������ģ���ǰ�˳� 
		{
			cout<<"�������"<<i+1<<"�֣��Ѿ�����"; 
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

