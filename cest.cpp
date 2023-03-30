#include <iostream>
using namespace std;


typedef struct BTnode{
	int data;
	BTnode *lchild, *rchild;	//???
} *BinTree;

class BST
{
	private:
		BinTree T;
	public:
		BinTree getRoot()
		{
			return T;
		}
		
};

BinTree insertEle_x(const int& x,BinTree& rt)
{
	;
}

int main(int argc,char* args[])
{
	BST T;
	insertEle_x(1,T.getRoot());
	
	for(int i=0;i<10;i++)
	{
		int a =1;
		cout<<a<<endl;
		a++;
	}
 	return 0;
}

