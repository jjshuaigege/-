/*
问题描述：求多项式f(x) = a0+a1*x+a2*x^2+a3*x^3+...+an*x^n 的值，其中a0~an的值以数组的方式给出,x为double类型，n为int类型 

*/ 

#include <iostream>
#include <cmath>
#include <ctime> 
#include <stdio.h>
using namespace std;

double normal_way(double a[], int n, double x)
{
	double P = a[0];
	for(int i = 1;i<=n;i++)
	{
		P = P + (a[i] * pow(x, i)); 
	}
	return P;
}

//多项式可化为这种形式：f(x) = a0+x(a1+x(a2+x(a3+x(...+x(an-1+x(an))...) 
double qinJiuShao_way(double a[], int n, double x)
{
	double P = a[n];
	for(int i = n-1;i>=0;i--)
	{
		P = P*x + a[i]; 
	}
	return P;
}

void ceshi_daima(double(*algorithm)(double*,int,double))
{
	
	double a[9] = {4,8,6,1,3,0,5,7,8};
	double oc = 0;
	double interv;
	double x=18.8;
	
	double start = clock();
	for (int i = 0;i<50000000;i++)
	{
		oc = algorithm(a,9,x);
	}
	double end = clock();
	
	interv = (end - start)/CLK_TCK;
	cout<<oc<<endl;
	cout<<"所花时间："<<interv<<endl;
}
int main(int argc,char* args[])
{
	
	ceshi_daima(qinJiuShao_way);
	ceshi_daima(normal_way);
	
	int b[] = {5,61,46};
	printf("%d\n",b);
	printf("%d\n",&(&b));
 	return 0;
}

