#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;
int oc;
vector<char> sign_set;
bool isfound;
//bool func(int a[])
//{
//	oc = a[0];
//	if(dfs(a,4)==24)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
void printOC(int a[])
{
	//��ӡ���
	cout<<a[0]<<" ";
	for(int i=0;i<3;i++)
	{
		cout<<sign_set[i]<<" ";
		cout<<a[i+1];
		if(i!=2)
		{
			cout<<" ";
		}
	}
	cout<<endl;
}

void dfs(int a[],int N,int flag)   //������a[0],a[1],a[2],...a[N-1]  
{
	
	
	if(N==5) //���� 
	{
		if(oc == 24)
		{
//			isfound = true;
			printOC(a);
			oc = 0;
		}
		return;
	}
	
	//�������
	int temp = oc;
	if(N==1)    //��� 
	{
		oc = a[N-1];
	}
	
	
	//���� 
	
	else
	{
		switch(flag)
		{
			case 0:
				sign_set.push_back('+');
				oc += a[N-1];
				break;
			case 1:
				sign_set.push_back('-');
				oc -= a[N-1];
				break;
			case 2:
				sign_set.push_back('*');
				oc *= a[N-1];
				break;
			case 3:	
				sign_set.push_back('/');
				oc /= a[N-1];
				break;
		}
	}
	
	
	
	//�ݹ�����ݲ���
	for(int subflag=0;subflag<4;subflag++)
	{
//		if(!isfound)
//		{
//			dfs(a,N+1,subflag);	
//		}
		dfs(a,N+1,subflag);	
		if(N+1==5)    //ִֻ��һ�� 
		{
			break;
		}
		
	}
	oc = temp;
	
	if(N>1&&N<5)
	{
		sign_set.pop_back();	
	}
	
	
}
	
void dfs_new(int a[], int N,int& oc)
{
	int temp;
	if(N == 5)
	{	
		if(oc==24)
		{
			cout<<a[0]<<" ";
			for(int i = 0;i<3;i++)
			{
				cout<<sign_set[i]<<" ";
				cout<<a[i+1]<<" ";
			}
			cout<<"= "<<oc<<endl;
		}
		
		return;
		
	}
	
	else if(N == 1)
	{
		oc = a[0];
		dfs_new(a,N+1,oc);
	}
	
	
	else   //5>N>1
	{
		//���� 
		temp = oc;
		
		for(int flag = 0;flag<3;flag++)    //4���ھ� 
		{
			switch(flag)
			{
				case 0:
					oc += a[N-1];
					sign_set.push_back('+');
					break;
				case 1:
					oc -= a[N-1];
					sign_set.push_back('-');
					break;
				case 2:
					oc *= a[N-1];
					sign_set.push_back('*');
					break;
				case 3:
					oc /= a[N-1];
					sign_set.push_back('/');
					break;
			}
			
			dfs_new(a,N+1,oc);
			
			//���� 
			oc=temp;
			sign_set.pop_back();
			
		}		
	}
	
	
 } 
int main(int argc,char* args[])
{
	int a[4];
	int num;
	cin>>num;
	for(int n=0;n<num;n++)
	{
		isfound = false;
		oc = 0;
		for(int l = 0;l<4;l++)
		{
			cin>>a[l];
		}
//		int oc=a[0];
//		vector<char> sign_set;
//		for(int i = 1;i<=3;i++)
//		{
//			//������� 
//			int temp = oc;
//			
//			for(int flag = 0;flag<4;flag++)
//			{
//				switch(flag)
//				{
//					case 0:
//						oc += a[i];
//						sign_set.push_back('+');
//						break;
//					case 1:
//						oc -= a[i];
//						sign_set.push_back('-');
//						break;
//					case 2:
//						oc *= a[i];
//						sign_set.push_back('*');
//						break;
//					case 3:
//						oc /= a[i];
//						sign_set.push_back('/');
//						break;
//			
//				}
//			}
//			if(i == 3 && oc == 24)  //ȫ�������ֶ����뵽���㣬���ҽ������24 
//			{
//				cout<<a[0]<<" "
//				for(int i = 0;i<3;i++)
//				{
//					cout<<*i<<" "
//					cout<<a[i]
//					if(i!=2)
//					{
//						cout<<" "
//					}
//				}
//				cout<<endl;
//			}
//			
//			//���ݲ��� 
//			oc = temp;
//			sign_set.pop_back();
//		}
		int oc = 0;
		dfs_new(a,1,oc);
	}
	
 	return 0;
}

