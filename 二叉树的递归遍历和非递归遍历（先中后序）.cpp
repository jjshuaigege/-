#include <iostream>
#include <stack>
using namespace std;



typedef struct BTnode{
	char data;
	BTnode *lchild, *rchild;	//???
} *BinTree;

stack<BinTree> st;

//������㣬�����ĸ��ڵ�ָ���Լ� ��flagΪ0�����޸��ڵ㣬Ϊ1�����Ǹ��ڵ�����ӣ�Ϊ2�������Һ��� 
BTnode* createNode(char x, int flag , BTnode* FT = nullptr)
{
	
	BTnode* T = new BTnode;
	T->data = x;
	T->lchild = T->rchild = nullptr;
	if (FT)
	{
		if(flag == 1)
		{
			FT->lchild = T;	
		}
		else if (flag == 2)
		{
		
			FT->rchild = T;
		}
	
	}
	
	return T;
} 
//����һ���������ڲ���
void BuildTree(BinTree& T)
{
	T = createNode('A', 0, nullptr);	
	BinTree temp = createNode('B', 1, T);
	createNode('D', 1, temp);
	temp = createNode('F', 2, temp);
	createNode('E',1,temp);
	temp = createNode('C', 2, T);
	BinTree temp1 = createNode('G',1,temp);
	createNode('H',2,temp1);	
	createNode('I', 2, temp);	
} 


void visit(BinTree T)
{
	cout<<T->data<<" ";
}

//���ֶ������ĵݹ���� 
void InOrderTraversal(BinTree T)
{
	if(T)
	{
		InOrderTraversal(T->lchild);
		visit(T);
		InOrderTraversal(T->rchild);
	}
	
}

void PreOrderTraversal(BinTree T)
{
	if(T)
	{
		visit(T);
		PreOrderTraversal(T->lchild);
		PreOrderTraversal(T->rchild);		
	}
	
}

void PostOrderTraversal(BinTree T)
{
	if(T)
	{
		PostOrderTraversal(T->lchild);
		PostOrderTraversal(T->rchild);
		visit(T);		
	}
	
}

//���ֶ������ķǵݹ����(�������汾)  ׼��һ��״̬���飬ÿ�������0����ʡ�ԣ���1��2����״̬��
//�ֱ����δ��ջ����ʡ�ԣ�����ջ�е�һ�α����ʣ���ջ�еڶ��α����� 




//���ֶ������ķǵݹ����(�����)

void InOrderTraversal_x(BinTree T)
{
	BinTree now_T = T;
	while(now_T || !st.empty())
	{
		if(now_T)
		{
			st.push(now_T);
			now_T = now_T->lchild;
		}
		else //��ǰ�ڵ�Ϊ�գ�Ӧ�ý�ջ���ڵ��ջ����Ϊջ���ڵ��ջ��ʱ�������������Ѿ������ʹ���������һ��ֻ����������������������Һ����Ƿ���ڣ� 
		{
			
			now_T = st.top();
			st.pop();
			//�ճ�ջʱ���˽����������ձ������꣬��˿����������ʸý�� 
			visit(now_T);			
			//���������� 
			now_T = now_T->rchild;
		}
	}
	
}

//������ͬ��ֻ�����visit������λ�ü��� 
void PreOrderTraversal_x(BinTree T)
{
	BinTree now_T = T;
	
	while(now_T || !st.empty())
	{
		if(now_T)
		{
			//������ջ֮ǰ�����ʸý�㣬�������������Ա����ķ���������������֮ǰ��һ˲�䱻���� 
			visit(now_T);
			st.push(now_T);
			now_T = now_T->lchild;
		}
		else //��ǰ�ڵ�Ϊ�գ�Ӧ�ý�ջ���ڵ��ջ����Ϊջ���ڵ��ջ��һ˲�䣬�����������ձ������꣬������һ��ֻ����������������������Һ����Ƿ���ڣ� 
		{
			now_T = st.top();
			st.pop();
			now_T = now_T->rchild;
		}
	}
	
}


//�ǵݹ��㷨�����������ǰ����������ڽϴ�ͬ������ʵ�����ķ��ʲ��������ӽ��ݹ��㷨������Ҫ��֤�ڷ���ĳ���ڵ�֮ǰ���������������������������ʣ�
//Ҳ����˵ÿ����㶼Ҫ����������3�Σ���ʵǰ���С���ݹ��㷨Ҳ�ܱ�֤ÿ����㱻����3�Σ�����ǰ��������ǵݹ��㷨ֻ��֤ǰ���ε���������ջʱ����1�Σ���ջʱ����1�Σ����Զ������˵�3�ε�����
//��˶��ڷǵݹ�����㷨���ڷ�����ĳ���ڵ��������֮����Ҫ���ý�㱣��ջ�У��ȷ���������������֮���ٶԸý����з��ʣ��Խ���visit�����Ĳ����� 
 
//Ϊ�˱�֤��һ��������3�Σ�Ҳ����ջ��Ԫ�ط������Σ���Ҫ���ֶ�ջ�е�Ԫ���ǵڼ��η��ʣ���Ϊ��һ�η��ʺ͵ڶ��η��� 

//(a)�����˼·�Ƕ�ÿ����㶼��һ����Ӧ��״̬λ����ֵΪ0���ڵ�һ�δ�ջ�з��ʽ��ʱ������״̬λΪ0���ʲ�������ջ��
//���ǽ�״̬λ��Ϊ1���ڵڶ��η��ʣ�����״̬λ��1�����Խ��ý���ջ




//(b)���ǻ�������һ��ȡ�ɵĵİ취 ��֮����Ҫ��ÿ��������3�Σ���Ϊ�˵���һ�����ִ��visit����ʱ�������������������������н�㶼��visit����
//��һ�η���ջ�е�ĳ�����ʱ���ý����������ոձ������꣬������������δ�����ʣ����Һ���û������
//�ڶ��η���ջ�е�ĳ�����ʱ
//(1)����ý������Һ��ӣ���ý����������ոձ������꣬��ô���ݺ�������Ļ��ƿ�֪�����һ�α����ʵ�һ���������Һ��� 
//(2����������Һ��ӣ���ֱ�ӶԸý�����visit����������ջ�������Ϊ˲����������������)

//******* 
//��˼����������£� 
//׼������һ��ָ��pre����ָ��ָ����һ�ξ�visit����������Ľ�� 
//���ÿ�η���ջ��Ԫ�ص�ʱ��Ϊ���жϸ�Ԫ���ǵ�һ�λ��ǵڶ��α����ʣ��������£�

//����������Һ��ӣ����ߴ����Һ��Ӳ���pre��rchildָ����ȣ�||�߼����������ʵ�֣���ֱ�ӽ���Ԫ�س�ջ ������visit���� ,preָ���Ԫ�أ�Tָ��գ��Ա��������ջ��Ԫ�ء� 
//���pre��rchildָ��ָ��һ�£�˵��ֻ�ǵ�һ�η���ջ���ĸý�㣬��������Ԫ������ջ�У�Ȼ����������Һ��� 
 
void PostOrderTraversal_x(BinTree T)
{
	BinTree now_T = T, pre_T = nullptr;
	
	while(now_T||!st.empty())
	{
		if(now_T)
		{
			st.push(now_T);
			now_T = now_T -> lchild;	
		}
		else
		{
			now_T = st.top(); // ��ʱnow_T�����������Ѿ���������� 
			
			if( !now_T->rchild || pre_T == now_T->rchild) //������������������������Ҳ�ѱ�������ϣ���ֱ�ӳ�ջ������ 
			{
				st.pop();
				visit(now_T);
				pre_T = now_T;
				now_T = nullptr;
			}
			else	//�����Һ��Ӳ���������û�б����ʹ� ��˵���ǵ�һ����ջ�б����� 
			{
				//���������� 
				now_T = now_T -> rchild;
			}
				
		}		
	}
	
}



int main(int argc,char* args[])
{
	BinTree T;
	BuildTree(T);
	cout<<T->data<<endl;
	cout<<T->lchild<<endl;
	cout<<T->rchild<<endl;
	
	//������� 
	PreOrderTraversal(T);
	cout<<endl;
	

	PreOrderTraversal_x(T);
	cout<<endl;
	
	//������� 
	InOrderTraversal(T);	
	cout<<endl;
	
	InOrderTraversal_x(T);	
	cout<<endl;
	
	//������� 
	PostOrderTraversal(T);
	cout<<endl;
	
	PostOrderTraversal_x(T);
	cout<<endl;
	
	
	cout<<"ceshi:"<<T->lchild->lchild->data;
 	return 0;
}

