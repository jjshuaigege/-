#include <iostream>
using namespace std;
//���ȶ�
//���αȽϺõĻ���ʱ�临�Ӷ�ƽ���ﵽO(n^1.5)
 
void shell_sort(int a[],int N)
{
	int D = 8;
	for(;D>=1;D/=2)
	{
		for(int d=0;d<D;d++)    //�ж�������У�ÿ������������Ԫ��֮��������D 
		{
			for(int i = D+d; i<N; i+=D)    //��ÿ�������н���ϣ������ 
			{
				int temp = a[i];
				int j;
				for(j = i-D; j>=0 && a[j]>temp; j-=D)
				{
					a[j+D] = a[j];
				}
				a[j+D] = temp;
			}	
		}
		cout<<"����Ϊ"<<D<<",�źõ�����Ϊ��";
		for(int i = 0;i<N;i++)
		{
			cout<<a[i]<<" ";
		}
		cout<<endl;	
	}	
}

int main(int argc,char* args[])
{

// 	int a[]={91,8,66,45,6};
	int a[]={6,8,91,56,44,94,12,31,49,67,89,13,64,94,13,65,12,64,78};
	shell_sort(a,19);
	for(int x:a)
	{
		cout<<x<<" ";
	}
	cout<<endl;
 	return 0;
}

