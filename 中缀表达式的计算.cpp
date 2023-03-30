#include <iostream>
#include <stack>
#include <cmath>
using namespace std;

//根据符号，确定优先级
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
//true代表>= ,false代表< 
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
思路一：
在中缀转后缀的基础之上，准备一个运算数的栈
A.从左至右进行遍历： 
(1)遇到操作数就入栈，
(2)遇到运算符，则依次将栈中的两个操作数出栈，若操作数A，B为出栈顺序，先出栈的操作数在右，后出栈在左，即B?A 

思路二：直接进行运算
准备两个栈：运算数栈和运算符栈
从左至右进行遍历 ： 
1.遇见运算数，直接压入运算数栈


2.遇见运算符 

	若新运算符为'('，直接入栈，进行遍历的下一步；
	若新运算符为')'，则依次将两个栈进行出栈并运算，直到碰见'('，对'('出栈，做完之后进行遍历的下一步
	
	 
loc:判断运算符栈是否为空

	a.为空：
	将新运算符压栈 
	b.不为空： 
	(1)若新运算符的优先级>=栈顶运算符：将新运算符入栈 
	
	
	(2)若新运算符的优先级<栈顶运算符： [由于提前设置了'('的优先级，故不必考虑它] 
		将运算符栈顶的运算符出栈，将运算数栈顶的两个运算数出栈，进行运算，运算结果压入运算数栈，否则跳过 
	继续判断 (回到2)

B.全部遍历完，【此时除非最后一个元素是')'，否则栈中不可能存在'('，所以也不必考虑】 将运算符栈顶的运算符出栈，将运算数栈顶的两个运算数出栈，进行运算，运算结果压入运算数栈，如此循环，直至运算符栈空，将运算数栈的元素出栈，即得到计算结果 
		
*/ 

//易错点：
/*
1.注意对'('和')'的特殊处理(似乎只能特殊处理。。。)，输出的时候，不要输出'('

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
			//运算数入栈 
			st1.push(sum);
			sum=0;
		}
		
		
		if(i<s1.size())
		{
			new_char = s1.at(i);
			if(s1.at(i)=='(')
			{
				//压入运算符栈 
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
		
			else //加减乘除
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
					if(compare(new_char, top_char))  //新的运算符大于等于栈顶运算符 
					{
						st2.push(new_char);
						continue;
					}
					else
					{
						st2.pop();
						
						//进行计算
						right = st1.top();
						st1.pop();
						left = st1.top();
						st1.pop();
						st1.push(do_calculate(left,right,top_char));
						
						goto loc;   //继续判断 
						 
					}
				}
			} 
		}
	}
	
	while(!st2.empty())
	{
		top_char = st2.top();
		st2.pop();
						
		//进行计算
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

