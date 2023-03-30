#include <iostream>
#include <cstdlib>
#include <ctime>
#define nullvalue -999
#define maxvalue 10000

using namespace std;
//typedef int elementype;
//一个结点在不同层，视作同一个结点
//data存放结点中的数据
//link是一个指针数组，指向不同层的下一个结点（显然，可能是不同的结点） 


template<typename T>
class SNode
{
	public:
		SNode(int maxsize, T data):maxsize(maxsize),link(new SNode<T>*[maxsize]),data(data)
		{
		
//			cout<<"chushi"<<maxsize<<"\n";	
		}
		~SNode()
		{
			delete[] link;
		}
//		friend class SkipList<T>;
	public:
		SNode** link;
		T data;
		int maxsize;
	
		
};




//跳表本身存在head和tail两个特殊节点，head（多级链，没有值）等效于链表的头结点，
//使得插入、删除操作不需要另外考虑，tail（单级链就行，值取无穷大）则起着哨兵的作用，故需要取一个很大的值 
//要对值为x的结点进行处理之前,首先得到该结点在每一层各自的前驱节点,pre就起着记录作用 

//插入新节点时，根据随机函数，为其生成 0~k个索引 k==min{level(),maxLevel,levels+1}
//levels指跳表的索引数目，包括第0层，则跳表当前层数共有levels+1层 
template<typename elementype>
class SkipList
{
	public:
		SkipList(int maxLevel,int levels):maxLevel(maxLevel),levels(levels)
		{
			head = new SNode<elementype>(maxLevel+1, nullvalue);
			tail = new SNode<elementype>(0, maxvalue);
			pre = new SNode<elementype>*[maxLevel+1];
			for(int i = maxLevel;i>=0;i--)
			{
				head->link[i] = tail;            //初始时，头结点的每一层指针都指向tail 
			}
			
			
		}
		~SkipList()
		{
			delete head;
			delete tail;
			delete[] pre;
		}
		
		SNode<elementype>* FindEle(elementype x)    //返回nullptr代表没找到 
		{
			SNode<elementype>* ret;
			
			SNode<elementype>* p = FindPre(x);
			
			if(p->link[0]->data == x)
			{
				ret = p->link[0];
			}
			else
			{
				ret = nullptr;
			}
			
			return ret;
		}
		bool InsertEle(elementype x)  //允许插入重复元素  
		{
			bool ret;
			
			int ele_level = Level();     //随机生成若干个上层的索引结点 
//			cout<<"charuzhi:"<<x<<"jiediangao:"<<ele_level<<endl;
			if(ele_level > levels)    //如果levels为maxLevel，则不等式不会成立 
			{
				ele_level = ++levels;    //跳表增加一层 ，元素的层次等于跳表层次 
			}
			
//			cout<<"anquan1"<<endl;
			
			SNode<elementype>* new_sn = new SNode<elementype>(ele_level+1, x);
//			cout<<"biaoji:"<<ele_level<<"\n";
			
//			cout<<"xinjianshi:"<<(new_sn->maxsize)<<"\n";
			
//			cout<<"anquan2"<<endl;
			FindPre(x);
			
			
			for(int i = ele_level;i>=0;i--)
			{
				new_sn->link[i] = pre[i]->link[i];     //!!pre[i]是新插入结点在第i层的前驱结点的地址 !!
				pre[i]->link[i] = new_sn;
			}
			
			ret = true;
			return ret;

					
		}
		DeleteEle(elementype x)
		{
			bool ret;
			SNode<elementype>* p =	FindPre(x)->link[0];   //得到指向被删除节点的指针 
			
			if(p->data == x)
			{
//				cout<<p->data<<"\n";
//				cout<<"调试："<<p->maxsize<<"\n";
				for(int i = p->maxsize-1;i>=0;i--)
				{
					SNode<elementype>* q = pre[i]->link[i];
					pre[i]->link[i] = q->link[i];
//					cout<<"调试:"<<q->data<<"\n";
		
					
					if(i == levels && head->link[i] == tail)
					{
						levels--;    //被删的分结点处于最高层，且已经没有任何节点，则levels减一 
					}
				}
				delete p;
				ret =true;	
			}
			
			else   //未找到元素，删除失败 
			{
				ret = false;	
			}
			
			return ret;	
		}
		
		void show()
		{
			for(int i = levels;i>=0;i--)
			{
				cout<<"第"<<i<<"层：\n";
				SNode<elementype>* p = head->link[i];
				if(p==tail)
				{
					cout<<"空";
				}
				while(p!=tail)
				{
					cout<<p->data<<" ";
					p = p->link[i];
				}
				cout<<"\n\n\n";
			}
		}
		
		
	private:
		int Level()   //返回0,1,2,...,k 
		{
			int level=0;
			
			while(rand()%2)
			{
				level++;
			}
//			cout<<"调试：随到了"<<level<<endl;
			return min(level,maxLevel);
		}
		SNode<elementype>* FindPre(elementype x)  //这是核心函数：要对值为x的结点进行处理之前,首先得到该结点在每一层各自的前驱节点
		{
			SNode<elementype>* p = head;
			for(int i = levels;i>=0;i--)
			{
				while(p->link[i]->data < x)
				{
					p = p->link[i];
				}
				
//				cout<<"调试：第"<<i<<"层，找到前驱"<<p->data<<endl;
				pre[i] = p;     //记录第i层的前驱结点位置 
//				cout<<"anquan3"<<endl;
				
			}
			return pre[0];	     //记录第0层的前驱结点的指针 
		}
		int maxLevel,levels;     //最大高度，当前高度 
		SNode<elementype>** pre;    //用于插入的时候，找到各个层次的前驱，将这些前驱的link指向新插入的结点 
		SNode<elementype>* head,*tail;		 		
};



int main(int argc,char* args[])
{
	srand(time(0));
	SkipList<int> sl(10,3);
	for(int i = 0;i<500;i++)
	{
		sl.InsertEle(rand()%365);
	}
	
	cout<<sl.FindEle(144)<<endl;
	cout<<sl.DeleteEle(144)<<endl;
	sl.show();
	
 	return 0;
}

