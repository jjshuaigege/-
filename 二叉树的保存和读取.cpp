#include <iostream>
#include <fstream>
using namespace std;
struct BTnode
{
	int data;
	BTnode* lchild;
	BTnode* rchild;
};

typedef BTnode* BinTree;

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


visit(BinTree T)
{
	cout<<T->data<<" ";
}
visit_to_save(BinTree T, ofstream& ofs)    
{
	if(T)
	{
		//二进制写文件
		ofs.write((const char*)T,sizeof(*T)); 
//		ofs<<*T;	
	}
//	
}
visit_to_load(BinTree& T, ifstream& ifs)
{

	//二进制读文件
	ifs.read((char*)T,sizeof(*T));
	
	
	//每个结点的孩子地址，不能沿用上一次程序运行时的地址，而需要重新开辟一片地址 
	if(T->lchild)   
	{
		BinTree temp_l = new BTnode;
		T->lchild = temp_l;
	}
	else
	{
		T->lchild = nullptr;
	}
	if(T->rchild)
	{
		BinTree temp_r = new BTnode;
		T->rchild = temp_r;
	}
	else
	{
		T->rchild = nullptr;
	}
	
	
}
PreOrderTraversal(BinTree T)
{
	if(T)
	{
		visit(T);
		PreOrderTraversal(T->lchild);
		PreOrderTraversal(T->rchild);
	}
}
PreOrderTraversal_save(BinTree T, ofstream& ofs)
{
	if(T)
	{
		visit_to_save(T, ofs);
		PreOrderTraversal_save(T->lchild, ofs);
		PreOrderTraversal_save(T->rchild, ofs);
	}
	
}

PreOrderTraversal_load(BinTree& T, ifstream& ifs)
{
	if(T)
	{
		visit_to_load(T, ifs);
		PreOrderTraversal_load(T->lchild, ifs);
		PreOrderTraversal_load(T->rchild, ifs);
	}
	
}

int main(int argc,char* args[])
{
	ofstream op("abcjs.txt",ios::out|ios::binary);

	BinTree T;
	BuildTree(T);
	cout<<"开始时："<<"\n";
//	op.write((char*)T,sizeof(*T));
	
	PreOrderTraversal(T);
	
	cout<<"开始存档\n";
	PreOrderTraversal_save(T,op);
	op.close();
	
	ifstream ip("abcjs.txt",ios::in|ios::binary);
	cout<<"开始读取\n";
	
	BinTree T2 = new BTnode;
//	ip.read((char*)T2,sizeof(*T2));
	PreOrderTraversal_load(T2,ip);
	
	cout<<"读取结果\n"<<T2->data<<endl;
	PreOrderTraversal(T2);
	
	int x = 685;
	cout.write((const char*)&x, sizeof(x));
	
	int xx;
	while(cin>>xx)
	{
		cout<<xx<<endl;
	}
 	return 0;
}

