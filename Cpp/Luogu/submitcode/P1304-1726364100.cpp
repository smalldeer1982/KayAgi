#include<bits/stdc++.h>
using namespace std;
int n,x;
bool flag=0;
int fun(int a)
{
	for(int j=2;j<=a/2;j++)
	{
		flag=0;
		x=a-j;
		for(int k=2;k<=sqrt(j);k++)
		{
			if(j%k==0)
			{
				flag=1;
				break;
			}
		}
		for(int k=2;k<=sqrt(x);k++)
		{
			if(x%k==0)
			{
				flag=1;
				break;
			}
		}
		if(flag==0)
		{
			return j;
		}
	}
}
int main()
{
	cin>>n;
	for(int i=4;i<=n;i+=2)
	{
		cout<<i<<"="<<fun(i)<<"+"<<i-fun(i)<<endl;
	}
	return 0;
}