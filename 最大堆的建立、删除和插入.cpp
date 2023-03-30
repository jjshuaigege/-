#include <iostream>
#include <algorithm>
using namespace std;
template<typename elementype>
class Heap
{
	public:
		int maxsize;
		int length;
		elementype *A; 
		
		//˽�к��������ܱ��ⲿ���� 
		void adjustHeap(int k)    //�����±�Ϊk��Ԫ��Ϊ���ڵ����������һ����Ҫǰ�᣺�ø��ڵ�����������Ѿ���һ������� 
		{
			elementype item = A[k];
			int parent = k;
			for(int child=2*k;child<length;child*=2)
			{
				if(A[child+1]&&A[child+1]>A[child])
				{
					child++;
				}
				if(item < A[child])
				{
					A[parent] = A[child];
				}
				else
				{
					break;
				}
			
				parent = child;
			}
			A[parent] = item;
			
		}
	public:
		Heap(int maxsize):maxsize(maxsize),A(new elementype[maxsize+1]),length(0){}
		
		bool isfull()
		{
			if(length == maxsize)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		
		bool isempty()
		{
			if(length == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		
		void buildHeap(elementype extern_A[], int extern_length)   //�����ⲿ���������飬����һ������� 
		{	
			length = extern_length;
			for(int i = 1;i<=extern_length;i++) 
			//�����һ����Ҷ�ӽڵ㿪ʼ�����ϵص����Ըý��Ϊ���ڵ������Ϊ�����
			//�������ĺô��ǣ�ÿ�η��ʵ�һ�����ʱ������������һ���Ѿ���һ��������ˡ� 
			
			{
				A[i] = extern_A[i];
			}
			
			for(int i = length/2;i>0;i--)
			{
				adjustHeap(i);
			}
			
		}
		

		bool deleteEle()   //�Ӷ���ɾ�����Ԫ�� 
		{
			if(isempty())
			{
				cout<<"�ѿգ�����ʧ��"<<endl;
				return false;
			}
			else
			{
				swap(A[1],A[length]);
				length--;
				adjustHeap(1);
				
				return true;
			}
			
		}
		

		bool insertEle(elementype ele)
		{
			if(isfull())
			{
				cout<<"����������ʧ��"<<endl;
				return false;
			}
			else
			{
				A[length+1] = ele;
				int child = length + 1;
				for(int parent = child/2; parent>0; parent /= 2)
				{
					if(ele>A[parent])
					{
						A[child] = A[parent];
					}
					else
					{
						break;
					}
					child = parent;
				}
				A[child] = ele;
				length++;
				return true;
			}
			
		}
		
		//������(��ı�ԭ���Ķ�)
		elementype* sort()
		{
			elementype *ret = new elementype[length];
			for(int i = 0;length>0;i++)
			{
				deleteEle();
				ret[i] = A[length+1];
			}
			
			return ret;
		 } 
		
		void show()
		{
			for(int i = 1;i<=length;i++)
			{
				cout<<A[i]<<" ";
			}
			cout<<endl;
		}
};
//template<typename elementype>
//void adjustHeap(elementype A[], int k, int length)
//{
//	elementype item = A[k];
//	int parent = k;
//	for(int child=2*k;child<length;child*=2)
//	{
//		if(A[child+1]&&A[child+1]>A[child])
//		{
//			child++;
//		}
//		if(item < A[child])
//		{
//			A[parent] = A[child];
//		}
//		else
//		{
//			break;
//		}
//	
//		parent = child;
//	}
//	A[parent] = item;
//	
//}
//
//template<typename elementype>
//void buildHeap(elementype A[],int length)
//{
//	for(int i = length/2;i>0;i--)
//	{
//		adjustHeap(A,i,length);
//	}
//	
//}
//
//template<typename elementype>
//void deleteEle(elementype A[],int length)
//{
//	swap(A[1],A[length]);
//	adjustHeap(A, 1, length-1);
//}
//
//template<typename elementype>
//void insertEle(elementype A[], int length, elementype ele)
//{
//	A[length+1] = ele;
//	int child = length + 1;
//	for(int parent = child/2; parent>0; parent /= 2)
//	{
//		if(ele>A[parent])
//		{
//			A[child] = A[parent];
//		}
//		else
//		{
//			break;
//		}
//		child = parent;
//	}
//	A[child] = ele;
//}

int main(int argc,char* args[])
{
	int a[] = {-9999,79,66,43,83,30,87,38,55,91,72,49,9};
//	buildHeap(a,12);
//	for(int i = 1;i<=12;i++)
//	{
//		cout<<a[i]<<" ";
//	}
//	
//	cout<<endl;
	Heap<int> hp(13);
	hp.buildHeap(a,12);
	hp.show();
	hp.insertEle(100);
	hp.show();
	hp.deleteEle();
	hp.show();
	
	int* b = hp.sort();
	for(int i = 0;i<12;i++)
	{
		cout<<b[i]<<"\t";
	}
	cout<<endl;
 	return 0;
}

