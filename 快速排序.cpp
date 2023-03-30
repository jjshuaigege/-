#include <iostream>
using namespace std;

//���ŵĺ���˼��ͷ����ǻ��֣���ѡ��һ�������е�һ��Ԫ����Ϊ��Ԫ������һϵ�в�����ʹ�����ձ���Ԫ���Ԫ�ر�������Ԫ�ұߣ�����ԪС 
int N = 19;
//ͨ�õĻ��֣�ѡȡ��һ��λ�õ�Ԫ����Ϊ��Ԫ�� 
int partition(int a[], int left, int right)
{
//	//���� 
//	int cnt = 0;
//	//
	
	
	int temp = a[left];
//	a[left] = -999;     // ���Դ��룬����� 
	int i = left,j = right;
	while(i != j)
	{
		while(i != j && a[j] > temp)     //���ڵ�ʱ��Ҳ���������������ڡ�ȫԪ����ȵ����顱�������������������ɵ������Ԫ�ᴦ���м�λ�ã�ԭԪ�����еȷ�Ϊ�������� 
		{
			j--;	
		}
		
		if(i != j)
		{
			a[i] = a[j];
//			a[j] = -999;	//���Դ��룬�����
			i++;
		}
		
//		//���Դ���
//		cout<<"��"<<++cnt<<"��:";
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
//			a[i] = -999;    //���Դ��룬����� 
			j--;			
		}
		
//		//���Դ���
//		cout<<"��"<<++cnt<<"��:";
//		for(int i = 0;i<N;i++)
//		{
//			cout<<a[i]<<" ";
//		}
//		cout<<endl;
		
					
	}
	
	//��Ԫ�����λ�ã�i��jָ�빲ָͬ���λ�ã� 
	a[i] = temp;
	
	return i;
//	//���Դ���
//	cout<<"���ս����";
//	for(int i = 0;i<N;i++)
//	{
//		cout<<a[i]<<" ";
//	}
//	cout<<endl;
	
} 

//����ȡ�з��Ļ��� 
int partition_advanced(int a[], int left, int right)     //    һ����˵right-left>=1������������Ԫ�أ�����û��Ҫ����    ��ֻ������Ԫ�ص��������Ҫ���⴦�� 
{
	//���� 
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
	swap(a[mid],a[right-1]);    //����Ԫ�ص�right-1��λ�� 
	//���� "N==1" ������� 
	int temp = a[right-1];
	
//	���Դ���
	cout<<"��������ȡ�з�ѡ����Ԫ����Ԫ��ֵΪ"<<temp<<"\n";
	
//	���Դ���
	cout<<"������Ԫ��ĳ�ʼ�׶Σ�";      
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
		if(i<=j)     // ���i�Ѿ�Խ��j�ˣ���ʱ�Ͳ��ܽ����� 
		{
			swap(a[i],a[j]);
			i++;               //��iΪ�����������ˣ������ƶ�i��λ�ã������ܱ�֤����i��λ��һ����j�ĺ��� 
		}
		
		
		//���Դ���
//		cout<<"i:"<<i<<"j:"<<j<<"a[i]="<<a[i]<<"��"<<++cnt<<"�ν�������Ԫ��֮��";   
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
	//���Դ���
//	cout<<"���ս����";
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
//		���Դ���  
		cout<<left<<"��"<<right<<"�Ļ�����ɺ�\n";
		for(int i = 0;i<N;i++)
		{
			cout<<a[i]<<" ";
		}
		cout<<"\n";
		
		quick_sort_main(a,left,ele_index-1);
		quick_sort_main(a,ele_index+1,right);
	}
}

void quick_sort(int a[],int N)    //ͳһ�����ӿ�Ϊ��void (*)(int a[], int N)������ʽ 
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
	//���Դ���
	cout<<"���ս����";
	for(int i = 0;i<N;i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
	
 	return 0;
}

