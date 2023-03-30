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
			if(this->T==nullptr)      //���������⴦�� 
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
					
					//���¸߶� 
					T->height = max(height(T->lchild), height(T->rchild))+1;	
				}
				
				else
				{
					T = new BTNode{x, 1, nullptr, nullptr};
					ret = T;
				}
			}
			
			
			
			//���ʧ�⣬�������TΪ���ڵ�Ķ����� 
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
					
					//�������� 
				}
				else if (x > T->data)
				{
					T->rchild = DeleteEle(T->rchild, x);      
					
					//�������� 
				}
				else                             //T����ֵ����x���ҵ��˸ý�㣩 
				{
					if(T->lchild && T->rchild)   //�������������� 
					{
						BinTree max_T = T->lchild;    //Ѱ���������е����Ԫ��
						while(max_T->rchild)
						{
							max_T = max_T->rchild;	
						}
						swap(max_T->data, T->data);   //����T��max_T�����ڵ��ֵ 
						
						T->lchild = DeleteEle(T->lchild,x);  //�ݹ�ɾ���ڵ�Ϊx��ֵ����ʱ�ڵ�Ϊx���Ǹ����һ���ǵ����ӻ����޺��� 
					}                                 //�������� 
					
					else				//ֻ��һ�����ӻ���û�к��� 
					{
						
						if(T->lchild)   //ֻ������ 
						{
							ret = T->lchild;
						}
						else            //ֻ���Һ��ӻ���û�к��ӣ�nullptr�� 
						{
							ret = T->rchild;
						}
						
						if(T == this->T)
						{
							this->T = nullptr;
						}
						
						delete T; 
						return ret;    //ɾ�����ڵ�������˳� 
					}
				}
				
				
				
				
				
				
			}
			else
			{
				cout<<"ɾ��ʧ��\n"<<endl;
			}
			
			//���¸߶� 
			T->height = max(height(T->lchild), height(T->rchild))+1;
			
			//���ʧ�⣬�������TΪ���ڵ�Ķ����� 
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
				cout<<"����ʧ��\n";
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
				
			if(balanceFactor == 2)//����������Ԫ�ص���ʧ��
			{
				//LR��� 
				if (BalanceFactor(T->lchild) == -1)
				{
					//������������
					
					//Ϊ�˿ɶ��� 
					BTNode* A = T; 
					BTNode* B = T->lchild;
					BTNode* C = B->rchild;
					
					A->lchild = RotateLeft(B);
					RotateRight(A);
					
					ret = C;
				}
				
				//LL��� 
				else //(BalanceFactor(T->lchild) == 1)����ɾ����� 
				{
					ret = RotateRight(T);
				}	
			}
			else if (balanceFactor == -2)//����������Ԫ�ص���ʧ�� 
			{
				//RL���  
				if(BalanceFactor(T->rchild) == 1)
				{
					//������������
					
					//Ϊ�˿ɶ��� 
					BTNode* A = T; 
					BTNode* B = T->rchild;
					BTNode* C = B->lchild;
					
					A->rchild = RotateRight(B);
					RotateLeft(A);
					
					ret = C;
				}	
				//RR��� 
				else     //(BalanceFactor(T->rchild) == -1)  ����ɾ����� 
				{
					ret = RotateLeft(T);
				}
				
				
				 
				 
			}
			else  //�������ƽ��� 
			{
				ret = T;	
			}
			
			
			if(T==this->T)   //�����Сʧ����ǡ�����Ը��ڵ�Ϊ������������Ҫ����ָ������޸� 
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
				ret = 0;    //��ʵû������ 
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
			
			//���¸߶� 
			A->height = max(height(A->lchild), height(A->rchild))+1;
			B->height = max(height(B->lchild), height(B->rchild))+1;
			return B;   //������������ĸ��ڵ㷵�س�ȥ�� 
		}
		
		BTNode* RotateRight(BinTree A)
		{
			BTNode* B = A->lchild;
			A->lchild = B->rchild;
			B->rchild = A;
			
			//���¸߶� 
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

