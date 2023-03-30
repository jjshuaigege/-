#include <iostream>
#include <Cstring>
#include <stack>
using namespace std;


//中缀表达式转后缀表达式 如中缀表达式：2+9/3-5    后缀表达式：2 9 3 / + 5 -
/*
基本思路：
建立一个关于运算符的栈
对中缀表达式从左至右进行遍历 
1.碰到运算数，则直接输出 
2.碰到运算符A，若栈顶元素为空，则入栈；若栈顶元素B不为空，则将其与栈顶运算符B的优先级作比较
（1）若A>=B，则将运算符A入栈
（2）若A<B, 则将B出栈，A继续与栈顶运算符做优先级的比较，若A<B，则继续将栈顶元素B出栈。
直至A>=B或者栈空，将A入栈。
(3)若已全部遍历完，则将栈中元素依次出栈并且输出 
**注意！ 碰到运算符 '('，则必定入栈。 
**若碰到运算符')'，则依次将栈中运算符出栈，直至遇见'(' 
*/ 

//记录运算符类型与运算符优先级 
struct ele
{
	char value;
	int priority_level;
	
	//初始化，并且根据字符值设置优先级 
	ele(char value):value(value)
	{
		switch(value)
		{
			case '(':
				priority_level = -1;
				break;
			case '+':
			case '-':
				priority_level = 0;
				break;
			case '*':
			case '/':
				priority_level = 1;
				break;
			default:
				priority_level = -11;
		}
	}
	
	friend ostream& operator << (ostream& o,const ele& x)
	{
		o<<"值："<<x.value<<"\t"<<"优先级:"<<x.priority_level;
	}
};

void s2_add(string& s2, const char& x)
{

	if(x!='(')
	{
		s2.push_back(x);
	}
	
}

int main(int argc,char* args[])
{
	while(true)
	{
		stack<ele> St;
	
		ele popped_ele(' '),top_ele(' '),new_ele(' ');
		
		char now_char;
		
		//中缀表达式的字符串 
		string s1;
		cin>>s1;
		
		//后缀表达式的字符串 
		string s2="";
		
		int i = 0; 
		loc1:
		for(;i<s1.size();i++)
		{
			now_char=s1.at(i);
			
			//用于比较实际运算符的优先级 
			int now_char_level = -1;
			
			
			
			//直接输出 
			if(now_char>='0'&&now_char<='9')
			{
				int flag = 0;
				while(now_char>='0'&&now_char<='9')
				{
					s2_add(s2,now_char);
					i++;
					
					if(i>=s1.size())
					{
						flag=1;
						break;
					}
					else
					{
						now_char = s1.at(i);
						if(!(now_char>='0'&&now_char<='9'))
						{
							s2_add(s2,' ');
							goto loc2;
						}
					}
				}
				
				if(flag == 1)
				{
					goto loc1;
				}
				
			}
			
			
			
			else
			{
				loc2:
				switch(now_char)
				{
				case '(':   //直接入栈 
					St.push(ele(now_char));    //入栈后，优先级设置为最低 
					break;
				case ')':	//栈内运算符依次出栈，直至遇见'('
					popped_ele = St.top();
					while(popped_ele.value!='(') 
					{	
						s2_add(s2,popped_ele.value);
						St.pop();
						popped_ele = St.top();
					} 
					//'('出栈！
					St.pop();
					
					break;
					
				default:   //新的符号为加减乘除 
					
					
					new_ele = ele(now_char);
					if(!St.empty())
					{
						top_ele = St.top();
					}
					while(!St.empty()&&new_ele.priority_level<=top_ele.priority_level)
					{
						//输出 
						s2_add(s2,top_ele.value);
						//栈顶元素出栈 
						St.pop();
						
						//查看下一个栈顶元素 
						if(!St.empty())
						{
						top_ele = St.top();
						}
						
						else
						{
							break;
						}
									
					}
					
					//此时栈空或者栈顶元素优先级小于新元素，对新元素压栈
					
					St.push(new_ele); 
					
					
					
	
				
						
				}
			}
			
		}
		
		//全部遍历完，栈内元素依次出栈
		while(!St.empty())
		{
			top_ele = St.top();
			s2_add(s2,top_ele.value);
			St.pop();
		} 
		cout<<s2<<endl;
	
	}
	 	return 0;
}

