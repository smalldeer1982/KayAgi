#include<bits/stdc++.h>
using namespace std;
int n,a[100005],flag=1,y;
int fun1(int x)
{
	flag=1;
	for(int j=2;j<=sqrt(x);j++)
	{
		if(x%j==0)
		{
			flag=0;
		}
	}
	return flag;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i]; 
	}
	for(int i=1;i<=n;i++)
	{
		y=fun1(a[i]);
		if(a[i]==1)
		{
			y=0;
		}
		if(y==0)
		{
			a[i]=0;
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(a[i]!=0)
		{
			cout<<a[i]<<" ";
		}
	}
	return 0;
}