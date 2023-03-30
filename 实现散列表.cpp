#include <iostream>
#include <string>
#include <cmath>
#include <tuple>
#include <vector>
#include <fstream>
#define EmptyData -1  
//#define looplimit 1000
using namespace std;
typedef int elementype; 
/*
所谓查找的本质，就是已知对象，去查找对象所在的位置。
一般，根据数据的分布，可以分为全有序，半有序和无序三种情况
其中全有序对应着二分查找(O(logn),静态)，无序对应着线性查找(O(n))，半有序对应着二叉搜索树（改进版：平衡二叉搜索树（AVL树））(O(logn)，动态)
而哈希查找，其本质是根据对象，以及提前设置好的哈希函数和冲突解决办法(因为对于一般的哈希函数而言，不同对象可能对应同一个哈希值，此时需要冲突解决办法)，
算出对象所处的位置，
因此在哈希函数和冲突解决办法以及装填因子都处于合适的条件下，其时间复杂度为O（1） 

一、常用的哈希函数有：
(1) 对数字 
1.直接定址法（h(x) = a*x+b）
2.除留余数法(h(x) = x mod p,其中p一般去小于等于tablesize的第一个质数。 
(取质数的理由：比如表长为8，质数为7，对于分布间隔分别为1,2,3,4,5,6的数据来说，2、4、6分布间隔对模长为表长的方法来说，最后的分布都是不均匀的，而模长为质数则不会出现这种情况)

3.数字分析法（对于一个数字，例如十进制，取最常变化的那几位数字，比如手机号后4为h(x) = atoi(x+7),x为char*）) 
4.折叠法  5.平方取中法
(2) 对字符串
1.ASCII码加和法：各个为上的字符所对应的ASCII码进行加和，再mod tablesize 

2.1的缺点，计算量过大，依其而来的改进为，只取前3个字符，h(x) = (x[0]*27^2+x[1]*27+x[2]) mod tablesize ，其中27的由来是26个字母加上空格

3.移位法(将在下面的程序进行实现)：比如对于一个长度为6的字符串，h(x) = (x[0]*32^5+x[1]*32^4+x[2]*32^3+x[3]*32^2+x[4]*32+x[5]) mod tablesize,
其中32的由来：是因为32是2的倍数，且刚好大于26，因此便于进行移位操作（便于底层硬件的实现，速度很快） 
实际的实现方法是结合秦九韶和移位算法 

二、处理冲突的方法，可以分成两大类：开放地址法和链地址法
开放地址法：哈希表的每个位置只能存放一个数据，因此如果发生了冲突，就需要根据冲突解决算法另寻其它空位置 
链地址法：哈希表的每个位置都是一个指针，指向一条链表，因此每个位置都可以存放很多条数据 

开放地址法的通用公式为final_adress(x) = h(x) + di
其中di是第i次发生冲突时的偏移量  
不同的冲突寻址算法的不同，有线性探测法，平方探测法，双散列
1.线性探测法：di = di ,缺点是会产生“聚集”现象 
2.平方探测法：di = (-1)^(i+1)*(i/2)^2 ，即di(x) = 1^2,-(1)^2,2^2,-(2)^2,3^2,-(3)^2,...,(tablesize/2)^2, -(tablesize/2)^2，
改进了“聚集现象”，但是在tablesize选择不恰当的条件下，不能探查到整个散列表空间，除非tablesize选取为4k+3(k为正整数)的质数 
3. 双散列：di = i*h2(x),h2(x)是另一个散列函数,
一般要求h2(x)恒不为0，且能够保证可探测到整个散列表空间 
比如 可以设置h2(x) = p-(key mod p) ,p是小于等于tablesize的第一个质数 
*/
struct key_type
{
	int t1=-999;
	string t2="";
	key_type(){}
	key_type(const int x):t1(x){}
	key_type(const string& x):t2(x){}
	key_type(const char* x):t2(x){}
	

	friend ostream& operator<<(ostream& o,const key_type& x)
	{
		if(x.t2 != "")
		{
			o<<x.t2;
		}
		else if (x.t1 != -999)
		{
			o<<x.t1;
		}
		return o;
	}
	bool operator !=(const int x)
	{
		return t1 != x;
	}
	bool operator ==(const int x)
	{
		return t1 == x;
	}
	bool operator !=(const string& x)
	{
		return t2!=x;
	}
	bool operator ==(const string& x)
	{
		return t2 == x;
	}
};

struct LNode
{
	key_type key;
//	bool key_type_flag;    //为0代表int，为1代表string 
	elementype data; 
	LNode* next;
};
struct LinkList
{
	LNode* head;
	LNode* tail;
};
enum slotStatus{empty,occupied}; 


struct slot_OA
{
	key_type key;
//	bool key_type_flag;
	elementype data;
	slotStatus flag = empty;             //为0代表空，为1代表被占用 
};
typedef LinkList slot_LA;


enum slot_type_name{OpenAddress,LinkAddress};

//哈希函数： 对于int类型是除留余数法，对于String类型是移位法
//冲突解决办法有开放地址法和链地址法两种，开放地址法采用平方探测法，  
bool isPrime(int x)
{
	bool ret = true;
	if(x==1)                 //1不是素数 
	{
		ret = false;
	}
	else if(x>2 && x%2==0)   //大于2的偶数 不是素数 
	{
		ret = false;
	}
	else                    
	{
		for(int i = 3;i<=sqrt(x);i+=2)
		{
			if(x%i == 0)
			{
				ret = false;
				break;
			}
		}
	
	}
	return ret;	
}
int getPrime(int x)
{
	int ret;
	if(x == 1)
	{
		ret = -1;
	}
	else  //x>=2
	{
		int now_num = x;
		while(!isPrime(now_num))
		{
			now_num--;
		}
		ret = now_num;
	}
	return ret;
} 
class MyHashMap
{
	private:
		slot_OA* slots_OA=nullptr;
		slot_LA* slots_LA=nullptr;		
		
		int slot_type;
	public:
		int TableSize;
		int P;   //质数
		 
	public:
		MyHashMap(int TableSize,int slot_type=LinkAddress):TableSize(TableSize),slot_type(slot_type)   
		{
			P = getPrime(TableSize);
			if(P==-1)
			{
				throw 1;
			}
			
			if(slot_type==LinkAddress)
			{
				slots_LA = new slot_LA[TableSize];
				for(int i = 0;i<TableSize;i++)
				{
					slots_LA[i].head=nullptr;
					slots_LA[i].tail=nullptr;
				}
			}
			else
			{
				slots_OA = new slot_OA[TableSize];
			}
			
		}
		void initialize()
		{
			if(slot_type==LinkAddress)
			{
				if(slots_LA)
				{
					for(int i = 0;i<TableSize;i++)
					{
						LNode* p = slots_LA[i].head;
						LNode* q;
						while(p)
						{
							q = p;
							p = p->next;
							delete q;
						}
					}
					delete[] slots_LA;
				}
				
				slots_LA = new slot_LA[TableSize];
				for(int i = 0;i<TableSize;i++)
				{
					slots_LA[i].head=nullptr;
					slots_LA[i].tail=nullptr;
				}
			}
			
			else
			{
				if(slots_OA)
				{
					delete[] slots_OA;
				}
				slots_OA = new slot_OA[TableSize];
			}
		}
		tuple<int,LNode*> findAvailablePos(int hash_value)   //1部分.返回-1代表没找到 ,如果不为-1，则代表数组下标位置 
		//2部分.返回nullptr代表该位置为空，后续操作时应将链表应该指向该结点，如果不为nullptr，返回的是即将插入的新节点的前驱结点 
		{
			tuple<int,LNode*> ret{-1,nullptr};
			if(slot_type == OpenAddress)
			{
				int cnt = 0;
				const int looplimit = 2*log(TableSize)/log(2);
				int loop_cnt = 0;
				int orignal_position = hash_value;
				int final_position = orignal_position;
				int shift_value;
				while(slots_OA[final_position].flag == occupied && loop_cnt<looplimit)
				{
					loop_cnt++;
					//平方探测法
					if(++cnt%2)   //奇数 
					{
						shift_value = ((cnt+1)/2)*((cnt+1)/2); 
					
						
							
					} 
					else
					{
						shift_value = -(cnt/2)*(cnt/2);
						
						
					}
					final_position = orignal_position + shift_value;
					
					while(final_position>TableSize-1)
					{
						final_position -= TableSize;
					}
					
					while(final_position<0)
					{
						final_position += TableSize;
					}
					
					
				}
				
			
//				get<0>(ret) = final_position;
				if(loop_cnt == looplimit)
				{
					get<0>(ret) = -1;
				}
				else
				{
					get<0>(ret) = final_position;
				}
				
			}
			else    //LinkAddress
			{
				LNode* p;
				if(slots_LA[hash_value].head == nullptr)
				{
					get<1>(ret) = nullptr;
				}
				else
				{
					p = slots_LA[hash_value].head;
					if(p)
					{
						while(p->next!=nullptr)
						{
							p = p->next;
						}
					}
					
					
					get<1>(ret) = p;
				}
			}
			return ret;
		}
		template<typename T>
		tuple<elementype,int,LNode*> getElebyHashValue(T key, int hash_value)    //返回data，数组下标，链表结点地址 
		{

			tuple<elementype,int,LNode*> ret;
			if(slot_type == OpenAddress)
			{
				int cnt = 0;
				int orignal_position = hash_value;
				int final_position = orignal_position;
				int shift_value;
				int loopcnt = 0;
				const int looplimit = 2*log(TableSize)/log(2);
				while(loopcnt<looplimit && slots_OA[final_position].flag == occupied && slots_OA[final_position].key!=key)
				{
					loopcnt++;
					//平方探测法
					if(++cnt%2)   //奇数 
					{
						shift_value = ((cnt+1)/2)*((cnt+1)/2); 
						final_position = orignal_position + shift_value;
						while(final_position>TableSize-1)
						{
							final_position -= TableSize;
						}
							
					} 
					else
					{
						shift_value = -(cnt/2)*(cnt/2);
						final_position = orignal_position + shift_value;
						while(final_position<0)
						{
							final_position += TableSize;
						}
					}
					
					
				}
				if(slots_OA[final_position].flag == occupied)
				{
					get<0>(ret) = slots_OA[final_position].data;
					get<1>(ret) = final_position;
					get<2>(ret) = nullptr;
				}
				else
				{
					get<0>(ret) = EmptyData;
					get<1>(ret) = -1;
					get<2>(ret) = nullptr;
				}
				
			}
			else    //LinkAddress
			{

				LNode* p;
				if(slots_LA[hash_value].head == nullptr)
				{
					get<0>(ret) = EmptyData;
					get<1>(ret) = -1;
					get<2>(ret) = nullptr;
				}
				else
				{
					p = slots_LA[hash_value].head;
					while(p->key!=key && p->next!=nullptr)
					{
						p = p->next;
					}
					
					if(p->key == key)
					{
						get<0>(ret) = p->data;
						get<1>(ret) = -1;
						get<2>(ret) = p;
					}
					else
					{
						get<0>(ret) = EmptyData;
						get<1>(ret) = -1;
						get<2>(ret) = nullptr;
					}
				}
			}
			
			return ret;
		}
		
		int calculateHashValue(int key)
		{
			//除留余数法计算哈希值
			int hash_value = key%P;
			return hash_value;
		}
		int calculateHashValue(const string& key)     //计算初始的哈希值，这一步先不考虑冲突 
		{
			//移位法计算哈希值 
			int length = key.size();
			int hash_value = 0;
			if(length > 0 )
			{
				hash_value = key[0];
				for(int i = 1;i<length;i++)
				{
					hash_value = hash_value << 5;
					if(hash_value>1e6)
					{
						hash_value = hash_value%TableSize;
					}
					hash_value += key[i] ;
				}
			}
			
			hash_value = hash_value%TableSize;
			return hash_value;
		}
		
		template<typename T>
		elementype findEle(T key)    //返回EmptyData代表没找到 
		{			
			int hash_value = calculateHashValue(key);
			elementype ret = get<0>(getElebyHashValue(key, hash_value));
			return ret;
		}
	
		template<typename T>
		bool insertEle(T key, elementype data)
		{
			bool ret =true;
			int hash_value = calculateHashValue(key);                                             //得到初步的哈希值 
			tuple<int,LNode*> pos_tuple = findAvailablePos(hash_value);     //根据初步哈希值，得到最终要插入的数组下标位置或者前驱链表节点位置
//			cout<<"调试："<<(get<0>(pos_tuple))<<"\n";
			 
			if(slot_type == OpenAddress)
			{
//				struct slot_OA
//				{
//					key_type key;
//				//	bool key_type_flag;
//					elementype data;
//					slotStatus flag = empty;             //为0代表空，为1代表被占用 
//				};


				if(get<0>(pos_tuple)==-1)
				{
					ret =false;                         //哈希表已满，或者已经找不到合法的插入位置 
				}
				else
				{
					slots_OA[get<0>(pos_tuple)].key = key; 
					slots_OA[get<0>(pos_tuple)].data =data;
					slots_OA[get<0>(pos_tuple)].flag = occupied;
				}
			}
			else     //LinkAddress                     //链地址法永远不会满 
			{
				LNode* new_node = new LNode{key,data,nullptr};
				
				if(get<1>(pos_tuple) == nullptr)
				{
					slots_LA[hash_value].head = new_node;
//					cout<<"调试！！"<<slots_LA[hash_value].head->data<<slots_LA[hash_value].head->key<<"\n";
					slots_LA[hash_value].tail = new_node;   //更新尾指针的位置 
				}
				else
				{
									
					get<1>(pos_tuple)->next = new_node; //连接操作 
					slots_LA[hash_value].tail = new_node;   //更新尾指针的位置 
				}
			}	
			return ret;
		}
		
		template<typename T>
		bool modifyEle(T key, elementype data)
		{
//			tuple<elementype,int,LNode*> getElebyHashValue(T key, int hash_value)
			bool ret =true;
			int hash_value = calculateHashValue(key);                                             //得到初步的哈希值 
			tuple<elementype,int,LNode*> Ele_tuple = getElebyHashValue(key,hash_value);
			
			if(slot_type == OpenAddress)
			{
				if(get<1>(Ele_tuple) == -1)
				{
					ret = false;
				}
				else
				{
					slots_OA[get<1>(Ele_tuple)].data=data;
				}
			}
			else
			{
				if(get<2>(Ele_tuple) == nullptr)
				{
					ret = false;
				}
				else
				{
					get<2>(Ele_tuple)->data = data;
				}
			}
			return ret;
		}
		
		template<typename T>
		bool deleteEle(T key)
		{
			bool ret =true;
			int hash_value = calculateHashValue(key);                                             //得到初步的哈希值 
			tuple<elementype,int,LNode*> Ele_tuple = getElebyHashValue(key,hash_value);
			if(slot_type == OpenAddress)
			{
				if(get<1>(Ele_tuple) == -1)
				{
					ret = false;
				}
				else
				{
					slots_OA[get<1>(Ele_tuple)].flag = empty;     //逻辑删除 
				}
			}
			else      //LinkAddress 
			{
				LNode* q = slots_LA[hash_value].head;
				if(!q)                                 //链表本身为空 
				{
					ret = false;
				}
				else if(get<2>(Ele_tuple) == nullptr)   //找不到被删除的目标节点 
				{
					ret = false;
				}
				else
				{
					
					if(q == get<2>(Ele_tuple))   //删除的是首个结点 
					{
						slots_LA[hash_value].head=get<2>(Ele_tuple)->next;
						if(slots_LA[hash_value].tail == q)
						{
							slots_LA[hash_value].tail=nullptr;
						}
						delete get<2>(Ele_tuple);	
					} 
					else
					{
					 	while(q && q->next!=get<2>(Ele_tuple))
						{
							q = q->next; 
						}
					
					
						
						q->next = get<2>(Ele_tuple)->next;
							
						if(q->next==nullptr)
						{
							slots_LA[hash_value].tail = q;
						}
						
						delete get<2>(Ele_tuple);
					}
					
					
				}
			}
			return ret;
		}
		
		void showAllEle()
		{
			if(slot_type = OpenAddress)
			{
				for(int i = 0;i<TableSize;i++)
				{
					cout<<slots_OA[i].key<<":"<<slots_OA[i].data<<" ";
					if(i+1%4 == 0)
					{
						cout<<endl;
					}
				}
			}
			else
			{
				int cnt = 0;
				for(int i = 0;i<TableSize;i++)
				{
					LNode* p = slots_LA[i].head;
					LNode* q;
					while(p)
					{
						q = p;
						cout<<q->key<<":"<<q->data<<" ";
						cnt++;
						if(cnt%4==0)
						{
							cout<<endl;
						}
						p = p->next;
					}
				}
			}
		}
		
		//应用：统计英文文本词频
		void wordFrequenceStatics(string file_path)
		{
			initialize();
			ifstream ifs(file_path,ios::in|ios::binary);
			if(!ifs)
			{
				throw 1;
			}
			string sss;

			
			elementype cnt;
			while(ifs>>sss)
			{
				char last_char = sss.at(sss.size()-1);
				if(last_char == ',' || last_char == '.' || last_char == '?' || last_char == '!' || last_char == ':' || last_char == '\'')
				sss.pop_back();
				if(sss.size()>=3)
				{

					cnt = findEle(sss);

					if(cnt == EmptyData)
					{
						insertEle(sss,1);

					}
					else
					{
						modifyEle(sss,cnt+1);
					}	
				}
				
			}
			
			showAllEle();
			
		}
		 
};
int main(int argc,char* args[])
{

	
//	while(1)
//	{
//		int x;
//		cin >> x;
//		cout<<getPrime(8)<<endl;
//	}

//tuple<elementype,int,LNode*> getElebyHashValue(T key, int hash_value)    //返回data，数组下标，链表结点地址  
//tuple<int,LNode*> findAvailablePos(int hash_value)   //1部分.返回-1代表没找到 ,如果不为-1，则代表数组下标位置
 	MyHashMap hm1(10,LinkAddress);
 	hm1.wordFrequenceStatics("Hamlet.txt");
 	
// 	vector<string> key_vec1;
// 	vector<int> key_vec2;
// 	vector<elementype> data_vec1;
// 	vector<elementype> data_vec2;
// 	
// 	key_vec1.push_back("15");
// 	key_vec1.push_back("asd");
// 	key_vec1.push_back("ggh");
// 	
// 	key_vec2.push_back(15);
// 	key_vec2.push_back(44);
// 	key_vec2.push_back(333);
// 	key_vec2.push_back(26);
// 	key_vec2.push_back(37);
// 	key_vec2.push_back(344);
// 	
// 	
// 	data_vec1.push_back(45);
// 	data_vec1.push_back(91);
// 	data_vec1.push_back(101);
// 	
// 	
// 	data_vec2.push_back(123);
// 	data_vec2.push_back(678);
// 	data_vec2.push_back(282);
// 	data_vec2.push_back(321);
// 	data_vec2.push_back(876);
// 	data_vec2.push_back(888);
// 	
// 	for(int i = 0;i<key_vec1.size();i++)
// 	{
// 		hm1.insertEle(key_vec1[i],data_vec1[i]);
//	}
//	for(int i = 0;i<key_vec2.size();i++)
// 	{
// 		hm1.insertEle(key_vec2[i],data_vec2[i]);
//	}
//	
//	for(int i = key_vec1.size()-1;i>=0;i--)
// 	{
// 		cout<<hm1.findEle(key_vec1[i])<<"\n";
//	}
//	
//	for(int i = key_vec2.size()-1;i>=0;i--)
// 	{
// 		cout<<hm1.findEle(key_vec2[i])<<"\n";
//	}
// 	

//	cout<<hm1.TableSize<<endl;
//	cout<<get<0>(hm1.findAvailablePos(10))<<endl;
//	hm1.insertEle(21,686);
//	
//	cout<<hm1.findEle(15)<<endl;
//	hm1.modifyEle(15,666);
//	cout<<hm1.findEle(15)<<endl;
//	
//	hm1.insertEle(23,777);
//	cout<<hm1.findEle(23)<<endl;
//	cout<<(hm1.deleteEle(23))<<endl; 
//	cout<<hm1.findEle(23)<<endl;
//	
//	hm1.insertEle(23,777);
//	cout<<hm1.findEle(23)<<endl;
//	cout<<(hm1.deleteEle(23))<<endl; 
//	cout<<hm1.findEle(23)<<endl;
//	
//	hm1.insertEle(24,888);
//	hm1.insertEle(35,999);
//	cout<<hm1.findEle(24)<<endl;
//	cout<<hm1.findEle(35)<<endl;
//	cout<<(hm1.deleteEle(24))<<endl; 
//	cout<<hm1.findEle(24)<<endl;
//	cout<<hm1.findEle(35)<<endl;
////	cout<<false<<endl;
//	cout<<"结束"<<endl;
	
 	return 0;
}

