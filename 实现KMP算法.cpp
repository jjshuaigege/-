#include <iostream>
#include <string>
#define NotFound -1
using namespace std;
typedef int position;
/* 
1.令j=i-1
2.考虑j<0或者next[j]==-1的情况，若j<0,则next[i] = -1;若next[j] == -1:(1)若a[i] == a[0]，则next[i] = 0 (2)若a[i] != a[0]，则next[i] = -1
3.(j>=0且next[j]>=0)   有核心递推式：若next[j]+1 == a[i],则next[i] = next[j]+1，否则j := next[j]，回到2  
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
				next[i] = temp+1;     //包含两种情况，1.有符号条件的前、后缀公共子序列    2.没有符合条件的前、后缀公共子序列 
				break;
			}
			else     
			{
				if(temp==-1)
				{
					next[i] = -1;     //没有符合条件的前、后缀公共子序列，且与a[0]不等 
					break;	
				}
				else
				{
					temp = s[temp];   //找下一个更短的前、后缀公共子序列
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
	
	//求模式串所对应的next数组 
	int* next = new int[pattern_length];
	
	calculateNext(next,pattern_string);
	
	position ret;
	int p=0,q=0;    //p是主串的指针，q是模式串的指针 
	
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
	cout<<"位置为"<<pos<<endl;
	string s3 = s1.substr(pos,s2.length());
	cout<<s3<<endl;
 	return 0;
}

