#include <iostream>
#include <cmath>
using namespace std;


//以数组顺序结构实现并查集，数组的下标等于对应元素的数据的值
class UFset
{
	private:
		int size;
		int* a;
	public:
		UFset(int size):size(size),a(new int[size])
		{
			for(int i = 0;i<size;i++)
			{
				a[i] = -1;    //初始的时候，每个结点的父节点都是自己，因此小于0；每个集合所包含的结点的个数都是1，因此绝对值为1；综合起来，初始化为-1	
			}	
		}
		
	//寻找结点value的根节点 
	int find(int value)
	{
		
		if(a[value]>0)
		{
			//找本节点双亲结点的根节点，并赋值给本节点的双亲结点(实现了路径压缩)
			a[value] = find(a[value]);
			return a[value];
		}
		else
		{
			return value;	
		}
		
//		//不使用路径压缩的非递归算法 
//		int parent = a[value];
//		while(parent>0)
//		{
//			value = parent;
//			parent = a[value];
//		}
	
//		return value;
		
		
	}
	
	//判断结点x1和x2是否属于同一个集合
	bool judge_same(int x1, int x2)
	{
		int r1 = find(x1);
		int r2 = find(x2);
		if(r1 == r2)
		{
			return true;
		}
		else
		{
			return false;
		}	
	} 
	
	//合并结点x1和结点x2分别所在的集合 
	void Union_o(int x1,int x2)
	{
		int r1 = find(x1);
		int r2 = find(x2);
		
		if(r1!=r2)
		{	
			//按秩归并，包含两类：（1）按树高归并、（2）按结点数归并。两类算法均使得最后查找任一结点的时候，时间复杂度均为O(logn) 
			//此处使用按结点数归并 
			//根节点r的a[r]均为负数，绝对值代表了所包含的结点数，a[r1] a[r2]均为负数，所以更小的一方集合所包含的结点数更多 
			if(a[r1]<=a[r2])
			{
				a[r1] += a[r2];
				a[r2] = r1;
			}
			else
			{
				a[r2] += a[r1];
				a[r1] = r2;
			}
			
//			//按树高归并的算法
//			if(a[r1]<=a[r2])
//			{
//				if(a[r1]==a[r2])
//				{
//					a[r1]--;   //总树高加一 
//				}
//				a[r2] = r1;  //r2的双亲指针指向r1					
//			}
//			else
//			{
//				a[r1] = r2;
//			 } 
			
		}
	}
	void show()
	{
		for(int i = 0;i<size;i++)
		{
			cout<<"a["<<i<<"]="<<a[i]<<endl;
		}
	}
	
			
} ;





int main(int argc,char* args[])
{
	UFset uf(7);
	uf.Union_o(2,5);
	uf.Union_o(4,3);
	uf.Union_o(2,4);
	uf.Union_o(6,1);
	uf.Union_o(6,0);
//	uf.find(3);
	uf.show();
	
//	cout<<INT_MAX<<endl;
 	return 0;
}

