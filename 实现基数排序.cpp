#include <iostream>
#include <cmath>
using namespace std;
//���ڱȽϵ��������Ų������O(nlogn)
//��Ͱ����ͻ�����������Դﵽ���Լ���ĸ��Ӷ�O(n) 

/*
�ȴ�Ͱ����˵�� :
����˵����1000��ѧ��������ѧ�����Ŀ��������0~100�������������Χ
��ô����׼��101��Ͱ��ÿ��Ͱ��������һ��ָ�룬ָ��һ������
ͨ�õĹ�ʽ��������N�����ݣ�ÿ����������ȡ����ɢֵ��B�� 
�ֳɷ�����ռ������׶Ρ�
1.�ռ��׶Σ�����ÿһ��ѧ�����鿴��/���ķ��������շ���ֵ���ز�ͬ��Ͱ֮��   ʱ�临�Ӷ�ΪO(N) 
2.�ռ��׶Σ�����ÿ��Ͱ��������ͷȡ�£����������ս�������β��            ʱ�临�Ӷ�ΪO(B)
�ܵ�ʱ�临�Ӷ�ΪO(N+B) 

���������ǻ���Ͱ���������ĸĽ�
����˵��10������ÿ��������ȡ��ֵ�ķ�ΧΪ 0~999�������� ����ô����ѡ����10Ϊ������Ҫôλ���Ӹߵ���(��λ����)��Ҫô�ӵ͵��ߣ���λ���ȣ�
���Դ�λ����Ϊ�������н��⣺
���Էֳ�3�ַ�����ռ�
��һ��ֻ��ע��λ��
�ڶ���ֻ��עʮλ��
������ֻ��ע��λ��
ÿһ�֣��ֱ����һ��Ͱ��������

 ��������ȡֵ��Χ��M�֣�������Ͱ�ĸ�����ΪB����ô���� P = ��BΪ�׵�logM      �ܵ�ʱ�临�Ӷ�ΪO(P(N+B)) 	
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
		void attachToBucket(const int num,const int digit_num)   //0��buckets_amount-1 
		{
			if(buckets[digit_num]->head==nullptr)
			{
				buckets[digit_num]->head = new LNode{num,nullptr};
				buckets[digit_num]->tail = buckets[digit_num]->head;
			}
			else
			{
				buckets[digit_num]->tail->next = new LNode{num,nullptr};          //Ͱ�в����½ڵ� 
				buckets[digit_num]->tail = 	buckets[digit_num]->tail->next;		  //����βָ�� 
			}
			
		}
		void detachLinkList(const int bucket_num, LinkList& total_list)
		{
			if(buckets[bucket_num]->head != nullptr)   //���Ͱ�е������ǿյģ��Ͳ����κβ��� 
			{
				if(total_list->head == nullptr)
				{
					total_list->head = buckets[bucket_num]->head;
					total_list->tail = buckets[bucket_num]->tail;
				}
				else
				{
					total_list->tail->next = buckets[bucket_num]->head;                  //����Ͱ��������� 
					total_list->tail = buckets[bucket_num]->tail;                       //����βָ���λ�� 
				}
				
				buckets[bucket_num]->head = buckets[bucket_num]->tail = nullptr;    //��Ͱ�ÿ�		
			}	
		}
		
		void distribution(const int a[], const int length, const int digit)    //digit==0�������λ 
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
			
			//�������ֵд�ص�����a
			LNode* p = total_list->head;
			LNode* q;
			for(int i = 0;i<length;i++)
			{
					
				a[i] = p->data;
//				cout<<"����:"<<a[i]<<"\n";
				q = p;
				p = p->next;
				delete q;
			}
			delete total_list; 
		}
		void radix_sort(int a[], int length,int p)   //p������ 
		{
			//��λ���� 
			for(int digit = 0;digit<p;digit++)
			{
				
				distribution(a,length,digit);
				collection(a,length);
				
				//���ڵ���
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

