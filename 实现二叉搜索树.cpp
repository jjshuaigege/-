#include <iostream>
#include <algorithm>
#include <vector>
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
		BST():T(nullptr)
		{
			
		}
		const BinTree& getRoot()
		{
			return T;
		}
		
		//插入的递归实现
		BinTree insertEle_x(const int& x,BinTree rt)
		{
			//实际插入过程 
			if(rt==nullptr)
			{
				rt = new BTnode;
				rt->data = x;
				rt->lchild = rt->rchild = nullptr;
				if (!T)   // 若插入前为空树，则应修改根节点指针的值 
				{
					T = rt;
				}
			}
			else if(x<=rt->data)
			{
				rt->lchild=insertEle_x(x,rt->lchild);
			}
			else
			{
				rt->rchild=insertEle_x(x,rt->rchild);	
			}
			return rt;	
		} 
		
		
		//插入一个元素
		bool insertEle(const int& x)
		{
			BinTree now_T = new BTnode;
			now_T->data = x;
			now_T->lchild=now_T->rchild=nullptr;
			
			BinTree FT=T;
			
			//如果当前的树不是空树 
			if(T)
			{
				while(true)
				{
					if(x<=FT->data)
					{
						if(FT->lchild)
						{
							FT = FT->lchild;
							continue;
						}
						else
						{
							FT->lchild = now_T;
							break;
						}
					}
					else
					{
						if(FT->rchild)
						{
							FT = FT->rchild;
							continue;
						}
						else
						{
							FT->rchild = now_T;
							break;
						}
					}
					
				}
				
			}
			else // 是空树 
			{
				T = now_T;
			}
		}
		
		//查找的递归 
		BinTree findEle_x(const int& x, const BinTree& rt)
		{
			if(rt==T)
			cout<<"开始递归查找"<<endl;
			if(!rt)
			{
				cout<<"查找失败"<<endl;
				cout<<endl;
				return nullptr;
			}
			cout<<"当前节点的值为："<<rt->data<<endl;
			if(x<rt->data)
			{
				cout<<"左走。。。"<<endl;
				return findEle_x(x,rt->lchild);
			}
			else if(x>rt->data)
			{
				cout<<"右走。。。"<<endl;  
				return findEle_x(x,rt->rchild);
			}
			else
			{
				cout<<"已找到！"<<endl;
				cout<<endl;
				return rt;
			}
			
		}
		
		
		//供内部使用，若找到则返回指向元素的指针，否则返回nullptr则代表没找到, FT和flag是为找到该结点的父节点，以及左右连接关系 
		BinTree findEle(const int& x, BinTree& FT, int& flag)
		{
			BinTree now_T = T;
			while(now_T)
			{
//				cout<<"now is "<<now_T->data;
				if(x < now_T->data)
				{
					FT=now_T;
//					cout<<",going to left";
					now_T = now_T->lchild;
					flag = 0;
				}
				else if(x > now_T->data)
				{
					FT=now_T;
//					cout<<",going to right";
					now_T = now_T->rchild;
					flag = 1;
				}
				else
				{
//					cout<<"found "<<x<<endl;
					break;
				}
			}
			return now_T;
		}
		
		//重载函数，供外部使用
		BinTree findEle(const int& x)
		{
			cout<<"beginning search"<<endl;
			BinTree now_T = T;
			while(now_T)
			{
				cout<<"now is "<<now_T->data<<endl;
				if(x<now_T->data)
				{
					cout<<",going to left\n";
					now_T = now_T->lchild;
				}
				else if(x>now_T->data)
				{
					cout<<",going to right\n";
					now_T = now_T->rchild;
				}
				else
				{
					cout<<"found "<<x<<endl;
					break;
				}
			}
			cout<<endl;
			return now_T;
		} 
		
		
		void cat_FAS(BTnode* FT, BTnode* ST,int flag)
		{
			if(flag==0)
			{
				FT->lchild = ST;
			}
			else if(flag==1)
			{
				FT->rchild = ST;
			}
		}
		
		//查找结点的递归实现方法
	
		
		//删除结点的递归实现方法，**抛弃了复杂的记录前驱和孩子的左右关系，简洁许多** 
		//删除以rt为根节点的数中值为x的结点，如果做的操作包含删除则返回孩子结点，不包含则返回本身 
		BTnode* deleteEle_x(const int& x, BinTree rt)
		{
			BTnode* max_T;
			if(rt==nullptr)
			{
				cout<<"未找到被删除结点"<<endl; 
			}
			else if (x==rt->data)
			{
				//被删节点有双孩子
				if(rt->lchild&&rt->rchild)
				{
					//先进行值的交换 
					max_T=rt->lchild;
					while(max_T->rchild)
					{
						max_T=max_T->rchild;
					}
					swap(rt->data,max_T->data);
					
					
					rt->lchild = deleteEle_x(x,rt->lchild);	  //最大值节点一定没有右孩子 ，且此时该结点的值已经被赋值为x, 因此会转入单孩子删除（真正的删除）。 
				} 
				//rt单孩子或无孩子
				else
				{
					BinTree temp = rt;
					if(rt->rchild)
					{
						rt = rt->rchild;			
					}
					else
					{
						rt = rt->lchild;
					}
					if(temp==T) //被删节点为根节点，需要将对象中的根节点指针置空 
					{
						T = nullptr;
					}
					delete temp;
				}	
			}
			else if(x<rt->data)
			{
				rt->lchild = deleteEle_x(x,rt->lchild);
			}
			else if(x>rt->data)
			{
				rt->rchild = deleteEle_x(x,rt->rchild);
			}
			return rt;
		}
		
		// 需要找到等于该值的结点，以及该结点的父节点 
		bool deleteEle(const int& x)
		{
			BinTree FT = nullptr;   //FT记录被删节点的父亲 
			int flag = -1;//-1，0,1分别代表T没有双亲结点，T是FT的左孩子，T是FT的右孩子 
			BinTree now_T = findEle(x,FT,flag);
			cout<<"调试"<<FT->data<<endl;
			if(now_T)
			{
				//定义删除单孩子或无孩子结点T的lambda函数表达式，返回指向它的孩子的指针，返回空指针则代表无孩子 
				auto delete_solo_son_ele = [=](BTnode* T)-> BinTree
				{
					//有两个孩子则不允许进行操作 
					if(T->lchild && T->rchild)
					{
						return nullptr;	
					}
					else
					{
						if(T -> lchild)
						{
							return T->lchild;
						}
						else if(T -> rchild)
						{
							return T->rchild;
						}
						else  //无孩子 
						{
							return nullptr;
						}
						//回收该结点的空间
						delete T; 
					}	
				};
				
				//被删节点只有一个孩子，或者没有孩子 
				if(!(now_T->lchild && now_T->rchild))
				{
					BinTree catted_T = delete_solo_son_ele(now_T);
					cat_FAS(FT,catted_T,flag);
				}
				
				
				else
				//被删节点有左、右两个孩子
				//1.被删节点的值赋值为左子树中最大的结点的值
				//2.按照单儿子节点的删除方法，删除该最大节点（因为根据BST的性质，最大节点一定没有右孩子）					
				{
					//找到左子树的最大节点
					
					//FT和flag记录左子树最大节点的连接方式 
					FT = now_T; 
					flag=0;
					BinTree max_T = now_T->lchild;
					
					while(max_T->rchild)
					{
						FT = max_T;
						flag=1;
						max_T = max_T->rchild;
					}
					//交换两个结点的值 
					swap(now_T->data, max_T->data);
					
					BinTree catted_T = delete_solo_son_ele(max_T);
					cat_FAS(FT,catted_T,flag);
					 
				}
				return true;	
			}
			else
			{
				return false; //删除失败 
			}
		} 
};


int main(int argc,char* args[])
{
	BST T;
//	T.insertEle_x(3,T.getRoot());
//	T.deleteEle_x(3,T.getRoot());
//	cout<<T.getRoot()<<endl;

	vector<int> ser = {30,15,41,50,33,35,34};
//	vector<int> ser = {30,15,41,33};
	//建树 
	for(int x:ser)
	{
		T.insertEle_x(x,T.getRoot());	
	} 
	
	//查看树 
	for(int x:ser)
	{
		T.findEle_x(x,T.getRoot());	
	}
	
	//删除41
	for(auto iter = ser.begin();iter!=ser.end();iter++)
	{
		if(*iter==41)
		{
			ser.erase(iter);
		}
	} 
	T.deleteEle_x(41,T.getRoot());
	
	//重新检查树 
	for(int x:ser)
	{
		T.findEle(x);	
	} 
	
	
	
 	return 0;
}

