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
��ν���ҵı��ʣ�������֪����ȥ���Ҷ������ڵ�λ�á�
һ�㣬�������ݵķֲ������Է�Ϊȫ���򣬰�����������������
����ȫ�����Ӧ�Ŷ��ֲ���(O(logn),��̬)�������Ӧ�����Բ���(O(n))���������Ӧ�Ŷ������������Ľ��棺ƽ�������������AVL������(O(logn)����̬)
����ϣ���ң��䱾���Ǹ��ݶ����Լ���ǰ���úõĹ�ϣ�����ͳ�ͻ����취(��Ϊ����һ��Ĺ�ϣ�������ԣ���ͬ������ܶ�Ӧͬһ����ϣֵ����ʱ��Ҫ��ͻ����취)��
�������������λ�ã�
����ڹ�ϣ�����ͳ�ͻ����취�Լ�װ�����Ӷ����ں��ʵ������£���ʱ�临�Ӷ�ΪO��1�� 

һ�����õĹ�ϣ�����У�
(1) ������ 
1.ֱ�Ӷ�ַ����h(x) = a*x+b��
2.����������(h(x) = x mod p,����pһ��ȥС�ڵ���tablesize�ĵ�һ�������� 
(ȡ���������ɣ������Ϊ8������Ϊ7�����ڷֲ�����ֱ�Ϊ1,2,3,4,5,6��������˵��2��4��6�ֲ������ģ��Ϊ���ķ�����˵�����ķֲ����ǲ����ȵģ���ģ��Ϊ�����򲻻�����������)

3.���ַ�����������һ�����֣�����ʮ���ƣ�ȡ��仯���Ǽ�λ���֣������ֻ��ź�4Ϊh(x) = atoi(x+7),xΪchar*��) 
4.�۵���  5.ƽ��ȡ�з�
(2) ���ַ���
1.ASCII��Ӻͷ�������Ϊ�ϵ��ַ�����Ӧ��ASCII����мӺͣ���mod tablesize 

2.1��ȱ�㣬������������������ĸĽ�Ϊ��ֻȡǰ3���ַ���h(x) = (x[0]*27^2+x[1]*27+x[2]) mod tablesize ������27��������26����ĸ���Ͽո�

3.��λ��(��������ĳ������ʵ��)���������һ������Ϊ6���ַ�����h(x) = (x[0]*32^5+x[1]*32^4+x[2]*32^3+x[3]*32^2+x[4]*32+x[5]) mod tablesize,
����32������������Ϊ32��2�ı������Ҹպô���26����˱��ڽ�����λ���������ڵײ�Ӳ����ʵ�֣��ٶȺܿ죩 
ʵ�ʵ�ʵ�ַ����ǽ���ؾ��غ���λ�㷨 

���������ͻ�ķ��������Էֳ������ࣺ���ŵ�ַ��������ַ��
���ŵ�ַ������ϣ���ÿ��λ��ֻ�ܴ��һ�����ݣ������������˳�ͻ������Ҫ���ݳ�ͻ����㷨��Ѱ������λ�� 
����ַ������ϣ���ÿ��λ�ö���һ��ָ�룬ָ��һ���������ÿ��λ�ö����Դ�źܶ������� 

���ŵ�ַ����ͨ�ù�ʽΪfinal_adress(x) = h(x) + di
����di�ǵ�i�η�����ͻʱ��ƫ����  
��ͬ�ĳ�ͻѰַ�㷨�Ĳ�ͬ��������̽�ⷨ��ƽ��̽�ⷨ��˫ɢ��
1.����̽�ⷨ��di = di ,ȱ���ǻ�������ۼ������� 
2.ƽ��̽�ⷨ��di = (-1)^(i+1)*(i/2)^2 ����di(x) = 1^2,-(1)^2,2^2,-(2)^2,3^2,-(3)^2,...,(tablesize/2)^2, -(tablesize/2)^2��
�Ľ��ˡ��ۼ����󡱣�������tablesizeѡ��ǡ���������£�����̽�鵽����ɢ�б�ռ䣬����tablesizeѡȡΪ4k+3(kΪ������)������ 
3. ˫ɢ�У�di = i*h2(x),h2(x)����һ��ɢ�к���,
һ��Ҫ��h2(x)�㲻Ϊ0�����ܹ���֤��̽�⵽����ɢ�б�ռ� 
���� ��������h2(x) = p-(key mod p) ,p��С�ڵ���tablesize�ĵ�һ������ 
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
//	bool key_type_flag;    //Ϊ0����int��Ϊ1����string 
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
	slotStatus flag = empty;             //Ϊ0����գ�Ϊ1����ռ�� 
};
typedef LinkList slot_LA;


enum slot_type_name{OpenAddress,LinkAddress};

//��ϣ������ ����int�����ǳ���������������String��������λ��
//��ͻ����취�п��ŵ�ַ��������ַ�����֣����ŵ�ַ������ƽ��̽�ⷨ��  
bool isPrime(int x)
{
	bool ret = true;
	if(x==1)                 //1�������� 
	{
		ret = false;
	}
	else if(x>2 && x%2==0)   //����2��ż�� �������� 
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
		int P;   //����
		 
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
		tuple<int,LNode*> findAvailablePos(int hash_value)   //1����.����-1����û�ҵ� ,�����Ϊ-1������������±�λ�� 
		//2����.����nullptr�����λ��Ϊ�գ���������ʱӦ������Ӧ��ָ��ý�㣬�����Ϊnullptr�����ص��Ǽ���������½ڵ��ǰ����� 
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
					//ƽ��̽�ⷨ
					if(++cnt%2)   //���� 
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
		tuple<elementype,int,LNode*> getElebyHashValue(T key, int hash_value)    //����data�������±꣬�������ַ 
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
					//ƽ��̽�ⷨ
					if(++cnt%2)   //���� 
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
			//���������������ϣֵ
			int hash_value = key%P;
			return hash_value;
		}
		int calculateHashValue(const string& key)     //�����ʼ�Ĺ�ϣֵ����һ���Ȳ����ǳ�ͻ 
		{
			//��λ�������ϣֵ 
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
		elementype findEle(T key)    //����EmptyData����û�ҵ� 
		{			
			int hash_value = calculateHashValue(key);
			elementype ret = get<0>(getElebyHashValue(key, hash_value));
			return ret;
		}
	
		template<typename T>
		bool insertEle(T key, elementype data)
		{
			bool ret =true;
			int hash_value = calculateHashValue(key);                                             //�õ������Ĺ�ϣֵ 
			tuple<int,LNode*> pos_tuple = findAvailablePos(hash_value);     //���ݳ�����ϣֵ���õ�����Ҫ����������±�λ�û���ǰ������ڵ�λ��
//			cout<<"���ԣ�"<<(get<0>(pos_tuple))<<"\n";
			 
			if(slot_type == OpenAddress)
			{
//				struct slot_OA
//				{
//					key_type key;
//				//	bool key_type_flag;
//					elementype data;
//					slotStatus flag = empty;             //Ϊ0����գ�Ϊ1����ռ�� 
//				};


				if(get<0>(pos_tuple)==-1)
				{
					ret =false;                         //��ϣ�������������Ѿ��Ҳ����Ϸ��Ĳ���λ�� 
				}
				else
				{
					slots_OA[get<0>(pos_tuple)].key = key; 
					slots_OA[get<0>(pos_tuple)].data =data;
					slots_OA[get<0>(pos_tuple)].flag = occupied;
				}
			}
			else     //LinkAddress                     //����ַ����Զ������ 
			{
				LNode* new_node = new LNode{key,data,nullptr};
				
				if(get<1>(pos_tuple) == nullptr)
				{
					slots_LA[hash_value].head = new_node;
//					cout<<"���ԣ���"<<slots_LA[hash_value].head->data<<slots_LA[hash_value].head->key<<"\n";
					slots_LA[hash_value].tail = new_node;   //����βָ���λ�� 
				}
				else
				{
									
					get<1>(pos_tuple)->next = new_node; //���Ӳ��� 
					slots_LA[hash_value].tail = new_node;   //����βָ���λ�� 
				}
			}	
			return ret;
		}
		
		template<typename T>
		bool modifyEle(T key, elementype data)
		{
//			tuple<elementype,int,LNode*> getElebyHashValue(T key, int hash_value)
			bool ret =true;
			int hash_value = calculateHashValue(key);                                             //�õ������Ĺ�ϣֵ 
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
			int hash_value = calculateHashValue(key);                                             //�õ������Ĺ�ϣֵ 
			tuple<elementype,int,LNode*> Ele_tuple = getElebyHashValue(key,hash_value);
			if(slot_type == OpenAddress)
			{
				if(get<1>(Ele_tuple) == -1)
				{
					ret = false;
				}
				else
				{
					slots_OA[get<1>(Ele_tuple)].flag = empty;     //�߼�ɾ�� 
				}
			}
			else      //LinkAddress 
			{
				LNode* q = slots_LA[hash_value].head;
				if(!q)                                 //������Ϊ�� 
				{
					ret = false;
				}
				else if(get<2>(Ele_tuple) == nullptr)   //�Ҳ�����ɾ����Ŀ��ڵ� 
				{
					ret = false;
				}
				else
				{
					
					if(q == get<2>(Ele_tuple))   //ɾ�������׸���� 
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
		
		//Ӧ�ã�ͳ��Ӣ���ı���Ƶ
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

//tuple<elementype,int,LNode*> getElebyHashValue(T key, int hash_value)    //����data�������±꣬�������ַ  
//tuple<int,LNode*> findAvailablePos(int hash_value)   //1����.����-1����û�ҵ� ,�����Ϊ-1������������±�λ��
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
//	cout<<"����"<<endl;
	
 	return 0;
}

