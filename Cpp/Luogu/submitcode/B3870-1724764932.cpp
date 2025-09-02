#include<bits/stdc++.h>
using namespace std;
long long n,a[1005][10],sum=1,x=1,y=8,sum1=1,ans=0;
char c;
bool flag=0;
int main()
{
	cin>>n;
	if(n==0)
	{
		cout<<"00";
		return 0;
	}
	while(true)
	{
		if(y==1)
		{
			x+=1;
			y=8;
		}
		if(n==1)
		{
			break;
		}
		a[x][y]=n%2;
		n/=2;
		y-=1;
	}
	if(y==1)
	{
		x+=1;
		y=8;
	}
	a[x][y]=n%2;
	n/=2;
	for(int i=1;i<=x;i++)
	{
		if(i!=x)
		{
			a[i][1]=1;
		}
	}
	for(int i=1;i<=x;i++)
	{
		for(int k=1;k<=2;k++)
		{
			ans=0;
			sum1=1;
			for(int j=k*4;j>=k*4-3;j--)
			{
				ans+=a[i][j]*sum1;
				sum1*=2;
			}
			if(ans<10)
			{
				cout<<ans;
			}
			else
			{
				c=ans-10+'A';
				cout<<c;
			}
		}
		cout<<" ";
	}
	return 0;
}