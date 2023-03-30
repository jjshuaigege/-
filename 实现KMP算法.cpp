#include <iostream>
#include <string>
#define NotFound -1
using namespace std;
typedef int position;
/* 
1.��j=i-1
2.����j<0����next[j]==-1���������j<0,��next[i] = -1;��next[j] == -1:(1)��a[i] == a[0]����next[i] = 0 (2)��a[i] != a[0]����next[i] = -1
3.(j>=0��next[j]>=0)   �к��ĵ���ʽ����next[j]+1 == a[i],��next[i] = next[j]+1������j := next[j]���ص�2  
*/
int*& calculateNext(int*& next, string s)
{
	int length = s.size();
	
	next[0] = -1;
	for(int i = 1;i<length;i++)
	{
		int j = i-1;
		int temp = next[j];
		
		while(true)
		{
			if(s[i] == s[temp+1])
			{
				next[i] = temp+1;     //�������������1.�з���������ǰ����׺����������    2.û�з���������ǰ����׺���������� 
				break;
			}
			else     
			{
				if(temp==-1)
				{
					next[i] = -1;     //û�з���������ǰ����׺���������У�����a[0]���� 
					break;	
				}
				else
				{
					temp = s[temp];   //����һ�����̵�ǰ����׺����������
				}
				
			}
		}
	}
	return next;
}
position KMP(string main_string, string pattern_string)
{
	int pattern_length = pattern_string.size();
	int main_length = main_string.size();
	
	//��ģʽ������Ӧ��next���� 
	int* next = new int[pattern_length];
	
	calculateNext(next,pattern_string);
	
	position ret;
	int p=0,q=0;    //p��������ָ�룬q��ģʽ����ָ�� 
	
	while(q<pattern_length && p<main_length)
	{
		if(main_string[p] == pattern_string[q])
		{
			p++;
			q++;
		}
		else if(q>0)
		{
			q = next[q-1]+1;
		}
		else
		{
			p++;
		}
		
	}
	if(q == pattern_length)
	{
		ret = p-pattern_length;
	}
	else
	{
		ret = NotFound;
	}
	
	return ret;
}
int main(int argc,char* args[])
{
//	string sa = "abcghabc";
//	int* p =new int[sa.size()];
//	p = calculateNext(p,sa);
//	for(int i = 0;i<sa.size();i++)
//	{
//		cout<<p[i]<<" ";
//	}
//	cout<<"\n";
	string s1,s2;
	cin>>s1>>s2;
	int pos = KMP(s1,s2);
	cout<<"λ��Ϊ"<<pos<<endl;
	string s3 = s1.substr(pos,s2.length());
	cout<<s3<<endl;
 	return 0;
}

