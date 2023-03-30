#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

typedef int elementype;

struct BTNode
{
	elementype data;
	int height;	
	BTNode* lchild;
	BTNode* rchild;
};

typedef BTNode* BinTree;

class AVL
{
	public:
		AVL():T(nullptr)
		{
			
		}
		~AVL()
		{
			RecurrentDelete(T);
		}
		BTNode* GetRoot()
		{
			return T;
		}
		BTNode* InsertEle(BinTree T, elementype x)
		{
			BTNode* ret = T;
			if(this->T==nullptr)      //空树需另外处理 
			{
				this->T = new BTNode{x, 1, nullptr, nullptr};
				ret = this->T;
			}
			
			else
			{
				if(T)
				{
					if(x < T->data)
					{
						T->lchild = InsertEle(T->lchild, x);
					}
					else
					{
						T->rchild = InsertEle(T->rchild, x);
					}
					
					//更新高度 
					T->height = max(height(T->lchild), height(T->rchild))+1;	
				}
				
				else
				{
					T = new BTNode{x, 1, nullptr, nullptr};
					ret = T;
				}
			}
			
			
			
			//如果失衡，则调整以T为根节点的二叉树 
			ret = AdjustTheTree(T);
			
			return ret;
		}

		BTNode* DeleteEle(BinTree T, elementype x)
		{
			BTNode* ret = T;
			if(T)
			{
				if(x < T->data)
				{
					T->lchild = DeleteEle(T->lchild, x);
					
					//返回自身 
				}
				else if (x > T->data)
				{
					T->rchild = DeleteEle(T->rchild, x);      
					
					//返回自身 
				}
				else                             //T结点的值等于x（找到了该结点） 
				{
					if(T->lchild && T->rchild)   //有左右两个孩子 
					{
						BinTree max_T = T->lchild;    //寻找左子树中的最大元素
						while(max_T->rchild)
						{
							max_T = max_T->rchild;	
						}
						swap(max_T->data, T->data);   //交换T和max_T两个节点的值 
						
						T->lchild = DeleteEle(T->lchild,x);  //递归删除节点为x的值，此时节点为x的那个结点一定是单孩子或者无孩子 
					}                                 //返回自身 
					
					else				//只有一个孩子或者没有孩子 
					{
						
						if(T->lchild)   //只有左孩子 
						{
							ret = T->lchild;
						}
						else            //只有右孩子或者没有孩子（nullptr） 
						{
							ret = T->rchild;
						}
						
						if(T == this->T)
						{
							this->T = nullptr;
						}
						
						delete T; 
						return ret;    //删除本节点后，立即退出 
					}
				}
				
				
				
				
				
				
			}
			else
			{
				cout<<"删除失败\n"<<endl;
			}
			
			//更新高度 
			T->height = max(height(T->lchild), height(T->rchild))+1;
			
			//如果失衡，则调整以T为根节点的二叉树 
			ret = AdjustTheTree(T);
			
			return ret;
		}
		
		BTNode* FindEle(BTNode* T, elementype x)
		{
			BTNode* ret;
			if(T)
			{
				if(x < T->data)
				{
					ret = FindEle(T->lchild, x);		
				}
				else if (x > T->data)
				{
					ret = FindEle(T->rchild, x);	
				}
				else
				{
					ret = T;
				}
				
			}
			else
			{
				cout<<"查找失败\n";
				ret = nullptr;
			}
			return ret;	
		}
		
		void show_broad()
		{
			queue<BinTree> qu;
			if(T)
			qu.push(T);
			
			while(!qu.empty())
			{
				BinTree now_T = qu.front();
				qu.pop();
				
				if(now_T)
				cout<<now_T->data<<":"<<BalanceFactor(now_T)<<":"<<height(now_T)<<"      ";
				
				if(now_T->lchild)qu.push(now_T->lchild);
				if(now_T->rchild)qu.push(now_T->rchild);
			}
			cout<<"\n";
		}
		
		void PreOrdershow(BinTree T)
		{
			if(T)
			{
				cout<<T->data<<" ";	
				PreOrdershow(T->lchild);
				PreOrdershow(T->rchild);
			}
			
		}
		void show_deep()
		{
				
		}		
	private:
		BinTree T;
		BinTree AdjustTheTree(BinTree T)
		{
			BinTree ret;
			int balanceFactor = BalanceFactor(T);
				
			if(balanceFactor == 2)//左子树插入元素导致失衡
			{
				//LR情况 
				if (BalanceFactor(T->lchild) == -1)
				{
					//先左旋再右旋
					
					//为了可读性 
					BTNode* A = T; 
					BTNode* B = T->lchild;
					BTNode* C = B->rchild;
					
					A->lchild = RotateLeft(B);
					RotateRight(A);
					
					ret = C;
				}
				
				//LL情况 
				else //(BalanceFactor(T->lchild) == 1)或者删除情况 
				{
					ret = RotateRight(T);
				}	
			}
			else if (balanceFactor == -2)//右子树插入元素导致失衡 
			{
				//RL情况  
				if(BalanceFactor(T->rchild) == 1)
				{
					//先右旋再左旋
					
					//为了可读性 
					BTNode* A = T; 
					BTNode* B = T->rchild;
					BTNode* C = B->lchild;
					
					A->rchild = RotateRight(B);
					RotateLeft(A);
					
					ret = C;
				}	
				//RR情况 
				else     //(BalanceFactor(T->rchild) == -1)  或者删除情况 
				{
					ret = RotateLeft(T);
				}
				
				
				 
				 
			}
			else  //插入后是平衡的 
			{
				ret = T;	
			}
			
			
			if(T==this->T)   //如果最小失衡树恰好是以根节点为根的树，则需要将根指针进行修改 
			{
				this->T = ret;
			}
			
			
			return ret;
			
		}
		
		int height(BinTree T)
		{
			int ret; 
			if(T==nullptr)
			{
				ret = 0; 
			}
			else
			{
				ret = T->height;
			}
			return ret;
		}
		int BalanceFactor(BinTree T)
		{
			int ret;
			if(T==nullptr)
			{
				ret = 0;    //其实没有意义 
			}
			else
			{
				ret = height(T->lchild) - height(T->rchild);
			}
			return ret;
		}
		void RecurrentDelete(BinTree T)
		{
			if(T)
			{
				RecurrentDelete(T->lchild);
				RecurrentDelete(T->rchild);
				delete T;	
			}
		}
		BTNode* RotateLeft(BinTree A)
		{
			BTNode* B = A->rchild;
			A->rchild = B->lchild;
			B->lchild = A;
			
			//更新高度 
			A->height = max(height(A->lchild), height(A->rchild))+1;
			B->height = max(height(B->lchild), height(B->rchild))+1;
			return B;   //将左旋后的树的根节点返回出去。 
		}
		
		BTNode* RotateRight(BinTree A)
		{
			BTNode* B = A->lchild;
			A->lchild = B->rchild;
			B->rchild = A;
			
			//更新高度 
			A->height = max(height(A->lchild), height(A->rchild))+1;
			B->height = max(height(B->lchild), height(B->rchild))+1;
			return B;
		}
	
};
int main(int argc,char* args[])
{
	AVL avl;
	vector<int> ser = {30,40,35,28,33,37,42};
	
	for(auto i = ser.begin();i!=ser.end();i++)
	{
		avl.InsertEle(avl.GetRoot(),*i);
	}
	
	avl.show_broad();
	avl.PreOrdershow(avl.GetRoot());
	cout<<"\n";
	
	avl.DeleteEle(avl.GetRoot(),40);
	avl.show_broad();
	avl.PreOrdershow(avl.GetRoot());
	cout<<"\n";
	
	avl.DeleteEle(avl.GetRoot(),37);
	avl.show_broad();
	avl.PreOrdershow(avl.GetRoot());
	cout<<"\n";
	
	avl.DeleteEle(avl.GetRoot(),42);
	avl.show_broad();
	avl.PreOrdershow(avl.GetRoot());
	cout<<"\n";
	

 	return 0;
}

