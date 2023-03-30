#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <typeinfo>
using namespace std;
struct node
{
	int weight;
	const char* name;
	node *lchild, *rchild;
	node(int weight, const char* name):weight(weight),name(name),lchild(nullptr),rchild(nullptr)
	{
		
	}
	bool operator == (int x)
	{
		if(weight == x)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator < (const node& x)
	{
		if(weight < x.weight)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	node operator+(const node& x)
	{
		const char* c = "?";
		int d = weight + x.weight;
		node n3 = {d,c};
		return n3;
	}
	
	friend ostream& operator << (ostream& o, const node& nd)
	{
		o<<nd.name<<":"<<nd.weight;
	}
};




void visit(node* T)
{
	cout<<T->name<<":"<<T->weight<<endl;
}

//三种二叉树的递归遍历 
void InOrderTraversal(node* T)
{
	if(T)
	{
		InOrderTraversal(T->lchild);
		visit(T);
		InOrderTraversal(T->rchild);
	}
	
}

node* Build_huffmanTree_x(vector<node>& v1)
{
	node* ret = nullptr;
	node* n3 = nullptr;
	if(v1.size()==1)
	{
		n3 = new node((*(v1.begin())).weight,(*(v1.begin())).name);
		n3->lchild = v1.begin()->lchild;
		n3->rchild = v1.begin()->rchild;
		ret = n3;
		
		v1.erase(v1.begin());
	}
	if(v1.size()>1)
	{
		auto min_it = min_element(v1.begin(),v1.end());
		node* n1 = new node(*min_it);
		v1.erase(min_it);
	
		min_it = min_element(v1.begin(),v1.end());
		node* n2 = new node(*min_it);
		v1.erase(min_it);
		
		int weight = n1->weight+n2->weight;
		cout<<n1->weight<<"+"<<n2->weight<<endl;
		char* name = new char[10];
		itoa(weight, name, 10);
		
		n3 = new node(weight, name);
		n3->lchild = n1;
		n3->rchild = n2;
		
		v1.push_back(*n3);
		
		ret = Build_huffmanTree_x(v1);
		
		
	}
	return ret;
}

node* Build_huffmanTree(vector<node> v1)
{
	node* n3 = nullptr;
	if(v1.size()==1)
	{
		n3 = new node((*(v1.begin())).weight,(*(v1.begin())).name);
	}
	while(v1.size()>1)
	{
		auto min_it = min_element(v1.begin(),v1.end());
		node* n1 = new node(*min_it);
		v1.erase(min_it);
		
		min_it = min_element(v1.begin(),v1.end());
		node* n2 = new node(*min_it);
		v1.erase(min_it);
		
		//构建双亲节点，并且连接两个结点 
		
		int weight = n1->weight+n2->weight;
		cout<<n1->weight<<"+"<<n2->weight<<endl;
		char* name = new char[10];
		itoa(weight, name, 10);
		
		n3 = new node(weight, name);
		n3->lchild = n1;
		n3->rchild = n2;
		
		//树的根节点重新进入集合 
		v1.push_back(*n3);	
		 
	}
	//出循环时，所得到的n3就是根节点 
	return n3;
}


int main(int argc,char* args[])
{
	vector<node> v1={{1,"a"},{2,"c"},{2,"e"},{3,"b"},{7,"d"}};
//	auto it = min_element(v1.begin(),v1.end());
//	node* p =it;
//	cout<<*p<<endl;
//	v1.erase(it);
//	cout<<*p<<endl;
//	cout<<"-----------------------------------------------------"<<endl;
//	
//	for(auto i = v1.cbegin();i!=v1.cend();i++)
//	{
//		cout<<*i<<endl;
//	}
//	
//	cout<<"--------"<<endl;
	
	node* n3 = Build_huffmanTree_x(v1);
	
	cout<<"--------"<<endl;
	for(auto i = v1.cbegin();i!=v1.cend();i++)
	{
		cout<<*i<<endl;
	}
	cout<<"--------"<<endl;
////	InOrderTraversal


	InOrderTraversal(n3);
		
//	v1.erase(v1.rbegin());
	

//	v1.erase(v1.rbegin().base());
	

	
//	cout<<"tiaoshi1:"<<*i<<endl;
//	i--;
//	cout<<"tiaoshi1:"<<*i<<endl;
	

	
		
	
 	return 0;
}

