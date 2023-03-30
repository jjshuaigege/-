#include <iostream>
#include <cmath>
using namespace std;
//基于比较的排序，最优不会低于O(nlogn)
//而桶排序和基数排序则可以达到线性级别的复杂度O(n) 

/*
先从桶排序说起 :
比如说现有1000个学生，考数学这个科目，分数在0~100（整数）这个范围
那么可以准备101个桶，每个桶的内容是一个指针，指向一条链表。
通用的公式，假设有N条数据，每条数据所能取的离散值有B种 
分成分配和收集两个阶段。
1.收集阶段，遍历每一个学生，查看他/她的分数，按照分数值挂载不同的桶之中   时间复杂度为O(N) 
2.收集阶段，遍历每个桶，将链表头取下，连接在最终结果链表的尾部            时间复杂度为O(B)
总的时间复杂度为O(N+B) 

基数排序，是基于桶排序所做的改进
比如说有10个数，每个数所能取得值的范围为 0~999（整数） ，那么可以选择以10为基数，要么位数从高到低(主位优先)，要么从低到高（次位优先）
现以次位优先为例，进行讲解：
可以分成3轮分配和收集
第一轮只关注个位数
第二轮只关注十位数
第三轮只关注百位数
每一轮，又变成了一个桶排序问题

 假设数的取值范围有M种，基数（桶的个数）为B。那么轮数 P = 以B为底的logM      总的时间复杂度为O(P(N+B)) 	
*/
struct LNode
{
	int data;
	LNode* next;
};

typedef struct HTNode
{
	LNode* head;
	LNode* tail;
} *LinkList;

class radix_sorting_substance
{
	private:
		LinkList* buckets;
		int buckets_amount;
	public:
		radix_sorting_substance(int buckets_amount):buckets_amount(buckets_amount),buckets(new LinkList[buckets_amount])
		{
			for(int i = 0;i<buckets_amount;i++)
			{
				buckets[i] = new HTNode{nullptr, nullptr};
			}
		}
		static int getDigit(const int x, const int digit)
		{
			int s1 = pow(10,digit);
			int ret = x/s1;
			ret = ret%10;
			return ret;
		}
		void attachToBucket(const int num,const int digit_num)   //0到buckets_amount-1 
		{
			if(buckets[digit_num]->head==nullptr)
			{
				buckets[digit_num]->head = new LNode{num,nullptr};
				buckets[digit_num]->tail = buckets[digit_num]->head;
			}
			else
			{
				buckets[digit_num]->tail->next = new LNode{num,nullptr};          //桶中插入新节点 
				buckets[digit_num]->tail = 	buckets[digit_num]->tail->next;		  //更新尾指针 
			}
			
		}
		void detachLinkList(const int bucket_num, LinkList& total_list)
		{
			if(buckets[bucket_num]->head != nullptr)   //如果桶中的链表是空的，就不做任何操作 
			{
				if(total_list->head == nullptr)
				{
					total_list->head = buckets[bucket_num]->head;
					total_list->tail = buckets[bucket_num]->tail;
				}
				else
				{
					total_list->tail->next = buckets[bucket_num]->head;                  //连接桶里面的链表 
					total_list->tail = buckets[bucket_num]->tail;                       //更新尾指针的位置 
				}
				
				buckets[bucket_num]->head = buckets[bucket_num]->tail = nullptr;    //将桶置空		
			}	
		}
		
		void distribution(const int a[], const int length, const int digit)    //digit==0代表最低位 
		{
			for(int i = 0;i<length;i++)
			{
				int digit_num = getDigit(a[i], digit);
				attachToBucket(a[i], digit_num);
			}			
		}
		void collection(int a[], const int length)
		{
			LinkList total_list = new HTNode{nullptr,nullptr};
			for(int i = 0;i<buckets_amount;i++)
			{
				detachLinkList(i, total_list);	
			}
			
			//链表里的值写回到数组a
			LNode* p = total_list->head;
			LNode* q;
			for(int i = 0;i<length;i++)
			{
					
				a[i] = p->data;
//				cout<<"调试:"<<a[i]<<"\n";
				q = p;
				p = p->next;
				delete q;
			}
			delete total_list; 
		}
		void radix_sort(int a[], int length,int p)   //p是轮数 
		{
			//低位优先 
			for(int digit = 0;digit<p;digit++)
			{
				
				distribution(a,length,digit);
				collection(a,length);
				
				//用于调试
				for(int i = 0;i<length;i++)
				{
					cout<<a[i]<<" ";
				}
				cout<<endl; 
			}
		}
				
};

int main(int argc,char* args[])
{
	radix_sorting_substance rsc(10);
	int a[] = {64, 34, 8, 216, 512, 27, 729, 0, 1, 343, 125};
	rsc.radix_sort(a,11,3);
 	return 0;
}

