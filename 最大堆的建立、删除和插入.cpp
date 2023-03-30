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
		
		//私有函数，不能被外部调用 
		void adjustHeap(int k)    //调整下标为k的元素为根节点的树，这有一个重要前提：该根节点的左右子树已经是一个大根堆 
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
		
		void buildHeap(elementype extern_A[], int extern_length)   //根据外部的乱序数组，创建一个大根堆 
		{	
			length = extern_length;
			for(int i = 1;i<=extern_length;i++) 
			//从最后一个非叶子节点开始，不断地调整以该结点为根节点的树变为大根堆
			//这样做的好处是，每次访问到一个结点时，其左右子树一定已经是一个大根堆了。 
			
			{
				A[i] = extern_A[i];
			}
			
			for(int i = length/2;i>0;i--)
			{
				adjustHeap(i);
			}
			
		}
		

		bool deleteEle()   //从顶部删除最大元素 
		{
			if(isempty())
			{
				cout<<"堆空，操作失败"<<endl;
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
				cout<<"堆满，操作失败"<<endl;
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
		
		//堆排序(会改变原来的堆)
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

