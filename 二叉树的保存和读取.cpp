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
		//������д�ļ�
		ofs.write((const char*)T,sizeof(*T)); 
//		ofs<<*T;	
	}
//	
}
visit_to_load(BinTree& T, ifstream& ifs)
{

	//�����ƶ��ļ�
	ifs.read((char*)T,sizeof(*T));
	
	
	//ÿ�����ĺ��ӵ�ַ������������һ�γ�������ʱ�ĵ�ַ������Ҫ���¿���һƬ��ַ 
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
	cout<<"��ʼʱ��"<<"\n";
//	op.write((char*)T,sizeof(*T));
	
	PreOrderTraversal(T);
	
	cout<<"��ʼ�浵\n";
	PreOrderTraversal_save(T,op);
	op.close();
	
	ifstream ip("abcjs.txt",ios::in|ios::binary);
	cout<<"��ʼ��ȡ\n";
	
	BinTree T2 = new BTnode;
//	ip.read((char*)T2,sizeof(*T2));
	PreOrderTraversal_load(T2,ip);
	
	cout<<"��ȡ���\n"<<T2->data<<endl;
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

