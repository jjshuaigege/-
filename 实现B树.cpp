#include <iostream>
#include <vector>
#include <queue>
/*
m��B�� 
1.ÿ�����������m-1��Ԫ�أ������m���ֲ棨���ӣ�
2.���˸����֮�⣬�ǿս�������m/2������ȡ�������ֲ棬 m/2������ȡ����-1��Ԫ��
3.ÿ�������������������߾����
4.��ÿ����������:����0<Ԫ��0<����1<Ԫ��1<����2<Ԫ��2<...<����m-1<Ԫ��m-1<����m  
    
�ն˽����û�к��ӵķǿս��
Ҷ�ӽ���ǿս�� 
 
*/
using namespace std;
typedef int elementype;
struct BTNode
{
	int size_to_spilt;      //���ʵ�ʵ�Ԫ�ظ���Ϊsize_to_spilt-1
	vector<elementype> datas;                   //[size_to_spilt];
	vector<BTNode*> childs;                     //[size_to_spilt+1];              
	//childs[0]|datas[0]|childs[1]|datas[1]|...|childs[size_to_spilt-1]|datas[size_to_spilt-1]|childs[size_to_spilt]
	
	public:
		
		BTNode()
		{
			childs.push_back(nullptr);
		}
		BTNode(int size_to_spilt, const BTNode* x,int s,int e):size_to_spilt(size_to_spilt)       //����һ�� size_to_spilt-1���㣬
		//����ԭx����s��e ������[ data[s],data[e] ]�Լ� ������[ child[s],childs[e+1] ]��ֵ���½ڵ� 
		{
			int i;
			for(i = s;i <= e;i++)
			{
				elementype temp_data = x->datas[i];
				BTNode* temp_child = x->childs[i];
				datas.push_back(temp_data);
				childs.push_back(temp_child);
			}
			
			if(s<=e)     //��Ч
			{
				childs.push_back(x->childs[i]);	
			} 
			
			
			else   //��Ч���
			{
				childs.push_back(nullptr); 
			}
		}
	
};


class BTree
{
	public:
		friend int main(int,char**);
		BTree(int size_to_spilt):root(nullptr),size_to_spilt(size_to_spilt)
		{
			min_limit = (this->size_to_spilt+1)/2 - 1;    // m/2����ȡ�� -1��С�ڸ�ֵ��ʱ�����Ҫ���н�������ߺϲ������� 
		}
		
		~BTree()
		{
			
		}
		
		BTNode* findEle(elementype x)
		{
			return findEle_re(root,x,nullptr);
		}
		
		
		void insertEle(elementype x)
		{
			if(root == nullptr)
			{
				root = new BTNode;
				root->size_to_spilt = this->size_to_spilt;
			}
			insertEle_re(root,x);
		}
		
		void deleteEle(elementype x)
		{
			
			
			deleteEle_re(root,x);
		}
		
		void showAll() //������� 
		{
			struct Qunode
			{
				BTNode* BTN;
				int level;
			};
			int cnt=0;
			queue<Qunode> qu;
			if(root!=nullptr)
			{
				int level = 0;
				qu.push(Qunode{root,level});
				while(!qu.empty())
				{
					Qunode front_T = qu.front();
					qu.pop();
					
					cout<<"���"<<cnt++<<"������Ϊ"<<front_T.level<<",������Ԫ����:";
					
					for(int i = 0;i<front_T.BTN->datas.size();i++)
					{
						cout<<front_T.BTN->datas.at(i)<<" ";
					}
					cout<<"\n";
					
					
					level = front_T.level+1;
					for(int i = 0;i<front_T.BTN->childs.size();i++)
					{
						BTNode* to_in = front_T.BTN->childs.at(i);
						if(to_in!=nullptr)
						{
							qu.push(Qunode{to_in,level});
						}	
					}  
						
				}
				cout<<"\n\n";
			}
			else
			{
				cout<<"������Ϊ��\n";
			}
			
			BTNode* p, *q;
			
		}
		
	private:
		BTNode* root;     //���ڵ� 
		BTNode* pre;      //������ʱ��Ų���ĳ���ڵ��ǰ�ýڵ�Ľ��  
		int size_to_spilt;
		int min_limit;    //m/2����ȡ�� -1������Ԫ�ظ���С�ڸ�ֵ��ʱ�����Ҫ���н�������ߺϲ�������
//		bool ifInChilds(BTNode* p, BTNode* q)  //�ж�q�Ƿ���p�ĺ���֮�� 
//		{
//			ret = false;
//			for(auto i = p->childs.begin();i!=p->childs.end();i++)
//			{
//				if((*i) == q)
//				{
//					ret = true;
//					break;	
//				}
//			}
//			return ret;
//		}
		BTNode* find_smaller_ele(elementype)
		{
			
		}
		void deleteEle_re(BTNode* now_T, elementype x)   //ɾ����now_TΪ���ڵ��B����ֵΪx��Ԫ�� 
		{
			//�ҵ�ֵΪx��Ԫ�����ڵĽ��
			BTNode* deleted_node = findEle_re(now_T, x);
			
			if(deleted_node) 
			{
				/*
				���ɾ�����Ƿ��ն˽����ֵΪx��Ԫ��(�зǿպ��ӽ��),�ҵ���Ԫ�ص�ֱ��ǰ�����պ�С�ڸ�Ԫ�ص�Ԫ�أ���ֵΪy��
				��ôֱ��ǰ��һ�������ն˽���ϣ�����ɾ��Ԫ�غ�ֱ��ǰ��Ԫ�ص�ֵ���н���,������ת��Ϊɾ����������ֵΪy�Ľ��
				(���ն˽ڵ��ɾ������ת��Ϊ�ն˽ڵ��ɾ������) 
				*/
				if(deleted_node->childs[0])   //���ն˽��
				{
					int index;
					for(index = deleted_node->datas.size()-1 ;index >= 0; index--)
					{
						if(deleted_node->datas.at(index) == x)
						{
							break;
						}
					}
					//�Ҹ�Ԫ����ָ��ָ����������������Ǹ�Ԫ�� 
					BTNode* smaller_node = deleted_node->childs[index];
					
					while(smaller_node->childs.back()!=nullptr)
					{
						smaller_node = smaller_node->childs.back();
					}
					//Ѱ�ҽ����ĩβ���Ǹ�Ԫ��
					elementype smaller_value = smaller_node->datas.back(); 
					
					//����ֵ 
					swap(deleted_node->datas[index], smaller_node->datas.back());
					
					//�ݹ�ɾ����smaller_node���Ϊ����������ֵΪx��Ԫ��
					deleteEle_re(smaller_node, x);	                   //ת��Ϊ�˶��ն˽���е�Ԫ�ص�ɾ�� 
				} 
				else   //�ն˽�� 
				{
					deleteForNode_re(deleted_node,x);
//					int min_limit = (this->size_to_spilt+1)/2 - 1;    // m/2����ȡ�� -1��С�ڸ�ֵ����Ҫ���н�������ߺϲ�����
					
				}
				
				/*
				//���ɾ�������ն˽���е�Ԫ�أ������������
				1.�����ֵ���һ�����裨�����������ֵܣ��������ֵܣ� 
				
				2.�����ֵܶ������裬��������ֵܣ���ϲ��Լ������ֵܣ�����ϲ��Լ������ֵ�(������û���ֵ�) 
				 
				*/	
			}
			else
			{
				cerr<<"ɾ��ʧ�ܣ������ڰ���ֵΪ"<<x<<"Ԫ�صĽ��\n";
			}
			
		}
		BTNode* mergeTwoNode(BTNode* left,BTNode*& right, elementype mid_ele)
		{
			
			BTNode* new_node = new BTNode(this->size_to_spilt,left,0,left->datas.size()-1);
			
			new_node->datas.push_back(mid_ele);
			
//			const int start_ci = new_node -> datas.size();
			int i;
			for(i = 0;i<right->datas.size();i++)
			{
				new_node->childs.push_back(right->childs.at(i));
				new_node->datas.push_back(right->datas.at(i));
			}
			new_node->childs.push_back(right->childs.at(i));
			
//			delete left;
//			delete right;        //����ע��!!!!!!!!!!!!!!!!!!!!!! 
			
			
			return new_node;
		}
		BTNode* deleteForNode_re(BTNode* T, elementype x)     //��Ԫ��x�ӽ��T��ɾ��,Left��right��Ԫ��x�������ߵ�ָ��   
		//��һ�ν���ʱ������Ķ����ն˽ڵ㣬���ǵݹ���ú󣬾Ϳ����Ƿ��ն˽���� 
		//����ɾ��֮�󣬷��ر��ڵ���ߺϲ�����½ڵ� 
		{
			BTNode* ret = T;
			BTNode* left;
			BTNode* right;
			
			//�ҵ�ɾ��λ�ã��ҵ�����������һ������x��λ��
			int index;
			for(index = 0; index<T->datas.size(); index++)
			{
				if(T->datas.at(index)==x)
				{
					break;
				}
			}
			if(index == T->datas.size())
			{
				cerr<<"deleteForNode_re�������ִ���,xΪ�Ƿ�ֵ\n";
				return nullptr;
			}
			//��¼��ɾ��Ԫ�ص�����ָ��
			left = T->childs[index];
			right = T->childs[index+1]; 
			
			//��¼�ý���ǰ�����
			findEle(x);
			BTNode* pre = this->pre; 
			
			
			int i;
			for(i = index;i<T->datas.size()-1;i++)
			{
				T->datas.at(i) = T->datas.at(i+1);
				T->childs.at(i+1) = T->childs.at(i+2);
			} 
			
			
			T->datas.pop_back();
			T->childs.pop_back();                    //�����Ѿ����ɾ��Ԫ�صĲ��� 
			
			if(T != this->root && T->datas.size() < this->min_limit)    //��Ҫ���н�������ߺϲ����� 
			{
				int i;
				int l_bro_i,r_bro_i;
				//Ū����ǰ���ĵڼ�������
				for(i = 0;i<pre->childs.size();i++)
				{
					if(pre->childs[i] == T)
					{
						break;
					}
				} 
				
				l_bro_i = i-1;
				r_bro_i = i+1;
				
				BTNode* l_bro = (l_bro_i >= 0 ? pre->childs[l_bro_i] : nullptr);
				BTNode* r_bro = (r_bro_i < pre->childs.size() ? pre->childs[r_bro_i] : nullptr);
				
				//���н�������ᾪ���ϲ㣨����ݹ�ɾ���� 
				if(l_bro && l_bro->datas.size() > this->min_limit )    //���ֵܴ����ҹ��裬���н���� 
				{
					//���ֵ������Ǹ�Ԫ��ele1��ȥ�����ֵ��м���Ǹ���Ԫ��ele2��������ɾ���
					elementype ele1 = l_bro->datas.back();
					elementype ele2 = pre->datas.at(l_bro_i);
					
					deleteForNode_re(l_bro, ele1);
					pre->datas.at(l_bro_i) = ele1;           //����Ԫ�ؽ��и�ֵ�������ı�����ָ�룩 
					insertForNode_re(T, ele2,nullptr,nullptr); 
				}
				
				else if(r_bro && r_bro->datas.size() > this->min_limit )	//���ֵܴ����ҹ���,���н���� 
				{
					//���ֵ���С���Ǹ�Ԫ��ele1��ȥ�����ֵ��м���Ǹ���Ԫ��ele2��������ɾ��� 
					elementype ele1 = r_bro->datas.at(0);
					elementype ele2 = pre->datas.at(i);
					
					deleteForNode_re(r_bro, ele1);
					pre->datas.at(i) = ele1;           //����Ԫ�ؽ��и�ֵ�������ı�����ָ�룩 
					insertForNode_re(T, ele2,nullptr,nullptr); 
				} 
				
				else if(l_bro || r_bro)
				{
					elementype ele2;
					BTNode* left,*right;
					if(l_bro)                                               //�����ֵܺϲ� 
					{
						ele2 = pre->datas.at(l_bro_i);
						left = l_bro;
						right = T;
						
						
						
						
					}
					else if(r_bro)                                                 //�����ֵܺϲ� 
					{
						ele2 = pre->datas.at(i);
						left = T;
						right = r_bro;
						
						
					}
					
					//�ݹ�ɾ�����ڵ���Ǹ���Ԫ�� 
					pre = deleteForNode_re(pre,ele2);
					
					
					ret = mergeTwoNode(left, right, ele2);
					
					
					if(pre == root && root == nullptr)    //���ڵ��Ǹ��ڵ㣬�Ҿ����ݹ�ϲ�֮���Ѿ�û��Ԫ�أ�Ӧ�ø��ڵ�����ºϲ��Ľ�� 
					{
						root = ret;
					}
					
					else     //���ڵ㲻�Ǹ��ڵ㣨�����ڵ����ֵܣ������߸��ڵ��Ǹ��ڵ㵫�ǻ���Ԫ�أ���������Ӳ��� 
					{
						elementype ele3 = ret->datas.at(0);
						int index = 0;
						while(index < pre->datas.size() && pre->datas.at(index) < ele3)
						{
							index++;
						}
						
						//��ʱpre->datas.at(index) > ele3
						//�������Ӳ��� 
						pre->childs.at(index) = ret;
					}
					
					
				}
				
				else
				{
					cerr<<"deleteForNode_re���������˲��ó��ֵĴ���\n";
				}
				
			}
			
			if(T==this->root && T->datas.size()==0)
			{
				delete T;
				this->root = nullptr;
				ret = nullptr;
			}
			
			return ret;
		
		}
		
		void insertForNode_re(BTNode* T, elementype x, BTNode* left, BTNode* right)    //Ԫ��xֱ�Ӳ�����T�У�left��right��Ԫ��x�������ߵ�ָ�� 
		//left��x��ߵ�ָ�룬right��x�ұߵ�ָ�룬
		//�������������
		//1.�ҵ�����λ��i(�����ұ�����data[i]��һ�����ڵ���x��λ��)
		//2.data[i]��֮���Ԫ������ƶ�
		//3.x���뵽�±�Ϊi��λ��
		//4.childs[i]=left
		//5.childs[i+1]�Լ�֮���Ԫ�غ���
		//6.childs[i+1]=right
		//7.����ʱ���Ԫ�ظ�������������ƣ���������ϵݹ� 
		{
//			//���뵽ĩβλ��
//			T->datas.push_back(x);
			
			int index;
			//һ���������� 
			T->datas.push_back(0);   //data vector����һ��Ԫ�� 
			T->childs.push_back(nullptr);  //childs vector ����һ��Ԫ�� 
			for(index = T->datas.size()-1 ;index-1 >= 0 && T->datas[index-1] >= x; index--)
			{
				T->datas[index] = T->datas[index-1];
				T->childs[index+1] = T->childs[index];
			}
			
			T->datas[index] = x;
			T->childs[index+1] = right;
			T->childs[index] = left;
			
			if(T->datas.size()==T->size_to_spilt)    //�ﵽ�������������з��� 
			{
				int index = T->datas.size()/2 ;
				
				elementype new_x = T->datas[index];
				//��ǰ��
				findEle(new_x); 
				BTNode* pre = this->pre;
				
				//���� 
//				BTNode(int size_to_spilt, const BTNode* x,int s_d,int e_d, int s_c, int e_c)
				BTNode* new_left = new BTNode(this->size_to_spilt, T, 0, index-1);
				BTNode* new_right = new BTNode(this->size_to_spilt, T, index+1, T->datas.size()-1);
				
				//ɾ���ýڵ�
		 		delete T;
		 		
				if(pre == nullptr)     //�����Ѿ�û�д��ڵĽ���� 
				{
					pre = new BTNode;
					pre->size_to_spilt = this->size_to_spilt;
				}
		 		
		 		//�ݹ������Ԫ�ص����ڵ� 
				insertForNode_re(pre, new_x, new_left, new_right);
				
			}
			
		}
		void insertEle_re(BTNode* now_T, elementype x)    //��now_TΪ����B���ϣ�����Ԫ��x 
		{
			if(now_T)
			{
				//����Ϊ�ײ㣺�ݹ�������ײ��� 
				if((now_T->childs[0]))    //��Ϊ�ײ�
				{
					for(int i = 0; i<now_T->childs.size(); i++)
					{
						if( (i-1 < 0|| now_T->datas[i-1]<x) && (i>=now_T->datas.size() || now_T->datas[i] >= x) )
						{
							BTNode* obj_child = now_T -> childs[i];
							insertEle_re(obj_child, x);    //�ݹ�ȥ�Ҷ�Ӧ�ĺ��� 
							break;
						}	
					}
					
				}
				else  //��Ϊ�ײ㣺
				{
					//(���á�������Ԫ�غ���������insertForNode_re��) ���ú��������������£� 
					//����ֱ�Ӳ����������Ԫ����Ӧ�ڵ�λ�ã����Ҳ�������Ԫ�����ҵ�ָ�룬�����Ԫ���Լ�ָ��������
					//���������ɺ󣬽���Ԫ����Ŀ�����������з���,�м��Ԫ�ؼ������������ڵ�
					insertForNode_re(now_T, x, nullptr, nullptr);    //�ײ�Ľ��ÿ��Ԫ�ص�����ָ���Ϊnullptr 
					 
				}	
			}
			
			else
			{
				cerr<<"insertEle_re����ʧ�ܣ�����Ϊ��ָ��\n";
			}			 
		}
		BTNode* findEle_re(BTNode* now_T, elementype x, BTNode* pre = nullptr)    //����now_TΪ�������ϣ�����ֵΪx��Ԫ�أ�pre����now_T�ĸ���� 
		{
			BTNode* ret = nullptr;
			if(now_T)
			{
				BTNode* obj_child = nullptr;
				for(int i = 0; i<now_T->childs.size(); i++)   // ˳����ҽڵ��ڵ�ÿ��Ԫ�أ��ҵ������ķֲ�ͬʱ�������������
				//1.�ֲ�ǰû��Ԫ�ػ��߷ֲ�ǰ��Ԫ��С��x
				//2.�ֲ��û��Ԫ�ػ��߷ֲ���Ԫ�ش���x 
				{
					if(i<now_T->datas.size() && now_T->datas[i] == x)
					{
						ret = now_T;    //�ҵ��� 
						this->pre = pre;
						break;
					}
					
					if( (i-1 < 0|| now_T->datas[i-1]<x) && (i>=now_T->datas.size() || now_T->datas[i] > x) )
					{
						obj_child = now_T->childs[i];
						ret = findEle_re(obj_child, x, now_T);    //�ݹ�ȥ�Ҷ�Ӧ�ĺ��� 
						break;
					}
				}
				
					
			}
			
			else    //���ҵ�Ҷ�ӽ�㣨�ս�㣩��û�ҵ����� 
			{
				this->pre = pre;
				ret = nullptr;
			}
			
			return ret;	
		}


		BTNode* findPreNode(BTNode* T)
		{
			BTNode* ret = nullptr;
			if(T)
			{
				BTNode* pre = root;
				elementype obj_x = T->datas[0];
				findEle(obj_x);
				return this->pre;
				
				
			}
			else
			{
				cerr<<"findepreNode�������󣬲���Ϊ�ս��\n";
			}
			
		}
};
int main(int argc,char* args[])
{
	BTree bt(5);
	vector<elementype> vc1 = {25,38,49,60,80,90,99,88,83,87,70,92,93,94,73,74,75};
	for(elementype x : vc1)
	{
		bt.insertEle(x);
//		bt.showAll();
	}
//	bt.insertEle(88);
//	bt.insertEle(45);
//	bt.deleteEle(45);
//	
//	bt.insertEle(50);
//	bt.insertEle(52);
//	bt.insertEle(56);
//	bt.insertEle(60); 
//	bt.insertEle(68); 
//	bt.showAll();

//	bt.deleteEle(60);
//	cout<<"���ԣ�"<<bt.root->datas.at(0)<<"\n";
	
	bt.showAll();
	
	
	for(elementype x : vc1)
	{
		bt.deleteEle(x);
		bt.showAll();
	}
	
 	return 0;
}

