#include <bits/stdc++.h>
using namespace std;
typedef struct LNode
{
	int data;
	LNode* next;
} *LinkList;
int main(int argc,char* args[])
{
	LNode* p = new LNode(5,nullptr);
	cout<<p->data;
 	return 0;
}

