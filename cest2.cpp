//输入4个数，比如:1 1 1 24
//在这四个数之间任意的加上加减乘除，并且任意的加上一对对括号，当最终结果为24时，有多少种组合方法？ 
#include <iostream>
#include <vector>
#include <cmath>
#define num_scale 4
using namespace std;
double nums[num_scale];
char sign_samples[] ={'+','-','*','/'}; 
char signs[num_scale-1];
int num_of_ways = 0;
vector<double> calculate_the_part(double nums[], int start_index,int end_index)
{
	vector<double> ret;
	
	if(start_index == end_index)
	{
		
		ret.push_back(nums[start_index]);
	}
	else
	{
		for(int mid = start_index; mid<end_index; mid++)
		{
			vector<double> left_part_oc = calculate_the_part(nums,start_index,mid);
			vector<double> right_part_oc = calculate_the_part(nums,mid+1,end_index);
			
			for(auto i = left_part_oc.begin();i!=left_part_oc.end();i++)
			{
				for(auto j = right_part_oc.begin();j!=right_part_oc.end();j++)
				{
					switch(signs[mid])
					{
						case '+':
							ret.push_back(*i + *j);
							break;
						case '-':
							ret.push_back(*i - *j);
							break;
						case '*':
							ret.push_back(*i * *j);
							break;
						case '/':
//							ret.push_back(*i / *j);
							if(*j!=0)
							{
								ret.push_back(*i / *j);
							}
							break;
					}			
				}
			}
			
		}
		
		if(end_index - start_index + 1 == 4)
		{
			for(auto i = ret.begin();i!=ret.end();i++)
			{
				if(abs(*i - 24)<1e-6)
				{
					num_of_ways++;
					
					//调试代码
					cout<<nums[0]<<" ";
					for(int i = 0;i<num_scale-1;i++)
					{
						cout<<signs[i]<<" ";
						cout<<nums[i+1];
						if(i!=num_scale-2)
						{
							cout<<" ";
						}
					}
					cout<<endl;
					 
				}
			}
		}
		
	}

	return ret;
}
int main(int argc,char* args[])
{
	cin>>nums[0];
	for(int l=1;l<num_scale;l++)
	{
		cin>>nums[l];
	}
	vector<double> temp;
	vector<double> ret;
	for(int i = 0;i<4;i++)
	{
		signs[0]=sign_samples[i];
		for(int j = 0;j<4;j++)
		{
			signs[1] = sign_samples[j];
			for(int k = 0;k<4;k++)
			{
				signs[2] = sign_samples[k];
				temp = calculate_the_part(nums,0,3) ;		
				ret.insert(ret.end(),temp.begin(),temp.end());		
			}
		}
	}
	
	cout<<num_of_ways<<endl;
	cout<<ret.size()<<endl;
 	return 0;
}

