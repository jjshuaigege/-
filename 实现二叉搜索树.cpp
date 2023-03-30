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
		
		//����ĵݹ�ʵ��
		BinTree insertEle_x(const int& x,BinTree rt)
		{
			//ʵ�ʲ������ 
			if(rt==nullptr)
			{
				rt = new BTnode;
				rt->data = x;
				rt->lchild = rt->rchild = nullptr;
				if (!T)   // ������ǰΪ��������Ӧ�޸ĸ��ڵ�ָ���ֵ 
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
		
		
		//����һ��Ԫ��
		bool insertEle(const int& x)
		{
			BinTree now_T = new BTnode;
			now_T->data = x;
			now_T->lchild=now_T->rchild=nullptr;
			
			BinTree FT=T;
			
			//�����ǰ�������ǿ��� 
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
			else // �ǿ��� 
			{
				T = now_T;
			}
		}
		
		//���ҵĵݹ� 
		BinTree findEle_x(const int& x, const BinTree& rt)
		{
			if(rt==T)
			cout<<"��ʼ�ݹ����"<<endl;
			if(!rt)
			{
				cout<<"����ʧ��"<<endl;
				cout<<endl;
				return nullptr;
			}
			cout<<"��ǰ�ڵ��ֵΪ��"<<rt->data<<endl;
			if(x<rt->data)
			{
				cout<<"���ߡ�����"<<endl;
				return findEle_x(x,rt->lchild);
			}
			else if(x>rt->data)
			{
				cout<<"���ߡ�����"<<endl;  
				return findEle_x(x,rt->rchild);
			}
			else
			{
				cout<<"���ҵ���"<<endl;
				cout<<endl;
				return rt;
			}
			
		}
		
		
		//���ڲ�ʹ�ã����ҵ��򷵻�ָ��Ԫ�ص�ָ�룬���򷵻�nullptr�����û�ҵ�, FT��flag��Ϊ�ҵ��ý��ĸ��ڵ㣬�Լ��������ӹ�ϵ 
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
		
		//���غ��������ⲿʹ��
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
		
		//���ҽ��ĵݹ�ʵ�ַ���
	
		
		//ɾ�����ĵݹ�ʵ�ַ�����**�����˸��ӵļ�¼ǰ���ͺ��ӵ����ҹ�ϵ��������** 
		//ɾ����rtΪ���ڵ������ֵΪx�Ľ�㣬������Ĳ�������ɾ���򷵻غ��ӽ�㣬�������򷵻ر��� 
		BTnode* deleteEle_x(const int& x, BinTree rt)
		{
			BTnode* max_T;
			if(rt==nullptr)
			{
				cout<<"δ�ҵ���ɾ�����"<<endl; 
			}
			else if (x==rt->data)
			{
				//��ɾ�ڵ���˫����
				if(rt->lchild&&rt->rchild)
				{
					//�Ƚ���ֵ�Ľ��� 
					max_T=rt->lchild;
					while(max_T->rchild)
					{
						max_T=max_T->rchild;
					}
					swap(rt->data,max_T->data);
					
					
					rt->lchild = deleteEle_x(x,rt->lchild);	  //���ֵ�ڵ�һ��û���Һ��� ���Ҵ�ʱ�ý���ֵ�Ѿ�����ֵΪx, ��˻�ת�뵥����ɾ����������ɾ������ 
				} 
				//rt�����ӻ��޺���
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
					if(temp==T) //��ɾ�ڵ�Ϊ���ڵ㣬��Ҫ�������еĸ��ڵ�ָ���ÿ� 
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
		
		// ��Ҫ�ҵ����ڸ�ֵ�Ľ�㣬�Լ��ý��ĸ��ڵ� 
		bool deleteEle(const int& x)
		{
			BinTree FT = nullptr;   //FT��¼��ɾ�ڵ�ĸ��� 
			int flag = -1;//-1��0,1�ֱ����Tû��˫�׽�㣬T��FT�����ӣ�T��FT���Һ��� 
			BinTree now_T = findEle(x,FT,flag);
			cout<<"����"<<FT->data<<endl;
			if(now_T)
			{
				//����ɾ�������ӻ��޺��ӽ��T��lambda�������ʽ������ָ�����ĺ��ӵ�ָ�룬���ؿ�ָ��������޺��� 
				auto delete_solo_son_ele = [=](BTnode* T)-> BinTree
				{
					//������������������в��� 
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
						else  //�޺��� 
						{
							return nullptr;
						}
						//���ոý��Ŀռ�
						delete T; 
					}	
				};
				
				//��ɾ�ڵ�ֻ��һ�����ӣ�����û�к��� 
				if(!(now_T->lchild && now_T->rchild))
				{
					BinTree catted_T = delete_solo_son_ele(now_T);
					cat_FAS(FT,catted_T,flag);
				}
				
				
				else
				//��ɾ�ڵ���������������
				//1.��ɾ�ڵ��ֵ��ֵΪ�����������Ľ���ֵ
				//2.���յ����ӽڵ��ɾ��������ɾ�������ڵ㣨��Ϊ����BST�����ʣ����ڵ�һ��û���Һ��ӣ�					
				{
					//�ҵ������������ڵ�
					
					//FT��flag��¼���������ڵ�����ӷ�ʽ 
					FT = now_T; 
					flag=0;
					BinTree max_T = now_T->lchild;
					
					while(max_T->rchild)
					{
						FT = max_T;
						flag=1;
						max_T = max_T->rchild;
					}
					//������������ֵ 
					swap(now_T->data, max_T->data);
					
					BinTree catted_T = delete_solo_son_ele(max_T);
					cat_FAS(FT,catted_T,flag);
					 
				}
				return true;	
			}
			else
			{
				return false; //ɾ��ʧ�� 
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
	//���� 
	for(int x:ser)
	{
		T.insertEle_x(x,T.getRoot());	
	} 
	
	//�鿴�� 
	for(int x:ser)
	{
		T.findEle_x(x,T.getRoot());	
	}
	
	//ɾ��41
	for(auto iter = ser.begin();iter!=ser.end();iter++)
	{
		if(*iter==41)
		{
			ser.erase(iter);
		}
	} 
	T.deleteEle_x(41,T.getRoot());
	
	//���¼���� 
	for(int x:ser)
	{
		T.findEle(x);	
	} 
	
	
	
 	return 0;
}

