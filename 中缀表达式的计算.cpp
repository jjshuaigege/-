#include <iostream>
#include <stack>
#include <cmath>
using namespace std;

//���ݷ��ţ�ȷ�����ȼ�
int get_prior(const char& obj)
{
	switch(obj)
	{
		case '(':
			return -1;
			break;
		case '+':
		case '-':
			return 0;
			break;
		case '*':
		case '/':
			return 1;
			break;
		default:
			return -99;
	}
} 
//true����>= ,false����< 
bool compare(const char& new_char, const char& top_char)
{
		return get_prior(new_char) >= get_prior(top_char);
} 

do_calculate(const int& left,const int& right,const char& sign)
{
	int ret=-999;
	switch(sign)
	{
		case '+':
			ret = left + right;
			break;
		case '-':
			ret = left - right;
			break;
		case '*':
			ret = left * right;
			break;
		case '/':
			ret = left / right;
			break;
	}
	return ret;
}
//
/*
˼·һ��
����׺ת��׺�Ļ���֮�ϣ�׼��һ����������ջ
A.�������ҽ��б����� 
(1)��������������ջ��
(2)����������������ν�ջ�е�������������ջ����������A��BΪ��ջ˳���ȳ�ջ�Ĳ��������ң����ջ���󣬼�B?A 

˼·����ֱ�ӽ�������
׼������ջ��������ջ�������ջ
�������ҽ��б��� �� 
1.������������ֱ��ѹ��������ջ


2.��������� 

	���������Ϊ'('��ֱ����ջ�����б�������һ����
	���������Ϊ')'�������ν�����ջ���г�ջ�����㣬ֱ������'('����'('��ջ������֮����б�������һ��
	
	 
loc:�ж������ջ�Ƿ�Ϊ��

	a.Ϊ�գ�
	���������ѹջ 
	b.��Ϊ�գ� 
	(1)��������������ȼ�>=ջ��������������������ջ 
	
	
	(2)��������������ȼ�<ջ��������� [������ǰ������'('�����ȼ����ʲ��ؿ�����] 
		�������ջ�����������ջ����������ջ����������������ջ���������㣬������ѹ��������ջ���������� 
	�����ж� (�ص�2)

B.ȫ�������꣬����ʱ�������һ��Ԫ����')'������ջ�в����ܴ���'('������Ҳ���ؿ��ǡ� �������ջ�����������ջ����������ջ����������������ջ���������㣬������ѹ��������ջ�����ѭ����ֱ�������ջ�գ���������ջ��Ԫ�س�ջ�����õ������� 
		
*/ 

//�״�㣺
/*
1.ע���'('��')'�����⴦��(�ƺ�ֻ�����⴦������)�������ʱ�򣬲�Ҫ���'('

*/ 
int main(int argc,char* args[])
{
	while(true)
	{
		
	stack<int> st1;
	stack<char> st2;
	string s1,s2;
	int sum=0,digit=0;
	char top_char;
	char new_char;
	int left,right;
	cin>>s1;
	for(int i=0;i<s1.size();i++)
	{
		if(s1.at(i)>='0'&&s1.at(i)<='9')
		{
			while (i<s1.size()&&s1.at(i)>='0'&&s1.at(i)<='9')
			{
				digit = 1-'1'+s1.at(i);
				sum = sum*10+digit;
				i++;
			}
			//��������ջ 
			st1.push(sum);
			sum=0;
		}
		
		
		if(i<s1.size())
		{
			new_char = s1.at(i);
			if(s1.at(i)=='(')
			{
				//ѹ�������ջ 
				st2.push(new_char);
				continue;
			}
			else if(new_char==')')
			{
				top_char = st2.top();
				st2.pop();
				while(top_char!='(')
				{
					
					right = st1.top();
					st1.pop();
					left = st1.top();
					st1.pop();
					
					
					
					st1.push(do_calculate(left,right,top_char));
					
					top_char = st2.top();
					st2.pop();
				}
				
			}
		
			else //�Ӽ��˳�
			{
				loc:
				if(st2.empty())
				{
					st2.push(new_char);
					continue;
				}
				else
				{
					top_char = st2.top();
					if(compare(new_char, top_char))  //�µ���������ڵ���ջ������� 
					{
						st2.push(new_char);
						continue;
					}
					else
					{
						st2.pop();
						
						//���м���
						right = st1.top();
						st1.pop();
						left = st1.top();
						st1.pop();
						st1.push(do_calculate(left,right,top_char));
						
						goto loc;   //�����ж� 
						 
					}
				}
			} 
		}
	}
	
	while(!st2.empty())
	{
		top_char = st2.top();
		st2.pop();
						
		//���м���
		right = st1.top();
		st1.pop();
		left = st1.top();
		st1.pop();
		st1.push(do_calculate(left,right,top_char));
	}
	
	int ret = st1.top();
	cout<<ret<<endl;
	 
	

	}
 	return 0;
}

