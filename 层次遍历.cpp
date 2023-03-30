#include <iostream>
#include <queue>
using namespace std;



typedef struct BTnode{
	char data;
	BTnode *lchild, *rchild;	//???
} *BinTree;

queue<BinTree> qu;

//������㣬�����ĸ��ڵ�ָ���Լ� ��flagΪ0�����޸��ڵ㣬Ϊ1�����Ǹ��ڵ�����ӣ�Ϊ2�������Һ��� 
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
//����һ���������ڲ���
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
		//��ͷһ�������� 
		now_T = qu.front();
		qu.pop();
		
		//���Ӻ�ͽ���visit���� 
		visit(now_T);
		
		//�ý������Һ�����ӣ�������ڵĻ���
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

