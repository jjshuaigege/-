#include <iostream>
using namespace std;
//��ͷָ��ָ���ͷԪ������λ�ã���βָ��ָ���βԪ�ص���һ��λ�ã����������λ��) 
//ѭ������ 
class MyQueue
{
	private:
		int maxsize;
		int* data;
		int front,rear;
	public:
 	MyQueue(int maxsize):maxsize(maxsize),data(new int[maxsize])
	{
		
	}
	~MyQueue()
	{
		delete[] data;
	}
	bool enqueue(int x)
	{
		if((rear+1)%maxsize==front)
		{
			return false;
		}
		else
		{
			data[rear] = x;
			rear = (rear+1)%maxsize;
			return true;
		}
		
	}
	bool dequeue(int& x)
	{
		if(front==rear)
		{
			return false;
		}
		else
		{
			x = data[front];
			front = (front+1) % maxsize;
			return true;
		}
	}
	void show()
	{
		cout<<"���е�ֵ:";
		for(int i = front;i!=rear;i=(i+1)%maxsize)
		{
			cout<<data[i]<<" ";
		}
		cout<<endl;
	}
};
int main(int argc,char* args[])
{
	MyQueue q(8);
	
	
	int temp;
	
	q.enqueue(64);
	q.enqueue(64);
	q.enqueue(64);
	q.enqueue(64);
	q.enqueue(68);
	q.enqueue(64);
	q.enqueue(64);
	q.enqueue(77);
	q.enqueue(64);
	
	q.show();
	
	q.dequeue(temp);
	q.dequeue(temp);
	
	q.show();
	return 0;
}

