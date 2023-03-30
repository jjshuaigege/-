#include <iostream>
#include <queue>
using namespace std;



typedef struct BTnode{
	char data;
	BTnode *lchild, *rchild;	//???
} *BinTree;

queue<BinTree> qu;

//创建结点，让它的父节点指向自己 ，flag为0代表无父节点，为1代表是父节点的左孩子，为2代表是右孩子 
BTnode* createNode(char x, int flag , BTnode* FT = nullptr)
{
	
	BTnode* T = new BTnode;
	T->data = x;
	T->lchild = T->rchild = nullptr;
	if (FT)
	{
		if(flag == 1)
		{
			FT->lchild = T;	
		}
		else if (flag == 2)
		{
		
			FT->rchild = T;
		}
	
	}
	
	return T;
} 
//创建一棵树，用于测试
void BuildTree(BinTree& T)
{
	T = createNode('A', 0);	
	BinTree temp = createNode('B', 1, T);
	createNode('D', 1, temp);
	temp = createNode('F', 2, temp);
	createNode('E',1,temp);
	temp = createNode('C', 2, T);
	BinTree temp1 = createNode('G',1,temp);
	createNode('H',2,temp1);	
	createNode('I', 2, temp);	
} 


void visit(BinTree T)
{
	cout<<T->data<<" ";
}

void LevelOrderTraversal(BinTree T)
{
	qu.push(T);
	BinTree now_T;
	while(!qu.empty())
	{
		//队头一个结点出队 
		now_T = qu.front();
		qu.pop();
		
		//出队后就进行visit操作 
		visit(now_T);
		
		//该结点的左右孩子入队（如果存在的话）
		if(now_T->lchild)
		{
			qu.push(now_T->lchild);
		}
		if(now_T->rchild)
		{
			qu.push(now_T->rchild);	
		} qu.
			
	}
}

int main(int argc,char* args[])
{
	BinTree T;
	BuildTree(T);
	LevelOrderTraversal(T);
 	return 0;
}

