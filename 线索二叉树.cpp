#include <iostream>
using namespace std;

typedef struct BTnode{
	char data;
	BTnode *lchild, *rchild;	//???
	int ltag=0,rtag=0;
} *BinTree;

//������㣬�����ĸ��ڵ�ָ���Լ� ��flagΪ0�����޸��ڵ㣬Ϊ1�����Ǹ��ڵ�����ӣ�Ϊ2�������Һ��� 
BTnode* createNode(char x, int flag , BTnode* FT = nullptr)
{
	
	BTnode* T = new BTnode;
	T->data = x;
	T->lchild = T->rchild = nullptr;
	T->ltag = T->rtag = 0;
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
	T = createNode('A', 0, nullptr);	
	BinTree temp = createNode('B', 1, T);
	createNode('D', 1, temp);
	temp = createNode('F', 2, temp);
	createNode('E',1,temp);
	temp = createNode('C', 2, T);
	BinTree temp1 = createNode('G',1,temp);
	createNode('H',2,temp1);	
	createNode('I', 2, temp);	
} 

//��������������� 
visit(BinTree T, BTnode*& pre)
{
	cout<<"���ڶԽڵ�"<<T->data<<"����������������"<<endl;
	if(pre&&!pre->rchild)
	{
		pre->rtag = 1;
		pre->rchild = T;
	}
	if(!T->lchild)
	{
		T->ltag = 1;
		T->lchild = pre;
	}
	pre = T;
}


//���ֶ������ĵݹ���� 
void InOrderTraversal(BinTree T, BTnode*& pre)
{
	if(T)
	{
		InOrderTraversal(T->lchild,pre);
		visit(T,pre);
		InOrderTraversal(T->rchild,pre);
	}
	
}

void PreOrderTraversal(BinTree T, BTnode*& pre)
{
	if(T)
	{ 
		cout<<"tiaoshi:"<<T->data<<endl;
		visit(T,pre);
		if(T->ltag==0)
		{
			PreOrderTraversal(T->lchild,pre);
		}
//		PreOrderTraversal(T->lchild,pre);
		if(T->rtag==0)
		{
			PreOrderTraversal(T->rchild,pre);
		}
		
				
	}
	
}

void PostOrderTraversal(BinTree T, BTnode*& pre)
{
	if(T)
	{
		PostOrderTraversal(T->lchild,pre);
		PostOrderTraversal(T->rchild,pre);
		visit(T,pre);		
	}
	
}

void Threading(BinTree T)
{
	BTnode* pre=nullptr;	
	PreOrderTraversal(T, pre);
	//β�������� 
	if(pre->rchild = nullptr)
	{
		pre->rtag = 1;	
	}	
} 

int main(int argc,char* args[])
{
	
	BinTree rt;
	BuildTree(rt);
	Threading(rt);
 	return 0;
}

