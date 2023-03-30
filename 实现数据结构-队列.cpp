#include <iostream>
using namespace std;
//队头指针指向队头元素所在位置，队尾指针指向队尾元素的下一个位置（即将插入的位置) 
//循环队列 
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
		cout<<"队列的值:";
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

