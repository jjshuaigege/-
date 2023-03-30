#include <iostream>
#include <vector>
#include <queue>
/*
m叉B树 
1.每个结点最多包含m-1个元素，最多有m个分叉（孩子）
2.除了根结点之外，非空结点必须有m/2（向上取整）个分叉， m/2（向上取整）-1个元素
3.每个结点的所有子树的树高均相等
4.对每个结点均满足:子树0<元素0<子树1<元素1<子树2<元素2<...<子树m-1<元素m-1<子树m  
    
终端结点是没有孩子的非空结点
叶子结点是空结点 
 
*/
using namespace std;
typedef int elementype;
struct BTNode
{
	int size_to_spilt;      //结点实际的元素个数为size_to_spilt-1
	vector<elementype> datas;                   //[size_to_spilt];
	vector<BTNode*> childs;                     //[size_to_spilt+1];              
	//childs[0]|datas[0]|childs[1]|datas[1]|...|childs[size_to_spilt-1]|datas[size_to_spilt-1]|childs[size_to_spilt]
	
	public:
		
		BTNode()
		{
			childs.push_back(nullptr);
		}
		BTNode(int size_to_spilt, const BTNode* x,int s,int e):size_to_spilt(size_to_spilt)       //创建一个 size_to_spilt-1叉结点，
		//根据原x结点从s到e 闭区间[ data[s],data[e] ]以及 闭区间[ child[s],childs[e+1] ]赋值给新节点 
		{
			int i;
			for(i = s;i <= e;i++)
			{
				elementype temp_data = x->datas[i];
				BTNode* temp_child = x->childs[i];
				datas.push_back(temp_data);
				childs.push_back(temp_child);
			}
			
			if(s<=e)     //有效
			{
				childs.push_back(x->childs[i]);	
			} 
			
			
			else   //无效结点
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
			min_limit = (this->size_to_spilt+1)/2 - 1;    // m/2向上取整 -1，小于该值的时候就需要进行借操作或者合并操作了 
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
		
		void showAll() //层序遍历 
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
					
					cout<<"结点"<<cnt++<<"，层数为"<<front_T.level<<",包含的元素有:";
					
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
				cout<<"整棵树为空\n";
			}
			
			BTNode* p, *q;
			
		}
		
	private:
		BTNode* root;     //根节点 
		BTNode* pre;      //用于临时存放查找某个节点的前置节点的结果  
		int size_to_spilt;
		int min_limit;    //m/2向上取整 -1，结点的元素个数小于该值的时候就需要进行借操作或者合并操作了
//		bool ifInChilds(BTNode* p, BTNode* q)  //判断q是否在p的孩子之中 
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
		void deleteEle_re(BTNode* now_T, elementype x)   //删除以now_T为根节点的B树中值为x的元素 
		{
			//找到值为x的元素所在的结点
			BTNode* deleted_node = findEle_re(now_T, x);
			
			if(deleted_node) 
			{
				/*
				如果删除的是非终端结点中值为x的元素(有非空孩子结点),找到该元素的直接前驱（刚好小于该元素的元素），值为y，
				那么直接前驱一定处于终端结点上，将被删除元素和直接前驱元素的值进行交换,则问题转化为删除左子树上值为y的结点
				(非终端节点的删除问题转化为终端节点的删除问题) 
				*/
				if(deleted_node->childs[0])   //非终端结点
				{
					int index;
					for(index = deleted_node->datas.size()-1 ;index >= 0; index--)
					{
						if(deleted_node->datas.at(index) == x)
						{
							break;
						}
					}
					//找该元素左指针指向的左子树中最大的那个元素 
					BTNode* smaller_node = deleted_node->childs[index];
					
					while(smaller_node->childs.back()!=nullptr)
					{
						smaller_node = smaller_node->childs.back();
					}
					//寻找结点最末尾的那个元素
					elementype smaller_value = smaller_node->datas.back(); 
					
					//交换值 
					swap(deleted_node->datas[index], smaller_node->datas.back());
					
					//递归删除以smaller_node结点为根的子树中值为x的元素
					deleteEle_re(smaller_node, x);	                   //转变为了对终端结点中的元素的删除 
				} 
				else   //终端结点 
				{
					deleteForNode_re(deleted_node,x);
//					int min_limit = (this->size_to_spilt+1)/2 - 1;    // m/2向上取整 -1，小于该值则需要进行借操作或者合并操作
					
				}
				
				/*
				//如果删除的是终端结点中的元素，分两种情况：
				1.左右兄弟有一个够借（可以先问左兄弟，再问右兄弟） 
				
				2.左右兄弟都不够借，如果有左兄弟，则合并自己和左兄弟，否则合并自己和右兄弟(不可能没有兄弟) 
				 
				*/	
			}
			else
			{
				cerr<<"删除失败，不存在包含值为"<<x<<"元素的结点\n";
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
//			delete right;        //尤其注意!!!!!!!!!!!!!!!!!!!!!! 
			
			
			return new_node;
		}
		BTNode* deleteForNode_re(BTNode* T, elementype x)     //将元素x从结点T中删除,Left和right是元素x左右两边的指针   
		//第一次进入时，处理的都是终端节点，但是递归调用后，就可能是非终端结点了 
		//做完删除之后，返回本节点或者合并后的新节点 
		{
			BTNode* ret = T;
			BTNode* left;
			BTNode* right;
			
			//找到删除位置，右到左遍历，最后一个等于x的位置
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
				cerr<<"deleteForNode_re函数出现错误,x为非法值\n";
				return nullptr;
			}
			//记录被删除元素的左右指针
			left = T->childs[index];
			right = T->childs[index+1]; 
			
			//记录该结点的前驱结点
			findEle(x);
			BTNode* pre = this->pre; 
			
			
			int i;
			for(i = index;i<T->datas.size()-1;i++)
			{
				T->datas.at(i) = T->datas.at(i+1);
				T->childs.at(i+1) = T->childs.at(i+2);
			} 
			
			
			T->datas.pop_back();
			T->childs.pop_back();                    //至此已经完成删除元素的操作 
			
			if(T != this->root && T->datas.size() < this->min_limit)    //需要进行借操作或者合并操作 
			{
				int i;
				int l_bro_i,r_bro_i;
				//弄清是前驱的第几个孩子
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
				
				//进行借操作不会惊动上层（不会递归删除） 
				if(l_bro && l_bro->datas.size() > this->min_limit )    //左兄弟存在且够借，进行借操作 
				{
					//左兄弟最大的那个元素ele1上去，两兄弟中间的那个父元素ele2下来到被删结点
					elementype ele1 = l_bro->datas.back();
					elementype ele2 = pre->datas.at(l_bro_i);
					
					deleteForNode_re(l_bro, ele1);
					pre->datas.at(l_bro_i) = ele1;           //给父元素进行赋值（并不改变它的指针） 
					insertForNode_re(T, ele2,nullptr,nullptr); 
				}
				
				else if(r_bro && r_bro->datas.size() > this->min_limit )	//右兄弟存在且够借,进行借操作 
				{
					//右兄弟最小的那个元素ele1上去，两兄弟中间的那个父元素ele2下来到被删结点 
					elementype ele1 = r_bro->datas.at(0);
					elementype ele2 = pre->datas.at(i);
					
					deleteForNode_re(r_bro, ele1);
					pre->datas.at(i) = ele1;           //给父元素进行赋值（并不改变它的指针） 
					insertForNode_re(T, ele2,nullptr,nullptr); 
				} 
				
				else if(l_bro || r_bro)
				{
					elementype ele2;
					BTNode* left,*right;
					if(l_bro)                                               //与左兄弟合并 
					{
						ele2 = pre->datas.at(l_bro_i);
						left = l_bro;
						right = T;
						
						
						
						
					}
					else if(r_bro)                                                 //与右兄弟合并 
					{
						ele2 = pre->datas.at(i);
						left = T;
						right = r_bro;
						
						
					}
					
					//递归删除父节点的那个父元素 
					pre = deleteForNode_re(pre,ele2);
					
					
					ret = mergeTwoNode(left, right, ele2);
					
					
					if(pre == root && root == nullptr)    //父节点是根节点，且经过递归合并之后，已经没有元素，应让根节点等于新合并的结点 
					{
						root = ret;
					}
					
					else     //父节点不是根节点（即父节点有兄弟），或者父节点是根节点但是还有元素，则进行连接操作 
					{
						elementype ele3 = ret->datas.at(0);
						int index = 0;
						while(index < pre->datas.size() && pre->datas.at(index) < ele3)
						{
							index++;
						}
						
						//此时pre->datas.at(index) > ele3
						//进行连接操作 
						pre->childs.at(index) = ret;
					}
					
					
				}
				
				else
				{
					cerr<<"deleteForNode_re函数出现了不该出现的错误！\n";
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
		
		void insertForNode_re(BTNode* T, elementype x, BTNode* left, BTNode* right)    //元素x直接插入结点T中，left和right是元素x左右两边的指针 
		//left是x左边的指针，right是x右边的指针，
		//插入过程描述：
		//1.找到插入位置i(从左到右遍历，data[i]第一个大于等于x的位置)
		//2.data[i]及之后的元素向后移动
		//3.x插入到下标为i的位置
		//4.childs[i]=left
		//5.childs[i+1]以及之后的元素后移
		//6.childs[i+1]=right
		//7.若此时结点元素个数大于最大限制，则继续向上递归 
		{
//			//插入到末尾位置
//			T->datas.push_back(x);
			
			int index;
			//一步插入排序 
			T->datas.push_back(0);   //data vector扩容一个元素 
			T->childs.push_back(nullptr);  //childs vector 扩容一个元素 
			for(index = T->datas.size()-1 ;index-1 >= 0 && T->datas[index-1] >= x; index--)
			{
				T->datas[index] = T->datas[index-1];
				T->childs[index+1] = T->childs[index];
			}
			
			T->datas[index] = x;
			T->childs[index+1] = right;
			T->childs[index] = left;
			
			if(T->datas.size()==T->size_to_spilt)    //达到分裂条件，进行分裂 
			{
				int index = T->datas.size()/2 ;
				
				elementype new_x = T->datas[index];
				//找前驱
				findEle(new_x); 
				BTNode* pre = this->pre;
				
				//分裂 
//				BTNode(int size_to_spilt, const BTNode* x,int s_d,int e_d, int s_c, int e_c)
				BTNode* new_left = new BTNode(this->size_to_spilt, T, 0, index-1);
				BTNode* new_right = new BTNode(this->size_to_spilt, T, index+1, T->datas.size()-1);
				
				//删除该节点
		 		delete T;
		 		
				if(pre == nullptr)     //上面已经没有存在的结点了 
				{
					pre = new BTNode;
					pre->size_to_spilt = this->size_to_spilt;
				}
		 		
		 		//递归插入新元素到父节点 
				insertForNode_re(pre, new_x, new_left, new_right);
				
			}
			
		}
		void insertEle_re(BTNode* now_T, elementype x)    //以now_T为根的B树上，插入元素x 
		{
			if(now_T)
			{
				//若不为底层：递归查找至底层结点 
				if((now_T->childs[0]))    //不为底层
				{
					for(int i = 0; i<now_T->childs.size(); i++)
					{
						if( (i-1 < 0|| now_T->datas[i-1]<x) && (i>=now_T->datas.size() || now_T->datas[i] >= x) )
						{
							BTNode* obj_child = now_T -> childs[i];
							insertEle_re(obj_child, x);    //递归去找对应的孩子 
							break;
						}	
					}
					
				}
				else  //若为底层：
				{
					//(调用“结点插入元素函数”：“insertForNode_re”) ，该函数所做工作如下： 
					//首先直接插入至结点中元素所应在的位置，左右插入两入元素左右的指针，后面的元素以及指针往后移
					//如果插入完成后，结点的元素数目超过最大，则进行分裂,中间的元素继续插入至父节点
					insertForNode_re(now_T, x, nullptr, nullptr);    //底层的结点每个元素的左右指针均为nullptr 
					 
				}	
			}
			
			else
			{
				cerr<<"insertEle_re函数失败，参数为空指针\n";
			}			 
		}
		BTNode* findEle_re(BTNode* now_T, elementype x, BTNode* pre = nullptr)    //在以now_T为根的树上，查找值为x的元素，pre代表now_T的父结点 
		{
			BTNode* ret = nullptr;
			if(now_T)
			{
				BTNode* obj_child = nullptr;
				for(int i = 0; i<now_T->childs.size(); i++)   // 顺序查找节点内的每个元素，找到这样的分叉同时满足两种情况：
				//1.分叉前没有元素或者分叉前的元素小于x
				//2.分叉后没有元素或者分叉后的元素大于x 
				{
					if(i<now_T->datas.size() && now_T->datas[i] == x)
					{
						ret = now_T;    //找到了 
						this->pre = pre;
						break;
					}
					
					if( (i-1 < 0|| now_T->datas[i-1]<x) && (i>=now_T->datas.size() || now_T->datas[i] > x) )
					{
						obj_child = now_T->childs[i];
						ret = findEle_re(obj_child, x, now_T);    //递归去找对应的孩子 
						break;
					}
				}
				
					
			}
			
			else    //查找到叶子结点（空结点）仍没找到数据 
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
				cerr<<"findepreNode函数错误，参数为空结点\n";
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
//	cout<<"调试："<<bt.root->datas.at(0)<<"\n";
	
	bt.showAll();
	
	
	for(elementype x : vc1)
	{
		bt.deleteEle(x);
		bt.showAll();
	}
	
 	return 0;
}

