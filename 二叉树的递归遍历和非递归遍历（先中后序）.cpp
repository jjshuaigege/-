#include <iostream>
#include <stack>
using namespace std;



typedef struct BTnode{
	char data;
	BTnode *lchild, *rchild;	//???
} *BinTree;

stack<BinTree> st;

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


void visit(BinTree T)
{
	cout<<T->data<<" ";
}

//三种二叉树的递归遍历 
void InOrderTraversal(BinTree T)
{
	if(T)
	{
		InOrderTraversal(T->lchild);
		visit(T);
		InOrderTraversal(T->rchild);
	}
	
}

void PreOrderTraversal(BinTree T)
{
	if(T)
	{
		visit(T);
		PreOrderTraversal(T->lchild);
		PreOrderTraversal(T->rchild);		
	}
	
}

void PostOrderTraversal(BinTree T)
{
	if(T)
	{
		PostOrderTraversal(T->lchild);
		PostOrderTraversal(T->rchild);
		visit(T);		
	}
	
}

//三种二叉树的非递归遍历(容易理解版本)  准备一个状态数组，每个结点有0（可省略）、1、2三种状态。
//分别代表未入栈（可省略），在栈中第一次被访问，在栈中第二次被访问 




//三种二叉树的非递归遍历(精简版)

void InOrderTraversal_x(BinTree T)
{
	BinTree now_T = T;
	while(now_T || !st.empty())
	{
		if(now_T)
		{
			st.push(now_T);
			now_T = now_T->lchild;
		}
		else //当前节点为空，应该将栈顶节点出栈，因为栈顶节点出栈的时候，它的左子树已经被访问过，所以下一步只需访问它的右子树（无论右孩子是否存在） 
		{
			
			now_T = st.top();
			st.pop();
			//刚出栈时，此结点的左子树刚被访问完，因此可以立即访问该结点 
			visit(now_T);			
			//访问右子树 
			now_T = now_T->rchild;
		}
	}
	
}

//与中序同理，只需更改visit函数的位置即可 
void PreOrderTraversal_x(BinTree T)
{
	BinTree now_T = T;
	
	while(now_T || !st.empty())
	{
		if(now_T)
		{
			//即将入栈之前，访问该结点，这样就能做到对本结点的访问正好在左子树之前的一瞬间被访问 
			visit(now_T);
			st.push(now_T);
			now_T = now_T->lchild;
		}
		else //当前节点为空，应该将栈顶节点出栈，因为栈顶节点出栈的一瞬间，它的左子树刚被访问完，所以下一步只需访问它的右子树（无论右孩子是否存在） 
		{
			now_T = st.top();
			st.pop();
			now_T = now_T->rchild;
		}
	}
	
}


//非递归算法，后序遍历与前序与中序存在较大不同，但事实上它的访问步骤才是最接近递归算法，由于要保证在访问某个节点之前，它的左子树和右子树均被访问，
//也就是说每个结点都要完整的遇到3次（其实前、中、后递归算法也能保证每个结点被遇见3次），而前序与中序非递归算法只保证前两次的遇见（入栈时遇见1次，出栈时遇见1次），自动忽略了第3次的遇见
//因此对于非递归后序算法，在访问完某个节点的左子树之后，仍要将该结点保存栈中，等访问完它的右子树之后，再对该结点进行访问，以进行visit函数的操作。 
 
//为了保证对一个结点访问3次（也即对栈中元素访问两次），要区分对栈中的元素是第几次访问，分为第一次访问和第二次访问 

//(a)常规的思路是对每个结点都有一个相应的状态位，初值为0，在第一次从栈中访问结点时，由于状态位为0；故不立即出栈，
//而是将状态位置为1，在第二次访问，由于状态位是1，所以将该结点出栈




//(b)但是还存在另一种取巧的的办法 ：之所以要对每个结点访问3次，是为了当对一个结点执行visit操作时，它的左子树和右子树的所有结点都被visit过，
//第一次访问栈中的某个结点时，该结点的左子树刚刚被访问完，而右子树则尚未被访问，即右孩子没被访问
//第二次访问栈中的某个结点时
//(1)如果该结点存在右孩子，则该结点的右子树刚刚被访问完，那么根据后序遍历的机制可知，最近一次被访问的一定是它的右孩子 
//(2如果不存在右孩子，则直接对该结点进行visit操作，并出栈（可理解为瞬间对这个结点访问两次)

//******* 
//因此简便的做法如下： 
//准备另外一个指针pre，该指针指向上一次经visit函数处理过的结点 
//如果每次访问栈顶元素的时候，为了判断该元素是第一次还是第二次被访问，做法如下：

//如果不存在右孩子，或者存在右孩子并且pre与rchild指针相等（||逻辑运算符就能实现），直接将该元素出栈 ，进行visit操作 ,pre指向该元素，T指向空，以便继续访问栈顶元素。 
//如果pre和rchild指针指向不一致，说明只是第一次访问栈顶的该结点，继续将该元素留在栈中，然后访问它的右孩子 
 
void PostOrderTraversal_x(BinTree T)
{
	BinTree now_T = T, pre_T = nullptr;
	
	while(now_T||!st.empty())
	{
		if(now_T)
		{
			st.push(now_T);
			now_T = now_T -> lchild;	
		}
		else
		{
			now_T = st.top(); // 此时now_T结点的左子树已经被访问完毕 
			
			if( !now_T->rchild || pre_T == now_T->rchild) //不存在右子树，或者右子树也已被访问完毕，则直接出栈并处理 
			{
				st.pop();
				visit(now_T);
				pre_T = now_T;
				now_T = nullptr;
			}
			else	//存在右孩子并且右子树没有被访问过 ，说明是第一次在栈中被访问 
			{
				//访问右子树 
				now_T = now_T -> rchild;
			}
				
		}		
	}
	
}



int main(int argc,char* args[])
{
	BinTree T;
	BuildTree(T);
	cout<<T->data<<endl;
	cout<<T->lchild<<endl;
	cout<<T->rchild<<endl;
	
	//先序遍历 
	PreOrderTraversal(T);
	cout<<endl;
	

	PreOrderTraversal_x(T);
	cout<<endl;
	
	//中序遍历 
	InOrderTraversal(T);	
	cout<<endl;
	
	InOrderTraversal_x(T);	
	cout<<endl;
	
	//后序遍历 
	PostOrderTraversal(T);
	cout<<endl;
	
	PostOrderTraversal_x(T);
	cout<<endl;
	
	
	cout<<"ceshi:"<<T->lchild->lchild->data;
 	return 0;
}

