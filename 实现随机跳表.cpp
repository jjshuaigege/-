#include <iostream>
#include <cstdlib>
#include <ctime>
#define nullvalue -999
#define maxvalue 10000

using namespace std;
//typedef int elementype;
//һ������ڲ�ͬ�㣬����ͬһ�����
//data��Ž���е�����
//link��һ��ָ�����飬ָ��ͬ�����һ����㣨��Ȼ�������ǲ�ͬ�Ľ�㣩 


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




//���������head��tail��������ڵ㣬head���༶����û��ֵ����Ч�������ͷ��㣬
//ʹ�ò��롢ɾ����������Ҫ���⿼�ǣ�tail�����������У�ֵȡ������������ڱ������ã�����Ҫȡһ���ܴ��ֵ 
//Ҫ��ֵΪx�Ľ����д���֮ǰ,���ȵõ��ý����ÿһ����Ե�ǰ���ڵ�,pre�����ż�¼���� 

//�����½ڵ�ʱ���������������Ϊ������ 0~k������ k==min{level(),maxLevel,levels+1}
//levelsָ�����������Ŀ��������0�㣬������ǰ��������levels+1�� 
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
				head->link[i] = tail;            //��ʼʱ��ͷ����ÿһ��ָ�붼ָ��tail 
			}
			
			
		}
		~SkipList()
		{
			delete head;
			delete tail;
			delete[] pre;
		}
		
		SNode<elementype>* FindEle(elementype x)    //����nullptr����û�ҵ� 
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
		bool InsertEle(elementype x)  //��������ظ�Ԫ��  
		{
			bool ret;
			
			int ele_level = Level();     //����������ɸ��ϲ��������� 
//			cout<<"charuzhi:"<<x<<"jiediangao:"<<ele_level<<endl;
			if(ele_level > levels)    //���levelsΪmaxLevel���򲻵�ʽ������� 
			{
				ele_level = ++levels;    //��������һ�� ��Ԫ�صĲ�ε��������� 
			}
			
//			cout<<"anquan1"<<endl;
			
			SNode<elementype>* new_sn = new SNode<elementype>(ele_level+1, x);
//			cout<<"biaoji:"<<ele_level<<"\n";
			
//			cout<<"xinjianshi:"<<(new_sn->maxsize)<<"\n";
			
//			cout<<"anquan2"<<endl;
			FindPre(x);
			
			
			for(int i = ele_level;i>=0;i--)
			{
				new_sn->link[i] = pre[i]->link[i];     //!!pre[i]���²������ڵ�i���ǰ�����ĵ�ַ !!
				pre[i]->link[i] = new_sn;
			}
			
			ret = true;
			return ret;

					
		}
		DeleteEle(elementype x)
		{
			bool ret;
			SNode<elementype>* p =	FindPre(x)->link[0];   //�õ�ָ��ɾ���ڵ��ָ�� 
			
			if(p->data == x)
			{
//				cout<<p->data<<"\n";
//				cout<<"���ԣ�"<<p->maxsize<<"\n";
				for(int i = p->maxsize-1;i>=0;i--)
				{
					SNode<elementype>* q = pre[i]->link[i];
					pre[i]->link[i] = q->link[i];
//					cout<<"����:"<<q->data<<"\n";
		
					
					if(i == levels && head->link[i] == tail)
					{
						levels--;    //��ɾ�ķֽ�㴦����߲㣬���Ѿ�û���κνڵ㣬��levels��һ 
					}
				}
				delete p;
				ret =true;	
			}
			
			else   //δ�ҵ�Ԫ�أ�ɾ��ʧ�� 
			{
				ret = false;	
			}
			
			return ret;	
		}
		
		void show()
		{
			for(int i = levels;i>=0;i--)
			{
				cout<<"��"<<i<<"�㣺\n";
				SNode<elementype>* p = head->link[i];
				if(p==tail)
				{
					cout<<"��";
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
		int Level()   //����0,1,2,...,k 
		{
			int level=0;
			
			while(rand()%2)
			{
				level++;
			}
//			cout<<"���ԣ��浽��"<<level<<endl;
			return min(level,maxLevel);
		}
		SNode<elementype>* FindPre(elementype x)  //���Ǻ��ĺ�����Ҫ��ֵΪx�Ľ����д���֮ǰ,���ȵõ��ý����ÿһ����Ե�ǰ���ڵ�
		{
			SNode<elementype>* p = head;
			for(int i = levels;i>=0;i--)
			{
				while(p->link[i]->data < x)
				{
					p = p->link[i];
				}
				
//				cout<<"���ԣ���"<<i<<"�㣬�ҵ�ǰ��"<<p->data<<endl;
				pre[i] = p;     //��¼��i���ǰ�����λ�� 
//				cout<<"anquan3"<<endl;
				
			}
			return pre[0];	     //��¼��0���ǰ������ָ�� 
		}
		int maxLevel,levels;     //���߶ȣ���ǰ�߶� 
		SNode<elementype>** pre;    //���ڲ����ʱ���ҵ�������ε�ǰ��������Щǰ����linkָ���²���Ľ�� 
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

