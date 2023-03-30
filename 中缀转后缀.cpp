#include <iostream>
#include <Cstring>
#include <stack>
using namespace std;


//��׺���ʽת��׺���ʽ ����׺���ʽ��2+9/3-5    ��׺���ʽ��2 9 3 / + 5 -
/*
����˼·��
����һ�������������ջ
����׺���ʽ�������ҽ��б��� 
1.��������������ֱ����� 
2.���������A����ջ��Ԫ��Ϊ�գ�����ջ����ջ��Ԫ��B��Ϊ�գ�������ջ�������B�����ȼ����Ƚ�
��1����A>=B���������A��ջ
��2����A<B, ��B��ջ��A������ջ������������ȼ��ıȽϣ���A<B���������ջ��Ԫ��B��ջ��
ֱ��A>=B����ջ�գ���A��ջ��
(3)����ȫ�������꣬��ջ��Ԫ�����γ�ջ������� 
**ע�⣡ ��������� '('����ض���ջ�� 
**�����������')'�������ν�ջ���������ջ��ֱ������'(' 
*/ 

//��¼�������������������ȼ� 
struct ele
{
	char value;
	int priority_level;
	
	//��ʼ�������Ҹ����ַ�ֵ�������ȼ� 
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
		o<<"ֵ��"<<x.value<<"\t"<<"���ȼ�:"<<x.priority_level;
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
		
		//��׺���ʽ���ַ��� 
		string s1;
		cin>>s1;
		
		//��׺���ʽ���ַ��� 
		string s2="";
		
		int i = 0; 
		loc1:
		for(;i<s1.size();i++)
		{
			now_char=s1.at(i);
			
			//���ڱȽ�ʵ������������ȼ� 
			int now_char_level = -1;
			
			
			
			//ֱ����� 
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
				case '(':   //ֱ����ջ 
					St.push(ele(now_char));    //��ջ�����ȼ�����Ϊ��� 
					break;
				case ')':	//ջ����������γ�ջ��ֱ������'('
					popped_ele = St.top();
					while(popped_ele.value!='(') 
					{	
						s2_add(s2,popped_ele.value);
						St.pop();
						popped_ele = St.top();
					} 
					//'('��ջ��
					St.pop();
					
					break;
					
				default:   //�µķ���Ϊ�Ӽ��˳� 
					
					
					new_ele = ele(now_char);
					if(!St.empty())
					{
						top_ele = St.top();
					}
					while(!St.empty()&&new_ele.priority_level<=top_ele.priority_level)
					{
						//��� 
						s2_add(s2,top_ele.value);
						//ջ��Ԫ�س�ջ 
						St.pop();
						
						//�鿴��һ��ջ��Ԫ�� 
						if(!St.empty())
						{
						top_ele = St.top();
						}
						
						else
						{
							break;
						}
									
					}
					
					//��ʱջ�ջ���ջ��Ԫ�����ȼ�С����Ԫ�أ�����Ԫ��ѹջ
					
					St.push(new_ele); 
					
					
					
	
				
						
				}
			}
			
		}
		
		//ȫ�������꣬ջ��Ԫ�����γ�ջ
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

