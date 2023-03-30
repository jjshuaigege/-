#include <iostream>
#include <exception>
using namespace std;

template<typename Elementype>
class MyStack
{
	private:
		int top;
		Elementype* data;
		int maxsize;
	public:
		MyStack(int maxsize):maxsize(maxsize)
		{
			data = new Elementype[maxsize];
			statckIniate();
		}
		
		statckIniate()
		{
			top = -1;
		}
		bool stackDelete()
		{
			delete[] data;
		}
		bool pop(Elementype& ret)
		{
			if(top<0)
			{
				cerr<<"Õ»¿Õ£¡²Ù×÷Ê§°Ü"<<endl;
				return false;	
			}	
			else
			{
				ret = data[top--];          
				return true;
			}
		}
		bool push(const Elementype& x)
		{
			if(top>=maxsize-1)
			{
				cerr<<"Õ»Âú£¡²Ù×÷Ê§°Ü"<<endl;
				return false;
			}
			else
			{
				data[++top] = x;
				return true;
			}
		}
		bool peek(Elementype& ret)
		{
			
			if(top<0)
			{

				cerr<<"Õ»¿Õ£¡²Ù×÷Ê§°Ü"<<endl;
				return false;
	
			}
			else
			{
				ret = data[top];
				return true;
			}
		}
		void show()
		{
			cout<<"Õ»ÖÐÔªËØÓÐ£º";
			for(int i =top;i>=0;i--)
			{
				
				cout<<data[i];
				cout<<" ";
			}
			cout<<endl;
		}
};
int main(int argc,char* args[])
{
	MyStack<double> s(10);
	double temp = -101.1;
	s.peek(temp);
	cout<<temp<<endl;
	s.push(2.5);
	s.peek(temp);
	cout<<temp<<endl;
	s.push(3.14);
	s.peek(temp);
	cout<<temp<<endl;
	s.show();
	s.pop(temp);
	cout<<temp<<endl;
	s.show();
	
	s.pop(temp);
	s.pop(temp);s.pop(temp);s.pop(temp);s.pop(temp);s.pop(temp);s.pop(temp);s.pop(temp);s.pop(temp);
	s.show();

 	return 0;
}

